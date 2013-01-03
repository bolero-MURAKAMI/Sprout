#ifndef SPROUT_ITERATOR_DISTANCE_HPP
#define SPROUT_ITERATOR_DISTANCE_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/type_traits/is_iterator.hpp>
#include <sprout/utility/pair.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl iterator_distance(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_constant_distance_iterator<RandomAccessIterator>::value,
			typename std::iterator_traits<RandomAccessIterator>::difference_type
		>::type
		iterator_distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag*) {
			return last - first;
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		iterator_distance_impl_1(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return current.first == last ? current
				: n == 1 ? type(sprout::next(current.first), current.second + 1)
				: sprout::iterator_detail::iterator_distance_impl_1(
					sprout::iterator_detail::iterator_distance_impl_1(
						current,
						last, n / 2
						),
					last, n - n / 2
					)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type>
		iterator_distance_impl(
			sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> const& current,
			InputIterator last, typename std::iterator_traits<InputIterator>::difference_type n
			)
		{
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return current.first == last ? current
				: sprout::iterator_detail::iterator_distance_impl(
					sprout::iterator_detail::iterator_distance_impl_1(
						current,
						last, n
						),
					last, n * 2
					)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		iterator_distance(InputIterator first, InputIterator last, void*) {
			typedef sprout::pair<InputIterator, typename std::iterator_traits<InputIterator>::difference_type> type;
			return sprout::iterator_detail::iterator_distance_impl(type(first, 0), last, 1).second;
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_literal_type<InputIterator>::value,
			typename std::iterator_traits<InputIterator>::difference_type
		>::type
		iterator_distance(InputIterator first, InputIterator last) {
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::iterator_detail::iterator_distance(first, last, category());
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!std::is_literal_type<InputIterator>::value,
			typename std::iterator_traits<InputIterator>::difference_type
		>::type
		iterator_distance(InputIterator first, InputIterator last) {
			return std::distance(first, last);
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		using sprout::iterator_detail::iterator_distance;
		using sprout_adl::iterator_distance;
		return iterator_distance(first, last);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// distance
	//
	//	effect:
	//		ADL callable iterator_distance(first, last) -> iterator_distance(first, last)
	//		otherwise, [first, last) is not LiteralType -> std::distance(first, last)
	//		otherwise, [first, last) is RandomAccessIterator && not Pointer -> last - first
	//		otherwise -> linearly count: first to last
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return sprout_iterator_detail::distance(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DISTANCE_HPP
