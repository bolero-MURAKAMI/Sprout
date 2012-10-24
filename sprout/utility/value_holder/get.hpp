#ifndef SPROUT_UTILITY_VALUE_HOLDER_GET_HPP
#define SPROUT_UTILITY_VALUE_HOLDER_GET_HPP

#include <sprout/config.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>

namespace sprout {
	//
	// get
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::reference_const_type
	get(sprout::value_holder<T> const& x) {
		return x.get();
	}
	template<typename T>
	inline typename sprout::value_holder<T>::reference_type
	get(sprout::value_holder<T>& x) {
		return x.get();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::pointer_const_type
	get(sprout::value_holder<T> const* x) {
		return x->get_pointer();
	}
	template<typename T>
	inline typename sprout::value_holder<T>::pointer_type
	get(sprout::value_holder<T>* x) {
		return x->get_pointer();
	}

	//
	// get_pointer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::value_holder<T>::pointer_const_type
	get_pointer(sprout::value_holder<T> const& x) {
		return x.get_pointer();
	}
	template<typename T>
	inline typename sprout::value_holder<T>::pointer_type
	get_pointer(sprout::value_holder<T>& x) {
		return x.get_pointer();
	}
}	// namespace sprout

#endif // #ifndef SPROUT_UTILITY_VALUE_HOLDER_GET_HPP
