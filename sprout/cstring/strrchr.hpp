/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRRCHR_HPP
#define SPROUT_CSTRING_STRRCHR_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/type_traits/is_char_type.hpp>

namespace sprout {
	namespace detail {
		template<typename ForwardIterator, typename T>
		inline SPROUT_CONSTEXPR ForwardIterator
		strrchr_impl_check(sprout::pair<ForwardIterator, ForwardIterator> const& found, T const& value) {
			return *found.second == value ? found.second
				: !value ? found.first
				: ForwardIterator()
				;
		}
		template<typename ForwardIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		strrchr_impl_1(
			sprout::pair<ForwardIterator, ForwardIterator> const& current,
			T const& value,
			typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return !*current.first ? current
				: n == 1 ? *current.first == value ? type(sprout::next(current.first), current.first) : type(sprout::next(current.first), current.second)
				: sprout::detail::strrchr_impl_1(
					sprout::detail::strrchr_impl_1(
						current,
						value, n / 2
						),
					value, n - n / 2
					)
				;
		}
		template<typename ForwardIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<ForwardIterator, ForwardIterator>
		strrchr_impl(
			sprout::pair<ForwardIterator, ForwardIterator> const& current,
			T const& value,
			typename std::iterator_traits<ForwardIterator>::difference_type n
			)
		{
			return !*current.first ? current
				: sprout::detail::strrchr_impl(
					sprout::detail::strrchr_impl_1(
						current,
						value, n
						),
					value, n * 2
					)
				;
		}
		template<typename ForwardIterator, typename T>
		inline SPROUT_CONSTEXPR ForwardIterator
		strrchr(ForwardIterator first, T const& value) {
			typedef sprout::pair<ForwardIterator, ForwardIterator> type;
			return sprout::detail::strrchr_impl_check(
				sprout::detail::strrchr_impl(type(first, first), value, 1),
				value
				);
		}
	}	// namespace detail

	// 7.21.5.5 strrchr ä÷êî
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR char const*
	strrchr(char const* s, int c) {
		return sprout::detail::strrchr(s, static_cast<char>(c));
	}
	inline SPROUT_CONSTEXPR char*
	strrchr(char* s, int c) {
		return sprout::detail::strrchr(s, static_cast<char>(c));
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		Elem*
	>::type
	strrchr(Elem* s, typename std::decay<Elem>::type c) {
		return sprout::detail::strrchr(s, c);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRRCHR_HPP
