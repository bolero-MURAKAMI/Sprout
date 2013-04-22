#ifndef SPROUT_CONTAINER_BEGIN_HPP
#define SPROUT_CONTAINER_BEGIN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/container_range_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_begin(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_begin(Container& cont) {
			return sprout::container_range_traits<Container>::range_begin(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_begin(Container const& cont) {
			return sprout::container_range_traits<Container>::range_begin(cont);
		}
	}	// namespace container_detail

	//
	// begin
	//
	//	effect:
	//		ADL callable range_begin(cont) -> range_begin(cont)
	//		otherwise -> sprout::container_range_traits<Container>::range_begin(cont)
	//		[default]
	//			cont.begin()
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	begin(Container& cont) {
		using sprout::container_detail::range_begin;
		using sprout_adl::range_begin;
		return range_begin(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	begin(Container const& cont) {
		using sprout::container_detail::range_begin;
		using sprout_adl::range_begin;
		return range_begin(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
	begin(T (& arr)[N]) {
		return sprout::container_detail::range_begin(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	begin(T const (& arr)[N]) {
		return sprout::container_detail::range_begin(arr);
	}

	//
	// cbegin
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cbegin(Container const& cont) {
		return sprout::begin(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	cbegin(T const (& arr)[N]) {
		return sprout::begin(arr);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_BEGIN_HPP
