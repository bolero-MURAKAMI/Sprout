#ifndef SPROUT_FIXED_CONTAINER_FIXED_END_HPP
#define SPROUT_FIXED_CONTAINER_FIXED_END_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/end.hpp>
#include <sprout/fixed_container/get_fixed.hpp>

namespace sprout {
	//
	// fixed_end
	//
	template<typename Range>
	typename sprout::fixed_container_traits<
		typename sprout::fixed_container_traits<Range>::fixed_container_type
	>::iterator fixed_end(Range& range) {
		return sprout::end(sprout::get_fixed(range));
	}
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<
		typename sprout::fixed_container_traits<Range>::fixed_container_type
	>::const_iterator fixed_end(Range const& range) {
		return sprout::end(sprout::get_fixed(range));
	}

	//
	// fixed_cend
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<
		typename sprout::fixed_container_traits<Range>::fixed_container_type
	>::const_iterator fixed_cend(Range const& range) {
		return sprout::end(sprout::get_fixed(range));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_FIXED_END_HPP
