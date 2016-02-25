/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_GET_HPP
#define SPROUT_OPTIONAL_GET_HPP

#include <sprout/config.hpp>
#include <sprout/optional/optional.hpp>

namespace sprout {
	//
	// get
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::reference_type
	get(sprout::optional<T>& x) {
		return sprout::optional<T>::get(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::rvalue_reference_type
	get(sprout::optional<T>&& x) {
		return sprout::optional<T>::get(sprout::move(x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::reference_const_type
	get(sprout::optional<T> const& x) {
		return sprout::optional<T>::get(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::pointer_type
	get(sprout::optional<T>* x) {
		return sprout::optional<T>::get_pointer(*x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::pointer_const_type
	get(sprout::optional<T> const* x) {
		return sprout::optional<T>::get_pointer(*x);
	}

	//
	// get_pointer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::pointer_type
	get_pointer(sprout::optional<T>& x) {
		return sprout::optional<T>::get_pointer(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::pointer_type
	get_pointer(sprout::optional<T>&& x) {
		return sprout::optional<T>::get_pointer(sprout::move(x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::pointer_const_type
	get_pointer(sprout::optional<T> const& x) {
		return sprout::optional<T>::get_pointer(x);
	}

	//
	// get_value_or
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::reference_type
	get_value_or(sprout::optional<T>& x, typename sprout::optional<T>::reference_type v) {
		return sprout::optional<T>::get_value_or(x, v);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::rvalue_reference_type
	get_value_or(sprout::optional<T>&& x, typename sprout::optional<T>::rvalue_reference_type v) {
		return sprout::optional<T>::get_value_or(sprout::move(x), static_cast<typename sprout::optional<T>::rvalue_reference_type>(v));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::optional<T>::reference_const_type
	get_value_or(sprout::optional<T> const& x, typename sprout::optional<T>::reference_const_type v) {
		return sprout::optional<T>::get_value_or(x, v);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_GET_HPP
