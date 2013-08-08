/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_TUPLE_HPP
#define SPROUT_SUB_ARRAY_TUPLE_HPP

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::sub_array<Container> >::value_type&
	tuple_get(sprout::sub_array<Container>& t)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(*sprout::next(sprout::internal_begin(t), I)))
	{
		static_assert(I < sprout::container_traits<sprout::sub_array<Container> >::static_size, "tuple_get: index out of range");
		return *sprout::next(sprout::internal_begin(t), I);
	}
	template<std::size_t I, typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::sub_array<Container> >::value_type const&
	tuple_get(sprout::sub_array<Container> const& t)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(*sprout::next(sprout::internal_begin(t), I)))
	{
		static_assert(I < sprout::container_traits<sprout::sub_array<Container> >::static_size, "tuple_get: index out of range");
		return *sprout::next(sprout::internal_begin(t), I);
	}
	template<std::size_t I, typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::sub_array<Container> >::value_type&&
	tuple_get(sprout::sub_array<Container>&& t)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::move(sprout::tuples::get<I>(t))))
	{
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename Container>
	struct tuple_size<sprout::sub_array<Container> >
		: public std::tuple_size<typename std::remove_reference<Container>::type>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename Container>
	struct tuple_element<I, sprout::sub_array<Container> >
		: public std::tuple_element<I, typename std::remove_reference<Container>::type>
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_SUB_ARRAY_TUPLE_HPP
