/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MEMORY_ADDRESSOF_HPP
#define SPROUT_MEMORY_ADDRESSOF_HPP

#include <utility>
#include <memory>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout {
	namespace detail {
		struct address_op_helper {};
		void operator&(sprout::detail::address_op_helper const&);

		template<typename T>
		struct has_mem_address_op_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(std::declval<U>().operator&())>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_mem_address_op_test<T>::test(0))>::type>
		struct has_mem_address_op
			: public Base_
		{};
#else
		template<typename T>
		struct has_mem_address_op
			: public sprout::identity<decltype(sprout::detail::has_mem_address_op_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct has_nonmem_address_op_test {
		public:
			template<
				typename U = T,
				typename = typename sprout::identity<decltype(operator&(std::declval<U>()))>::type
			>
			static sprout::true_type test(int);
			static sprout::false_type test(...);
		};
#if defined(_MSC_VER) && (_MSC_VER > 1900)
		template<typename T, typename Base_ = typename sprout::identity<decltype(sprout::detail::has_nonmem_address_op_test<T>::test(0))>::type>
		struct has_nonmem_address_op
			: public Base_
		{};
#else
		template<typename T>
		struct has_nonmem_address_op
			: public sprout::identity<decltype(sprout::detail::has_nonmem_address_op_test<T>::test(0))>::type
		{};
#endif

		template<typename T>
		struct has_address_op
			: public sprout::bool_constant<
				sprout::detail::has_mem_address_op<T>::value || sprout::detail::has_nonmem_address_op<T>::value
			>
		{};

		template<typename T, bool IsOverloaded = sprout::detail::has_address_op<T>::value>
		struct addressof_traits_default;
		template<typename T>
		struct addressof_traits_default<T, true> {
		public:
			template<typename U>
			static U*
			get_addressof(U& t) SPROUT_NOEXCEPT {
				return std::addressof(t);
			}
		};
		template<typename T>
		struct addressof_traits_default<T, false> {
		public:
			template<typename U>
			static SPROUT_CONSTEXPR U*
			get_addressof(U& t) SPROUT_NOEXCEPT {
				return &t;
			}
		};
	}	// namespace detail

	//
	// address_traits
	//
	template<typename T>
	struct address_traits
		: public sprout::detail::addressof_traits_default<T>
	{};
	template<typename T>
	struct address_traits<T const>
		: public sprout::address_traits<T>
	{};
	template<typename T>
	struct address_traits<T volatile>
		: public sprout::address_traits<T>
	{};
	template<typename T>
	struct address_traits<T const volatile>
		: public sprout::address_traits<T>
	{};
}	// namespace sprout

namespace sprout_adl {
	sprout::not_found_via_adl get_addressof(...);
}	// namespace sprout_adl

namespace sprout_addressof_detail {
	template<typename T>
	inline SPROUT_CONSTEXPR T*
	get_addressof(T& t) SPROUT_NOEXCEPT {
		return sprout::address_traits<T>::get_addressof(t);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR T*
	call_get_addressof(T& t) SPROUT_NOEXCEPT {
		using sprout_adl::get_addressof;
		using sprout_addressof_detail::get_addressof;
		return get_addressof(t);
	}
}	// namespace sprout_addressof_detail

namespace sprout {
	//
	// addressof
	//
	//	effect:
	//		ADL callable get_addressof(t) -> get_addressof(t)
	//		otherwise -> sprout::address_traits<T>::get_addressof(t)
	//		[default]
	//			no overloaded operator&() -> &t
	//			otherwise -> std::addressof(t)
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T*
	addressof(T& t) SPROUT_NOEXCEPT {
		return sprout_addressof_detail::call_get_addressof(t);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_MEMORY_ADDRESSOF_HPP
