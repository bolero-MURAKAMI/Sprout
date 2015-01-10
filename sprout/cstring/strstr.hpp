/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRSTR_HPP
#define SPROUT_CSTRING_STRSTR_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/detail/str.hpp>

namespace sprout {
	namespace detail {
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool>
		strstr_one_impl_1(
			sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> const& current,
			ForwardIterator1 first1_, typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> type;
			return sprout::tuples::get<2>(current) ? current
				: !*sprout::tuples::get<1>(current) ? type(first1_, sprout::tuples::get<1>(current), true)
				: !*sprout::tuples::get<0>(current) ? type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
				: n == 1 ? !(*sprout::tuples::get<0>(current) == *sprout::tuples::get<1>(current))
						? type(sprout::next(sprout::tuples::get<0>(current)), sprout::tuples::get<1>(current), true)
						: type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)), false)
				: sprout::detail::strstr_one_impl_1(
					sprout::detail::strstr_one_impl_1(
						current,
						first1_, n / 2
						),
					first1_, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool>
		strstr_one_impl(
			sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> const& current,
			ForwardIterator1 first1_, typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> type;
			return sprout::tuples::get<2>(current) ? current
				: !*sprout::tuples::get<1>(current) ? type(first1_, sprout::tuples::get<1>(current), true)
				: !*sprout::tuples::get<0>(current) ? type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), true)
				: sprout::detail::strstr_one_impl(
					sprout::detail::strstr_one_impl_1(
						current,
						first1_, n
						),
					first1_, n * 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR ForwardIterator1
		strstr_one(ForwardIterator1 first1, ForwardIterator2 first2) {
			typedef sprout::tuples::tuple<ForwardIterator1, ForwardIterator2, bool> type;
			return sprout::tuples::get<0>(sprout::detail::strstr_one_impl(type(first1, first2, false), first1, 1));
		}

		template<typename ForwardIterator>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, bool>
		strstr_impl_fork(sprout::pair<ForwardIterator, bool> const& current, ForwardIterator searched) {
			typedef sprout::pair<ForwardIterator, bool> type;
			return searched == current.first || !*searched ? type(searched, true)
				: type(sprout::next(current.first), false)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		strstr_impl_1(
			sprout::pair<ForwardIterator1, bool> const& current,
			ForwardIterator2 first2,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.second || !*current.first ? current
				: n == 1 ? sprout::detail::strstr_impl_fork(
					current,
					sprout::detail::strstr_one(current.first, first2)
					)
				: sprout::detail::strstr_impl_1(
					sprout::detail::strstr_impl_1(
						current,
						first2, n / 2
						),
					first2, n - n / 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator1, bool>
		strstr_impl(
			sprout::pair<ForwardIterator1, bool> const& current,
			ForwardIterator2 first2,
			typename std::iterator_traits<ForwardIterator1>::difference_type n
			)
		{
			return current.second || !*current.first ? current
				: sprout::detail::strstr_impl(
					sprout::detail::strstr_impl_1(
						current,
						first2, n
						),
					first2, n * 2
					)
				;
		}
		template<typename ForwardIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR ForwardIterator1
		strstr(ForwardIterator1 first1, ForwardIterator2 first2) {
			typedef sprout::pair<ForwardIterator1, bool> type;
			return !*first2 ? first1
				: sprout::detail::strstr_impl(type(first1, false), first2, 1).first
				;
		}
	}	// namespace detail

	// 7.21.5.7 strstr ä÷êî
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR char const*
	strstr(char const* s1, char const* s2) {
		return sprout::detail::str_find_check(
			sprout::detail::strstr(s1, s2)
			);
	}
	inline SPROUT_CONSTEXPR char*
	strstr(char* s1, char const* s2) {
		return sprout::detail::str_find_check(
			sprout::detail::strstr(s1, s2)
			);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		Elem*
	>::type
	strstr(Elem* s1, typename std::remove_const<Elem>::type const* s2) {
		return sprout::detail::str_find_check(
			sprout::detail::strstr(s1, s2)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRSTR_HPP
