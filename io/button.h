#pragma once

#include "base.h"

namespace io
{
	class button : public io::in<ULONG>
	{
	public:
		button() = delete;
		explicit button(digital_t<ULONG> digitalIn) : in(digitalIn), prev_(0) {}
		~button() {}

		bool isEdge() {
			bool res = prev_ ^ read();
			prev_ = read();
			return res;
		}

	protected:
		ULONG prev_;
	};
}
