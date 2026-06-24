# 27. MRF (Material Recovery Facility) Assumptions

This system should simulate a realistic material recovery facility rather than a perfectly controlled manufacturing conveyor.

The following assumptions override earlier simplifications.

---

# 28. Random Object Placement

Objects shall not be spawned in perfectly aligned positions.

Objects may appear:

- Rotated
- Offset from belt center
- Partially overlapping conveyor lanes
- At arbitrary orientations
- With varying spacing between objects

Examples:

```text
Good Manufacturing Conveyor

[Cube] [Cube] [Cube] [Cube]

MRF Conveyor

[Cube]

          [Bottle]

    [Can]

                    [Box]
```

The object generator must therefore generate:

```yaml
spawn_position:
  x:
  y:
  z:

spawn_orientation:
  roll:
  pitch:
  yaw:
```

Object orientation should be randomized within configurable limits.

---

# 29. Object Pose

Pose refers to an object's position and orientation.

Every object shall contain:

```yaml
object_pose:

  position:
    x:
    y:
    z:

  orientation:
    roll:
    pitch:
    yaw:
```

The robot shall always use the latest pose information.

---

# 30. External Classification System

Classification is NOT the responsibility of the robot.

Assume the existence of an external perception system.

The external system provides:

```yaml
object_id:

object_category:

object_pose:

confidence:

timestamp:
```

Examples:

```yaml
object_id: obj_001

object_category: plastic

confidence: 0.98

pose:
  x: 1.23
  y: 0.17
  z: 0.04
```

The robot consumes this information.

The robot does not:

- Detect objects
- Segment images
- Track objects
- Classify materials

The robot only executes sorting tasks.

---

# 31. Gazebo Ground Truth Mode

During simulation development:

Classification information shall be generated directly during object creation.

Example:

```yaml
Object Generated

shape = bottle

material = plastic

category = plastic
```

The generated category shall be inserted into the perception pipeline as if it came from a real detector.

This allows development without computer vision.

Workflow:

```text
Object Generator
        ↓
Ground Truth Category
        ↓
Simulated Perception Layer
        ↓
Task Scheduler
        ↓
Robot
```

This architecture allows future replacement of the simulated perception layer with:

- YOLO
- RT-DETR
- DINO
- Custom Detector

without changing robot logic.

---

# 32. Perception Interface

The robot shall never communicate directly with the object generator.

Instead, the robot communicates only with a perception interface.

Interface Output:

```yaml
object_id:

category:

position:

orientation:

velocity:

timestamp:
```

This abstraction layer ensures:

- Simulator independence
- Detector independence
- Easier migration to real hardware

---

# 33. Conveyor Constraints

The conveyor belt speed may be reduced.

The conveyor belt shall NEVER stop.

Valid states:

```text
RUNNING_FAST

RUNNING_MEDIUM

RUNNING_SLOW
```

Invalid state:

```text
STOPPED
```

The robot must adapt to conveyor motion.

The robot may wait.

The belt may not.

---

# 34. Picking Strategy

The robot is NOT required to pick every object.

The robot shall focus only on target categories.

Example:

```text
Plastic Bottle
→ Pick

Plastic Bottle
→ Pick

Metal Can
→ Ignore

Cardboard
→ Ignore
```

This reflects realistic MRF operations where only selected streams are recovered.

---

# 35. Single-Target Recovery Mode

MVP Mode

Robot only recovers one category.

Example:

```text
Target Category

Plastic
```

All other objects continue along the conveyor.

Robot only performs:

```text
Detect Plastic

Predict Intercept

Pick

Drop
```

This is the recommended first implementation.

---

# 36. Dual-Category Recovery Mode

Intermediate Mode

Robot recovers two categories.

Example:

```text
Plastic
Metal
```

Decision Logic:

```text
IF category = plastic

    send_to_plastic_bin

ELSE IF category = metal

    send_to_metal_bin

ELSE

    ignore
```

---

# 37. Object Prioritization

When multiple valid objects exist simultaneously:

The scheduler must select the best candidate.

Priority Factors:

1. Closest object to pick zone

2. Highest confidence

3. Earliest arrival

4. Lowest travel cost

Example:

```text
Plastic Bottle A

Arrival = 1 second

Plastic Bottle B

Arrival = 4 seconds

Select Bottle A
```

---

# 38. Missed Object Policy

Not every object will be collected.

This is expected behavior.

Miss conditions:

```text
Object leaves workspace

Robot busy

Interception impossible

Pose uncertainty too high
```

Action:

```text
Mark Object = MISSED

Allow object to continue
```

Do not stop the system.

Do not attempt emergency recovery.

---

# 39. Robot Work Envelope

Define a pick region.

Objects outside this region are ignored.

Example:

```yaml
pick_zone:

min_x:
max_x:

min_y:
max_y:

min_z:
max_z:
```

Scheduler only considers objects within this workspace.

---

# 40. Updated System Philosophy

The objective is NOT:

"Pick every object."

The objective IS:

"Continuously recover selected materials from a moving waste stream without stopping conveyor flow."

The robot behaves as a recovery agent.

The conveyor behaves as a continuous waste stream.

The perception system provides object category and pose.

The scheduler decides whether recovery is worthwhile.

The robot executes recovery when feasible.