/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PAIR_TUPLE_HPP
#define SPROUT_UTILITY_PAIR_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<std::size_t I, typename T1, typename T2>
			struct tuple_element_impl<I, sprout::pair<T1, T2> >
				: public sprout::detail::nil_base
			{};
			template<typename T1, typename T2>
			struct tuple_element_impl<0, sprout::pair<T1, T2> >
				: public sprout::identity<T1>
			{};
			template<typename T1, typename T2>
			struct tuple_element_impl<1, sprout::pair<T1, T2> >
				: public sprout::identity<T2>
			{};

			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T1, typename T2>
			struct get_impl<0, sprout::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T1& operator()(sprout::pair<T1, T2>& t) const {
					return t.first;
				}
				SPROUT_CONSTEXPR T1 const& operator()(sprout::pair<T1, T2> const& t) const {
					return t.first;
				}
			};
			template<typename T1, typename T2>
			struct get_impl<1, sprout::pair<T1, T2> > {
			public:
				SPROUT_CONSTEXPR T2& operator()(sprout::pair<T1, T2>& t) const {
					return t.second;
				}
				SPROUT_CONSTEXPR T2 const& operator()(sprout::pair<T1, T2> const& t) const {
					return t.second;
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
	template<typename T1, typename T2>
	struct tuple_size<sprout::pair<T1, T2> >
		: public sprout::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T1, typename T2>
	struct tuple_element<I, sprout::pair<T1, T2> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::pair<T1, T2> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type&
	tuple_get(sprout::pair<T1, T2>& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::pair<T1, T2> >()(t);
	}
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type const&
	tuple_get(sprout::pair<T1, T2> const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::pair<T1, T2> >()(t);
	}
	template<std::size_t I, typename T1, typename T2>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type&&
	tuple_get(sprout::pair<T1, T2>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_TUPLE_HPP
