#pragma once

#include <cstdint>
#include <filesystem>

#include <spdlog/common.h>

class Settings {
public:
    Settings();

    void Load(const std::filesystem::path& settingsFilePath);

    [[nodiscard]] uint8_t GetMaxFps() const noexcept;
    [[nodiscard]] spdlog::level::level_enum GetLogLevel() const noexcept;

private:
    uint8_t maxFps_;
    spdlog::level::level_enum logLevel_;
};
