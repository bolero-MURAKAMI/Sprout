/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_RANGE_FUNCTIONS_FWD_HPP
#define SPROUT_CONTAINER_RANGE_FUNCTIONS_FWD_HPP

#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// begin
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	begin(Container& cont);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	begin(Container const& cont);

	//
	// end
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	end(Container& cont);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	end(Container const& cont);

	//
	// size
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	size(Container const& cont);

	//
	// empty
	//
	template<typename Container>
	SPROUT_CONSTEXPR bool
	empty(Container const& cont);

	//
	// front
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	front(Container& cont);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	front(Container const& cont);

	//
	// back
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	back(Container& cont);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	back(Container const& cont);

	//
	// subscript_at
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	subscript_at(Container& cont, typename sprout::container_traits<Container>::size_type i);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	subscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i);

	//
	// at
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	at(Container& cont, typename sprout::container_traits<Container>::size_type i);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	at(Container const& cont, typename sprout::container_traits<Container const>::size_type i);

	//
	// nth
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	nth(Container& cont, typename sprout::container_traits<Container>::size_type i);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i);

	//
	// index_of
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	index_of(Container& cont, typename sprout::container_traits<Container>::iterator p);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p);

	//
	// data
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
	data(Container& cont);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
	data(Container const& cont);

	//
	// range_index_check
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	range_index_check(Container const& cont, typename sprout::container_traits<Container const>::size_type i);

	//
	// shrink_to_fit
	//
	template<typename Container>
	SPROUT_CXX14_CONSTEXPR void
	shrink_to_fit(Container&& cont);
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_RANGE_FUNCTIONS_FWD_HPP
