#pragma once

// IO
#define LED_MASK    0xE0000
#define BUTTON_MASK 0x10000

// RPC
namespace protocol
{
    namespace rpc
    {
        namespace id
        {
            static constexpr ULONG none = 0x00;

            struct led {
                static constexpr ULONG set = 0x08;
                static constexpr ULONG status = 0x09;
            };

            struct btn {
                static constexpr ULONG status = 0x010;
            };
        }

        namespace param
        {
            struct led {
                struct mode {
                    static constexpr ULONG blink = 0x00;
                    static constexpr ULONG solid = 0x01;
                };

                struct color {
                    static constexpr ULONG none = 0x00;
                    static constexpr ULONG red = 0x01;
                    static constexpr ULONG green = 0x02;
                    static constexpr ULONG blue = 0x04;
                    static constexpr ULONG yellow = red | green;
                    static constexpr ULONG white = red | green | blue;
                };
            };
        }
    }
}