#ifndef SPROUT_OPTIONAL_GET_HPP
#define SPROUT_OPTIONAL_GET_HPP

#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>

namespace sprout {
	//
	// get
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::reference_const_type
	get(sprout::optional<T> const& x) {
		return x.get();
	}
	template<typename T>
	inline typename sprout::optional<T>::reference_type
	get(sprout::optional<T>& x) {
		return x.get();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::pointer_const_type
	get(sprout::optional<T> const* x) {
		return x->get_pointer();
	}
	template<typename T>
	inline typename sprout::optional<T>::pointer_type
	get(sprout::optional<T>* x) {
		return x->get_pointer();
	}

	//
	// get_pointer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::pointer_const_type
	get_pointer(sprout::optional<T> const& x) {
		return x.get_pointer();
	}
	template<typename T>
	inline typename sprout::optional<T>::pointer_type
	get_pointer(sprout::optional<T>& x) {
		return x.get_pointer();
	}

	//
	// get_optional_value_or
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::reference_const_type
	get_optional_value_or(sprout::optional<T> const& x, typename sprout::optional<T>::reference_const_type v) {
		return x.get_value_or(v);
	}
	template<typename T>
	inline typename sprout::optional<T>::reference_type
	get_optional_value_or(sprout::optional<T>& x, typename sprout::optional<T>::reference_type v) {
		return x.get_value_or(v);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_GET_HPP
