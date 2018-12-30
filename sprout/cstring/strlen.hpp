/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRLEN_HPP
#define SPROUT_CSTRING_STRLEN_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/algorithm/find.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, std::size_t>
		strlen_impl_1(
			sprout::pair<InputIterator, std::size_t> const& current,
			typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, std::size_t> type;
			return !*current.first ? current
				: n == 1 ? type(sprout::next(current.first), current.second + 1)
				: sprout::detail::strlen_impl_1(
					sprout::detail::strlen_impl_1(
						current,
						n / 2
						),
					n - n / 2
					)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, std::size_t>
		strlen_impl(
			sprout::pair<InputIterator, std::size_t> const& current,
			typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			return !*current.first ? current
				: sprout::detail::strlen_impl(
					sprout::detail::strlen_impl_1(
						current,
						n
						),
					n * 2
					)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR std::size_t
		strlen(InputIterator first) {
			typedef sprout::pair<InputIterator, std::size_t> type;
			return sprout::detail::strlen_impl(type(first, 0), 1).second;
		}
	}	// namespace detail

	// 7.21.6.3 strlen function
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR std::size_t
	strlen(char const* s) {
		return sprout::detail::strlen(s);
	}
	inline SPROUT_CONSTEXPR std::size_t
	strlen(char const* s, std::size_t n) {
		return sprout::distance(
			sprout::ptr_index(s),
			sprout::find(sprout::ptr_index(s), sprout::ptr_index(s, n), '\0')
			);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		std::size_t
	>::type
	strlen(Elem* s) {
		return sprout::detail::strlen(s);
	}
	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		std::size_t
	>::type
	strlen(Elem* s, std::size_t n) {
		typedef typename std::decay<Elem>::type type;
		return sprout::distance(
			sprout::ptr_index(s),
			sprout::find(sprout::ptr_index(s), sprout::ptr_index(s, n), type())
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRLEN_HPP
