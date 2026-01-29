# Smart Parking System Design

## Zone and Slot Representation
[cite_start]The city is divided into a custom hierarchy: `Zone` -> `ParkingArea` -> `ParkingSlot`[cite: 17, 21]. [cite_start]We use dynamic arrays to manage these without STL containers[cite: 79].

## Request Lifecycle
Each request follows a state machine:
- **REQUESTED**: Initial state.
- [cite_start]**ALLOCATED**: Slot assigned[cite: 46].
- [cite_start]**CANCELLED**: Request terminated[cite: 49].
- [cite_start]**RELEASED**: Parking complete[cite: 45].

## Rollback Design
[cite_start]Uses a **Stack-based RollbackManager**[cite: 6]. [cite_start]When an allocation is undone, the last request is popped, and the slot's `isAvailable` status is set back to `true`[cite: 65, 67].

## Complexity
- **Allocation**: $O(A \times S)$ where $A$ is areas and $S$ is slots.
- [cite_start]**Rollback**: $O(1)$ for the last operation[cite: 103].