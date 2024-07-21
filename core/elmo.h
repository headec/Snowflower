#pragma once

#define SET_BIT(n) 1 << n
#define CLR_BIT(n) 0 << n

namespace slv
{	
	namespace cmd
	{
		static constexpr USHORT
			// controlword
			s   = SET_BIT(0),
			v   = SET_BIT(1),
			q   = SET_BIT(2),
			op  = SET_BIT(3),
			f_r = SET_BIT(7),

			// command
			shutdown		= v | q,
			switch_on		= v | q | s,
			enable_op		= v | q | s | op,
			disable_op		= v | q | s,
			disable_voltage = CLR_BIT(1),
			fault_reset		= f_r;
	}

	namespace res
	{
		static constexpr USHORT
			// statusword
			s_r		= SET_BIT(0),
			s		= SET_BIT(1),
			op		= SET_BIT(2),
			f		= SET_BIT(3),
			v		= SET_BIT(4),
			q		= SET_BIT(5),
			s_d		= SET_BIT(6),
			w		= SET_BIT(7),
			t_r  	= SET_BIT(10),

			// state
			nrdy_to_switch_on	= 0,
			switch_on_disabled	= s_d,
			rdy_to_switch_on	= s_r | q,
			switch_on			= s_r | q | s,
			enable_op			= s_r | q | s | op,
			fault_rxn_active	= s_r | s | op | f,
			fault				= f;
	}

	class elmo
	{
	public:
		struct mode_t {
			char* mode;
		};

		struct type_t {
			USHORT* controlword;
			USHORT* statusword;
			LONG* actualPos;
			LONG* targetPos;
		};

		elmo() {}
		elmo(mode_t m, type_t v) : mode_(m), val_(v) {}
		~elmo() {}

		bool hasError() { return isStatus(slv::res::fault); }

	protected:
		// boolean
		bool isCommand(USHORT cmd) const { return *val_.controlword == cmd; }
		bool isStatus(USHORT which) const { return (*val_.statusword & which) == which; }

		// setter
		void setCommand(USHORT cmd) { *val_.controlword = cmd; }

		// variable
		mode_t mode_;
		type_t val_;
	};
}