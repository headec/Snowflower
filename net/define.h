#pragma once

// IO
#define LED_MASK    0xE0000
#define BUTTON_MASK 0x10000

// RPC
namespace protocol
{
    namespace rpc
    {
        namespace funcId
        {
            static constexpr ULONG none = 0x00;

            struct {
                static constexpr ULONG set = 0x08;
                static constexpr ULONG status = 0x09;
            } led;

            struct {
                static constexpr ULONG status = 0x010;
            } btn;
        }
    }
}