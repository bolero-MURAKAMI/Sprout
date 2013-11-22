/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DETAIL_ARRAY_LIKE_HPP
#define SPROUT_CONTAINER_DETAIL_ARRAY_LIKE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace detail {
		template<typename Container>
		struct is_array_like
			: public sprout::false_type
		{};
		template<template<typename, std::size_t> class Array, typename T, std::size_t N>
		struct is_array_like<Array<T, N> >
			: public sprout::true_type
		{};
		template<typename Container>
		struct is_array_like<Container const>
			: public sprout::detail::is_array_like<Container>
		{};
		template<typename Container>
		struct is_array_like<Container volatile>
			: public sprout::detail::is_array_like<Container>
		{};
		template<typename Container>
		struct is_array_like<Container const volatile>
			: public sprout::detail::is_array_like<Container>
		{};

		template<typename Container>
		struct array_like_static_size {};
		template<template<typename, std::size_t> class Array, typename T, std::size_t N>
		struct array_like_static_size<Array<T, N> >
			: public sprout::integral_constant<std::size_t, N>
		{};
		template<typename Container>
		struct array_like_static_size<Container const>
			: public sprout::detail::array_like_static_size<Container>
		{};
		template<typename Container>
		struct array_like_static_size<Container volatile>
			: public sprout::detail::array_like_static_size<Container>
		{};
		template<typename Container>
		struct array_like_static_size<Container const volatile>
			: public sprout::detail::array_like_static_size<Container>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_DETAIL_ARRAY_LIKE_HPP
