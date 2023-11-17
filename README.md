<h1 align="center">Logger</h1>

<div align="center">
    <a href="https://sonarcloud.io/summary/new_code?id=xorz57_Logger">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=alert_status" alt="Quality Gate Status">
    </a>
    <a href="https://sonarcloud.io/summary/new_code?id=xorz57_Logger">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=bugs" alt="Bugs">
    </a>
    <a href="https://sonarcloud.io/summary/new_code?id=xorz57_Logger">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=vulnerabilities" alt="Vulnerabilities">
    </a>
    <a href="https://sonarcloud.io/summary/new_code?id=xorz57_Logger">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=code_smells" alt="Code Smells">
    </a>
    <a href="https://sonarcloud.io/summary/new_code?id=xorz57_Logger">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=coverage" alt="Coverage">
    </a>
    <a href="https://sonarcloud.io/summary/new_code?id=xorz57_Logger">
        <img src="https://sonarcloud.io/api/project_badges/measure?project=xorz57_Logger&metric=duplicated_lines_density" alt="Duplicated Lines (%)">
    </a>
</div>

## Example

```c++
#include "Logger/Logger.hpp"

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

## Output

```console
[2023-03-22 11:17:11] [trace] trace
[2023-03-22 11:17:11] [debug] debug
[2023-03-22 11:17:11] [info] info
[2023-03-22 11:17:11] [warn] warn
[2023-03-22 11:17:11] [error] error
[2023-03-22 11:17:11] [critical] critical
```

## How to Build

#### Linux & macOS

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh

git clone https://github.com/xorz57/Logger.git
cd Logger
cmake -B build -DCMAKE_BUILD_TYPE=Release -S . -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
ctest --build-config Release
```

#### Windows

```powershell
git clone https://github.com/microsoft/vcpkg.git C:/vcpkg
C:/vcpkg/bootstrap-vcpkg.bat
C:/vcpkg/vcpkg.exe integrate install

git clone https://github.com/xorz57/Logger.git
cd Logger
cmake -B build -DCMAKE_BUILD_TYPE=Release -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
ctest --build-config Release
```
