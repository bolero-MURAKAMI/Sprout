#ifndef SPROUT_UTILITY_PAIR_PAIR_HPP
#define SPROUT_UTILITY_PAIR_PAIR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pair/pair_decl.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	//
	// pair
	//
	template <typename T1, typename T2>
	template <typename... Args1, typename... Args2, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(
		sprout::tuples::tuple<Args1...> first_args,
		sprout::tuples::tuple<Args2...> second_args,
		sprout::index_tuple<Indexes1...>,
		sprout::index_tuple<Indexes2...>
		)
		: first(sprout::tuples::get<Indexes1>(first_args)...)
		, second(sprout::tuples::get<Indexes2>(second_args)...)
	{}
	template <typename T1, typename T2>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(pair const&) = default;
	template <typename T1, typename T2>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(pair&&) = default;
	template <typename T1, typename T2>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair()
		: first()
		, second()
	{}
	template <typename T1, typename T2>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(T1 const& x, T2 const& y)
		: first(x)
		, second(y)
	{}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(U&& x, V&& y)
		: first(sprout::forward<U>(x))
		, second(sprout::forward<V>(y))
	{}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(sprout::pair<U, V> const& other)
		: first(other.first)
		, second(other.second)
	{}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(sprout::pair<U, V>&& other)
		: first(sprout::forward<U>(other.first))
		, second(sprout::forward<V>(other.second))
	{}
#if SPROUT_USE_DELEGATING_CONSTRUCTORS
	template <typename T1, typename T2>
	template<
		typename... Args1, typename... Args2,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(
		std::piecewise_construct_t,
		sprout::tuples::tuple<Args1...> first_args, sprout::tuples::tuple<Args2...> second_args
		)
		: pair(
			first_args,
			second_args,
			sprout::make_index_tuple<sizeof...(Args1)>::make(),
			sprout::make_index_tuple<sizeof...(Args2)>::make()
			)
	{}
#endif	// #if SPROUT_USE_DELEGATING_CONSTRUCTORS
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(sprout::tuples::tuple<U, V> const& other)
		: first(sprout::tuples::get<0>(other))
		, second(sprout::tuples::get<1>(other))
	{}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline SPROUT_CONSTEXPR sprout::pair<T1, T2>::pair(sprout::tuples::tuple<U, V>&& other)
		: first(sprout::forward<U>(sprout::tuples::get<0>(other)))
		, second(sprout::forward<V>(sprout::tuples::get<1>(other)))
	{}

	template <typename T1, typename T2>
	inline sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(pair const& rhs) = default;
	template <typename T1, typename T2>
	inline sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(pair&& rhs)
	SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<T1>::value && std::is_nothrow_move_assignable<T2>::value)
	{
		first = sprout::forward<T1>(rhs.first);
		second = sprout::forward<T2>(rhs.second);
		return *this;
	}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(sprout::pair<U, V> const& rhs) {
		first = rhs.first;
		second = rhs.second;
		return *this;
	}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(sprout::pair<U, V>&& rhs) {
		first = sprout::forward<U>(rhs.first);
		second = sprout::forward<V>(rhs.second);
		return *this;
	}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(sprout::tuples::tuple<U, V> const& rhs) {
		first = sprout::tuples::get<0>(rhs);
		second = sprout::tuples::get<0>(rhs);
		return *this;
	}
	template <typename T1, typename T2>
	template<
		typename U, typename V,
		typename
	>
	inline sprout::pair<T1, T2>& sprout::pair<T1, T2>::operator=(sprout::tuples::tuple<U, V>&& rhs) {
		first = sprout::forward<U>(sprout::tuples::get<0>(rhs));
		second = sprout::forward<V>(sprout::tuples::get<1>(rhs));
		return *this;
	}

	template <typename T1, typename T2>
	inline void sprout::pair<T1, T2>::swap(pair& other)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(first, other.first)) && SPROUT_NOEXCEPT_EXPR(sprout::swap(second, other.second))) {
		sprout::swap(first, other.first);
		sprout::swap(second, other.second);
	}

	//
	// swap
	//
	template<typename T1, typename T2>
	inline void
	swap(sprout::pair<T1, T2>& lhs, sprout::pair<T1, T2>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_PAIR_HPP
