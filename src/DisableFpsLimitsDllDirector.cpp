#include "Logger.h"
#include "SC4VersionDetection.h"
#include "Settings.h"
#include "version.h"

#include "cIGZCOM.h"
#include "cIGZFrameWork.h"
#include "cRZCOMDllDirector.h"

#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

#include <Windows.h>

static constexpr auto kDisableFpsLimitsDirectorID = 0x63AC6B81;

static constexpr std::string_view PluginSettingsFileName = "SC4DisableFpsLimits.ini";

namespace {
    std::wstring GetModulePath(HMODULE moduleHandle) {
        std::vector<wchar_t> pathBuffer(MAX_PATH);

        while (true) {
            DWORD copiedLength =
                GetModuleFileNameW(moduleHandle, pathBuffer.data(), static_cast<DWORD>(pathBuffer.size()));
            if (copiedLength == 0) {
                throw std::runtime_error("GetModuleFileNameW failed.");
            }
            if (copiedLength < pathBuffer.size() - 1) {
                return std::wstring(pathBuffer.data(), copiedLength);
            }

            pathBuffer.resize(pathBuffer.size() * 2);
        }
    }

    std::filesystem::path GetDllFolderPath() {
        HMODULE moduleHandle = nullptr;
        if (!GetModuleHandleExW(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCWSTR>(&GetDllFolderPath),
                &moduleHandle)) {
            throw std::runtime_error("GetModuleHandleExW failed.");
        }
        const std::filesystem::path temp(GetModulePath(moduleHandle));

        return temp.parent_path();
    }

    void OverwriteMemory(uintptr_t address, uint8_t newValue) {
        DWORD oldProtect;
        // Allow the executable memory to be written to.
        if (!VirtualProtect(reinterpret_cast<LPVOID>(address), sizeof(newValue), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            throw std::runtime_error("VirtualProtect failed.");
        }

        // Patch the memory at the specified address.
        *reinterpret_cast<uint8_t*>(address) = newValue;
    }

    void DisableFpsLimits(uint8_t maxFps) {
        const uint16_t gameVersion = SC4VersionDetection::GetInstance().GetGameVersion();

        if (gameVersion == 641) {
            try {
                // Original instruction:	0xC786840000000f000 (MOV dword ptr [ESI  + 0x84], 0xf)
                // New instruction:			0xC78684000000ff000 (MOV dword ptr [ESI  + 0x84], 0xff)

                LOG_INFO("Attempting to overwrite memory");

                OverwriteMemory(0x70244a, maxFps); // Cheetah speed
                OverwriteMemory(0x702457, maxFps); // Rhino speed
                OverwriteMemory(0x702462, maxFps); // Turtle speed

                LOG_INFO("Disabled the FPS limits during simulation. MaxFPS={}", static_cast<unsigned int>(maxFps));
            }
            catch (const std::exception& e) {
                LOG_ERROR("Failed to disable the FPS limits: {}", e.what());
            }
        }
        else {
            LOG_ERROR("Unable to disable the FPS limits. Requires game version 641, found game version {}.",
                      gameVersion);
        }
    }
} // namespace

class DisableFpsLimitsDllDirector final : public cRZCOMDllDirector {
public:
    DisableFpsLimitsDllDirector() {
        const std::filesystem::path dllFolderPath = GetDllFolderPath();
        Logger::Initialize("SC4DisableFpsLimits", dllFolderPath);
        LOG_INFO("SC4DisableFpsLimits v{} loaded.", PLUGIN_VERSION_STR);

        std::filesystem::path settingsFilePath = dllFolderPath;
        settingsFilePath /= PluginSettingsFileName;
        settings_.Load(settingsFilePath);
        Logger::SetLevel(settings_.GetLogLevel());
        LOG_INFO("Configured settings: MaxFPS={}, LogLevel={}", settings_.GetMaxFps(),
                 spdlog::level::to_short_c_str(settings_.GetLogLevel()));
    }

    [[nodiscard]] uint32_t GetDirectorID() const override { return kDisableFpsLimitsDirectorID; }

    bool OnStart(cIGZCOM* pCOM) override {
        DisableFpsLimits(settings_.GetMaxFps());

        return true;
    }

private:
    Settings settings_;
};

cRZCOMDllDirector* RZGetCOMDllDirector() {
    static DisableFpsLimitsDllDirector sDirector;
    return &sDirector;
}
