/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_INDEXES_HPP
#define SPROUT_CONTAINER_INDEXES_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/index_tuple/enable_make_indexes.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// container_indexes
		//
		template<typename Container>
		struct container_indexes
			: public sprout::enable_make_indexes<
				sprout::make_index_tuple<sprout::container_traits<Container>::static_size>
			>
		{};
	}	// namespace containers

	//
	// container_indexes
	//
	template<typename Container>
	struct container_indexes
		: public sprout::containers::container_indexes<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INDEXES_HPP
