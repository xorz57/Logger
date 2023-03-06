#include "Logger.hpp"

int main() {
    Logger::SetLevel(Logger::Level::Trace);
    Logger::SetFileOutput("Logger.log");
    Logger::Trace("trace");
    Logger::Debug("debug");
    Logger::Info("info");
    Logger::Warn("warn");
    Logger::Error("error");
    Logger::Critical("critical");
    return 0;
}
