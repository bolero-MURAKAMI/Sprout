/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPLEX_TUPLE_HPP
#define SPROUT_COMPLEX_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/complex/complex.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<std::size_t I, typename T>
			struct tuple_element_impl<I, sprout::complex<T> >
				: public sprout::detail::nil_base
			{};
			template<typename T>
			struct tuple_element_impl<0, sprout::complex<T> >
				: public sprout::identity<T>
			{};
			template<typename T>
			struct tuple_element_impl<1, sprout::complex<T> >
				: public sprout::identity<T>
			{};

			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T>
			struct get_impl<0, sprout::complex<T> > {
			public:
				SPROUT_CONSTEXPR T& operator()(sprout::complex<T>& t) const {
					return t.real();
				}
				SPROUT_CONSTEXPR T const& operator()(sprout::complex<T> const& t) const {
					return t.real();
				}
			};
			template<typename T>
			struct get_impl<1, sprout::complex<T> > {
			public:
				SPROUT_CONSTEXPR T& operator()(sprout::complex<T>& t) const {
					return t.imag();
				}
				SPROUT_CONSTEXPR T const& operator()(sprout::complex<T> const& t) const {
					return t.imag();
				}
			};
		}	// namespace detail
	}	// namespace tuples
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename T>
	struct tuple_size<sprout::complex<T> >
		: public sprout::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T>
	struct tuple_element<I, sprout::complex<T> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::complex<T> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::complex<T> >::type&
	tuple_get(sprout::complex<T>& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::complex<T> >()(t);
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::complex<T> >::type const&
	tuple_get(sprout::complex<T> const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::complex<T> >()(t);
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::complex<T> >::type&&
	tuple_get(sprout::complex<T>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPLEX_TUPLE_HPP
