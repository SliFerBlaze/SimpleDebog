---
title:          Beta Test Plan
subtitle:       SimpleDebog
author:         Candan Evan, Spiller Arthur, Deplaine Guillaume
module:         G-EIP-700
version:        1.0
---

# Beta Test Plan SimpleDebog

## **1. Project context**
SimpleDebog is a debugger for C/C++ programs designed to help developers analyze and fix runtime errors more easily. Debugging native applications can be complex due to low‑level concepts such as memory management, pointers, and multithreading, which often makes traditional tools difficult to use, especially for beginners.
SimpleDebog provides the essential features of a classic debugger, including breakpoints, step‑by‑step execution, variable inspection, and thread management, while also offering memory‑related diagnostics such as invalid memory access, memory leak detection, and uninitialized variable detection. The tool focuses on clarity, accessibility, and precise error localization to support both beginner and experienced developers during debugging sessions.

## **2. User role**

| **Role Name**  | **Description** |
|--------|----------------------|
| Advanced Developer     | Experienced programmer familiar with low‑level concepts and traditional debuggers; uses advanced features such as memory inspection, thread control.|
| Beginner Developer     | New to programming or has never used a debugger; needs guided workflows, simplified visualizations, and safe default features. |

---

## **3. Feature table**

| **Feature ID** | **User role** | **Feature name** | **Short description** |
|--------------------|-----------|--------------|-------------------|
| F1 | Everyone | Launch program under debugger | Start a C/C++ program with debugging symbols and control its execution from the debugger. |
| F2 | Everyone | Set breakpoint | Pause program execution at a specified source line or function entry. |
| F3 | Everyone | Continue execution | Resume program execution after a breakpoint, step, or pause. |
| F4 | Everyone | Step over instruction | Execute the next source line without entering called functions. |
| F5 | Everyone | Step into function | Execute the next instruction and enter the called function. |
| F6 | Everyone | Step out of function | Continue execution until the current function returns to its caller. |
| F7 | Everyone | Display call stack | Show the current stack trace with function names and source locations. |
| F8 | Everyone | Inspect variable value | Display the current value of local, global, and static variables. |
| F9 | Everyone | Modify variable value | Change variable values at runtime to test different execution paths. |
| F10 | Advanced Developer | Switch active thread | Select and inspect a specific thread during program execution. |
| F11 | Advanced Developer | Visualize thread states | Display the state of each thread (running, paused, blocked). |
| F12 | Everyone | Handle program crash | Automatically break execution and display context on crashes (e.g., segmentation fault). |
| F13 | Everyone | Attach to running process | Attach the debugger to an already running C/C++ process. |
| F14 | Everyone | Display source code | Show source code synchronized with the current execution point. |
| F15 | Everyone | Set conditional breakpoint | Pause execution only when a user-defined condition evaluates to true. |
| F16 | Everyone | Watch variable changes | Break execution when the value of a specified variable is modified. |
| F17 | Everyone | Detect invalid memory access | Identify and report invalid memory reads or writes during execution. |
| F18 | Everyone | Detect memory leaks | Identify memory that was allocated but not freed at program termination. |
| F19 | Everyone | Display exact error line | Highlight the exact source code line responsible for a runtime error or crash. |
| F20 | Everyone | Use debugger with keyboard only | Allow full debugger operation using keyboard controls to improve accessibility. |
| F21 | Everyone | Detect uninitialized variables | Warn when variables are accessed before being initialized. |
| F22 | Everyone | Log execution events | Record debugger actions and significant runtime events for analysis and debugging. |

---

## **4. Success Criteria**

| **Feature ID** | **Key success criteria** | **Indicator/metric** | **Result** |
|------------|----------------------|--------------------|--------|
| F1 | The debugger successfully launches and controls a C/C++ program under debugging. | Successful program launch and control rate: p > 99 % | |
| F2 | The debugger pauses program execution at user-defined breakpoints. | Correct breakpoint trigger rate: p > 99 % | |
| F3 | The debugger resumes execution correctly after a pause or breakpoint. | Successful execution resume rate: p > 99 % | |
| F4 | The debugger executes the next line without entering called functions. | Correct step-over behavior rate: p > 95 % | |
| F5 | The debugger enters the called function during step-into operations. | Correct step-into behavior rate: p > 95 % | |
| F6 | The debugger continues execution until the current function returns. | Correct step-out behavior rate: p > 95 % | |
| F7 | The debugger displays an accurate and complete call stack at any pause point. | Correct call stack display rate: p > 99 % | |
| F8 | The debugger displays correct values for inspected variables. | Correct variable value display rate: p > 99 % | |
| F9 | The debugger allows runtime modification of variable values. | Successful variable modification rate: p > 95 % | |
| F10 | The debugger allows switching between active threads during execution. | Successful thread switching rate: p > 99 % | |
| F11 | The debugger displays the correct state for each thread. | Correct thread state visualization rate: p > 95 % | |
| F12 | The debugger automatically pauses and displays context on program crashes. | Crash interception and context display rate: p > 99 % | |
| F13 | The debugger successfully attaches to an already running process. | Successful process attachment rate: p > 95 % | |
| F14 | The debugger displays source code synchronized with the current execution point. | Correct source-to-execution mapping rate: p > 99 % | |
| F15 | The debugger pauses execution when a conditional breakpoint evaluates to true. | Correct conditional breakpoint trigger rate: p > 90 % | |
| F16 | The debugger pauses execution when a watched variable changes value. | Correct watchpoint trigger rate: p > 90 % | |
| F17 | The debugger detects and reports invalid memory reads or writes. | Invalid memory access detection rate: p > 95 % | |
| F18 | The debugger detects memory leaks at program termination. | Memory leak detection rate: p > 95 % | |
| F19 | The debugger displays the exact source file and line responsible for a runtime error. | Correct error line identification rate: p > 80 % | |
| F20 | The debugger can be fully operated using keyboard-only controls. | Keyboard-accessible functionality rate: p > 99 % | |
| F21 | The debugger detects and warns when uninitialized variables are used. | Uninitialized variable detection rate: p > 95 % | |
| F22 | The debugger records debugger actions and significant runtime events. | Successful event logging rate: p > 99 % | |