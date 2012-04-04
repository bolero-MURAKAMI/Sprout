#ifndef SPROUT_CONTAINER_INDEXES_HPP
#define SPROUT_CONTAINER_INDEXES_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/container_construct_traits.hpp>

namespace sprout {
	namespace containers {
		//
		// container_indexes
		//
		template<typename Container>
		struct container_indexes
			: public sprout::detail::make_index_tuple_helper<
				sprout::index_range<0, sprout::container_traits<Container>::static_size>
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
