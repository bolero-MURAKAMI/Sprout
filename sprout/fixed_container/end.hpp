#ifndef SPROUT_FIXED_CONTAINER_END_HPP
#define SPROUT_FIXED_CONTAINER_END_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// end
	//
	template<typename Range>
	typename sprout::fixed_container_traits<Range>::iterator end(Range& range) {
		return range.end();
	}
	template<typename T, std::size_t N>
	typename sprout::fixed_container_traits<T const[N]>::iterator end(T (& arr)[N]) {
		return arr + N;
	}
	//
	// end
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::const_iterator end(Range const& range) {
		return range.end();
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<T const[N]>::const_iterator end(T const (& arr)[N]) {
		return arr + N;
	}

	//
	// cend
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::const_iterator cend(Range const& range) {
		return range.end();
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<T const[N]>::const_iterator cend(T const (& arr)[N]) {
		return arr + N;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_END_HPP
