/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_CONST_ITERATOR_CAST_HPP
#define SPROUT_ITERATOR_CONST_ITERATOR_CAST_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_same.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout {
	//
	// is_const_iterator_cast_convertible
	//
	template<typename From, typename To>
	struct is_const_iterator_cast_convertible
		: public sprout::is_same<typename std::remove_cv<From>::type, typename std::remove_cv<To>::type>
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
		: public sprout::is_same<typename std::remove_cv<From>::type, typename std::remove_cv<To>::type>
	{};
}	// namespace sprout

namespace sprout_adl {
	template<typename To>
	sprout::not_found_via_adl const_iterator_conversion(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<
			typename T, typename U,
			typename sprout::enabler_if<sprout::is_const_iterator_cast_convertible<U*, T>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR T
		const_iterator_conversion(U* it) {
			return const_cast<T>(it);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		const_iterator_conversion(T const& it) {
			return it;
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename To, typename From>
	inline SPROUT_CONSTEXPR To
	call_const_iterator_conversion(From const& it) {
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
		return sprout_iterator_detail::call_const_iterator_conversion<To>(it);
	}
}	// namespace sprout

//
//	note:
//		const_iterator_cast is an adaptable function for interconversion
//		with iterator and const_iterator.
//		If you want to adapt a user-defined iterator class to const_iterator_cast:
//		- Specialize sprout::is_const_iterator_cast_convertible.
//		- Overload const_iterator_conversion as to be lookup in the ADL.
//
//	example:
//		#include <type_traits>
//		#include <sprout/config.hpp>
//		#include <sprout/type_traits.hpp>
//		#include <sprout/iterator/const_iterator_cast.hpp>
//		/* Mylib::Iterator is an user-defined iterator class*/
//		namespace Mylib {
//			template<typename T>
//			struct Iterator {
//				T* p;
//				typedef T* pointer;
//				/* definition iterator interface... */
//			};
//		}
//		/* const_iterator_cast adapt for Mylib::Iterator */
//		namespace sprout {
//			template<typename From, typename To>
//			struct is_const_iterator_cast_convertible<
//				Mylib::Iterator<From>,
//				Mylib::Iterator<To>
//			>
//				: public sprout::is_same<
//					typename std::remove_cv<From>::type,
//					typename std::remove_cv<To>::type
//				>
//			{};
//		}
//		namespace Mylib {
//			template<typename To, typename From>
//			inline SPROUT_CONSTEXPR typename std::enable_if<
//				sprout::is_const_iterator_cast_convertible<Iterator<From>, To>::value,
//				To
//			>::type
//			const_iterator_conversion(Iterator<From> const& it) {
//				return To{const_cast<typename To::pointer>(it.p)};
//			}
//		}
//		/* test const_iterator_cast with Mylib::Iterator */
//		constexpr Mylib::Iterator<int const> it{0};
//		static_assert(sprout::const_iterator_cast<Mylib::Iterator<int> >(it).p == 0, "");
//

#endif	// #ifndef SPROUT_ITERATOR_CONST_ITERATOR_CAST_HPP
