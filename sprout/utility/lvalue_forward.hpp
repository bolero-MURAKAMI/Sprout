#ifndef SPROUT_UTILITY_LVALUE_FORWARD_HPP
#define SPROUT_UTILITY_LVALUE_FORWARD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/as_lvalue.hpp>
#include <sprout/type_traits.hpp>

namespace sprout {
	//
	// lvalue_forward
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::lvalue_reference<T>::type
	lvalue_forward(typename std::remove_reference<T>::type& t) {
		return sprout::as_lvalue(sprout::forward<T>(t));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::lvalue_reference<T>::type
	lvalue_forward(typename std::remove_reference<T>::type&& t) = delete;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_LVALUE_FORWARD_HPP
