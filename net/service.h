#pragma once

namespace protocol
{
	/* @brief   Not a legit RPC, but it does run functions from other processes' memory space */
	namespace rpc
	{
		struct frame_t
        {
            // Data size
            static constexpr size_t dataMaxSize = 7;

            struct bitshift
            {
                static constexpr uint8_t funcId = 0;
                static constexpr uint8_t uniqueId = 16;
            };

            frame_t() = delete;

            explicit frame_t(const ULONG id, std::vector<ULONG> data) : Id(id) {
                ASSERT(data.size() <= dataMaxSize);
                data.resize(dataMaxSize);
                for (int i = 0; i < data.size(); i++) {
                    Data[i] = static_cast<ULONG>(data[i]);
                }
            }

            explicit frame_t(const ULONG id, ULONG* data, const size_t size = dataMaxSize) : Id(id) {
                this->setData(data, size);
            }

            void setData(ULONG* data, const size_t size = dataMaxSize) {
                ASSERT(size <= dataMaxSize);
                memcpy(Data, data, size * sizeof(ULONG));
            }

            ULONG Id;
            ULONG Data[dataMaxSize];
        };

		template <class T>
		class service
		{
		public:
			service() = delete;
			
			explicit service(frame_t* in, frame_t* out) : in_(in), out_(out) {}

			template<typename T, typename = typename std::enable_if<!std::is_same<T, frame_t*>::value>::type>
			explicit service(T* in, T* out) : in_(reinterpret_cast<frame_t*>(in)), out_(reinterpret_cast<frame_t*>(out)) {}
			
			virtual ~service() = default;
			
			void write(frame_t data) {
				in_->Id = (data.Id & 0xFFFF); // | generateUniqueID();
				in_->setData(data.Data);
			}

			frame_t read() const {
				return *out_;
			}

		protected:
			static ULONG& uniqueID() {
				static ULONG obj = 0;
				return obj;
			}

			const ULONG generateUniqueID() {
				return ((uniqueID()++ % ULONG_MAX) << frame_t::bitshift::uniqueId);
			}

			frame_t* in_;
			frame_t* out_;
		};
	}
}


/*
//// DEPRECATED, but leaving it here in case of future use

// template <typename T, typename Ret, typename... Args>
// void assign(const int id, T* instance, Ret(T*::*func)(Args...)) {
// mapFunc_[id] = [=](Args... args) {
// (instance->*func)(args...);
// };
// }

// template <typename Ret, typename... Args>
// Ret call(const int id, Args... args) {
// auto it = mapFunc.find(id);
// if (it != mapFunc.end()) {
// auto func = it->second;
// return func(args...);
// }
// }

// /*
// template <typename F>
// void assign(const uint8_t id, F func) {
// funcMap_[id] = reinterpret_cast<void*>(func);
// }

// template<typename... Args>
// auto call(const uint8_t id, Args... funcArgs) -> typename std::invoke_result<decltype(reinterpret_cast<funcArgs*>(nullptr))>::type { //std::declval<F>()(funcArgs...)) {
// auto it = funcMap_.find(id);
// if (it != funcMap_.end()) {
// using F = decltype(reinterpret_cast<funcArgs*>(nullptr));
// F func = reinterpret_cast<F>(it->second);
// return func(funcArgs...);
// }
// return status_t::FUNC_NOT_FOUND;
// }

// // TwinCAT���� ���������� �ڵ������ϴ� ������ Ÿ������ ���� const_cast�� ����� �� �ۿ� ����.
// // 5 * default_cycle(ms) timeout
// inline rpc::frame_t read(const rpc::frame_t data) {
// static rpc::frame_t prev = rpc::frame_t{ const_cast<char*>(&protocol::rpc::status::not_received), 0 };
// static int timerCount = 0;

// // write
// if (*prev.Id != *data.Id) {
// (void)write(data);
// prev = data;
// }

// // if received id is same as the id sent, successfully received the updated data
// if (*data.Id == *in_.Id) {
// timerCount = 0;
// return out_;
// }

// // timeout
// timerCount++;
// return (timerCount % 5) ? rpc::frame_t{ const_cast<char*>(&protocol::rpc::status::timeout), 0 } : rpc::frame_t{ const_cast<char*>(&protocol::rpc::status::not_received), 0 };
// }

// inline char write(const rpc::frame_t data) {
// static rpc::frame_t prev = rpc::frame_t{ const_cast<char*>(&protocol::rpc::status::not_received), 0 };
// if (prev.Id != data.Id) {
// in_ = data;
// }
// return (*data.Id == *in_.Id) ? protocol::rpc::status::received : protocol::rpc::status::not_received;
// }

// void run_server() {
// read();
// }
*/