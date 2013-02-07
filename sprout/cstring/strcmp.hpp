#ifndef SPROUT_CSTRING_STRCMP_HPP
#define SPROUT_CSTRING_STRCMP_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/type_traits/is_char_type.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR int
		strcmp_impl_check(sprout::tuples::tuple<InputIterator1, InputIterator2, int> const& found) {
			return !*sprout::tuples::get<1>(found) ? (!*sprout::tuples::get<0>(found) ? 0 : 1)
				: !*sprout::tuples::get<0>(found) ? -1
				: sprout::tuples::get<2>(found)
				;
		}
		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, int>
		strcmp_impl_1(
			sprout::tuples::tuple<InputIterator1, InputIterator2, int> const& current,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, int> type;
			return sprout::tuples::get<2>(current) || !*sprout::tuples::get<1>(current) || !*sprout::tuples::get<0>(current) ? current
				: n == 1 ? (*sprout::tuples::get<0>(current)) < (*sprout::tuples::get<1>(current)) ? type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), -1)
					: (*sprout::tuples::get<1>(current)) < (*sprout::tuples::get<0>(current)) ? type(sprout::tuples::get<0>(current), sprout::tuples::get<1>(current), 1)
					: type(sprout::next(sprout::tuples::get<0>(current)), sprout::next(sprout::tuples::get<1>(current)), 0)
				: sprout::detail::strcmp_impl_1(
					sprout::detail::strcmp_impl_1(
						current,
						n / 2
						),
					n - n / 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<InputIterator1, InputIterator2, int>
		strcmp_impl(
			sprout::tuples::tuple<InputIterator1, InputIterator2, int> const& current,
			typename std::iterator_traits<InputIterator1>::difference_type n
			)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, int> type;
			return sprout::tuples::get<2>(current) || !*sprout::tuples::get<1>(current) || !*sprout::tuples::get<0>(current) ? current
				: sprout::detail::strcmp_impl(
					sprout::detail::strcmp_impl_1(
						current,
						n
						),
					n * 2
					)
				;
		}
		template<typename InputIterator1, typename InputIterator2>
		inline SPROUT_CONSTEXPR int
		strcmp(InputIterator1 first1, InputIterator2 first2)
		{
			typedef sprout::tuples::tuple<InputIterator1, InputIterator2, int> type;
			return sprout::detail::strcmp_impl_check(
				sprout::detail::strcmp_impl(type(first1, first2, 0), 1)
				);
		}
	}	// namespace detail

	// 7.21.4.2  strcmp ä÷êî
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	strcmp(char const* s1, char const* s2) {
		return sprout::detail::strcmp(s1, s2);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		int
	>::type
	strcmp(Elem* s1, Elem* s2) {
		return sprout::detail::strcmp(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCMP_HPP
