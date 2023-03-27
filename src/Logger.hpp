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

    [[maybe_unused]] static void SetLevel(Level level) {
        Logger &instance = GetInstance();
        instance.mLevel = level;
    }

    [[maybe_unused]] static void EnableFileOutput() {
        Logger &instance = GetInstance();
        instance.mFileOutputEnabled = true;
    }

    [[maybe_unused]] static void DisableFileOutput() {
        Logger &instance = GetInstance();
        instance.mFileOutputEnabled = false;
    }

    [[maybe_unused]] static void SetFileOutput(std::string_view output) {
        Logger &instance = GetInstance();
        instance.mFileOutputEnabled = true;
        instance.mFileOutput = output;
    }

    template<typename... Args>
    [[maybe_unused]] static void Trace(const char *format, Args... args) {
        Log(Level::Trace, "trace", format, args...);
    }

    template<typename... Args>
    [[maybe_unused]] static void Debug(const char *format, Args... args) {
        Log(Level::Debug, "debug", format, args...);
    }

    template<typename... Args>
    [[maybe_unused]] static void Info(const char *format, Args... args) {
        Log(Level::Info, "info", format, args...);
    }

    template<typename... Args>
    [[maybe_unused]] static void Warn(const char *format, Args... args) {
        Log(Level::Warn, "warn", format, args...);
    }

    template<typename... Args>
    [[maybe_unused]] static void Error(const char *format, Args... args) {
        Log(Level::Error, "error", format, args...);
    }

    template<typename... Args>
    [[maybe_unused]] static void Critical(const char *format, Args... args) {
        Log(Level::Critical, "critical", format, args...);
    }

    [[maybe_unused]] static void Trace(const char *str) {
        Log(Level::Trace, "trace", str);
    }

    [[maybe_unused]] static void Debug(const char *str) {
        Log(Level::Debug, "debug", str);
    }

    [[maybe_unused]] static void Info(const char *str) {
        Log(Level::Info, "info", str);
    }

    [[maybe_unused]] static void Warn(const char *str) {
        Log(Level::Warn, "warn", str);
    }

    [[maybe_unused]] static void Error(const char *str) {
        Log(Level::Error, "error", str);
    }

    [[maybe_unused]] static void Critical(const char *str) {
        Log(Level::Critical, "critical", str);
    }

private:
    Logger() = default;

    ~Logger() = default;

    template<typename... Args>
    [[maybe_unused]] static void Log(Level level, const char *tag, const char *format, Args... args) {
        Logger &instance = GetInstance();
        if (instance.mLevel <= level) {
            std::scoped_lock<std::mutex> lock(instance.mMutex);
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

    [[maybe_unused]] static void Log(Level level, const char *tag, const char *str) {
        Logger &instance = GetInstance();
        if (instance.mLevel <= level) {
            std::scoped_lock<std::mutex> lock(instance.mMutex);
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