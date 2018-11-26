#include "Singleton.h"

template <class T>
 std::unique_ptr<T> Singleton<T>::getInstance() {
	 static std::unique_ptr<T> _pInstance = std::make_unique<T>;
	 return _pInstance;
}