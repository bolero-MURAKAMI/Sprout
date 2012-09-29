#ifndef SPROUT_CONTAINER_END_HPP
#define SPROUT_CONTAINER_END_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::adl_not_found range_end(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline typename sprout::container_traits<Container>::iterator
		range_end(Container& cont) {
			return cont.end();
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
		range_end(Container const& cont) {
			return cont.end();
		}
	}	// namespace container_detail
}	// namespace sprout

namespace sprout {
	//
	// end
	//
	template<typename Container>
	inline typename sprout::container_traits<Container>::iterator
	end(Container& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
	end(Container const& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename T, std::size_t N>
	inline typename sprout::container_traits<T[N]>::iterator
	end(T (& arr)[N]) {
		return arr + N;
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
	end(T const (& arr)[N]) {
		return arr + N;
	}

	//
	// cend
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::const_iterator
	cend(Container const& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
	cend(T const (& arr)[N]) {
		return arr + N;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_END_HPP
