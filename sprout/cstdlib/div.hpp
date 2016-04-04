/*=============================================================================
  Copyright (c) 2011 RiSK (sscrisk)
  https://github.com/sscrisk/CEL---ConstExpr-Library

  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTDLIB_DIV_HPP
#define SPROUT_CSTDLIB_DIV_HPP

#include <cstdlib>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/iterator/reverse_iterator.hpp>
#include <sprout/functional/transparent.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>
#include <sprout/detail/static_size.hpp>

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
#if defined(_MSC_VER) && (_MSC_VER > 1900)
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

namespace sprout {
	namespace detail {
		template<typename Div>
		SPROUT_CONSTEXPR typename std::remove_reference<decltype(std::declval<Div>().quot)>::type&
		div_at(Div& d, std::size_t i)
		SPROUT_NOEXCEPT_IF_EXPR(std::declval<Div>().quot)
		{
			return i == 0 ? d.quot
				: i == 1 ? d.rem
				: (throw std::out_of_range("div_at: index out of range"), d.quot)
				;
		}
		template<typename Div>
		SPROUT_CONSTEXPR typename std::remove_reference<decltype(std::declval<Div>().quot)>::type const&
		div_at(Div const& d, std::size_t i)
		SPROUT_NOEXCEPT_IF_EXPR(std::declval<Div>().quot)
		{
			return i == 0 ? d.quot
				: i == 1 ? d.rem
				: (throw std::out_of_range("div_at: index out of range"), d.quot)
				;
		}

		template<typename T = void>
		struct div_at_f;
		template<>
		struct div_at_f<void>
			: public sprout::transparent<>
		{
		public:
			template<typename T, typename U>
			SPROUT_CONSTEXPR decltype(sprout::detail::div_at(std::declval<T>(), std::declval<U>()))
			operator()(T&& x, U&& y)
			const SPROUT_NOEXCEPT_IF_EXPR(sprout::detail::div_at(std::declval<T>(), std::declval<U>()))
			{
				return sprout::detail::div_at(SPROUT_FORWARD(T, x), SPROUT_FORWARD(U, y));
			}
		};
	}	// namespace detail

	//
	// container_traits
	//
#	define SPROUT_DETAIL_DIV_T_CONTAINER_TRAITS_IMPL(INT_T, DIV_T) \
	template<> \
	struct container_traits<DIV_T> \
		: public sprout::detail::base_static_size<std::size_t, 2> \
	{ \
	public: \
		typedef INT_T value_type; \
		typedef sprout::index_iterator<DIV_T&, false, sprout::detail::div_at_f<> > iterator; \
		typedef sprout::index_iterator<DIV_T const&, false, sprout::detail::div_at_f<> > const_iterator; \
		typedef INT_T& reference; \
		typedef INT_T const& const_reference; \
		typedef std::size_t size_type; \
		typedef std::ptrdiff_t difference_type; \
		typedef INT_T* pointer; \
		typedef INT_T const* const_pointer; \
		typedef sprout::reverse_iterator<iterator> reverse_iterator; \
		typedef sprout::reverse_iterator<const_iterator> const_reverse_iterator; \
	}

	SPROUT_DETAIL_DIV_T_CONTAINER_TRAITS_IMPL(int, sprout::div_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_TRAITS_IMPL(long, sprout::ldiv_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_TRAITS_IMPL(long long, sprout::lldiv_t);

	//
	// container_range_traits
	//
#	define SPROUT_DETAIL_DIV_T_CONTAINER_RANGE_TRAITS_IMPL(INT_T, DIV_T) \
	template<> \
	struct container_range_traits<DIV_T> { \
	public: \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::iterator \
		range_begin(DIV_T& t) { \
			typedef typename sprout::container_traits<DIV_T>::iterator type; \
			return type(t, 0); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T const>::iterator \
		range_begin(DIV_T const& t) { \
			typedef typename sprout::container_traits<DIV_T const>::iterator type; \
			return type(t, 0); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::iterator \
		range_end(DIV_T& t) { \
			typedef typename sprout::container_traits<DIV_T>::iterator type; \
			return type(t, 2); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T const>::iterator \
		range_end(DIV_T const& t) { \
			typedef typename sprout::container_traits<DIV_T const>::iterator type; \
			return type(t, 2); \
		} \
		 \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::size_type \
		range_size(DIV_T const&) { \
			return 2; \
		} \
		static SPROUT_CONSTEXPR bool \
		range_empty(DIV_T const&) { \
			return false; \
		} \
		 \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::reference \
		range_front(DIV_T& t) { \
			return sprout::detail::div_at(t, 0); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T const>::reference \
		range_front(DIV_T const& t) { \
			return sprout::detail::div_at(t, 0); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::reference \
		range_back(DIV_T& t) { \
			return sprout::detail::div_at(t, 1); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T const>::reference \
		range_back(DIV_T const& t) { \
			return sprout::detail::div_at(t, 1); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::reference \
		range_at(DIV_T& t, typename sprout::container_traits<DIV_T>::size_type i) { \
			return sprout::detail::div_at(t, i); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T const>::reference \
		range_at(DIV_T const& t, typename sprout::container_traits<DIV_T const>::size_type i) { \
			return sprout::detail::div_at(t, i); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::iterator \
		range_nth(DIV_T& t, typename sprout::container_traits<DIV_T>::size_type i) { \
			typedef typename sprout::container_traits<DIV_T>::iterator type; \
			return type(t, 0) + i; \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T const>::iterator \
		range_nth(DIV_T const& t, typename sprout::container_traits<DIV_T const>::size_type i) { \
			typedef typename sprout::container_traits<DIV_T const>::iterator type; \
			return type(t, 0) + i; \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T>::size_type \
		range_index_of(DIV_T& t, typename sprout::container_traits<DIV_T>::iterator p) { \
			typedef typename sprout::container_traits<DIV_T>::iterator type; \
			return sprout::distance(type(t, 0), p); \
		} \
		static SPROUT_CONSTEXPR typename sprout::container_traits<DIV_T const>::size_type \
		range_index_of(DIV_T const& t, typename sprout::container_traits<DIV_T const>::iterator p) { \
			typedef typename sprout::container_traits<DIV_T const>::iterator type; \
			return sprout::distance(type(t, 0), p); \
		} \
	}

	SPROUT_DETAIL_DIV_T_CONTAINER_RANGE_TRAITS_IMPL(int, sprout::div_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_RANGE_TRAITS_IMPL(long, sprout::ldiv_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_RANGE_TRAITS_IMPL(long long, sprout::lldiv_t);

	//
	// container_construct_traits
	//
#	define SPROUT_DETAIL_DIV_T_CONTAINER_CONSTRUCT_TRAITS_IMPL(INT_T, DIV_T) \
	template<> \
	struct container_construct_traits<DIV_T> { \
	public: \
		typedef DIV_T copied_type; \
	public: \
		template<typename Cont> \
		static SPROUT_CONSTEXPR copied_type \
		deep_copy(Cont&& cont) { \
			return SPROUT_FORWARD(Cont, cont); \
		} \
		template<typename... Args> \
		static SPROUT_CONSTEXPR copied_type \
		make(Args&&... args) { \
			return sprout::detail::div_impl<INT_T>(SPROUT_FORWARD(Args, args)...); \
		} \
		template<typename Cont, typename... Args> \
		static SPROUT_CONSTEXPR copied_type \
		remake(Cont&&, typename sprout::container_traits<DIV_T>::difference_type size, Args&&... args) { \
			return sprout::detail::div_impl<INT_T>(SPROUT_FORWARD(Args, args)...); \
		} \
	}

	SPROUT_DETAIL_DIV_T_CONTAINER_CONSTRUCT_TRAITS_IMPL(int, sprout::div_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_CONSTRUCT_TRAITS_IMPL(long, sprout::ldiv_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_CONSTRUCT_TRAITS_IMPL(long long, sprout::lldiv_t);

	//
	// container_transform_traits
	//
#	define SPROUT_DETAIL_DIV_T_CONTAINER_TRANSFORM_TRAITS_IMPL(INT_T, DIV_T) \
	template<> \
	struct container_transform_traits<DIV_T> { \
	public: \
		template<typename Type> \
		struct rebind_type { \
		public: \
			typedef typename sprout::detail::div_t_traits<Type>::type type; \
		}; \
	}

	SPROUT_DETAIL_DIV_T_CONTAINER_TRANSFORM_TRAITS_IMPL(int, sprout::div_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_TRANSFORM_TRAITS_IMPL(long, sprout::ldiv_t);
	SPROUT_DETAIL_DIV_T_CONTAINER_TRANSFORM_TRAITS_IMPL(long long, sprout::lldiv_t);
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTDLIB_DIV_HPP
