/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_STD_COMPLEX_HPP
#define SPROUT_CONTAINER_STD_COMPLEX_HPP

#include <complex>
#include <type_traits>
#include <stdexcept>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/index_iterator.hpp>

namespace sprout {
	namespace detail {
		struct std_complex_at {
		public:
			template<typename Complex, typename Index>
			SPROUT_CONSTEXPR typename Complex::value_type
			operator()(Complex const& c, Index i) const {
				return i == 0 ? c.real()
					: i == 1 ? c.imag()
					: throw std::out_of_range("std_complex_at<>: index out of range")
					;
			}
		};
	}	// namespace detail

	//
	// container_traits
	//
	template<typename T>
	struct container_traits<std::complex<T> > {
	public:
		typedef T value_type;
		typedef sprout::index_iterator<std::complex<T>&, true, sprout::detail::std_complex_at> iterator;
		typedef sprout::index_iterator<std::complex<T> const&, true, sprout::detail::std_complex_at> const_iterator;
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
	SPROUT_CONSTEXPR_OR_CONST typename sprout::container_traits<std::complex<T> >::size_type
	sprout::container_traits<std::complex<T> >::static_size;

	//
	// container_range_traits
	//
	template<typename T>
	struct container_range_traits<std::complex<T> >
		: public sprout::detail::container_range_traits_default<std::complex<T> >
	{
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::complex<T> >::iterator
		range_begin(std::complex<T>& cont) {
			return typename sprout::container_traits<std::complex<T> >::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::complex<T> const>::iterator
		range_begin(std::complex<T> const& cont) {
			return typename sprout::container_traits<std::complex<T> const>::iterator(cont, 0);
		}

		static SPROUT_CONSTEXPR typename sprout::container_traits<std::complex<T> >::iterator
		range_end(std::complex<T>& cont) {
			return typename sprout::container_traits<std::complex<T> >::iterator(cont, 2);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::complex<T> const>::iterator
		range_end(std::complex<T> const& cont) {
			return typename sprout::container_traits<std::complex<T> const>::iterator(cont, 2);
		}
	};

	//
	// container_construct_traits
	//
	template<typename T>
	struct container_construct_traits<std::complex<T> > {
	public:
		typedef std::complex<T> copied_type;
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
		remake(Cont&&, typename sprout::container_traits<std::complex<T> >::difference_type, Args&&... args) {
			return copied_type(SPROUT_FORWARD(Args, args)...);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_STD_COMPLEX_HPP
