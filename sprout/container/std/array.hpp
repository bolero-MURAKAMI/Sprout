#ifndef SPROUT_CONTAINER_STD_ARRAY_HPP
#define SPROUT_CONTAINER_STD_ARRAY_HPP

#include <array>
#include <sprout/config.hpp>
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <cstddef>
#	include <type_traits>
#	include <sprout/container/traits.hpp>
#	include <sprout/iterator/index_iterator.hpp>
#endif

#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
namespace sprout {
	//
	// container_traits
	//
	template<typename T, std::size_t N>
	struct container_traits<std::array<T, N> >
		: public sprout::detail::container_traits_default<std::array<T, N> >
	{
	public:
		typedef sprout::index_iterator<std::array<T, N>&, true> iterator;
		typedef sprout::index_iterator<std::array<T, N> const&, true> const_iterator;
	};
}	// namespace sprout

namespace sprout {
	//
	// range_begin
	//
	template<typename T, std::size_t N>
	inline typename sprout::container_traits<std::array<T, N> >::iterator
	range_begin(std::array<T, N>& cont) {
		return typename sprout::container_traits<std::array<T, N> >::iterator(cont, 0);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::const_iterator
	range_begin(std::array<T, N> const& cont) {
		return typename sprout::container_traits<std::array<T, N> >::const_iterator(cont, 0);
	}

	//
	// range_end
	//
	template<typename T, std::size_t N>
	inline typename sprout::container_traits<std::array<T, N> >::iterator
	range_end(std::array<T, N>& cont) {
		return typename sprout::container_traits<std::array<T, N> >::iterator(cont, cont.size());
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::const_iterator
	range_end(std::array<T, N> const& cont) {
		return typename sprout::container_traits<std::array<T, N> >::const_iterator(cont, cont.size());
	}
}	// namespace sprout
#endif

#endif	// #ifndef SPROUT_CONTAINER_STD_ARRAY_HPP
