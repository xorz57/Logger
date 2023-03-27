# Logger

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=xorz57_Logger)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=bugs)](https://sonarcloud.io/summary/new_code?id=xorz57_Logger)
[![Vulnerabilities](https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=vulnerabilities)](https://sonarcloud.io/summary/new_code?id=xorz57_Logger)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=xorz57_Logger)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=coverage)](https://sonarcloud.io/summary/new_code?id=xorz57_Logger)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=xorz57_Logger)

Logger written in C++17

## Example

```c++
#include "Logger.hpp"

int main() {
    Logger::SetLevel(Logger::Level::Trace);
    Logger::EnableFileOutput();
    Logger::SetFileOutput("Example.log");
    Logger::Trace("trace");
    Logger::Debug("debug");
    Logger::Info("info");
    Logger::Warn("warn");
    Logger::Error("error");
    Logger::Critical("critical");
    return 0;
}
```

```
[2023-03-22 11:17:11] [trace] trace
[2023-03-22 11:17:11] [debug] debug
[2023-03-22 11:17:11] [info] info
[2023-03-22 11:17:11] [warn] warn
[2023-03-22 11:17:11] [error] error
[2023-03-22 11:17:11] [critical] critical
```

## How to Build using [CMake](https://cmake.org/)

```bash
cmake -B build
cmake --build build --config Release
ctest -C Release
```
