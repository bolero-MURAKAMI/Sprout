#ifndef SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP
#define SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP

#include <cstddef>
#include <type_traits>
#include <sscrisk/cel/array.hpp>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
#	include <sprout/fixed_container/begin.hpp>
#	include <sprout/fixed_container/end.hpp>
#	include <sprout/iterator/index_iterator.hpp>
#endif

namespace sprout {
	//
	// rebind_fixed_size
	//
	template<typename T, std::size_t N>
	struct rebind_fixed_size<sscrisk::cel::array<T, N> > {
	public:
		template<typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::size_type S>
		struct apply {
			public:
				typedef sscrisk::cel::array<T, S> type;
		};
	};

#if SPROUT_USE_INDEX_ITERATOR_IMPLEMENTATION
	//
	// fixed_container_traits
	//
	template<typename T, std::size_t N>
	struct fixed_container_traits<sscrisk::cel::array<T, N> >
		: public sprout::detail::fixed_container_traits_base<sscrisk::cel::array<T, N> >
	{
	public:
		typedef sscrisk::cel::array<T, N> fixed_container_type;
		typedef fixed_container_type internal_type;
		typedef internal_type clone_type;
		typedef sprout::index_iterator<fixed_container_type&> iterator;
		typedef sprout::index_iterator<fixed_container_type const&> const_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR typename sprout::detail::fixed_container_traits_base<fixed_container_type>::size_type fixed_size
			= std::tuple_size<typename std::remove_const<internal_type>::type>::value
			;
	};
	//
	// fixed_container_traits
	//
	template<typename T, std::size_t N>
	struct fixed_container_traits<sscrisk::cel::array<T, N> const>
		: public sprout::detail::fixed_container_traits_base<sscrisk::cel::array<T, N> const>
	{
	public:
		typedef sscrisk::cel::array<T, N> const fixed_container_type;
		typedef typename std::remove_const<fixed_container_type>::type internal_type;
		typedef internal_type clone_type;
		typedef sprout::index_iterator<fixed_container_type&> iterator;
		typedef sprout::index_iterator<fixed_container_type const&> const_iterator;
	public:
		SPROUT_STATIC_CONSTEXPR typename sprout::detail::fixed_container_traits_base<fixed_container_type>::size_type fixed_size
			= std::tuple_size<typename std::remove_const<internal_type>::type>::value
			;
	};

	//
	// begin
	//
	template<typename T, std::size_t N>
	typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::iterator begin(sscrisk::cel::array<T, N>& range) {
		return typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::iterator(range, 0);
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator begin(sscrisk::cel::array<T, N> const& range) {
		return typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator(range, 0);
	}

	//
	// cbegin
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator cbegin(sscrisk::cel::array<T, N> const& range) {
		return sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator(range, 0);
	}

	//
	// end
	//
	template<typename T, std::size_t N>
	typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::iterator end(sscrisk::cel::array<T, N>& range) {
		return typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::iterator(range, range.size());
	}
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator end(sscrisk::cel::array<T, N> const& range) {
		return typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator(range, range.size());
	}

	//
	// cend
	//
	template<typename T, std::size_t N>
	SPROUT_CONSTEXPR typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator cend(sscrisk::cel::array<T, N> const& range) {
		return typename sprout::fixed_container_traits<sscrisk::cel::array<T, N> >::const_iterator(range, range.size());
	}
#endif
}	// namespace sprout

#endif	// #ifndef SPROUT_ADAPT_SSCRISK_CEL_ARRAY_HPP
