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
	// cbegin
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cbegin(Container const& cont);

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
	// cend
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cend(Container const& cont);

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
}	// namespace sprout


#include <sprout/container/size.hpp>
#include <sprout/container/empty.hpp>

#endif	// #ifndef SPROUT_CONTAINER_RANGE_FUNCTIONS_FWD_HPP
