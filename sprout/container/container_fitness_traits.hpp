/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_FITNESS_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_FITNESS_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/size.hpp>
#include <sprout/utility/forward.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// container_fitness_traits
	//
	template<typename Container>
	struct container_fitness_traits {
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::difference_type
		fit_size(Cont&& cont, typename sprout::container_traits<Container>::size_type size) {
			return NS_SSCRISK_CEL_OR_SPROUT::min(size, sprout::size(SPROUT_FORWARD(Cont, cont)));
		}
	};
	template<typename Container>
	struct container_fitness_traits<Container const>
		: public sprout::container_fitness_traits<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_FITNESS_TRAITS_HPP
