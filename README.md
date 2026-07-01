# MRF Sorting Simulation

A ROS 2 Humble + Gazebo Classic 11 simulation of a **Material Recovery Facility
(MRF)** sorting cell: a single industrial arm on a conveyor line picks four kinds
of recyclable waste and sorts each into its own colour-coded bin, inside a
guarded warehouse environment.


## What it does

- A never-stopping conveyor carries randomly-placed objects (rotated, offset,
  varied spacing — not tidy rows).
- Objects are generated with a **ground-truth category** baked in at spawn time;
  a **simulated perception layer** republishes it through a detector-agnostic
  interface (`mrf_msgs/PerceivedObjectArray`). The robot only ever talks to that
  interface — never to Gazebo or the generator — so it can later be swapped for
  a real detector (YOLO/RT-DETR/…).
- A **single 6-DOF arm** (with a 3-finger claw) intercepts each item as it
  arrives under the pick point and sorts it into the matching bin:

  | Waste type | Object | Bin |
  |---|---|---|
  | Plastic | clear PET bottle | **Blue — PLASTIC** |
  | Metal | aluminium soda can | **Yellow — METAL** |
  | Glass | green glass bottle | **Green — GLASS** |
  | Paper | kraft carton | **Brown — PAPER** |

- The belt speed and spawn interval are balanced so the single arm clears every
  item without misses.

## Scene / aesthetics

- Textured **concrete floor**, a **warehouse shell** (concrete walls, truss roof,
  pendant lights), a **wire-mesh safety fence** with orange posts and CAUTION
  signs, a procedural **blue sky with clouds**, and soft diffuse lighting.
- Realistic objects: translucent glossy glass/plastic, metallic cans with wrapped
  labels, kraft cardboard cartons.

## Packages

| package | role |
|---|---|
| `mrf_msgs` | `PerceivedObject` / `PerceivedObjectArray` perception interface |
| `mrf_description` | arm xacro (6R + spherical wrist, claw gripper) + ros2_control |
| `mrf_gazebo` | world + models: `concrete_floor`, `warehouse`, `safety_fence`, `recycle_bins`, `recyclables` |
| `mrf_perception` | simulated ground-truth perception layer |
| `mrf_coordinator` | object generator, conveyor, closed-form IK, scheduler/executor |
| `mrf_bringup` | top-level launch |

## Build

```bash
cd ~/robotic_arm_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
```

## Run

```bash
source /opt/ros/humble/setup.bash
source install/setup.bash
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:$PWD/install/mrf_gazebo/share/mrf_gazebo/models

ros2 launch mrf_bringup mrf_sim.launch.py           # GUI
ros2 launch mrf_bringup mrf_sim.launch.py gui:=false  # headless
```

## Useful topics

```bash
ros2 topic echo /mrf/perception/objects   # the perception interface
ros2 topic echo /mrf/arm1/stats            # recovered count
ros2 topic echo /mrf/objects/stats         # spawned / on_belt / missed
ros2 topic echo /mrf/conveyor/state        # RUNNING_FAST | MEDIUM | SLOW (never STOPPED)
```

## Design notes

- **Grasping is kinematic**: a committed pick "claims" the object (the generator
  stops moving it) and the coordinator slaves its pose to the live tool-centre
  point until it is released over the bin. Form-closure grasping is unreliable in
  Gazebo Classic, so the claw fingers are cosmetic.
- **IK** is a closed-form solution for the 6R-with-spherical-wrist arm
  (`mrf_coordinator/ik.py`); run `python3 ik.py` for the FK∘IK self-test.
- Category→bin routing lives in `coordinator.py` (`BINS` map); the bins are
  arranged in a reachable arc behind the arm. Object types and their geometry
  live in `object_manager.py` (`CATEGORIES`).
- Kinematic constants are shared between `kr_arm.xacro` and `ik.py` — keep them
  in sync if you change link lengths.
