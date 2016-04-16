/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_STD_ARRAY_HPP
#define SPROUT_CONTAINER_STD_ARRAY_HPP

#include <array>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/memory/addressof.hpp>
#include <sprout/functional/transparent.hpp>

namespace sprout {
	namespace detail {
		template<typename T = void>
		struct const_subscript;
		template<>
		struct const_subscript<void>
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(std::declval<T>()[std::declval<U>()])
			operator()(T&& x, U&& y)
			const SPROUT_NOEXCEPT_IF_EXPR(const_cast<decltype(std::declval<T>()[std::declval<U>()])>(sprout::as_const(std::declval<T>())[std::declval<U>()]))
			{
				return const_cast<decltype(std::declval<T>()[std::declval<U>()])>(sprout::as_const(x)[SPROUT_FORWARD(U, y)]);
			}
		};
	}	// namespace detail

	//
	// container_traits
	//
	template<typename T, std::size_t N>
	struct container_traits<std::array<T, N> >
		: public sprout::detail::container_traits_default<std::array<T, N> >
	{
	public:
		typedef sprout::index_iterator<std::array<T, N>&, true, sprout::detail::const_subscript<> > iterator;
		typedef sprout::index_iterator<std::array<T, N> const&, true, sprout::detail::const_subscript<> > const_iterator;
	};

	//
	// container_range_traits
	//
	template<typename T, std::size_t N>
	struct container_range_traits<std::array<T, N> >
		: public sprout::detail::container_range_traits_default<std::array<T, N> >
	{
	private:
		typedef sprout::detail::container_range_traits_default<std::array<T, N> > base_type;
	public:
		using base_type::range_front;
		using base_type::range_back;
		using base_type::range_at;
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::iterator
		range_begin(std::array<T, N>& cont) {
			return typename sprout::container_traits<std::array<T, N> >::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> const>::iterator
		range_begin(std::array<T, N> const& cont) {
			return typename sprout::container_traits<std::array<T, N> const>::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::iterator
		range_end(std::array<T, N>& cont) {
			return typename sprout::container_traits<std::array<T, N> >::iterator(cont, cont.size());
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> const>::iterator
		range_end(std::array<T, N> const& cont) {
			return typename sprout::container_traits<std::array<T, N> const>::iterator(cont, cont.size());
		}
		// element access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::reference
		range_front(std::array<T, N>& cont) {
			typedef typename sprout::container_traits<std::array<T, N> >::reference type;
			return const_cast<type>(base_type::range_front(sprout::as_const(cont)));
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::reference
		range_back(std::array<T, N>& cont) {
			typedef typename sprout::container_traits<std::array<T, N> >::reference type;
			return const_cast<type>(base_type::range_back(sprout::as_const(cont)));
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::reference
		range_at(std::array<T, N>& cont, typename sprout::container_traits<std::array<T, N> >::size_type i) {
			typedef typename sprout::container_traits<std::array<T, N> >::reference type;
			return const_cast<type>(base_type::range_at(sprout::as_const(cont), i));
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::pointer
		range_data(std::array<T, N>& cont) {
			return sprout::addressof(range_front(cont));
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> const>::pointer
		range_data(std::array<T, N> const& cont) {
			return sprout::addressof(range_front(cont));
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_STD_ARRAY_HPP
