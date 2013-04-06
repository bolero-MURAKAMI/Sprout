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
