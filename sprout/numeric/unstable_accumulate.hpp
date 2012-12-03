#ifndef SPROUT_NUMERIC_UNSTABLE_ACCUMLATE_HPP
#define SPROUT_NUMERIC_UNSTABLE_ACCUMLATE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/numeric/accumulate.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// unstable_accumulate
	//
	namespace detail {
		template<typename T, typename RandomAccessIterator, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		unstable_accumulate_ra(
			RandomAccessIterator first, RandomAccessIterator last, BinaryOperation binary_op,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot
			)
		{
			return pivot == 0 ? *first
				: binary_op(
					sprout::detail::unstable_accumulate_ra<T>(
						first, sprout::next(first, pivot), binary_op,
						pivot / 2
						),
					sprout::detail::unstable_accumulate_ra<T>(
						sprout::next(first, pivot), last, binary_op,
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) - pivot) / 2
						)
					)
				;
		}
		template<typename RandomAccessIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		unstable_accumulate(
			RandomAccessIterator first, RandomAccessIterator last, T init, BinaryOperation binary_op,
			std::random_access_iterator_tag*
			)
		{
			return first == last ? init
				: binary_op(
					init,
					sprout::detail::unstable_accumulate_ra<T>(
						first, last, binary_op,
						NS_SSCRISK_CEL_OR_SPROUT::distance(first, last) / 2
						)
					)
				;
		}

		template<typename InputIterator, typename T, typename BinaryOperation>
		inline SPROUT_CONSTEXPR T
		unstable_accumulate(
			InputIterator first, InputIterator last, T init, BinaryOperation binary_op,
			void*
			)
		{
			return sprout::accumulate(first, last, init, binary_op);
		}
	}	// namespace detail

	template<typename InputIterator, typename T, typename BinaryOperation>
	inline SPROUT_CONSTEXPR T
	unstable_accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
		typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
		return sprout::detail::unstable_accumulate(first, last, init, binary_op, category());
	}

	template<typename InputIterator, typename T>
	inline SPROUT_CONSTEXPR T
	unstable_accumulate(InputIterator first, InputIterator last, T init) {
		return sprout::unstable_accumulate(
			first, last, init,
			NS_SSCRISK_CEL_OR_SPROUT::plus<typename std::iterator_traits<InputIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_UNSTABLE_ACCUMLATE_HPP
