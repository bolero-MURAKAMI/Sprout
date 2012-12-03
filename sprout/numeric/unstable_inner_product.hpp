#ifndef SPROUT_NUMERIC_UNSTABLE_INNNER_PRODUCT_HPP
#define SPROUT_NUMERIC_UNSTABLE_INNNER_PRODUCT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/numeric/inner_product.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	//
	// unstable_inner_product
	//
	namespace detail {
		template<typename T, typename RandomAccessIterator1, typename RandomAccessIterator2, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		unstable_inner_product_ra(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			typename std::iterator_traits<RandomAccessIterator1>::difference_type pivot
			)
		{
			return pivot == 0 ? binary_op2(*first1, *first2)
				: binary_op1(
					sprout::detail::unstable_inner_product_ra<T>(
						first1, sprout::next(first1, pivot), first2, binary_op1, binary_op2,
						pivot / 2
						),
					sprout::detail::unstable_inner_product_ra<T>(
						sprout::next(first1, pivot), last1, sprout::next(first2, pivot), binary_op1, binary_op2,
						(NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) - pivot) / 2
						)
					)
				;
		}
		template<typename RandomAccessIterator1, typename RandomAccessIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		unstable_inner_product(
			RandomAccessIterator1 first1, RandomAccessIterator1 last1, RandomAccessIterator2 first2, T init,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			std::random_access_iterator_tag*
			)
		{
			return first1 == last1 ? init
				: binary_op1(
					init,
					sprout::detail::unstable_inner_product_ra<T>(
						first1, last1, first2, binary_op1, binary_op2,
						NS_SSCRISK_CEL_OR_SPROUT::distance(first1, last1) / 2
						)
					)
				;
		}

		template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
		inline SPROUT_CONSTEXPR T
		unstable_inner_product(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init,
			BinaryOperation1 binary_op1, BinaryOperation2 binary_op2,
			void*
			)
		{
			return sprout::inner_product(first1, last1, first2, init, binary_op1, binary_op2);
		}
	}	// namespace detail

	template<typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
	inline SPROUT_CONSTEXPR T
	unstable_inner_product(
		InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init,
		BinaryOperation1 binary_op1, BinaryOperation2 binary_op2
		)
	{
		typedef typename std::iterator_traits<InputIterator1>::iterator_category* category;
		return sprout::detail::unstable_inner_product(first1, last1, first2, init, binary_op1, binary_op2, category());
	}

	template<typename InputIterator1, typename InputIterator2, typename T>
	inline SPROUT_CONSTEXPR T
	unstable_inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init) {
		return sprout::unstable_inner_product(
			first1, last1, first2, init,
			sprout::plus<typename std::iterator_traits<InputIterator1>::value_type>(),
			NS_SSCRISK_CEL_OR_SPROUT::multiplies<typename std::iterator_traits<InputIterator1>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_UNSTABLE_INNNER_PRODUCT_HPP
