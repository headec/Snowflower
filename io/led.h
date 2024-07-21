#pragma once

#include "base.h"

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
		
		template <typename M, typename C, 
				  typename = typename std::enable_if<std::is_integral<M>::value && std::is_integral<C>::value>::type>
		void set(M mode, C color) {
			mode_ = static_cast<mode_t>(mode);
			*data_.digital_ = color_ = static_cast<color_t>(color);
		}

	protected:
		mode_t mode_;
		color_t color_;
		unsigned int cycle_;

	private:
		static constexpr int default_cycle_ = 50;
	};
}