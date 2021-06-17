# Overview

MicroEJ Core Engine Abstraction Layer implementation for Zephyr OS.

This module implements the `LLMJVM` Low Level API for MicroEJ Platforms connected to a Board Support Package based on [Zephyr OS](https://www.zephyrproject.org/).

See [these sections](https://docs.microej.com/en/latest/PlatformDeveloperGuide/appendix/llapi.html#llmjvm-microej-core-engine) of the MicroEJ documentation for a description of the `LLMJVM` functions:
- [LLMJVM: MicroEJ Core Engine](https://docs.microej.com/en/latest/PlatformDeveloperGuide/appendix/llapi.html#llmjvm-microej-core-engine)
- [MicroEJ Core Engine: Implementation](https://docs.microej.com/en/latest/PlatformDeveloperGuide/coreEngine.html#implementation)

# Usage

1. Install ``src`` and ``inc`` directories in your Board Support Package. They can be automatically downloaded using the following command lines:
   ```sh
    svn export --force https://github.com/MicroEJ/AbstractionLayer-Core-Zephyr/trunk/inc [path_to_bsp_directory]    
    svn export --force https://github.com/MicroEJ/AbstractionLayer-Core-Zephyr/trunk/src [path_to_bsp_directory]
   ```

2. Implement the MicroEJ time functions, as described in [microej_time.h](./inc/microej_time.h).

3. The `LLMJVM_IMPL_scheduleRequest` schedule request function in [LLMJVM_ZephyrOS.c](./src/LLMJVM_ZephyrOS.c) uses a software timer. In order to correctly schedule MicroEJ threads, check the following elements in the Zephyr OS configuration file:

   - `CONFIG_SYS_CLOCK_TICKS_PER_SEC`: can depend on the application, if it needs a 1 ms precision then the tick rate would be 1000 Hz, the recommended value is between 100 Hz and 1000 Hz (see [Zephyr Kernel Timing](https://docs.zephyrproject.org/2.5.0/reference/kernel/timing/clocks.html) page for more details)

# Requirements

None.

# Validation

This Abstraction Layer implementation can be validated in the target Board Support Package using the [MicroEJ Core Validation](https://github.com/MicroEJ/PlatformQualificationTools/tree/master/tests/core/java/microej-core-validation) Platform Qualification Tools project.

Here is a non exhaustive list of tested environments:
- Hardware
  - STMicroelectronics 32F746GDISCOVERY Discovery kit
- Compilers / Build environments:
  - arm-none-eabi-gcc v10.2.1 / cmake v3.20.0, ninja v1.10.2
- Zephyr OS v2.5.0

## MISRA Compliance

The implementation is MISRA-compliant (MISRA C 2004).
| Deviation | Category |                                                 Justification                                                                     |
|:---------:|:--------:|:---------------------------------------------------------------------------------------------------------------------------------:|
| Rule 11.3 | Advisory | A deviation from this rule is necessary as the pointer returned by k_current_get has to be cast to an int32_t to get a task id    | 

# Dependencies

- MicroEJ Architecture ``7.x`` or higher.
- Zephyr OS ``2.5.0`` or higher.

# Source

N/A.

# Restrictions

None.

---
_Copyright 2021 MicroEJ Corp. All rights reserved._  
_This library is provided in source code for use, modification and test, subject to license terms._    
_Any modification of the source code will break MicroEJ Corp. warranties on the whole library._
