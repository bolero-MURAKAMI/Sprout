/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_WEAK_REBIND_SIZE_HPP
#define SPROUT_CONTAINER_WEAK_REBIND_SIZE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_transform_traits.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace containers {
		namespace detail {
			template<
				typename T,
				template<typename sprout::container_traits<T>::size_type> class = T::template rebind_size
			>
			sprout::true_type sprout_has_xxx_impl_check_template_rebind_size(int);
			template<typename T>
			sprout::false_type sprout_has_xxx_impl_check_template_rebind_size(long);
#if defined(_MSC_VER)
			template<typename T, typename Base_ = decltype(sprout::containers::detail::sprout_has_xxx_impl_check_template_rebind_size<T>(0))>
			struct has_rebind_size
				: public Base_
			{};
#else
			template<typename T>
			struct has_rebind_size
				: public sprout::identity<decltype(sprout::containers::detail::sprout_has_xxx_impl_check_template_rebind_size<T>(0))>::type
			{};
#endif
		}	// namespace detail
		//
		// is_rebindable_size
		//
		template<typename Container>
		struct is_rebindable_size
			: public sprout::containers::detail::has_rebind_size<
				sprout::container_transform_traits<Container>
			>
		{};
		template<typename Container>
		struct is_rebindable_size<Container const>
			: public sprout::containers::is_rebindable_size<Container>
		{};
		template<typename Container>
		struct is_rebindable_size<Container volatile>
			: public sprout::containers::is_rebindable_size<Container>
		{};
		template<typename Container>
		struct is_rebindable_size<Container const volatile>
			: public sprout::containers::is_rebindable_size<Container>
		{};

		namespace detail {
			template<typename Container, typename sprout::container_traits<Container>::size_type Size, typename = void>
			struct weak_rebind_size_impl;
			template<typename Container, typename sprout::container_traits<Container>::size_type Size>
			struct weak_rebind_size_impl<
				Container, Size,
				typename std::enable_if<sprout::containers::is_rebindable_size<Container>::value>::type
			>
				: public sprout::container_transform_traits<Container>::template rebind_size<Size>
			{};
			template<typename Container, typename sprout::container_traits<Container>::size_type Size>
			struct weak_rebind_size_impl<
				Container, Size,
				typename std::enable_if<!sprout::containers::is_rebindable_size<Container>::value>::type
			> {
			public:
				typedef Container type;
			};
		}	// namespace detail
		//
		// weak_rebind_size
		//
		template<typename Container, typename sprout::container_traits<Container>::size_type Size>
		struct weak_rebind_size
			: public sprout::containers::detail::weak_rebind_size_impl<Container, Size>
		{};
	}	// namespace containers
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_WEAK_REBIND_SIZE_HPP
