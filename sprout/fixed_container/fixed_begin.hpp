#ifndef SPROUT_FIXED_CONTAINER_FIXED_BEGIN_HPP
#define SPROUT_FIXED_CONTAINER_FIXED_BEGIN_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/begin.hpp>
#include <sprout/fixed_container/get_fixed.hpp>

namespace sprout {
	//
	// fixed_begin
	//
	template<typename Range>
	typename sprout::fixed_container_traits<
		typename sprout::fixed_container_traits<Range>::fixed_container_type
	>::iterator fixed_begin(Range& range) {
		return sprout::begin(sprout::get_fixed(range));
	}
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<
		typename sprout::fixed_container_traits<Range>::fixed_container_type
	>::const_iterator fixed_begin(Range const& range) {
		return sprout::begin(sprout::get_fixed(range));
	}

	//
	// fixed_cbegin
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<
		typename sprout::fixed_container_traits<Range>::fixed_container_type
	>::const_iterator fixed_cbegin(Range const& range) {
		return sprout::begin(sprout::get_fixed(range));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_FIXED_BEGIN_HPP
