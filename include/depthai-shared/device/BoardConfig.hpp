#pragma once

// std
#include <cstdint>
#include <unordered_map>

// project
#include "depthai-shared/common/UsbSpeed.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/utility/Serialization.hpp"
#include "depthai-shared/xlink/XLinkConstants.hpp"

namespace dai {

constexpr static uint32_t BOARD_CONFIG_MAGIC1 = 0x78010000U;
constexpr static uint32_t BOARD_CONFIG_MAGIC2 = 0x21ea17e6U;

struct BoardConfig {
    // USB related config
    struct USB {
        uint16_t vid = 0x03e7, pid = 0xf63b;
        uint16_t flashBootedVid = 0x03e7, flashBootedPid = 0xf63d;
        UsbSpeed maxSpeed = UsbSpeed::SUPER;
    };

    USB usb;

    /// Network configuration
    struct Network {
        /// Network MTU, 0 is auto (usually 1500 for Ethernet) or forwarded
        /// from bootloader (not yet implemented there).
        /// Note: not advised to increase past 1500 for now
        uint16_t mtu = 0;
        /// Sets the `TCP_NODELAY` option for XLink TCP sockets (disable Nagle's algorithm),
        /// reducing latency at the expense of a small hit for max throughput. Default is `true`
        bool xlinkTcpNoDelay = true;
    };

    Network network;

    /// Optional list of FreeBSD sysctl parameters to be set (system, network, etc.).
    /// For example: "net.inet.tcp.delayed_ack=0" (this one is also set by default)
    std::vector<std::string> sysctl;

    // Watchdog config
    tl::optional<uint32_t> watchdogTimeoutMs;
    tl::optional<uint32_t> watchdogInitialDelayMs;

    // GPIO config
    struct GPIO {
        enum Mode : std::int8_t { ALT_MODE_0 = 0, ALT_MODE_1, ALT_MODE_2, ALT_MODE_3, ALT_MODE_4, ALT_MODE_5, ALT_MODE_6, DIRECT };
        Mode mode = Mode::DIRECT;
        enum Direction : std::int8_t { INPUT = 0, OUTPUT = 1 };
        Direction direction = Direction::INPUT;
        enum Level : std::int8_t { LOW = 0, HIGH = 1 };
        Level level = Level::LOW;
        enum Pull : std::int8_t { NO_PULL = 0, PULL_UP = 1, PULL_DOWN = 2, BUS_KEEPER = 3 };
        Pull pull = Pull::NO_PULL;
        /// Drive strength in mA (2, 4, 8 and 12mA)
        enum Drive : std::int8_t { MA_2 = 2, MA_4 = 4, MA_8 = 8, MA_12 = 12 };
        Drive drive = MA_2;
        bool schmitt = false, slewFast = false;
        GPIO() = default;
        GPIO(Direction direction) : direction(direction) {}
        GPIO(Direction direction, Level level) : direction(direction), level(level) {}
        GPIO(Direction direction, Level level, Pull pull) : direction(direction), level(level), pull(pull) {}
        GPIO(Direction direction, Mode mode) : mode(mode), direction(direction) {}
        GPIO(Direction direction, Mode mode, Pull pull) : mode(mode), direction(direction), pull(pull) {}
    };
    std::unordered_map<std::int8_t, GPIO> gpio;

    // Uart config

    /// UART instance config
    struct UART {
        // TBD
        // std::int8_t tx, rx;
        std::int8_t tmp;
    };
    /// UART instance map
    std::unordered_map<std::int8_t, UART> uart;

    // PCIe config
    tl::optional<bool> pcieInternalClock;

    // USB3 phy config
    tl::optional<bool> usb3PhyInternalClock;
};

DEPTHAI_SERIALIZE_EXT(BoardConfig::USB, vid, pid, flashBootedVid, flashBootedPid, maxSpeed);
DEPTHAI_SERIALIZE_EXT(BoardConfig::Network, mtu, xlinkTcpNoDelay);
DEPTHAI_SERIALIZE_EXT(BoardConfig::GPIO, mode, direction, level, pull, drive, schmitt, slewFast);
DEPTHAI_SERIALIZE_EXT(BoardConfig::UART, tmp);
DEPTHAI_SERIALIZE_EXT(BoardConfig, usb, network, sysctl, watchdogTimeoutMs, watchdogInitialDelayMs, gpio, uart, pcieInternalClock, usb3PhyInternalClock);

}  // namespace dai
