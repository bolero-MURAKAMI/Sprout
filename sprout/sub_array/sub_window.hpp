/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_SUB_WINDOW_HPP
#define SPROUT_SUB_ARRAY_SUB_WINDOW_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/type_traits.hpp>

namespace sprout {
	//
	// sub_window
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type
	sub_window(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type to_first,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type to_last
		)
	{
		return sprout::sub_array<Container&>(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type
	sub_window(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type to_first = 0
		)
	{
		return sprout::sub_array<Container&>(arr, to_first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	sub_window(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_last
		)
	{
		return sprout::sub_array<Container const&>(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	sub_window(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first = 0
		)
	{
		return sprout::sub_array<Container const&>(arr, to_first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type
	sub_window(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return Container(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type
	sub_window(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return Container(arr, to_first, sprout::size(arr));
	}

	//
	// csub_window
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	csub_window(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_last
		)
	{
		return sprout::sub_window(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	csub_window(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first = 0
		)
	{
		return sprout::sub_window(arr, to_first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type
	csub_window(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return sprout::sub_array<typename Container::internal_type const&>(
			arr.get_array(),
			arr.to_first() + to_first,
			arr.to_first() + to_last
			);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type
	csub_window(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return sprout::sub_array<typename Container::internal_type const&>(
			arr.get_array(),
			arr.to_first() + to_first,
			arr.to_first() + sprout::size(arr)
			);
	}

	//
	// sub_window_copy
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type
	sub_window_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return sprout::sub_array<Container>(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type
	sub_window_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return sprout::sub_array<Container>(arr, to_first, sprout::size(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type
	sub_window_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return sprout::sub_array<typename Container::internal_type>(
			arr.get_array(),
			arr.to_first() + to_first,
			arr.to_first() + to_last
			);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type
	sub_window_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return sprout::sub_array<typename Container::internal_type>(
			arr.get_array(),
			arr.to_first() + to_first,
			arr.to_first() + sprout::size(arr)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_SUB_WINDOW_HPP
