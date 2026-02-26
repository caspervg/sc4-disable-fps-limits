#include "Settings.h"
#include "Logger.h"

#include "mini/ini.h"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <exception>
#include <string>

namespace {
    constexpr uint8_t kDefaultMaxFps = 255;
    constexpr uint8_t kMinMaxFps = 1;
    constexpr uint8_t kMaxMaxFps = 255;
    constexpr spdlog::level::level_enum kDefaultLogLevel = spdlog::level::info;

    spdlog::level::level_enum ParseLogLevel(const std::string& value, bool& valid) {
        std::string normalized(value);
        std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        if (normalized == "trace") {
            valid = true;
            return spdlog::level::trace;
        }
        if (normalized == "debug") {
            valid = true;
            return spdlog::level::debug;
        }
        if (normalized == "info") {
            valid = true;
            return spdlog::level::info;
        }
        if (normalized == "warn" || normalized == "warning") {
            valid = true;
            return spdlog::level::warn;
        }
        if (normalized == "error") {
            valid = true;
            return spdlog::level::err;
        }
        if (normalized == "critical") {
            valid = true;
            return spdlog::level::critical;
        }
        if (normalized == "off") {
            valid = true;
            return spdlog::level::off;
        }

        valid = false;
        return kDefaultLogLevel;
    }
} // namespace

Settings::Settings() : maxFps_(kDefaultMaxFps), logLevel_(kDefaultLogLevel) {}

void Settings::Load(const std::filesystem::path& settingsFilePath) {
    maxFps_ = kDefaultMaxFps;
    logLevel_ = kDefaultLogLevel;

    try {
        const mINI::INIFile file(settingsFilePath.string());
        mINI::INIStructure ini;

        if (!file.read(ini)) {
            LOG_INFO("Using default settings, no configuration file detected: {}", settingsFilePath.string());
            return;
        }

        if (!ini.has("SC4DisableFpsLimits")) {
            LOG_INFO("Using default settings, section [SC4DisableFpsLimits] missing in {}", settingsFilePath.string());
            return;
        }
        auto section = ini.get("SC4DisableFpsLimits");

        if (!section.has("MaxFPS")) {
            LOG_INFO("MaxFPS not set in {}, defaulting to {}", settingsFilePath.string(), kDefaultMaxFps);
        }
        else {
            unsigned int parsedValue = 0;
            const std::string maxFpsText = section.get("MaxFPS");
            const auto [ptr, ec] =
                std::from_chars(maxFpsText.data(), maxFpsText.data() + maxFpsText.size(), parsedValue);

            if (ec != std::errc() || ptr != maxFpsText.data() + maxFpsText.size()) {
                LOG_ERROR("Invalid MaxFPS value '{}' in {}. Using default {}.", maxFpsText, settingsFilePath.string(),
                          kDefaultMaxFps);
            }
            else if (parsedValue > kMaxMaxFps) {
                LOG_WARN("MaxFPS value {} exceeds {} and has been capped.", parsedValue, kMaxMaxFps);
                maxFps_ = kMaxMaxFps;
            }
            else if (parsedValue < kMinMaxFps) {
                LOG_WARN("MaxFPS value {} is below {} and has been raised.", parsedValue, kMinMaxFps);
                maxFps_ = kMinMaxFps;
            }
            else {
                maxFps_ = static_cast<uint8_t>(parsedValue);
            }
        }

        if (!section.has("LogLevel")) {
            LOG_INFO("LogLevel not set in {}, defaulting to info", settingsFilePath.string());
        }
        else {
            bool validLogLevel = false;
            const std::string logLevelText = section.get("LogLevel");
            logLevel_ = ParseLogLevel(logLevelText, validLogLevel);
            if (!validLogLevel) {
                logLevel_ = kDefaultLogLevel;
                LOG_ERROR("Invalid LogLevel value '{}' in {}. Using default info.", logLevelText,
                          settingsFilePath.string());
            }
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR("Error reading settings file {}: {}", settingsFilePath.string(), e.what());
        maxFps_ = kDefaultMaxFps;
    }
}

uint8_t Settings::GetMaxFps() const noexcept { return maxFps_; }

spdlog::level::level_enum Settings::GetLogLevel() const noexcept { return logLevel_; }
