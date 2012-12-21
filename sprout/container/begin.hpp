#ifndef SPROUT_CONTAINER_BEGIN_HPP
#define SPROUT_CONTAINER_BEGIN_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_begin(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline typename sprout::container_traits<Container>::iterator
		range_begin(Container& cont) {
			return cont.begin();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
		range_begin(Container const& cont) {
			return cont.begin();
		}

		template<typename T, std::size_t N>
		inline typename sprout::container_traits<T[N]>::iterator
		range_begin(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator iterator;
			return iterator(arr);
		}
		template<typename T, std::size_t N>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
		range_begin(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::const_iterator iterator;
			return iterator(arr);
		}
	}	// namespace container_detail
}	// namespace sprout

namespace sprout {
	//
	// begin
	//
	template<typename Container>
	inline typename sprout::container_traits<Container>::iterator
	begin(Container& cont) {
		using sprout::container_detail::range_begin;
		using sprout_adl::range_begin;
		return range_begin(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
	begin(Container const& cont) {
		using sprout::container_detail::range_begin;
		using sprout_adl::range_begin;
		return range_begin(cont);
	}
	template<typename T, std::size_t N>
	inline typename sprout::container_traits<T[N]>::iterator
	begin(T (& arr)[N]) {
		return sprout::container_detail::range_begin(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
	begin(T const (& arr)[N]) {
		return sprout::container_detail::range_begin(arr);
	}

	//
	// cbegin
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
	cbegin(Container const& cont) {
		using sprout::container_detail::range_begin;
		using sprout_adl::range_begin;
		return range_begin(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
	cbegin(T const (& arr)[N]) {
		return sprout::container_detail::range_begin(arr);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_BEGIN_HPP
