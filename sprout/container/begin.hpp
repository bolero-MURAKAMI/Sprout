#ifndef SPROUT_CONTAINER_BEGIN_HPP
#define SPROUT_CONTAINER_BEGIN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// begin
	//
	template<typename Container>
	inline typename sprout::container_traits<Container>::iterator
	begin(Container& cont) {
		return cont.begin();
	}
	template<typename T, std::size_t N>
	inline typename sprout::container_traits<T[N]>::iterator
	begin(T (& arr)[N]) {
		return arr;
	}

	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
	begin(Container const& cont) {
		return cont.begin();
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
	begin(T const (& arr)[N]) {
		return arr;
	}

	//
	// cbegin
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
	cbegin(Container const& cont) {
		return cont.begin();
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
	cbegin(T const (& arr)[N]) {
		return arr;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_BEGIN_HPP
