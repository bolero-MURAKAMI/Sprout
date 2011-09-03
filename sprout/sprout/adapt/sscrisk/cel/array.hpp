#ifndef SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP

#include <cstddef>
#include <sscrisk/cel/array.hpp>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// rebind_fixed_size
	//
	template<typename T, std::size_t N>
	struct rebind_fixed_size<sscrisk::cel::array<T, N> > {
	public:
		template<typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::size_type S>
		struct apply {
			public:
				typedef sscrisk::cel::array<T, S> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP
