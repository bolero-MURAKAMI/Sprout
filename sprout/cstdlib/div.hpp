/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_DIV_HPP
#define SPROUT_CSTDLIB_DIV_HPP

#include <cstdlib>
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
	// div_t
	// ldiv_t
	// lldiv_t
	//
	typedef std::div_t div_t;
	typedef std::ldiv_t ldiv_t;
	typedef std::lldiv_t lldiv_t;

	namespace detail {
		template<typename T>
		struct div_t_traits {};

#	define SPROUT_DETAIL_DIV_T_TRAITS_IMPL(INT_T, DIV_T) \
		template<> \
		struct div_t_traits<INT_T> { \
		public: \
			typedef DIV_T type; \
			SPROUT_STATIC_CONSTEXPR std::size_t offsetof_quot = offsetof(DIV_T, quot); \
			SPROUT_STATIC_CONSTEXPR std::size_t offsetof_rem = offsetof(DIV_T, rem); \
		}

		SPROUT_DETAIL_DIV_T_TRAITS_IMPL(int, sprout::div_t);
		SPROUT_DETAIL_DIV_T_TRAITS_IMPL(long, sprout::ldiv_t);
		SPROUT_DETAIL_DIV_T_TRAITS_IMPL(long long, sprout::lldiv_t);
#	undef SPROUT_DETAIL_DIV_T_TRAITS_IMPL

		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::div_t_traits<T>::offsetof_quot == 0,
			typename sprout::detail::div_t_traits<T>::type
		>::type
		div_impl(T const& numer, T const& denom) {
#if defined(_MSC_VER)
			typename sprout::detail::div_t_traits<T>::type result = {numer / denom, numer % denom};
			return result;
#else
			return {numer / denom, numer % denom};
#endif
		}

		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::detail::div_t_traits<T>::offsetof_rem == 0,
			typename sprout::detail::div_t_traits<T>::type
		>::type
		div_impl(T const& numer, T const& denom) {
#if defined(_MSC_VER)
			typename sprout::detail::div_t_traits<T>::type result = {numer % denom, numer / denom};
			return result;
#else
			return {numer % denom, numer / denom};
#endif
		}
	}	// namespace detail

	// 7.20.6.2 divÅCldivÅCãyÇ— lldiv ä÷êî
	inline SPROUT_CONSTEXPR sprout::div_t
	div(int numer, int denom) {
		return sprout::detail::div_impl(numer, denom);
	}

	inline SPROUT_CONSTEXPR sprout::ldiv_t
	ldiv(long numer, long denom) {
		return sprout::detail::div_impl(numer, denom);
	}

	inline SPROUT_CONSTEXPR sprout::lldiv_t
	lldiv(long long numer, long long denom) {
		return sprout::detail::div_impl(numer, denom);
	}

	inline SPROUT_CONSTEXPR sprout::ldiv_t
	div(long numer, long denom) {
		return sprout::ldiv(numer, denom);
	}

	inline SPROUT_CONSTEXPR sprout::lldiv_t
	div(long long numer, long long denom) {
		return sprout::lldiv(numer, denom);
	}
}	// namespace sprout

