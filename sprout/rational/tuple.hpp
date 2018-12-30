/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RATIONAL_TUPLE_HPP
#define SPROUT_RATIONAL_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/rational/rational.hpp>
#include <sprout/tuple/tuple/tuple_traits.hpp>
#include <sprout/tuple/tuple/tuple_access_traits.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<std::size_t I, typename T>
			struct tuple_element_impl<I, sprout::rational<T> >
				: public sprout::detail::nil_base
			{};
			template<typename T>
			struct tuple_element_impl<0, sprout::rational<T> >
				: public sprout::identity<T>
			{};
			template<typename T>
			struct tuple_element_impl<1, sprout::rational<T> >
				: public sprout::identity<T>
			{};

			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T>
			struct get_impl<0, sprout::rational<T> > {
			public:
				SPROUT_CONSTEXPR T operator()(sprout::rational<T> const& t) const {
					return t.numerator();
				}
			};
			template<typename T>
			struct get_impl<1, sprout::rational<T> > {
			public:
				SPROUT_CONSTEXPR T operator()(sprout::rational<T> const& t) const {
					return t.denominator();
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
	struct tuple_size<sprout::rational<T> >
		: public sprout::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T>
	struct tuple_element<I, sprout::rational<T> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::rational<T> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

namespace sprout {
	namespace tuples {
		//
		// tuple_traits
		//
		template<typename T>
		struct tuple_traits<sprout::rational<T> > {
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t size = sprout::tuples::tuple_size<sprout::rational<T> >::value;
		public:
			template<std::size_t I>
			struct element
				: public sprout::tuples::tuple_element<I, sprout::rational<T> >
			{};
			template<std::size_t I>
			struct lvalue_reference
				: public element<I>
			{};
			template<std::size_t I>
			struct const_lvalue_reference
				: public element<I>
			{};
			template<std::size_t I>
			struct rvalue_reference
				: public element<I>
			{};
			template<std::size_t I>
			struct const_rvalue_reference
				: public element<I>
			{};
		};
		template<typename T>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::tuples::tuple_traits<sprout::rational<T> >::size;

		//
		// tuple_access_traits
		//
		template<typename T>
		struct tuple_access_traits<sprout::rational<T> > {
		public:
			template<std::size_t I>
			static SPROUT_CONSTEXPR T
			tuple_get(sprout::rational<T> const& t) SPROUT_NOEXCEPT {
				static_assert(I < 2, "tuple_get: index out of range");
				return sprout::tuples::detail::get_impl<I, sprout::rational<T> >()(t);
			}
		};
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_RATIONAL_TUPLE_HPP
