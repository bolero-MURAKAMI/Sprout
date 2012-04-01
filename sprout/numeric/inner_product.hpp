#ifndef SPROUT_NUMERIC_INNNER_PRODUCT_HPP
#define SPROUT_NUMERIC_INNNER_PRODUCT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 26.7.3 Inner product
	template<class InputIterator1, class InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
	SPROUT_CONSTEXPR T inner_product(
		InputIterator1 first1,
		InputIterator1 last1,
		InputIterator2 first2,
		T init,
		BinaryOperation1 binary_op1,
		BinaryOperation2 binary_op2
		)
	{
		return first1 == last1 ? init
			: sprout::inner_product(
				sprout::next(first1),
				last1,
				sprout::next(first2),
				binary_op1(init, binary_op2(*first1, *first2)),
				binary_op1,
				binary_op2
				)
			;
	}

	template<class InputIterator1, typename InputIterator2, typename T>
	SPROUT_CONSTEXPR T inner_product(
		InputIterator1 first1,
		InputIterator1 last1,
		InputIterator2 first2,
		T init
		)
	{
		return sprout::inner_product(
			first1,
			last1,
			first2,
			init,
			sprout::plus<typename std::iterator_traits<InputIterator1>::value_type>(),
			NS_SSCRISK_CEL_OR_SPROUT::multiplies<typename std::iterator_traits<InputIterator1>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_INNNER_PRODUCT_HPP
