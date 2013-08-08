/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_SUB_OFFSET_HPP
#define SPROUT_SUB_ARRAY_SUB_OFFSET_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/type_traits.hpp>

namespace sprout {
	//
	// sub_offset
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type
	sub_offset(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type from_begin = 0,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type from_end = 0
		)
	{
		return sprout::sub_array<Container&>(arr, from_begin, sprout::size(arr) + from_end);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	sub_offset(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type from_begin = 0,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type from_end = 0
		)
	{
		return sprout::sub_array<Container const&>(arr, from_begin, sprout::size(arr) + from_end);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type
	sub_offset(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type from_begin = 0,
		typename sprout::container_traits<Container>::difference_type from_end = 0
		)
	{
		return Container(arr, from_begin, sprout::size(arr) + from_end);
	}

	//
	// csub_offset
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	csub_offset(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type from_begin = 0,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type from_end = 0
		)
	{
		return sprout::sub_offset(arr, from_begin, from_end);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type
	csub_offset(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type from_begin = 0,
		typename sprout::container_traits<Container>::difference_type from_end = 0
		)
	{
		return sprout::sub_array<typename Container::internal_type const&>(
			arr.get_array(),
			arr.to_first() + from_begin,
			arr.to_last() + from_end
			);
	}

	//
	// sub_offset_copy
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type
	sub_offset_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type from_begin = 0,
		typename sprout::container_traits<Container>::difference_type from_end = 0
		)
	{
		return sprout::sub_array<Container>(arr, from_begin, sprout::size(arr) + from_end);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type
	sub_offset_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type from_begin = 0,
		typename sprout::container_traits<Container>::difference_type from_end = 0
		)
	{
		return sprout::sub_array<typename Container::internal_type>(
			arr.get_array(),
			arr.to_first() + from_begin,
			arr.to_last() + from_end
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_SUB_OFFSET_HPP
