#pragma once
#include <cstdint>

class SC4VersionDetection {
public:
    static SC4VersionDetection& GetInstance();

    [[nodiscard]] uint16_t GetGameVersion() const noexcept;

private:
    SC4VersionDetection();

    uint16_t gameVersion_;
};
