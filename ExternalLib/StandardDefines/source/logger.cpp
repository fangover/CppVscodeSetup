#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>
#include <chrono>
#include <ctime>
#include <vector>

#include "../include/logger.h"

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

std::mutex Logger::log_mutex_;

Logger::Logger() = default;

Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::logMessage(const char *level, const char *file, int line,
                        const char *func, const char *fmt, ...)
{
    std::lock_guard<std::mutex> lock(log_mutex_);
    std::string timestamp = getTimeStamp("%Y-%m-%d %T");

    va_list args;
    va_start(args, fmt);
    std::string message = formatMessage(fmt, args);
    va_end(args);

    message = formatLogMessage(timestamp, level, file, line, func, message);
    printConsole(message);

    auto log_path = prepareLogFile();
    if (!log_path.empty())
    {
        writeToFile(log_path, message);
    }
}

std::string Logger::formatMessage(const char *fmt, va_list args)
{
    va_list args_copy;
    va_copy(args_copy, args);
    int msg_size = vsnprintf(nullptr, 0, fmt, args_copy);
    va_end(args_copy);

    std::string message;
    if (msg_size > 0)
    {
        message.resize(msg_size + 1);
        vsnprintf(&message[0], message.size(), fmt, args);
        message.resize(msg_size);
    }
    return message;
}

std::string Logger::formatLogMessage(std::string &timestamp, const char *level,
                                     const char *file, int line, const char *func,
                                     const std::string &message)
{
    // E.g. output [2025-05-26 15:51:46] [main.cpp:24] [LOG] testFunction - LOG function try out
    const char *filename = filename_from_path(file);
    std::ostringstream oss;

    oss << "[" << timestamp << "] "
        << "[" << filename << ":" << line << "] "
        << "[" << level << "] "
        << func;

    if (!message.empty())
        oss << " - " << message;
    oss << std::endl;

    return oss.str();
}

void Logger::printConsole(const std::string &message)
{
    std::printf(message.c_str());
    std::fflush(stdout);
}

void Logger::writeToFile(const std::filesystem::path &path, const std::string &message)
{
    std::ofstream log_file(path, std::ios::app);
    if (log_file)
    {
        log_file << message.c_str();
    }
}

const char *Logger::filename_from_path(const char *path)
{
    const char *file = std::strrchr(path, '/');
    const char *alt = std::strrchr(path, '\\');
    file = std::max(file, alt);
    return file ? file + 1 : path;
}

std::filesystem::path Logger::prepareLogFile()
{
    try
    {
        std::filesystem::create_directories(log_dir_);
        auto log_path = getLogPath();

        if (std::filesystem::exists(log_path) && std::filesystem::file_size(log_path) > max_log_size_)
        {
            rotateLog(log_path);
        }

        return log_path;
    }
    catch (...)
    {
        return {};
    }
}

std::filesystem::path Logger::getLogPath()
{
    return std::filesystem::path(log_dir_) / (getTimeStamp("%d_%m_%y") + ".log");
}

const std::string Logger::getTimeStamp(const std::string cstrTimeFormat)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::vector<char> buffer(100);
    if (std::strftime(buffer.data(), buffer.size(), cstrTimeFormat.c_str(), &tm))
    {
        return std::string(buffer.data());
    }
    else
    {
        return std::string();
    }
}

void Logger::rotateLog(const std::filesystem::path &log_path)
{
    try
    {
        if (!std::filesystem::exists(log_path))
            return;

        std::string base_name = log_path.stem().string();
        int max_num = 0;

        for (const auto &entry : std::filesystem::directory_iterator(log_dir_))
        {
            std::string name = entry.path().filename().string();
            std::regex pattern(base_name + R"(\.lo(\d+))");
            std::smatch match;
            if (std::regex_search(name, match, pattern))
            {
                int num = std::stoi(match[1].str());
                max_num = std::max(max_num, num);
            }
        }

        std::filesystem::path new_name = std::filesystem::path(log_dir_) / (base_name + ".lo" + std::to_string(max_num + 1));
        std::filesystem::rename(log_path, new_name);
    }
    catch (...)
    {
    }
}

ScopeLogger::ScopeLogger(const char *file, int line, const char *func)
    : file_(file), line_(line), func_(func)
{
    Logger::instance().logMessage("ENTER", file_, line_, func_);
}

ScopeLogger::~ScopeLogger() noexcept
{
    Logger::instance().logMessage("EXIT", file_, line_, func_);
}
