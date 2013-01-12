#ifndef SPROUT_CSTRING_STRCHR_HPP
#define SPROUT_CSTRING_STRCHR_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/detail/str.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		strchr_impl_1(
			sprout::pair<InputIterator, bool> const& current,
			T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return current.second || !*current.first ? current
				: n == 1 ? *current.first == value ? type(current.first, true) : type(sprout::next(current.first), false)
				: sprout::detail::strchr_impl_1(
					sprout::detail::strchr_impl_1(
						current,
						 value, n / 2
						),
					value, n - n / 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, bool>
		strchr_impl(
			sprout::pair<InputIterator, bool> const& current,
			T const& value, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, bool> type;
			return current.second || !*current.first ? current
				: sprout::detail::strchr_impl(
					sprout::detail::strchr_impl_1(
						current,
						value, n
						),
					value, n * 2
					)
				;
		}
		template<typename InputIterator, typename T>
		inline SPROUT_CONSTEXPR InputIterator
		strchr(InputIterator first, T const& value) {
			typedef sprout::pair<InputIterator, bool> type;
			return sprout::detail::strchr_impl(type(first, false), value, 1).first;
		}

	}	// namespace detail

	// 7.21.5.2  strchr ä÷êî
	//
	//	recursion depth:
	//		O(log N)
	//
	inline SPROUT_CONSTEXPR char const*
	strchr(char const* s, int c) {
		return sprout::detail::str_find_check(
			sprout::detail::strchr(s, static_cast<char>(c)),
			static_cast<char>(c)
			);
	}
	inline SPROUT_CONSTEXPR char*
	strchr(char* s, int c) {
		return sprout::detail::str_find_check(
			sprout::detail::strchr(s, static_cast<char>(c)),
			static_cast<char>(c)
			);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		Elem*
	>::type
	strchr(Elem* s, typename std::decay<Elem>::type c) {
		return sprout::detail::str_find_check(
			sprout::detail::strchr(s, c),
			c
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCHR_HPP
