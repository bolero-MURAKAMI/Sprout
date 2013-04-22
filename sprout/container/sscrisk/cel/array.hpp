#ifndef SPROUT_CONTAINER_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_CONTAINER_SSCRISK_CEL_ARRAY_HPP

#include <sscrisk/cel/array.hpp>
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
	struct container_traits<sscrisk::cel::array<T, N> >
		: public sprout::detail::container_traits_default<sscrisk::cel::array<T, N> >
	{
	public:
		typedef sprout::index_iterator<sscrisk::cel::array<T, N>&, true> iterator;
		typedef sprout::index_iterator<sscrisk::cel::array<T, N> const&, true> const_iterator;
	};

	//
	// container_range_traits
	//
	template<typename T, std::size_t N>
	struct container_range_traits<sscrisk::cel::array<T, N> > {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator
		range_begin(sscrisk::cel::array<T, N>& cont) {
			return typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> const>::iterator
		range_begin(sscrisk::cel::array<T, N> const& cont) {
			return typename sprout::container_traits<sscrisk::cel::array<T, N> const>::iterator(cont, 0);
		}

		static SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator
		range_end(sscrisk::cel::array<T, N>& cont) {
			return typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator(cont, cont.size());
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> const>::iterator
		range_end(sscrisk::cel::array<T, N> const& cont) {
			return typename sprout::container_traits<sscrisk::cel::array<T, N> const>::iterator(cont, cont.size());
		}
	};
}	// namespace sprout
#endif

#endif	// #ifndef SPROUT_CONTAINER_SSCRISK_CEL_ARRAY_HPP
