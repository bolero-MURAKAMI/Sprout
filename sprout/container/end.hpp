#ifndef SPROUT_CONTAINER_END_HPP
#define SPROUT_CONTAINER_END_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/container_range_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_end(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_end(Container& cont) {
			return sprout::container_range_traits<Container>::range_end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_end(Container const& cont) {
			return sprout::container_range_traits<Container>::range_end(cont);
		}
	}	// namespace container_detail

	//
	// end
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	end(Container& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	end(Container const& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
	end(T (& arr)[N]) {
		return sprout::container_detail::range_end(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	end(T const (& arr)[N]) {
		return sprout::container_detail::range_end(arr);
	}

	//
	// cend
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cend(Container const& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	cend(T const (& arr)[N]) {
		return sprout::container_detail::range_end(arr);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_END_HPP
