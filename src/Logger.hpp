#pragma once

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

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

    static Logger &Get() {
        static Logger instance;
        return instance;
    }

    static void SetLevel(Level level) {
        Logger &instance = Get();
        instance.mLevel = level;
    }
    static void SetFileOutput(const std::string &path) {
        Logger &instance = Get();
        instance.mFileOutput = true;
        instance.mFileName = path;
    }

    template <typename... Args>
    static void Trace(const char *fmt, Args... args) {
        Log(Level::Trace, "trace", fmt, args...);
    }
    template <typename... Args>
    static void Debug(const char *fmt, Args... args) {
        Log(Level::Debug, "debug", fmt, args...);
    }
    template <typename... Args>
    static void Info(const char *fmt, Args... args) {
        Log(Level::Info, "info", fmt, args...);
    }
    template <typename... Args>
    static void Warn(const char *fmt, Args... args) {
        Log(Level::Warn, "warn", fmt, args...);
    }
    template <typename... Args>
    static void Error(const char *fmt, Args... args) {
        Log(Level::Error, "error", fmt, args...);
    }
    template <typename... Args>
    static void Critical(const char *fmt, Args... args) {
        Log(Level::Critical, "critical", fmt, args...);
    }

private:
    Logger() = default;
    ~Logger() = default;

    static void Log(Level level, const char *tag, const char *fmt, ...) {
        Logger &instance = Get();
        if (instance.mLevel <= level) {
            std::scoped_lock<std::mutex> lock(instance.mMutex);
            std::time_t t = std::time(nullptr);
            char time_buf[100];
            std::strftime(time_buf, sizeof time_buf, "%Y-%m-%d %H:%M:%S", std::gmtime(&t));
            va_list args1;
                    va_start(args1, fmt);
            va_list args2;
            va_copy(args2, args1);
            std::vector<char> buf(1 + std::vsnprintf(nullptr, 0, fmt, args1));
                    va_end(args1);
            std::vsnprintf(buf.data(), buf.size(), fmt, args2);
                    va_end(args2);
            std::printf("[%s] [%s] %s\n", time_buf, tag, buf.data());
            if (instance.mFileOutput) {
                std::FILE *file = std::fopen(instance.mFileName.c_str(), "a");
                std::fprintf(file, "[%s] [%s] %s\n", time_buf, tag, buf.data());
                std::fclose(file);
            }
        }
    }

    Level mLevel = Level::Info;
    bool mFileOutput = false;
    std::string mFileName;
    std::mutex mMutex;
};