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

    static void SetLevel(const Level level) {
        Logger &instance = GetInstance();
        instance.mLevel = level;
    }

    static void EnableFileOutput() {
        Logger &instance = GetInstance();
        instance.mFileOutputEnabled = true;
    }

    static void DisableFileOutput() {
        Logger &instance = GetInstance();
        instance.mFileOutputEnabled = false;
    }

    static void SetFileOutput(const char *output) {
        Logger &instance = GetInstance();
        instance.mFileOutputEnabled = true;
        instance.mFileOutput = output;
    }

    template<typename... Args>
    static void Trace(const char *format, Args... args) {
        Log(Level::Trace, "trace", format, args...);
    }

    template<typename... Args>
    static void Debug(const char *format, Args... args) {
        Log(Level::Debug, "debug", format, args...);
    }

    template<typename... Args>
    static void Info(const char *format, Args... args) {
        Log(Level::Info, "info", format, args...);
    }

    template<typename... Args>
    static void Warn(const char *format, Args... args) {
        Log(Level::Warn, "warn", format, args...);
    }

    template<typename... Args>
    static void Error(const char *format, Args... args) {
        Log(Level::Error, "error", format, args...);
    }

    template<typename... Args>
    static void Critical(const char *format, Args... args) {
        Log(Level::Critical, "critical", format, args...);
    }

    static void Trace(const char *str) {
        Log(Level::Trace, "trace", str);
    }

    static void Debug(const char *str) {
        Log(Level::Debug, "debug", str);
    }

    static void Info(const char *str) {
        Log(Level::Info, "info", str);
    }

    static void Warn(const char *str) {
        Log(Level::Warn, "warn", str);
    }

    static void Error(const char *str) {
        Log(Level::Error, "error", str);
    }

    static void Critical(const char *str) {
        Log(Level::Critical, "critical", str);
    }

private:
    Logger() = default;

    ~Logger() = default;

    template<typename... Args>
    static void Log(const Level level, const char *tag, const char *format, Args... args) {
        std::lock_guard<std::mutex> lock(instance.mMutex);
        Logger &instance = GetInstance();
        if (instance.mLevel <= level) {
            std::time_t t = std::time(nullptr);
            std::array<char, 100> time_buf{};
            std::strftime(time_buf.data(), sizeof time_buf, "%Y-%m-%d %H:%M:%S", std::gmtime(&t));
            std::printf("[%s] [%s] ", time_buf.data(), tag);
            std::printf(format, args...);
            std::printf("\n");
            if (instance.mFileOutputEnabled) {
                std::FILE *file = std::fopen(instance.mFileOutput.c_str(), "a");
                std::fprintf(file, "[%s] [%s] ", time_buf.data(), tag);
                std::fprintf(file, format, args...);
                std::fprintf(file, "\n");
                std::fclose(file);
            }
        }
    }

    static void Log(const Level level, const char *tag, const char *str) {
        std::lock_guard<std::mutex> lock(instance.mMutex);
        Logger &instance = GetInstance();
        if (instance.mLevel <= level) {
            std::time_t t = std::time(nullptr);
            std::array<char, 100> time_buf{};
            std::strftime(time_buf.data(), sizeof time_buf, "%Y-%m-%d %H:%M:%S", std::gmtime(&t));
            std::printf("[%s] [%s] %s\n", time_buf.data(), tag, str);
            if (instance.mFileOutputEnabled) {
                std::FILE *file = std::fopen(instance.mFileOutput.c_str(), "a");
                std::fprintf(file, "[%s] [%s] %s\n", time_buf.data(), tag, str);
                std::fclose(file);
            }
        }
    }

    Level mLevel = Level::Info;
    bool mFileOutputEnabled = false;
    std::string mFileOutput;
    std::mutex mMutex;
};