namespace sprout {
	//
	// hash_value
	//
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::div_t const& v) {
		return sprout::hash_values(v.quot, v.rem);
	}
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::ldiv_t const& v) {
		return sprout::hash_values(v.quot, v.rem);
	}
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::lldiv_t const& v) {
		return sprout::hash_values(v.quot, v.rem);
	}
}	// namespace sprout

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<std::size_t I>
			struct tuple_element_impl<I, sprout::div_t>
				: public sprout::detail::nil_base
			{};
			template<>
			struct tuple_element_impl<0, sprout::div_t>
				: public sprout::identity<int>
			{};
			template<>
			struct tuple_element_impl<1, sprout::div_t>
				: public sprout::identity<int>
			{};
			template<std::size_t I>
			struct tuple_element_impl<I, sprout::ldiv_t>
				: public sprout::detail::nil_base
			{};
			template<>
			struct tuple_element_impl<0, sprout::ldiv_t>
				: public sprout::identity<long>
			{};
			template<>
			struct tuple_element_impl<1, sprout::ldiv_t>
				: public sprout::identity<long>
			{};
			template<std::size_t I>
			struct tuple_element_impl<I, sprout::lldiv_t>
				: public sprout::detail::nil_base
			{};
			template<>
			struct tuple_element_impl<0, sprout::lldiv_t>
				: public sprout::identity<long long>
			{};
			template<>
			struct tuple_element_impl<1, sprout::lldiv_t>
				: public sprout::identity<long long>
			{};

			template<std::size_t I, typename T>
			struct get_impl;
			template<>
			struct get_impl<0, sprout::div_t> {
			public:
				SPROUT_CONSTEXPR int& operator()(sprout::div_t& t) const {
					return t.quot;
				}
				SPROUT_CONSTEXPR int const& operator()(sprout::div_t const& t) const {
					return t.quot;
				}
			};
			template<>
			struct get_impl<1, sprout::div_t> {
			public:
				SPROUT_CONSTEXPR int& operator()(sprout::div_t& t) const {
					return t.rem;
				}
				SPROUT_CONSTEXPR int const& operator()(sprout::div_t const& t) const {
					return t.rem;
				}
			};
			template<>
			struct get_impl<0, sprout::ldiv_t> {
			public:
				SPROUT_CONSTEXPR long& operator()(sprout::ldiv_t& t) const {
					return t.quot;
				}
				SPROUT_CONSTEXPR long const& operator()(sprout::ldiv_t const& t) const {
					return t.quot;
				}
			};
			template<>
			struct get_impl<1, sprout::ldiv_t> {
			public:
				SPROUT_CONSTEXPR long& operator()(sprout::ldiv_t& t) const {
					return t.rem;
				}
				SPROUT_CONSTEXPR long const& operator()(sprout::ldiv_t const& t) const {
					return t.rem;
				}
			};
			template<>
			struct get_impl<0, sprout::lldiv_t> {
			public:
				SPROUT_CONSTEXPR long long& operator()(sprout::lldiv_t& t) const {
					return t.quot;
				}
				SPROUT_CONSTEXPR long long const& operator()(sprout::lldiv_t const& t) const {
					return t.quot;
				}
			};
			template<>
			struct get_impl<1, sprout::lldiv_t> {
			public:
				SPROUT_CONSTEXPR long long& operator()(sprout::lldiv_t& t) const {
					return t.rem;
				}
				SPROUT_CONSTEXPR long long const& operator()(sprout::lldiv_t const& t) const {
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
	struct tuple_size<sprout::div_t>
		: public sprout::integral_constant<std::size_t, 2>
	{};
	template<>
	struct tuple_size<sprout::ldiv_t>
		: public sprout::integral_constant<std::size_t, 2>
	{};
	template<>
	struct tuple_size<sprout::lldiv_t>
		: public sprout::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I>
	struct tuple_element<I, sprout::div_t>
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::div_t>
	{};
	template<std::size_t I>
	struct tuple_element<I, sprout::ldiv_t>
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::ldiv_t>
	{};
	template<std::size_t I>
	struct tuple_element<I, sprout::lldiv_t>
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::lldiv_t>
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
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::div_t>::type&
	tuple_get(sprout::div_t& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::div_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::div_t>::type const&
	tuple_get(sprout::div_t const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::div_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::div_t>::type&&
	tuple_get(sprout::div_t&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::ldiv_t>::type&
	tuple_get(sprout::ldiv_t& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::ldiv_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::ldiv_t>::type const&
	tuple_get(sprout::ldiv_t const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::ldiv_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::ldiv_t>::type&&
	tuple_get(sprout::ldiv_t&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::lldiv_t>::type&
	tuple_get(sprout::lldiv_t& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::lldiv_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::lldiv_t>::type const&
	tuple_get(sprout::lldiv_t const& t) SPROUT_NOEXCEPT {
		static_assert(I < 2, "tuple_get: index out of range");
		return sprout::tuples::detail::get_impl<I, sprout::lldiv_t>()(t);
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::lldiv_t>::type&&
	tuple_get(sprout::lldiv_t&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_DIV_HPP
