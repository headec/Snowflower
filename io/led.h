#pragma once

#include <unordered_map>

#include "base.h"

#include "net/define.h"

namespace io
{
	class led : public io::out<ULONG>
	{
	public:
		enum color_t : ULONG {
			none = 0,
			red = 0x20000,
			green = 0x40000,
			blue = 0x80000,

			yellow = red | green,
			white = red | green | blue
		};

		enum class mode_t : char {
			blink,
			solid
		};

		led() = delete;
		explicit led(digital_t<ULONG> digitalOut, int _cycle = default_cycle_) : out(digitalOut), cycle_(_cycle) { write(color_t::none); }
		~led() {}

		void cyclicUpdate() {
			static unsigned int counter = 0;

			do {
				if (mode_ == mode_t::blink) {
					counter < (cycle_ / 2) ? write(color_) : write(color_t::none);
					++counter %= cycle_ + 1;
					break;
				}
				counter = 0;
			} while (false);
		}

		void set(mode_t mode, color_t color) {
			mode_ = mode;
			*data_.digital_ = color_ = color;
		}

		// From RPC
		void set(ULONG mode, ULONG color) {
			mode_ = static_cast<mode_t>(modeMap[mode]);
			*data_.digital_ = color_ = static_cast<color_t>(colorMap[color]);
		}

	protected:
		mode_t mode_;
		color_t color_;
		unsigned int cycle_;

		std::unordered_map<ULONG, mode_t> modeMap = {
			{ protocol::rpc::param::led::mode::blink, mode_t::blink },
			{ protocol::rpc::param::led::mode::solid, mode_t::solid }
		};

		std::unordered_map<ULONG, color_t> colorMap = {
			{ protocol::rpc::param::led::color::none, color_t::none },
			{ protocol::rpc::param::led::color::red, color_t::red },
			{ protocol::rpc::param::led::color::green, color_t::blue },
			{ protocol::rpc::param::led::color::yellow, color_t::yellow },
			{ protocol::rpc::param::led::color::white, color_t::white }
		};
	private:
		static constexpr int default_cycle_ = 50;
	};
}