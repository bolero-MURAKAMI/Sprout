/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_HPP
#define SPROUT_CONTAINER_INTERNAL_BEGIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/sub_container_traits.hpp>
#include <sprout/container/deep_internal.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/get_deep_internal.hpp>

namespace sprout {
	//
	// internal_begin
	//
	template<typename Container>
	typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::deep_internal<Container&>::type
		>::type
	>::iterator
	internal_begin(Container& cont) {
		return sprout::begin(sprout::get_deep_internal(cont));
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::deep_internal<Container const&>::type
		>::type
	>::const_iterator
	internal_begin(Container const& cont) {
		return sprout::begin(sprout::get_deep_internal(cont));
	}

	//
	// internal_cbegin
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::deep_internal<Container const&>::type
		>::type
	>::const_iterator
	internal_cbegin(Container const& cont) {
		return sprout::begin(sprout::get_deep_internal(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_HPP
