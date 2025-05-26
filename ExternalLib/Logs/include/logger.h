#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <mutex>
#include <filesystem>
#include <cstdarg>

class Logger
{
private:
    static std::mutex log_mutex_;
    static constexpr std::string_view log_dir_ = "build/out/log";
    static constexpr size_t max_log_size_ = 5 * 1024 * 1024;

    Logger();

public:
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    static Logger &instance();

    static void logMessage(const char *level, const char *file, int line,
                           const char *func, const char *fmt = "", ...);

private:
    static std::string formatMessage(const char *fmt, va_list args);
    static std::string formatLogMessage(std::string &timestamp, const char *level,
                                        const char *file, int line, const char *func,
                                        const std::string &message);

    static void printConsole(const std::string &message);
    static void writeToFile(const std::filesystem::path &path, const std::string &message);

    static const char *filename_from_path(const char *path);
    static std::filesystem::path prepareLogFile();
    static std::filesystem::path getLogPath();

    static const std::string getTimeStamp(const std::string cstrTimeFormat);
    static void rotateLog(const std::filesystem::path &log_path);
};

class ScopeLogger
{
public:
    ScopeLogger(const char *file, int line, const char *func);
    ~ScopeLogger() noexcept;

private:
    const char *file_;
    int line_;
    const char *func_;
};

#endif // LOGGING_H
