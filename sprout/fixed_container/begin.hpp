#ifndef SPROUT_FIXED_CONTAINER_BEGIN_HPP
#define SPROUT_FIXED_CONTAINER_BEGIN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>

namespace sprout {
	//
	// begin
	//
	template<typename Range>
	typename sprout::fixed_container_traits<Range>::iterator begin(Range& range) {
		return range.begin();
	}
	template<typename T, std::size_t N>
	typename sprout::fixed_container_traits<T[N]>::iterator begin(T (& arr)[N]) {
		return arr;
	}
	//
	// begin
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::const_iterator begin(Range const& range) {
		return range.begin();
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<T const[N]>::const_iterator begin(T const (& arr)[N]) {
		return arr;
	}

	//
	// cbegin
	//
	template<typename Range>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<Range>::const_iterator cbegin(Range const& range) {
		return range.begin();
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<T const[N]>::const_iterator cbegin(T const (& arr)[N]) {
		return arr;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FIXED_CONTAINER_BEGIN_HPP
