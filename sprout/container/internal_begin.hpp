#ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_HPP
#define SPROUT_CONTAINER_INTERNAL_BEGIN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/sub_container_traits.hpp>
#include <sprout/container/internal.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/get_internal.hpp>

namespace sprout {
	//
	// internal_begin
	//
	template<typename Container>
	typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::internal<Container&>::type
		>::type
	>::iterator internal_begin(Container& cont) {
		return sprout::begin(sprout::get_internal(cont));
	}
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::internal<Container const&>::type
		>::type
	>::const_iterator internal_begin(Container const& cont) {
		return sprout::begin(sprout::get_internal(cont));
	}

	//
	// internal_cbegin
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename sprout::container_traits<
		typename std::remove_reference<
			typename sprout::containers::internal<Container const&>::type
		>::type
	>::const_iterator internal_cbegin(Container const& cont) {
		return sprout::begin(sprout::get_internal(cont));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_INTERNAL_BEGIN_HPP
