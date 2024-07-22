#pragma once

#include "elmo.h"
#include "net/protocol.h"

namespace slv
{
	namespace cmd
	{
		static constexpr uint16_t
			// controlword
			sp	 = SET_BIT(4),
			sp_i = SET_BIT(5),
			r	 = SET_BIT(6),
			h	 = SET_BIT(8),
			b	 = SET_BIT(9),

			// command
			setpoint	 = enable_op | sp,
			setpoint_imd = setpoint  | sp_i,
			emg_halt	 = h,
			halt		 = enable_op | h,
			relative	 = r,
			blended		 = b;
	}

	class elmopp final : public elmo
	{
	public:
		struct setting_t {
			ULONG* vel;
			ULONG* accel;
			ULONG* deaccel;
		};

		elmopp() {}
		elmopp(mode_t m, setting_t s, type_t t) : elmo(m, t), set_(s) {}
		~elmopp() {}

		/* @warning	Must use this function when the base constructor is invoked;
		 *			otherwise, the object will be unconfigured
		 */
		void configure(mode_t m, setting_t s, type_t t) {
			mode_.mode = m.mode;

			set_.vel = s.vel;
			set_.accel = s.accel;
			set_.deaccel = s.deaccel;

			val_.controlword = t.controlword;
			val_.statusword = t.statusword;
			val_.targetPos = t.targetPos;
			val_.actualPos = t.actualPos;
		}

		void initialize(mode_t m, setting_t s) {
			*mode_.mode = *m.mode;

			*set_.vel = *s.vel;
			*set_.accel = *s.accel;
			*set_.deaccel = *s.deaccel;
		}

		void enable() {
			if (!isStatus(res::enable_op)) {
				if (isStatus(res::switch_on_disabled)) {
					setCommand(cmd::shutdown);
				}
				else if (isStatus(res::rdy_to_switch_on) || isStatus(res::switch_on)) {
					setCommand(cmd::enable_op);
				}
				else {
					setCommand(cmd::fault_reset);
				}
			}
		}

		void tryMove() {
			if (!isReached()) {
				setCommand(cmd::enable_op);
			}
		}
		
		void updatePos(protocol::move_t move) {
			if (isReached() || move.immediate) {
				*val_.targetPos = move.target_pos;
				setCommand(cmd::setpoint_imd);
			}
		}

		void stop() {
			if (!isCommand(cmd::halt)) {
				setCommand(cmd::halt);
			}
		}

		void disable() {
			if (!isCommand(cmd::emg_halt)) {
				setCommand(cmd::emg_halt);
			}
		}

		void reset() {
			if (!isCommand(cmd::fault_reset))
				setCommand(cmd::fault_reset);
		}

		bool isEnabled() const {
			return isStatus(res::enable_op);
		}

		bool isReached() const {
			return isStatus(res::t_r);
		}

	protected:
		setting_t set_;
	};
}