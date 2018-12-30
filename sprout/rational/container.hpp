/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_CONTAINER_HPP
#define SPROUT_RATIONAL_CONTAINER_HPP

#include <stdexcept>
#include <type_traits>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/index_iterator.hpp>

namespace sprout {
	namespace detail {
		struct rational_at {
		public:
			template<typename Rational, typename Index>
			SPROUT_CONSTEXPR typename Rational::value_type
			operator()(Rational const& c, Index i) const {
				return i == 0 ? c.numerator()
					: i == 1 ? c.denominator()
					: throw std::out_of_range("rational_at: index out of range")
					;
			}
		};
	}	// namespace detail

	//
	// container_traits
	//
	template<typename T>
	struct container_traits<sprout::rational<T> > {
	public:
		typedef T value_type;
		typedef sprout::index_iterator<sprout::rational<T>&, true, sprout::detail::rational_at> iterator;
		typedef sprout::index_iterator<sprout::rational<T> const&, true, sprout::detail::rational_at> const_iterator;
		typedef T reference;
		typedef T const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T const* const_pointer;
	public:
		SPROUT_STATIC_CONSTEXPR size_type static_size = 2;
	public:
		static SPROUT_CONSTEXPR size_type
		fixed_size() SPROUT_NOEXCEPT {
			return static_size;
		}
	};
	template<typename T>
	SPROUT_CONSTEXPR_OR_CONST typename sprout::container_traits<sprout::rational<T> >::size_type
	sprout::container_traits<sprout::rational<T> >::static_size;

	//
	// container_range_traits
	//
	template<typename T>
	struct container_range_traits<sprout::rational<T> >
		: public sprout::container_range_traits_default<sprout::rational<T> >
	{
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<sprout::rational<T> >::iterator
		range_begin(sprout::rational<T>& cont) {
			return typename sprout::container_traits<sprout::rational<T> >::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<sprout::rational<T> const>::iterator
		range_begin(sprout::rational<T> const& cont) {
			return typename sprout::container_traits<sprout::rational<T> const>::iterator(cont, 0);
		}

		static SPROUT_CONSTEXPR typename sprout::container_traits<sprout::rational<T> >::iterator
		range_end(sprout::rational<T>& cont) {
			return typename sprout::container_traits<sprout::rational<T> >::iterator(cont, 2);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<sprout::rational<T> const>::iterator
		range_end(sprout::rational<T> const& cont) {
			return typename sprout::container_traits<sprout::rational<T> const>::iterator(cont, 2);
		}
	};

	//
	// container_construct_traits
	//
	template<typename T>
	struct container_construct_traits<sprout::rational<T> > {
	public:
		typedef sprout::rational<T> copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type
		deep_copy(Cont&& cont) {
			return SPROUT_FORWARD(Cont, cont);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type
		make(Args&&... args) {
			return copied_type(SPROUT_FORWARD(Args, args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type
		remake(Cont&&, typename sprout::container_traits<sprout::rational<T> >::difference_type, Args&&... args) {
			return copied_type(SPROUT_FORWARD(Args, args)...);
		}
	};

	//
	// container_transform_traits
	//
	template<typename T>
	struct container_transform_traits<sprout::rational<T> > {
	public:
		template<typename Type>
		struct rebind_type {
		public:
			typedef sprout::rational<Type> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_RATIONAL_CONTAINER_HPP
