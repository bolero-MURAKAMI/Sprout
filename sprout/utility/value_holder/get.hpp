#ifndef SPROUT_UTILITY_VALUE_HOLDER_GET_HPP
#define SPROUT_UTILITY_VALUE_HOLDER_GET_HPP

#include <sprout/config.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	//
	// get
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::reference_type
	get(sprout::value_holder<T>& x) {
		return sprout::value_holder<T>::get(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::rvalue_reference
	get(sprout::value_holder<T>&& x) {
		return sprout::value_holder<T>::get(sprout::move(x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::reference_const_type
	get(sprout::value_holder<T> const& x) {
		return sprout::value_holder<T>::get(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::pointer_type
	get(sprout::value_holder<T>* x) {
		return sprout::value_holder<T>::get_pointer(*x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::pointer_const_type
	get(sprout::value_holder<T> const* x) {
		return sprout::value_holder<T>::get_pointer(*x);
	}

	//
	// get_pointer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::pointer_type
	get_pointer(sprout::value_holder<T>& x) {
		return sprout::value_holder<T>::get_pointer(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::pointer_type
	get_pointer(sprout::value_holder<T>&& x) {
		return sprout::value_holder<T>::get_pointer(sprout::move(x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::pointer_const_type
	get_pointer(sprout::value_holder<T> const& x) {
		return sprout::value_holder<T>::get_pointer(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_VALUE_HOLDER_GET_HPP
