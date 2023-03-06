#pragma once

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

#include <array>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <mutex>
#include <vector>

class Logger {
public:
    enum class Level {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical
    };

    Logger(const Logger &) = delete;

    Logger(Logger &&) = delete;

    Logger &operator=(const Logger &) = delete;

    Logger &operator=(Logger &&) = delete;

    static Logger &GetInstance() {
        static Logger instance;
        return instance;
    }

    static void SetLevel(Level level) {
        Logger &instance = GetInstance();
        instance.mLevel = level;
    }

    static void SetFileOutput(std::string_view path) {
        Logger &instance = GetInstance();
        instance.mFileOutputEnabled = true;
        instance.mFileOutput = path;
    }

    template<typename... Args>
    static void Trace(const char *fmt, Args... args) {
        Log(Level::Trace, "trace", fmt, args...);
    }

    template<typename... Args>
    static void Debug(const char *fmt, Args... args) {
        Log(Level::Debug, "debug", fmt, args...);
    }

    template<typename... Args>
    static void Info(const char *fmt, Args... args) {
        Log(Level::Info, "info", fmt, args...);
    }

    template<typename... Args>
    static void Warn(const char *fmt, Args... args) {
        Log(Level::Warn, "warn", fmt, args...);
    }

    template<typename... Args>
    static void Error(const char *fmt, Args... args) {
        Log(Level::Error, "error", fmt, args...);
    }

    template<typename... Args>
    static void Critical(const char *fmt, Args... args) {
        Log(Level::Critical, "critical", fmt, args...);
    }

private:
    Logger() = default;

    ~Logger() = default;

    template<typename... Args>
    static void Log(Level level, const char *tag, const char *fmt, Args... args) {
        Logger &instance = GetInstance();
        if (instance.mLevel <= level) {
            std::scoped_lock<std::mutex> lock(instance.mMutex);
            std::time_t t = std::time(nullptr);
            std::array<char, 100> time_buf{};
            std::strftime(time_buf.data(), sizeof time_buf, "%Y-%m-%d %H:%M:%S", std::gmtime(&t));
            std::printf("[%s] [%s] %s\n", time_buf.data(), tag, fmt, args...);
            if (instance.mFileOutputEnabled) {
                std::FILE *file = std::fopen(instance.mFileOutput.c_str(), "a");
                std::fprintf(file, "[%s] [%s] %s\n", time_buf.data(), tag, fmt, args...);
                std::fclose(file);
            }
        }
    }

    Level mLevel = Level::Info;
    bool mFileOutputEnabled = false;
    std::string mFileOutput;
    std::mutex mMutex;
};