/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRPBRK_HPP
#define SPROUT_CSTRING_STRPBRK_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/cstring/strchr.hpp>
#include <sprout/detail/str.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, bool>
		strpbrk_impl_1(
			sprout::pair<InputIterator1, bool> current,
			ForwardIterator2 first2,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator1, bool> type;
			return current.second || !*current.first ? current
				: n == 1 ? sprout::strchr(first2, *current.first)
					? type(current.first, true)
					: type(sprout::next(current.first), false)
				: sprout::detail::strpbrk_impl_1(
					sprout::detail::strpbrk_impl_1(
						current,
						first2, n / 2
						),
					first2, n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator1, bool>
		strpbrk_impl(
			sprout::pair<InputIterator1, bool> current,
			ForwardIterator2 first2,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			return current.second || !*current.first ? current
				: sprout::detail::strpbrk_impl(
					sprout::detail::strpbrk_impl_1(
						current,
						first2, n
						),
					first2, n * 2
					)
				;
		}
		template<typename InputIterator1, typename ForwardIterator2>
		inline SPROUT_CONSTEXPR InputIterator1
		strpbrk(InputIterator1 first1, ForwardIterator2 first2) {
			typedef sprout::pair<InputIterator1, bool> type;
			return sprout::detail::strpbrk_impl(type(first1, false), first2, 1).first;
		}
	}	// namespace detail

	// 7.21.5.4 strpbrk function
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR char const*
	strpbrk(char const* s1, char const* s2) {
		return sprout::detail::str_find_check(
			sprout::detail::strpbrk(s1, s2)
			);
	}
	inline SPROUT_CONSTEXPR char*
	strpbrk(char* s1, char const* s2) {
		return sprout::detail::str_find_check(
			sprout::detail::strpbrk(s1, s2)
			);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		Elem*
	>::type
	strpbrk(Elem* s1, typename std::remove_const<Elem>::type const* s2) {
		return sprout::detail::str_find_check(
			sprout::detail::strpbrk(s1, s2)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRPBRK_HPP
