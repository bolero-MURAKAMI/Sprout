/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_SUB_HPP
#define SPROUT_SUB_ARRAY_SUB_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/type_traits.hpp>
#include <sprout/sub_array/sub_window.hpp>

namespace sprout {
	//
	// sub
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type
	sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::const_iterator first,
		typename sprout::container_traits<sprout::sub_array<Container&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type
	sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type
	sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type to_first,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type to_last
		)
	{
		return sprout::sub_window(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container&> >::type
	sub(
		Container& arr,
		typename sprout::container_traits<sprout::sub_array<Container&> >::difference_type to_first = 0
		)
	{
		return sprout::sub_window(arr, to_first);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_last
		)
	{
		return sprout::sub_window(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	sub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first = 0
		)
	{
		return sprout::sub_window(arr, to_first);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type
	sub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return Container(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type
	sub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type
	sub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return sprout::sub_window(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, Container>::type
	sub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return sprout::sub_window(arr, to_first);
	}

	//
	// csub
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator last
		)
	{
		return sprout::sub_array<Container const&>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_last
		)
	{
		return sprout::csub_window(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<sprout::sub_array<Container const&> >::difference_type to_first = 0
		)
	{
		return sprout::csub_window(arr, to_first);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<typename Container::internal_type const&>(arr.get_array(), first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::csub(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return sprout::csub_window(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type const&> >::type
	csub(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return sprout::csub_window(arr, to_first);
	}

	//
	// sub_copy
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<Container>(arr, first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return sprout::sub_window_copy(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<!sprout::is_sub_array<Container>::value, sprout::sub_array<Container> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return sprout::sub_window_copy(arr, to_first);
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first,
		typename sprout::container_traits<Container>::const_iterator last
		)
	{
		return sprout::sub_array<typename Container::internal_type>(arr.get_array(), first, last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::const_iterator first
		)
	{
		return sprout::sub_copy(arr, first, sprout::end(arr));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first,
		typename sprout::container_traits<Container>::difference_type to_last
		)
	{
		return sprout::sub_window_copy(arr, to_first, to_last);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::enable_if<sprout::is_sub_array<Container>::value, sprout::sub_array<typename Container::internal_type> >::type
	sub_copy(
		Container const& arr,
		typename sprout::container_traits<Container>::difference_type to_first = 0
		)
	{
		return sprout::sub_window_copy(arr, to_first);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_SUB_HPP
