#ifndef SPROUT_UTILITY_PAIR_PAIR_HPP
#define SPROUT_UTILITY_PAIR_PAIR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	//
	// pair
	//
	template <typename T1, typename T2>
	struct pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		T1 first;
		T2 second;
	private:
		template <typename... Args1, typename... Args2, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
		SPROUT_CONSTEXPR pair(
			sprout::tuples::tuple<Args1...> first_args,
			sprout::tuples::tuple<Args2...> second_args,
			sprout::index_tuple<Indexes1...>,
			sprout::index_tuple<Indexes2...>
			)
			: first(sprout::tuples::get<Indexes1>(first_args)...)
			, second(sprout::tuples::get<Indexes2>(second_args)...)
		{}
	public:
		pair(pair const&) = default;
		pair(pair&&) = default;
		SPROUT_CONSTEXPR pair()
			: first()
			, second()
		{}
		SPROUT_CONSTEXPR pair(T1 const& x, T2 const& y)
			: first(x)
			, second(y)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR pair(U&& x, V&& y)
			: first(sprout::forward<U>(x))
			, second(sprout::forward<V>(y))
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR pair(sprout::pair<U, V> const& p)
			: first(p.first)
			, second(p.second)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR pair(sprout::pair<U, V>&& p)
			: first(sprout::forward<U>(p.first))
			, second(sprout::forward<V>(p.second))
		{}
#if SPROUT_USE_DELEGATING_CONSTRUCTORS
		template <typename... Args1, typename... Args2>
		SPROUT_CONSTEXPR pair(
			sprout::tuples::tuple<Args1...> first_args,
			sprout::tuples::tuple<Args2...> second_args
			)
			: pair(
				first_args,
				second_args,
				sprout::index_range<0, sizeof...(Args1)>::make(),
				sprout::index_range<0, sizeof...(Args2)>::make()
				)
		{}
#else	// #if SPROUT_USE_DELEGATING_CONSTRUCTORS
		template <typename... Args1, typename... Args2>
		SPROUT_CONSTEXPR pair(
			sprout::tuples::tuple<Args1...> first_args,
			sprout::tuples::tuple<Args2...> second_args
			);
#endif	// #if SPROUT_USE_DELEGATING_CONSTRUCTORS
		pair& operator=(pair const& p) = default;
		template<typename U, typename V>
		pair& operator=(sprout::pair<U, V> const& p) {
			first = p.first;
			second = p.second;
			return *this;
		}
		pair& operator=(pair&& p)
		SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<T1>::value && std::is_nothrow_move_assignable<T2>::value)
		{
			first = sprout::forward<T1>(p.first);
			second = std::forward<T2>(p.second);
			return *this;
		}
		template<typename U, typename V>
		pair& operator=(sprout::pair<U, V>&& p) {
			first = std::forward<U>(p.first);
			second = std::forward<V>(p.second);
			return *this;
		}
		void swap(pair& p)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(swap(first, p.first))
			&& SPROUT_NOEXCEPT_EXPR(swap(second, p.second))
			)
		{
			sprout::swap(first, p.first);
			sprout::swap(second, p.second);
		}
	};

	//
	// swap
	//
	template<class T1, class T2>
	inline void
	swap(sprout::pair<T1, T2>& lhs, sprout::pair<T1, T2>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_PAIR_HPP
