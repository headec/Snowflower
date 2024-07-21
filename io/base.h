#pragma once

namespace io
{
	template <typename IO>
	struct digital_t { IO* digital_; IO mask_; digital_t(IO* digital, IO mask) : digital_(digital), mask_(mask) {} };

	template <class T>
	class in
	{
	public:
		in() = delete;
		explicit in(digital_t<T> data) : data_(data) {}
		virtual ~in() = default;

		virtual inline T read() const {
			return *data_.digital_ & data_.mask_;
		}

	protected:
		digital_t<T> data_;
	};

	template <class T>
	class out
	{
	public:
		out() = delete;
		explicit out(digital_t<T> data) : data_(data) {}
		virtual ~out() = default;

		virtual inline T read() const {
			return *data_.digital_ & data_.mask_;
		}

		virtual inline void write(T data) {
			*data_.digital_ = (*data_.digital_ & ~data_.mask_) | data;
		}

	protected:
		digital_t<T> data_;
	};
}