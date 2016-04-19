/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_CONST_REFERENCE_CAST_HPP
#define SPROUT_ITERATOR_CONST_REFERENCE_CAST_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_const_cast_convertible.hpp>
#include <sprout/type_traits/remove_cvref.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout {
	//
	// is_const_reference_cast_convertible
	//
	template<typename From, typename To>
	struct is_const_reference_cast_convertible
		: public sprout::bool_constant<
			sprout::is_const_cast_convertible<From, To>::value
				|| std::is_same<typename sprout::remove_cvref<From>::type, typename std::remove_cv<To>::type>::value
		>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From, To const>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From, To volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From, To const volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const, To>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const, To const>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const, To volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const, To const volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From volatile, To>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From volatile, To const>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From volatile, To volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From volatile, To const volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const volatile, To>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const volatile, To const>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const volatile, To volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
	template<typename From, typename To>
	struct is_const_reference_cast_convertible<From const volatile, To const volatile>
		: public sprout::is_const_reference_cast_convertible<From, To>
	{};
}	// namespace sprout

namespace sprout_adl {
	template<typename To>
	sprout::not_found_via_adl const_reference_conversion(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<
			typename T, typename U,
			typename sprout::enabler_if<
				sprout::is_const_reference_cast_convertible<U&, T>::value
					&& std::is_reference<T>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_reference_conversion(U& t) {
			return const_cast<T>(t);
		}
		template<
			typename T, typename U,
			typename sprout::enabler_if<
				sprout::is_const_reference_cast_convertible<U const&, T>::value
					&& std::is_reference<T>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_reference_conversion(U const& t) {
			return const_cast<T>(t);
		}

		template<
			typename T, typename U,
			typename sprout::enabler_if<
				sprout::is_const_reference_cast_convertible<U&, T>::value
					&& std::is_pointer<T>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_reference_conversion(U& t) {
			return const_cast<T>(t);
		}
		template<
			typename T, typename U,
			typename sprout::enabler_if<
				sprout::is_const_reference_cast_convertible<U const&, T>::value
					&& std::is_pointer<T>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_reference_conversion(U const& t) {
			return const_cast<T>(t);
		}

		template<
			typename T, typename U,
			typename sprout::enabler_if<
				sprout::is_const_reference_cast_convertible<U&, T>::value
					&& !std::is_reference<T>::value && !std::is_pointer<T>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_reference_conversion(U& t) {
			return static_cast<T>(t);
		}
		template<
			typename T, typename U,
			typename sprout::enabler_if<
				sprout::is_const_reference_cast_convertible<U const&, T>::value
					&& !std::is_reference<T>::value && !std::is_pointer<T>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_reference_conversion(U const& t) {
			return static_cast<T>(t);
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename To, typename From>
	inline SPROUT_CONSTEXPR To
	call_const_reference_conversion(From&& t) {
		using sprout::iterator_detail::const_reference_conversion;
		using sprout_adl::const_reference_conversion;
		return const_reference_conversion<To>(SPROUT_FORWARD(From, t));
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// const_reference_cast
	//
	template<typename To, typename From>
	inline SPROUT_CONSTEXPR To
	const_reference_cast(From&& t) {
		return sprout_iterator_detail::call_const_reference_conversion<To>(SPROUT_FORWARD(From, t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_CONST_REFERENCE_CAST_HPP
