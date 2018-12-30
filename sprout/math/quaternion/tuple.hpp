/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_QUATERNION_TUPLE_HPP
#define SPROUT_MATH_QUATERNION_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/math/quaternion/quaternion.hpp>
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
			struct tuple_element_impl<I, sprout::math::quaternion<T> >
				: public sprout::detail::nil_base
			{};
			template<typename T>
			struct tuple_element_impl<0, sprout::math::quaternion<T> >
				: public sprout::identity<T>
			{};
			template<typename T>
			struct tuple_element_impl<1, sprout::math::quaternion<T> >
				: public sprout::identity<T>
			{};
			template<typename T>
			struct tuple_element_impl<2, sprout::math::quaternion<T> >
				: public sprout::identity<T>
			{};
			template<typename T>
			struct tuple_element_impl<3, sprout::math::quaternion<T> >
				: public sprout::identity<T>
			{};

			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T>
			struct get_impl<0, sprout::math::quaternion<T> > {
			public:
				SPROUT_CONSTEXPR T& operator()(sprout::math::quaternion<T>& t) const {
					return t[0];
				}
				SPROUT_CONSTEXPR T const& operator()(sprout::math::quaternion<T> const& t) const {
					return t[0];
				}
			};
			template<typename T>
			struct get_impl<1, sprout::math::quaternion<T> > {
			public:
				SPROUT_CONSTEXPR T& operator()(sprout::math::quaternion<T>& t) const {
					return t[1];
				}
				SPROUT_CONSTEXPR T const& operator()(sprout::math::quaternion<T> const& t) const {
					return t[1];
				}
			};
			template<typename T>
			struct get_impl<2, sprout::math::quaternion<T> > {
			public:
				SPROUT_CONSTEXPR T& operator()(sprout::math::quaternion<T>& t) const {
					return t[2];
				}
				SPROUT_CONSTEXPR T const& operator()(sprout::math::quaternion<T> const& t) const {
					return t[2];
				}
			};
			template<typename T>
			struct get_impl<3, sprout::math::quaternion<T> > {
			public:
				SPROUT_CONSTEXPR T& operator()(sprout::math::quaternion<T>& t) const {
					return t[3];
				}
				SPROUT_CONSTEXPR T const& operator()(sprout::math::quaternion<T> const& t) const {
					return t[3];
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
	struct tuple_size<sprout::math::quaternion<T> >
		: public sprout::integral_constant<std::size_t, 4>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T>
	struct tuple_element<I, sprout::math::quaternion<T> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::math::quaternion<T> >
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
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::math::quaternion<T> >::type&
	tuple_get(sprout::math::quaternion<T>& t) SPROUT_NOEXCEPT {
		static_assert(I < 4, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::math::quaternion<T> >()(t);
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::math::quaternion<T> >::type const&
	tuple_get(sprout::math::quaternion<T> const& t) SPROUT_NOEXCEPT {
		static_assert(I < 4, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::math::quaternion<T> >()(t);
	}
	template<std::size_t I, typename T>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::math::quaternion<T> >::type&&
	tuple_get(sprout::math::quaternion<T>&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_QUATERNION_TUPLE_HPP
