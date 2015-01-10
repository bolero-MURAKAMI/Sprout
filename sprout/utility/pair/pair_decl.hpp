/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_PAIR_PAIR_DECL_HPP
#define SPROUT_UTILITY_PAIR_PAIR_DECL_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pair/pair_fwd.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>

namespace sprout {
	//
	// pair
	//
	template<typename T1, typename T2>
	struct pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;
	public:
		T1 first;
		T2 second;
	private:
		template<typename... Args1, typename... Args2, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
		SPROUT_CONSTEXPR pair(
			sprout::tuples::tuple<Args1...> first_args, sprout::tuples::tuple<Args2...> second_args,
			sprout::index_tuple<Indexes1...>, sprout::index_tuple<Indexes2...>
			);
	public:
		SPROUT_CONSTEXPR pair()
			: first()
			, second()
		{}
		pair(pair const&) = default;
		pair(pair&&) = default;
		SPROUT_CONSTEXPR pair(T1 const& x, T2 const& y)
			: first(x)
			, second(y)
		{}
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_constructible<first_type, U&&>::value && std::is_constructible<second_type, V&&>::value
			>::type
		>
		SPROUT_CONSTEXPR pair(U&& x, V&& y)
			: first(SPROUT_FORWARD(U, x))
			, second(SPROUT_FORWARD(V, y))
		{}
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_constructible<first_type, U const&>::value && std::is_constructible<second_type, V const&>::value
			>::type
		>
		SPROUT_CONSTEXPR pair(sprout::pair<U, V> const& other)
			: first(other.first)
			, second(other.second)
		{}
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_constructible<first_type, U&&>::value && std::is_constructible<second_type, V&&>::value
			>::type
		>
		SPROUT_CONSTEXPR pair(sprout::pair<U, V>&& other)
			: first(SPROUT_FORWARD(U, other.first))
			, second(SPROUT_FORWARD(V, other.second))
		{}
		template<
			typename... Args1, typename... Args2,
			typename = typename std::enable_if<
				std::is_constructible<first_type, Args1&&...>::value && std::is_constructible<second_type, Args2&&...>::value
			>::type
		>
		SPROUT_CONSTEXPR pair(
			std::piecewise_construct_t,
			sprout::tuples::tuple<Args1...> first_args, sprout::tuples::tuple<Args2...> second_args
			);

		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_constructible<first_type, U const&>::value && std::is_constructible<second_type, V const&>::value
			>::type
		>
		SPROUT_CONSTEXPR pair(sprout::tuples::tuple<U, V> const& other);
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_constructible<first_type, U&&>::value && std::is_constructible<second_type, V&&>::value
			>::type
		>
		SPROUT_CONSTEXPR pair(sprout::tuples::tuple<U, V>&& other);

		SPROUT_CXX14_CONSTEXPR pair& operator=(pair const& rhs) {
			first = rhs.first;
			second = rhs.second;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR pair& operator=(pair&& rhs)
		SPROUT_NOEXCEPT_IF(std::is_nothrow_move_assignable<T1>::value && std::is_nothrow_move_assignable<T2>::value)
		{
			first = SPROUT_FORWARD(T1, rhs.first);
			second = SPROUT_FORWARD(T2, rhs.second);
			return *this;
		}
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_assignable<first_type&, U const&>::value && std::is_assignable<second_type&, V const&>::value
			>::type
		>
		SPROUT_CXX14_CONSTEXPR pair& operator=(sprout::pair<U, V> const& rhs) {
			first = rhs.first;
			second = rhs.second;
			return *this;
		}
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_assignable<first_type&, U&&>::value && std::is_assignable<second_type&, V&&>::value
			>::type
		>
		SPROUT_CXX14_CONSTEXPR pair& operator=(sprout::pair<U, V>&& rhs) {
			first = SPROUT_FORWARD(U, rhs.first);
			second = SPROUT_FORWARD(V, rhs.second);
			return *this;
		}
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_assignable<first_type&, U const&>::value && std::is_assignable<second_type&, V const&>::value
			>::type
		>
		SPROUT_CXX14_CONSTEXPR pair& operator=(sprout::tuples::tuple<U, V> const& rhs);
		template<
			typename U, typename V,
			typename = typename std::enable_if<
				std::is_assignable<first_type&, U&&>::value && std::is_assignable<second_type&, V&&>::value
			>::type
		>
		SPROUT_CXX14_CONSTEXPR pair&
		operator=(sprout::tuples::tuple<U, V>&& rhs);

		SPROUT_CXX14_CONSTEXPR void
		swap(pair& other)
		SPROUT_NOEXCEPT_IF(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(first, other.first))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(second, other.second))
			)
		{
			sprout::swap(first, other.first);
			sprout::swap(second, other.second);
		}
	};

	//
	// swap
	//
	template<typename T1, typename T2>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::pair<T1, T2>& lhs, sprout::pair<T1, T2>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_PAIR_DECL_HPP
