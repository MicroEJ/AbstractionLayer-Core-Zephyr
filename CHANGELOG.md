# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.0.0] - 2024-08-02

### Added

- Add dependency to SMT32F7508-DK VEE Port for static code analysis purpose.
- Add Zephyr as submodule for static code analysis purpose.

### Changed

- Update LLMJVM implementation for Zephyr OS 3.6.0.
- Update LICENSE.
- Update skeleton and build type version.
- Update MISRA C:2012 compliance.

### Removed

- Remove MicroEJ time header. Time now handled in ``LLMJVM_ZephyrOS.c``.

## [1.1.0] - 2022-06-10

### Changed

- Change license terms to MicroEJ Corp. BSD-style license.

## [1.0.2] - 2022-02-15

### Fixed

  - LLMJVM Zephyr OS MISRA C:2012 rule violation.
  - License updated to BSD license.

## [1.0.1] - 2021-06-18

### Added

  - LLMJVM Zephyr OS MISRA-compliant implementation (MISRA C 2012).
  
## [1.0.0] - 2021-05-12

### Added

  - MicroEJ time header.
  - LLMJVM Zephyr OS MISRA-compliant implementation (MISRA C 2004).
  - Cleanup for initial publication.

---
_Copyright 2021-2024 MicroEJ Corp. All rights reserved._
_Use of this source code is governed by a BSD-style license that can be found with this software._
