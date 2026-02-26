#include "Logger.h"

#include <exception>
#include <vector>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

std::shared_ptr<spdlog::logger> Logger::s_logger = nullptr;
bool Logger::s_initialized = false;
std::string Logger::s_logName = "SC4DisableFpsLimits";

std::shared_ptr<spdlog::logger> Logger::Get() {
    if (!s_initialized) {
        Initialize();
    }

    return s_logger;
}

void Logger::Initialize(const std::string& logName, const std::filesystem::path& logDirectory,
                        const spdlog::level::level_enum logLevel) {
    if (s_initialized && s_logger) {
        return;
    }

    s_logName = logName;

    try {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());

        if (!logDirectory.empty()) {
            std::filesystem::create_directories(logDirectory);
            const std::filesystem::path logPath = logDirectory / (s_logName + ".log");
            sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath.string(), true));
        }

        s_logger = std::make_shared<spdlog::logger>(s_logName, sinks.begin(), sinks.end());
        s_logger->set_level(logLevel);
        s_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");
        s_logger->flush_on(logLevel);
        s_initialized = true;

        s_logger->info("{} logger initialized", s_logName);
        if (!logDirectory.empty()) {
            const std::filesystem::path logPath = logDirectory / (s_logName + ".log");
            s_logger->info("Logging to file: {}", logPath.string());
        }
    }
    catch (const std::exception& e) {
        auto consoleSink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
        s_logger = std::make_shared<spdlog::logger>(s_logName, consoleSink);
        s_logger->set_level(logLevel);
        s_logger->flush_on(logLevel);
        s_logger->error("Failed to initialize file logging: {}", e.what());
        s_initialized = true;
    }
}

void Logger::SetLevel(const spdlog::level::level_enum logLevel) {
    if (!s_initialized || !s_logger) {
        Initialize();
    }

    s_logger->set_level(logLevel);
    s_logger->flush_on(logLevel);
}

void Logger::Shutdown() {
    if (s_logger) {
        s_logger->info("{} logger shutting down", s_logName);
        s_logger->flush();
        s_logger.reset();
    }

    s_initialized = false;
}
