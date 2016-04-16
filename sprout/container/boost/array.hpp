/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_BOOST_ARRAY_HPP
#define SPROUT_CONTAINER_BOOST_ARRAY_HPP

#include <utility>
#include <boost/array.hpp>
#include <sprout/config.hpp>
#include <type_traits>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/functional/transparent.hpp>

namespace sprout {
	namespace detail {
		template<typename T = void>
		struct elems_subscript;
		template<>
		struct elems_subscript<void>
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(std::declval<T>().elems[std::declval<U>()])
			operator()(T&& x, U&& y)
			const SPROUT_NOEXCEPT_IF_EXPR(std::declval<T>().elems[std::declval<U>()])
			{
				return SPROUT_FORWARD(T, x).elems[SPROUT_FORWARD(U, y)];
			}
		};
	}	// namespace detail

	//
	// container_traits
	//
	template<typename T, std::size_t N>
	struct container_traits<boost::array<T, N> >
		: public sprout::detail::container_traits_default<boost::array<T, N> >
	{
	public:
		typedef sprout::index_iterator<boost::array<T, N>&, true, sprout::detail::elems_subscript<> > iterator;
		typedef sprout::index_iterator<boost::array<T, N> const&, true, sprout::detail::elems_subscript<> > const_iterator;
	};

	//
	// container_range_traits
	//
	template<typename T, std::size_t N>
	struct container_range_traits<boost::array<T, N> >
		: public sprout::detail::container_range_traits_default<boost::array<T, N> >
	{
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> >::iterator
		range_begin(boost::array<T, N>& cont) {
			return typename sprout::container_traits<boost::array<T, N> >::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::iterator
		range_begin(boost::array<T, N> const& cont) {
			return typename sprout::container_traits<boost::array<T, N> const>::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> >::iterator
		range_end(boost::array<T, N>& cont) {
			return typename sprout::container_traits<boost::array<T, N> >::iterator(cont, cont.size());
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::iterator
		range_end(boost::array<T, N> const& cont) {
			return typename sprout::container_traits<boost::array<T, N> const>::iterator(cont, cont.size());
		}
		// capacity:
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::size_type
		range_size(boost::array<T, N> const& cont) {
			return N;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::size_type
		range_empty(boost::array<T, N> const& cont) {
			return N != 0;
		}
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> >::reference
		range_front(boost::array<T, N>& cont) {
			return cont.elems[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::reference
		range_front(boost::array<T, N> const& cont) {
			return cont.elems[0];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> >::reference
		range_back(boost::array<T, N>& cont) {
			return cont.elems[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::reference
		range_back(boost::array<T, N> const& cont) {
			return cont.elems[N - 1];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> >::reference
		range_at(boost::array<T, N>& cont, typename sprout::container_traits<boost::array<T, N> >::size_type i) {
			return cont.elems[i];
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::reference
		range_at(boost::array<T, N> const& cont, typename sprout::container_traits<boost::array<T, N> const>::size_type i) {
			return cont.elems[i];
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> >::pointer
		range_data(boost::array<T, N>& cont) {
			return cont.elems;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<boost::array<T, N> const>::pointer
		range_data(boost::array<T, N> const& cont) {
			return cont.elems;
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_BOOST_ARRAY_HPP
