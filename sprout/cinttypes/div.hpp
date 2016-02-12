/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CINTTYPES_DIV_HPP
#define SPROUT_CINTTYPES_DIV_HPP

#include <cstdlib>
#include <cstdint>
#if !defined(_MSC_VER)
#	include <cinttypes>
#endif
#include <functional>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	//
	// imaxdiv_t
	//
#if defined(_MSC_VER)
	struct imaxdiv_t {
	public:
		std::intmax_t quot;
		std::intmax_t rem;
	};
#else
	typedef std::imaxdiv_t imaxdiv_t;
#endif

	namespace detail {
		template<typename T>
		struct div_t_traits2 {};

#	define SPROUT_DETAIL_DIV_T_TRAITS2_IMPL(INT_T, DIV_T) \
		template<> \
		struct div_t_traits2<INT_T> { \
		public: \
			typedef DIV_T type; \
			SPROUT_STATIC_CONSTEXPR std::size_t offsetof_quot = offsetof(DIV_T, quot); \
			SPROUT_STATIC_CONSTEXPR std::size_t offsetof_rem = offsetof(DIV_T, rem); \
		}

		SPROUT_DETAIL_DIV_T_TRAITS2_IMPL(std::intmax_t, sprout::imaxdiv_t);
#	undef SPROUT_DETAIL_DIV_T_TRAITS2_IMPL

		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::div_t_traits2<T>::offsetof_quot == 0,
			typename sprout::detail::div_t_traits2<T>::type
		>::type
		div_impl2(T const& numer, T const& denom) {
#if defined(_MSC_VER) && (_MSC_VER > 1900)
			typename sprout::detail::div_t_traits2<T>::type result = {numer / denom, numer % denom};
			return result;
#else
			return {numer / denom, numer % denom};
#endif
		}

		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::div_t_traits2<T>::offsetof_rem == 0,
			typename sprout::detail::div_t_traits2<T>::type
		>::type
		div_impl2(T const& numer, T const& denom) {
#if defined(_MSC_VER) && (_MSC_VER > 1900)
			typename sprout::detail::div_t_traits2<T>::type result = {numer % denom, numer / denom};
			return result;
#else
			return {numer % denom, numer / denom};
#endif
		}
	}	// namespace detail

	inline SPROUT_CONSTEXPR sprout::imaxdiv_t
	imaxdiv(std::intmax_t numer, std::intmax_t denom) {
		return sprout::detail::div_impl2(numer, denom);
	}

	template<typename T>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		std::is_same<T, std::intmax_t>::value,
		sprout::imaxdiv_t
	>::type
	div(T numer, T denom) {
		return sprout::imaxdiv(numer, denom);
	}
}	// namespace sprout

namespace sprout {
	//
	// hash_value
	//
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::imaxdiv_t const& v) {
		return sprout::hash_values(v.quot, v.rem);
	}
}	// namespace sprout

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<std::size_t I>
			struct tuple_element_impl<I, sprout::imaxdiv_t>
				: public sprout::detail::nil_base
			{};
			template<>
			struct tuple_element_impl<0, sprout::imaxdiv_t>
				: public sprout::identity<std::intmax_t>
			{};
			template<>
			struct tuple_element_impl<1, sprout::imaxdiv_t>
				: public sprout::identity<std::intmax_t>
			{};

			template<std::size_t I, typename T>
			struct get_impl;
			template<>
			struct get_impl<0, sprout::imaxdiv_t> {
			public:
				SPROUT_CONSTEXPR std::intmax_t& operator()(sprout::imaxdiv_t& t) const {
					return t.quot;
				}
				SPROUT_CONSTEXPR std::intmax_t const& operator()(sprout::imaxdiv_t const& t) const {
					return t.quot;
				}
			};
			template<>
			struct get_impl<1, sprout::imaxdiv_t> {
			public:
				SPROUT_CONSTEXPR std::intmax_t& operator()(sprout::imaxdiv_t& t) const {
					return t.rem;
				}
				SPROUT_CONSTEXPR std::intmax_t const& operator()(sprout::imaxdiv_t const& t) const {
					return t.rem;
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
	template<>
	struct tuple_size<sprout::imaxdiv_t>
		: public sprout::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I>
	struct tuple_element<I, sprout::imaxdiv_t>
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::imaxdiv_t>
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::imaxdiv_t>::type&
	tuple_get(sprout::imaxdiv_t& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::imaxdiv_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::imaxdiv_t>::type const&
	tuple_get(sprout::imaxdiv_t const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::imaxdiv_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::imaxdiv_t>::type&&
	tuple_get(sprout::imaxdiv_t&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CINTTYPES_DIV_HPP
