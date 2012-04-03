#ifndef SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP

#include <sscrisk/cel/array.hpp>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <cstddef>
#	include <type_traits>
#	include <sprout/container/begin.hpp>
#	include <sprout/container/end.hpp>
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
	//
	// container_traits
	//
	template<typename T, std::size_t N>
	struct container_traits<sscrisk::cel::array<T, N> >
		: public sprout::detail::container_traits_default_types<sscrisk::cel::array<T, N> >
		, public sprout::detail::container_traits_default_size<sscrisk::cel::array<T, N> >
	{
	public:
		typedef sprout::index_iterator<sscrisk::cel::array<T, N>&> iterator;
		typedef sprout::index_iterator<sscrisk::cel::array<T, N> const&> const_iterator;
	};

	//
	// begin
	//
	template<typename T, std::size_t N>
	typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator begin(sscrisk::cel::array<T, N>& cont) {
		return typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator(cont, 0);
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator begin(sscrisk::cel::array<T, N> const& cont) {
		return typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator(cont, 0);
	}

	//
	// cbegin
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator cbegin(sscrisk::cel::array<T, N> const& cont) {
		return typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator(cont, 0);
	}

	//
	// end
	//
	template<typename T, std::size_t N>
	typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator end(sscrisk::cel::array<T, N>& cont) {
		return typename sprout::container_traits<sscrisk::cel::array<T, N> >::iterator(cont, cont.size());
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator end(sscrisk::cel::array<T, N> const& cont) {
		return typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator(cont, cont.size());
	}

	//
	// cend
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator cend(sscrisk::cel::array<T, N> const& cont) {
		return typename sprout::container_traits<sscrisk::cel::array<T, N> >::const_iterator(cont, cont.size());
	}
#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP
