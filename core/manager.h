#pragma once

#include <vector>
#include <unordered_set>

#include "elmopp.h"

#ifndef MAX_N_ELMO
#define MAX_N_ELMO 12 // default
#endif

// Contemplating removing this class ...
template <class T>
class manager
{
public:
	manager() {}
	manager(std::vector<T*> objs) : objs_(objs) {}
	~manager() { close(); }
	
	void attach(T* obj, int max_obj = MAX_N_ELMO) {
		if (objs_.size() <= max_obj) {
			objs_.push_back(obj);
		}
	}

	bool is(bool (*f)(T*), std::unordered_set<int>* index = nullptr) {
		bool res = true;
		if (index) {
			for (const auto& i : *index) { res = res && f(objs_[i]); }
		}
		else {
			for (const auto& obj : objs_) {	res = res && f(obj); }
		}
		return res;
	}

	bool isAtLeastOneTrue(bool(*f)(T*), std::unordered_set<int>* index = nullptr) {
		if (index) {
			for (const auto& i : *index) { if(f(objs_[i])) return true; }
		}
		else {
			for (const auto& obj : objs_) { if(f(obj)) return true; }
		}
		return false;
	}

	template <typename F>
	void run(F&& f, std::unordered_set<int>* index = nullptr) {
		if (index) {
			for (const auto& i : *index) { f(objs_[i]); }
		}
		else {
			for (const auto& obj : objs_) { f(obj); }
		}
	}

	void close() {
		objs_.clear();
	}

protected:
	std::vector<T*> objs_;
};