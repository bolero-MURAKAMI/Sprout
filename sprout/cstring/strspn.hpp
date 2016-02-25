/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRSPN_HPP
#define SPROUT_CSTRING_STRSPN_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/cstring/strchr.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, std::size_t, bool>
		strspn_impl_1(
			sprout::tuples::tuple<InputIterator1, std::size_t, bool> const& current,
			ForwardIterator2 first2, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, std::size_t, bool> type;
			return sprout::tuples::get<2>(current) || !*sprout::tuples::get<0>(current) ? current
				: n == 1 ? *sprout::detail::strchr(first2, *sprout::tuples::get<0>(current))
					? type(sprout::next(sprout::tuples::get<0>(current)), sprout::tuples::get<1>(current) + 1, false)
					: type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
				: sprout::detail::strspn_impl_1(
					sprout::detail::strspn_impl_1(
						current,
						first2, n / 2
						),
					first2, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, std::size_t, bool>
		strspn_impl(
			sprout::tuples::tuple<InputIterator1, std::size_t, bool> const& current,
			ForwardIterator2 first2, typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return sprout::tuples::get<2>(current) || !*sprout::tuples::get<0>(current) ? current
				: sprout::detail::strspn_impl(
					sprout::detail::strspn_impl_1(
						current,
						first2, n
						),
					first2, n * 2
					)
				;
		}
		template<typename InputIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR std::size_t
		strspn(InputIterator1 first1, ForwardIterator2 first2) {
			typedef sprout::tuples::tuple<InputIterator1, std::size_t, bool> type;
			return sprout::tuples::get<1>(sprout::detail::strspn_impl(type(first1, 0, false), first2, 1));
		}
	}	// namespace detail

	// 7.21.5.6 strspn ä÷êî
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR std::size_t
	strspn(char const* s1, char const* s2) {
		return sprout::detail::strspn(s1, s2);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		std::size_t
	>::type
	strspn(Elem* s1, Elem* s2) {
		return sprout::detail::strspn(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRSPN_HPP
