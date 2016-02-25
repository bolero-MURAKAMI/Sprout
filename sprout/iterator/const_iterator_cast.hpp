/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_CONST_ITERATOR_CAST_HPP
#define SPROUT_ITERATOR_CONST_ITERATOR_CAST_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout {
	//
	// is_const_iterator_cast_convertible
	//
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible
		: public sprout::false_type
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From, To const>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From, To volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From, To const volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const, To>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const, To const>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const, To volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const, To const volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From volatile, To>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From volatile, To const>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From volatile, To volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From volatile, To const volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const volatile, To>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const volatile, To const>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const volatile, To volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From const volatile, To const volatile>
		: public sprout::is_const_iterator_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible<From*, To*>
		: public std::is_same<typename std::remove_const<From>::type, typename std::remove_const<To>::type>
	{};

//	//
//	// pointer_add_const
//	//
//	template<typename T>
//	struct pointer_add_const
//		: public std::add_const<T>
//	{};
//	template<typename T>
//	struct pointer_add_const<T*>
//		: public sprout::identity<typename std::add_const<T>::type*>
//	{};
}	// namespace sprout

namespace sprout_adl {
	template<typename To>
	sprout::not_found_via_adl const_iterator_conversion(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<
			typename T,
			typename U,
			typename sprout::enabler_if<sprout::is_const_iterator_cast_convertible<U*, T>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_iterator_conversion(U* it) {
			return const_cast<T>(it);
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename To, typename From>
	inline SPROUT_CONSTEXPR To
	const_iterator_cast(From const& it) {
		using sprout::iterator_detail::const_iterator_conversion;
		using sprout_adl::const_iterator_conversion;
		return const_iterator_conversion<To>(it);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// const_iterator_cast
	//
	template<typename To, typename From>
	inline SPROUT_CONSTEXPR To
	const_iterator_cast(From const& it) {
		return sprout_iterator_detail::const_iterator_cast<To>(it);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_CONST_ITERATOR_CAST_HPP
