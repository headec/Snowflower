#pragma once

namespace protocol
{
	enum class btn_t : char
	{
		none,

		connect,
		disconnect,

		idle,
		run,
		emeregency,
		reset,

		move,
		halt,

		bending,
		all_motors,
		translation
	};

	enum class state_t : char
	{
		disconnected,
		init,
		idle,
		ready,
		active,
		emergency,
		recovery,
		error
	};

	struct setting_t
	{
		char mode;
		ULONG vel;
		ULONG accel;
		ULONG deaccel;
	};

	struct move_t
	{
		bool immediate;
		LONG target_pos;
	};
}
