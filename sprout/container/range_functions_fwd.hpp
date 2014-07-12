/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
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
	// at
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	at(Container& cont, typename sprout::container_traits<Container>::size_type i);
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	at(Container const& cont, typename sprout::container_traits<Container const>::size_type i);
}	// namespace sprout


#include <sprout/container/size.hpp>
#include <sprout/container/empty.hpp>

#endif	// #ifndef SPROUT_CONTAINER_RANGE_FUNCTIONS_FWD_HPP
