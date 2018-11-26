#pragma once

template <typename T> class Singleton {
protected:
	Singleton() {}
public:
	virtual ~Singleton() {}

	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;

public:
	static std::shared_ptr<T> getInstance() {
		auto ret_ptr = instance_.lock();
		if (!ret_ptr) {
			ret_ptr = std::shared_ptr<T>(new T{});
			instance_ = std::weak_ptr<T>(ret_ptr);
			return ret_ptr;
		}

		return instance_.lock();
	}

private:
	//using allocator = typename singleton_allocator<T>::type;
	static std::weak_ptr<T> instance_;
}; // class singleton


template <typename T> std::weak_ptr<T>  Singleton<T>::instance_;