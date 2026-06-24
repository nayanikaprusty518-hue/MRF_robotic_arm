"""Closed-form kinematics for the MRF 6R arm with spherical wrist.

The kinematic constants MUST match mrf_description/urdf/kr_arm.xacro.

Frame: base_link, Z up, mounted upright so base_link axes == world axes
(only translated by the spawn height). All math here is in the base_link frame.

Joint model (parent -> child = Translate(origin) then Rotate(axis, q)):
    joint1  origin (0,0,0.10)  axis Z
    joint2  origin (0,0,d1)    axis Y      shoulder, height H = 0.10 + d1
    joint3  origin (0,0,a2)    axis Y      elbow
    joint4  origin (0,0,d4)    axis Z      wrist center (axes 4,5,6 intersect)
    joint5  origin (0,0,0)     axis Y
    joint6  origin (0,0,0)     axis Z
    tcp     origin (0,0,d6)    fixed
"""
import math
import numpy as np

D1 = 0.40
A2 = 0.45
D4 = 0.42
D6 = 0.15
J1_Z = 0.10
H = J1_Z + D1          # shoulder height above base_link = 0.50
REACH = A2 + D4        # 0.87 max wrist-center distance from shoulder


def _rot(axis, q):
    c, s = math.cos(q), math.sin(q)
    if axis == 'z':
        return np.array([[c, -s, 0], [s, c, 0], [0, 0, 1]])
    if axis == 'y':
        return np.array([[c, 0, s], [0, 1, 0], [-s, 0, c]])
    return np.array([[1, 0, 0], [0, c, -s], [0, s, c]])


def _tf(axis, q, origin):
    T = np.eye(4)
    T[:3, :3] = _rot(axis, q)
    T[:3, 3] = origin
    return T


def fk(q):
    """Forward kinematics. q = [q1..q6]. Returns (tcp_position(3), R0t(3x3))."""
    T = np.eye(4)
    T = T @ _tf('z', q[0], [0, 0, J1_Z])
    T = T @ _tf('y', q[1], [0, 0, D1])
    T = T @ _tf('y', q[2], [0, 0, A2])
    R03 = T[:3, :3].copy()
    wc = T[:3, 3].copy()                      # wrist center (joint4 origin)
    T = T @ _tf('z', q[3], [0, 0, D4])
    T = T @ _tf('y', q[4], [0, 0, 0])
    T = T @ _tf('z', q[5], [0, 0, 0])
    T = T @ _tf('z', 0.0, [0, 0, D6])         # fixed tcp offset
    return T[:3, 3], T[:3, :3], wc, R03


def ik_topdown(p, yaw=0.0, elbow_up=True):
    """Solve joints for TCP at position p (base_link frame) with the tool
    pointing straight down and gripper yaw `yaw` about the vertical.

    Returns list[6] of joint angles, or None if unreachable.
    """
    p = np.asarray(p, dtype=float)
    # tool +Z points down -> wrist center is d6 *above* the tip
    wc = p + np.array([0.0, 0.0, D6])

    q1 = math.atan2(wc[1], wc[0])
    r = math.hypot(wc[0], wc[1])
    z = wc[2] - H
    D = math.hypot(r, z)
    if D > REACH * 0.999 or D < abs(A2 - D4) * 1.001:
        return None

    # elbow angle q3 (law of cosines; q3=0 => fully extended)
    cos_q3 = (D * D - A2 * A2 - D4 * D4) / (2 * A2 * D4)
    cos_q3 = max(-1.0, min(1.0, cos_q3))
    q3_mag = math.acos(cos_q3)
    q3 = -q3_mag if elbow_up else q3_mag

    # q2 from the two planar equations
    phi = math.atan2(r, z)                      # target angle from vertical
    cos_alpha = (D * D + A2 * A2 - D4 * D4) / (2 * A2 * D)
    cos_alpha = max(-1.0, min(1.0, cos_alpha))
    alpha = math.acos(cos_alpha)
    q2 = phi - alpha if elbow_up else phi + alpha
    # forearm absolute angle, then q3 consistent with chosen q2
    fa = math.atan2(r - A2 * math.sin(q2), z - A2 * math.cos(q2))
    q3 = fa - q2

    # ----- wrist: ZYZ decomposition of R3t = R03^T * R0t -----
    _, _, _, R03 = fk([q1, q2, q3, 0, 0, 0])
    z_t = np.array([0.0, 0.0, -1.0])
    x_t = np.array([math.cos(yaw), math.sin(yaw), 0.0])
    y_t = np.cross(z_t, x_t)
    R0t = np.column_stack([x_t, y_t, z_t])
    R3t = R03.T @ R0t

    q5 = math.atan2(math.hypot(R3t[0, 2], R3t[1, 2]), R3t[2, 2])
    if abs(math.sin(q5)) < 1e-6:
        q4 = 0.0
        q6 = math.atan2(-R3t[0, 1], R3t[0, 0])
    else:
        q4 = math.atan2(R3t[1, 2], R3t[0, 2])
        q6 = math.atan2(R3t[2, 1], -R3t[2, 0])

    q = [q1, q2, q3, q4, q5, q6]
    # joint limits from the urdf
    lim = [3.5, 2.5, 2.8, 3.14, 2.8, 3.14]
    for v, l in zip(q, lim):
        if abs(v) > l + 1e-3:
            return None
    return q


def _selftest():
    rng = np.random.default_rng(0)
    ok = 0
    tot = 0
    worst = 0.0
    for _ in range(4000):
        # sample a reachable point in front of / around the robot
        x = rng.uniform(-0.6, 0.6)
        y = rng.uniform(-0.7, 0.7)
        zc = rng.uniform(-0.4, 0.6)          # tip height rel base_link
        yaw = rng.uniform(-math.pi, math.pi)
        p = [x, y, zc]
        q = ik_topdown(p, yaw)
        if q is None:
            continue
        tot += 1
        pos, Rt, _, _ = fk(q)
        perr = np.linalg.norm(pos - np.array(p))
        # tool z axis should point down
        zerr = np.linalg.norm(Rt[:, 2] - np.array([0, 0, -1]))
        worst = max(worst, perr, zerr)
        if perr < 1e-4 and zerr < 1e-4:
            ok += 1
    print(f"IK self-test: {ok}/{tot} solved cleanly, worst error {worst:.2e}")
    assert ok == tot and tot > 0, "IK round-trip failed"


if __name__ == '__main__':
    _selftest()
