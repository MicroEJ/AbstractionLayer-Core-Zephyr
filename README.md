# Overview

MicroEJ Core Engine Abstraction Layer implementation for Zephyr OS.

This module implements the `LLMJVM` Low Level API for MicroEJ Platforms connected to a Board Support Package based on [Zephyr OS](https://www.zephyrproject.org/).

See [these sections](https://docs.microej.com/en/latest/PlatformDeveloperGuide/appendix/llapi.html#llmjvm-microej-core-engine) of the MicroEJ documentation for a description of the `LLMJVM` functions:
- [LLMJVM: MicroEJ Core Engine](https://docs.microej.com/en/latest/PlatformDeveloperGuide/appendix/llapi.html#llmjvm-microej-core-engine)
- [MicroEJ Core Engine: Implementation](https://docs.microej.com/en/latest/PlatformDeveloperGuide/coreEngine.html#implementation)

# Usage

1. Install the ``src`` directory in your Board Support Package. It can be automatically downloaded using the following command line:
   ```sh
    svn export --force https://github.com/MicroEJ/AbstractionLayer-Core-Zephyr/trunk/src/main/c/src [path_to_bsp_directory]
   ```

2. The `LLMJVM_IMPL_scheduleRequest` schedule request function in [LLMJVM_ZephyrOS.c](./src/main/c/src/LLMJVM_ZephyrOS.c) uses a software timer. In order to correctly schedule MicroEJ threads, check the following elements in the Zephyr OS configuration file:

   - `CONFIG_SYS_CLOCK_TICKS_PER_SEC`: can depend on the application, if it needs a 1 ms precision then the tick rate would be 1000 Hz, the recommended value is between 100 Hz and 1000 Hz (see [Zephyr Kernel Timing](https://docs.zephyrproject.org/3.6.0/kernel/services/timing/clocks.html) page for more details)

3. The `LLMJVM_IMPL_getTimeNanos` function in [LLMJVM_ZephyrOS.c](./src/main/c/src/LLMJVM_ZephyrOS.c) gets the current timestamp in nanoseconds. 
   Not all hardware have 64 bit counters. This function returns a timestamp with a resolution depending on ``CONFIG_SYS_CLOCK_TICKS_PER_SEC`` if ``CONFIG_TIMER_HAS_64BIT_CYCLE_COUNTER`` is not set. In this case, it is strongly recommended to update your implementation using the APIs of your target HAL drivers
   to get a better precision.

**_Note:_** the application time is retrieved using the Zephyr Kernel API [k_uptime_get()](https://docs.zephyrproject.org/3.6.0/kernel/services/timing/clocks.html#c.k_uptime_get). 
While this function returns time in milliseconds, it does not mean it has millisecond resolution. The actual resolution depends on ``CONFIG_SYS_CLOCK_TICKS_PER_SEC`` config option.

# Requirements

None.

# Validation

This Abstraction Layer implementation can be validated in the target Board Support Package using the [MicroEJ Core Validation](https://github.com/MicroEJ/PlatformQualificationTools/tree/master/tests/core/java/microej-core-validation) VEE Port Qualification Tools project.

Here is a non-exhaustive list of tested environments:
- Hardware
  - STMicroelectronics NUCLEO-H563ZI
- Compilers / Build environments:
  - ZEPHYR SDK 0.16.5
- Zephyr OS v3.6.0

## MISRA Compliance

The implementation is MISRA-compliant (MISRA C:2012). It has been verified with Cppcheck v2.10.0. 
Here is the list of deviations:

| Deviation | Category |   Action   |                                                 Justification                                                                     |
|:---------:|:--------:|:----------:|:---------------------------------------------------------------------------------------------------------------------------------:|
| Rule 2.1  | Required | Flagged    | A deviation from this rule is necessary as LLMJVM_IMPL_ functions are called from the VM	               		   | 
| Rule 5.5  | Required | Ignored    | A deviation from this rule is necessary as macros are used to map VM symbols to LLMJVM_IMPL_ functions	               		   | 
  
## Usage

Copy/paste source code in your VEE Port BSP project or add the following line to your VEE Port configuration `module.ivy`:
> `<dependency org="com.microej.clibrary.llimpl" name="mjvm-zephyros" rev="..."/>`

**_Note:_**  Run the [MicroEJ Core Validation](https://github.com/MicroEJ/PlatformQualificationTools/tree/master/tests/core/java/microej-core-validation) VEE Port Qualification Tools project to validate code integration in your environment.

# Dependencies

- MicroEJ Architecture ``8.x`` or higher.
- Zephyr OS ``3.6.0`` or higher.

# Source

N/A.

# Restrictions

None.

---
_Copyright 2021-2024 MicroEJ Corp. All rights reserved._
_Use of this source code is governed by a BSD-style license that can be found with this software._
