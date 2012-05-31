#ifndef SPROUT_UTILITY_PAIR_HPP
#define SPROUT_UTILITY_PAIR_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/functional/ref.hpp>

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
		pair& operator=(pair&& p) SPROUT_NOEXCEPT_EXPR(
			std::is_nothrow_move_assignable<T1>::value && std::is_nothrow_move_assignable<T2>::value
			)
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
		void swap(pair& p) SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(swap(first, p.first)) && SPROUT_NOEXCEPT_EXPR(swap(second, p.second))
			)
		{
			using std::swap;
			swap(first, p.first);
			swap(second, p.second);
		}
	};

	template<class T1, class T2>
	inline SPROUT_CONSTEXPR bool operator==(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return x.first == y.first && x.second == y.second;
	}
	template<class T1, class T2>
	inline SPROUT_CONSTEXPR bool operator!=(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return !(x == y);
	}
	template<class T1, class T2>
	inline SPROUT_CONSTEXPR bool operator<(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return x.first < y.first
			|| (!(y.first < x.first) && x.second < y.second)
			;
	}
	template<class T1, class T2>
	inline SPROUT_CONSTEXPR bool operator>(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return y < x;
	}
	template<class T1, class T2>
	inline SPROUT_CONSTEXPR bool operator<=(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return !(y < x);
	}
	template<class T1, class T2>
	inline SPROUT_CONSTEXPR bool operator>=(sprout::pair<T1, T2> const& x, sprout::pair<T1, T2> const& y) {
		return !(x < y);
	}

	//
	// swap
	//
	template<class T1, class T2>
	inline void swap(pair<T1, T2>& x, pair<T1, T2>& y) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(x.swap(y))) {
		x.swap(y);
	}

	//
	// make_pair
	//
	template<typename T1, typename T2>
	SPROUT_CONSTEXPR sprout::pair<
		typename sprout::strip_reference<typename std::decay<T1>::type>::type,
		typename sprout::strip_reference<typename std::decay<T2>::type>::type
	>
	make_pair(T1&& x, T2&& y) {
		return sprout::pair<
			typename sprout::strip_reference<typename std::decay<T1>::type>::type,
			typename sprout::strip_reference<typename std::decay<T2>::type>::type
		>(
			sprout::forward<T1>(x),
			sprout::forward<T2>(y)
			);
	}
}	// namespace sprout

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<typename T1, typename T2>
			struct tuple_element_impl<0, sprout::pair<T1, T2> > {
			public:
				typedef T1 type;
			};
			template<typename T1, typename T2>
			struct tuple_element_impl<1, sprout::pair<T1, T2> > {
			public:
				typedef T2 type;
			};
		}	// namespace detail
	}	// namespace tuples
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename T1, typename T2>
	struct tuple_size<sprout::pair<T1, T2> >
		: public std::integral_constant<std::size_t, 2>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T1, typename T2>
	struct tuple_element<I, sprout::pair<T1, T2> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::pair<T1, T2> >
	{};
}	// namespace std

namespace sprout {
	namespace tuples {
		//
		// get
		//
		namespace detail {
			template<std::size_t I, typename T>
			struct get_impl;
			template<typename T1, typename T2>
			struct get_impl<0, sprout::pair<T1, T2> > {
			public:
				T1& operator()(sprout::pair<T1, T2>& t) const {
					return t.first;
				}
				T1 const& operator()(sprout::pair<T1, T2> const& t) const {
					return t.first;
				}
			};
			template<typename T1, typename T2>
			struct get_impl<1, sprout::pair<T1, T2> > {
			public:
			public:
				T2& operator()(sprout::pair<T1, T2>& t) const {
					return t.second;
				}
				T2 const& operator()(sprout::pair<T1, T2> const& t) const {
					return t.second;
				}
			};
		}	// namespace detail
		template<std::size_t I, typename T1, typename T2>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type&
		get(sprout::pair<T1, T2>& t) SPROUT_NOEXCEPT {
			static_assert(I < 2, "get: index out of range");
			return sprout::tuples::detail::get_impl<I, sprout::pair<T1, T2> >()(t);
		}
		template<std::size_t I, typename T1, typename T2>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type const&
		get(sprout::pair<T1, T2> const& t) SPROUT_NOEXCEPT {
			static_assert(I < 2, "get: index out of range");
			return sprout::tuples::detail::get_impl<I, sprout::pair<T1, T2> >()(t);
		}
		template<std::size_t I, typename T1, typename T2>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::pair<T1, T2> >::type&&
		get(sprout::pair<T1, T2>&& t) SPROUT_NOEXCEPT {
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_PAIR_HPP
