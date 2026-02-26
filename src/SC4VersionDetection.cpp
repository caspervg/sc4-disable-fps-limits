#include "SC4VersionDetection.h"
#include <Windows.h>
#include <string>
#include <vector>

namespace {
    std::wstring GetModulePath(HMODULE moduleHandle) {
        std::vector<wchar_t> pathBuffer(MAX_PATH);

        while (true) {
            DWORD copiedLength =
                GetModuleFileNameW(moduleHandle, pathBuffer.data(), static_cast<DWORD>(pathBuffer.size()));
            if (copiedLength == 0) {
                return {};
            }
            if (copiedLength < pathBuffer.size() - 1) {
                return std::wstring(pathBuffer.data(), copiedLength);
            }

            pathBuffer.resize(pathBuffer.size() * 2);
        }
    }

    uint64_t GetAssemblyVersion(HMODULE hModule) {
        std::wstring szVersionFile = GetModulePath(hModule);
        if (szVersionFile.empty()) {
            return 0;
        }

        // http://stackoverflow.com/a/940743
        DWORD verHandle = 0;
        UINT size = 0;
        DWORD verSize = GetFileVersionInfoSizeW(szVersionFile.c_str(), &verHandle);

        if (verSize > 0) {
            std::vector<BYTE> verData(verSize);
            LPBYTE lpBuffer = nullptr;

            if (GetFileVersionInfoW(szVersionFile.c_str(), 0, verSize, verData.data()) &&
                VerQueryValueW(verData.data(), L"\\", reinterpret_cast<LPVOID*>(&lpBuffer), &size) && size > 0) {
                VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
                if (verInfo->dwSignature == 0xfeef04bd) {
                    uint64_t qwValue = (uint64_t)verInfo->dwFileVersionMS << 32;
                    qwValue |= verInfo->dwFileVersionLS;

                    return qwValue;
                }
            }
        }

        return 0;
    }

    uint16_t DetermineGameVersion() {
        uint64_t qwFileVersion = GetAssemblyVersion(nullptr);
        uint16_t wMajorVer = (qwFileVersion >> 48) & 0xFFFF;
        uint16_t wMinorVer = (qwFileVersion >> 32) & 0xFFFF;
        uint16_t wRevision = (qwFileVersion >> 16) & 0xFFFF;
        uint16_t wBuildNum = qwFileVersion & 0xFFFF;

        uint16_t nGameVersion = 0;

        // 1.1.x.x
        if (qwFileVersion > 0 && wMajorVer == 1 && wMinorVer == 1) {
            nGameVersion = wRevision;
        }
        else {
            nGameVersion = 0;
        }

        // Fall back to a less accurate detection mechanism
        if (nGameVersion == 0) {
            uint8_t uSentinel = *(uint8_t*)0x6E5000;

            switch (uSentinel) {
            case 0x8B:
                nGameVersion = 610; // Can't distinguish from 613
                break;
            case 0xFF:
                nGameVersion = 638;
                break;
            case 0x24:
                nGameVersion = 640;
                break;
            case 0x0F:
                nGameVersion = 641;
                break;
            default:
                nGameVersion = 0;
                break;
            }
        }

        return nGameVersion;
    }
} // namespace

SC4VersionDetection& SC4VersionDetection::GetInstance() {
    static SC4VersionDetection instance;

    return instance;
}

uint16_t SC4VersionDetection::GetGameVersion() const noexcept { return gameVersion_; }

SC4VersionDetection::SC4VersionDetection() : gameVersion_(DetermineGameVersion()) {}
