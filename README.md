# Workpiece Sorter FSM Embedded

This repository contains the embedded software developed as part of a university project in Embedded Systems Programming.  
The system was designed, implemented, and tested by a team of 4, running on two machines that collaborate to identify and sort workpieces.

---

## Project Overview
- **Hardware Setup**: Two Festo machines equipped with a multiple sensors to identify pieces.
- **Functionality**:  
  - Pieces are fed into the system.  
  - Light barriers are used to locate the piece.
  - A height sensor identifies the piece.  
  - Pieces are sorted depending on if they follow the specified order machine.  
- **Software Design**:  
  - Event-driven, asynchronous message-based communication between system components.  
  - Three-layer architecture for separation of concerns.  
  - Core logic modeled and implemented using Finite State Machines (FSMs).  
  - FSM designs can be found in the Documents folder.

---

## Features
- Multi-machine coordination.  
- Asynchronous, message-based communication.  
- Modular 3-layer software design.  
- FSM-driven control logic.  
- Emergency stop (E-Stop) implemented and tested extensively for machine and user safety.  
- Calibration mode for accurate piece detection and setup.
- Can locate and process up to 5 pieces per machine simultaneously. 
- LED indicators for error states and a reset button.
- Tested and validated on embedded hardware. 
