#pragma once

#include "net/protocol.h"
#include <unordered_map>

namespace ads
{
	enum class error_t {
		request_fail,
		response_fail
	};

	enum class offset {
		state,
		setting,
		move,
		event
	};

	class elmo {
	public:
		elmo() : debug_(false) {}
		elmo(PAmsAddr pAddr) : pAddr_(pAddr), debug_(false) {}
		~elmo() {}

		virtual int initialize() {
			char state[]	= { "Snowflower_Obj1 (Module1).State" };
			char setting[]	= { "Snowflower_Obj1 (Module1).Setting" };
			char pos[]		= { "Snowflower_Obj1 (Module1).Move" };
			char event[]	= { "Snowflower_Obj1 (Module1).Event" };

			checkError(AdsSyncReadWriteReq(pAddr_, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(baseAddr_[offset::state]), &baseAddr_[offset::state], sizeof(state), state));
			checkError(AdsSyncReadWriteReq(pAddr_, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(baseAddr_[offset::setting]), &baseAddr_[offset::setting], sizeof(setting), setting));
			checkError(AdsSyncReadWriteReq(pAddr_, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(baseAddr_[offset::move]), &baseAddr_[offset::move], sizeof(pos), pos));
			checkError(AdsSyncReadWriteReq(pAddr_, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(baseAddr_[offset::event]), &baseAddr_[offset::event], sizeof(event), event));
		
			return getError() ? -1 : 0;
		}


		template <class T>
		long send(offset what, T type) {
			long res = writeADS(baseAddr_[what], sizeof(type), &type);
			if (res != 0) throw error_t::request_fail;
			return res;
		}

		template <class T>
		long receive(offset what, T& data) {
			long res = readADS(baseAddr_[what], sizeof(data), &data);
			if (res != 0) throw error_t::response_fail;
			return res;
		}

	protected:
		long writeADS(unsigned long offset, unsigned long size, void* data) {
			checkError(AdsSyncWriteReq(pAddr_, ADSIGRP_SYM_VALBYHND, offset, size, data));
			return getError();
		}

		long readADS(unsigned long offset, unsigned long size, void* data) {
			checkError(AdsSyncReadReq(pAddr_, ADSIGRP_SYM_VALBYHND, offset, size, data));
			return getError();
		}

		void checkError(const long nErr) {
			error_.push_back(nErr);
		}

		// returns the latest error number if multiple errors
		long getError() {
			long res = 0;
			for (const long& nErr : error_) {
				if (nErr) {
					res = nErr;
					if (debug_) {
						CString sErr;
						sErr.Format(_T("%d"), nErr);
						CString error_msg = _T("Error number: ") + sErr;
						AfxMessageBox(error_msg);
					}
				}
			}
			error_.clear();
			return res;
		}

		PAmsAddr pAddr_;
		std::vector<long> error_;
		std::unordered_map<ads::offset, unsigned long> baseAddr_;
		bool debug_;
	};
}