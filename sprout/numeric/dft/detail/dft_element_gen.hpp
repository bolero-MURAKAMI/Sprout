#ifndef SPROUT_NUMERIC_DFT_DETAIL_DFT_ELEMENT_GEN_HPP
#define SPROUT_NUMERIC_DFT_DETAIL_DFT_ELEMENT_GEN_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>

namespace sprout {
	namespace detail {
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::value_type
		dft_element_gen_impl_ra(
			RandomAccessIterator first, RandomAccessIterator last,
			typename std::iterator_traits<RandomAccessIterator>::value_type::value_type arg,
			typename std::iterator_traits<RandomAccessIterator>::difference_type pivot,
			typename std::iterator_traits<RandomAccessIterator>::difference_type k = 0
			)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			using sprout::cos;
			using sprout::sin;
			return pivot == 0 ? *first * value_type(cos(arg * k), sin(arg * k))
				: sprout::detail::dft_element_gen_impl_ra(
					first, sprout::next(first, pivot), arg, pivot / 2, k
					)
					+ sprout::detail::dft_element_gen_impl_ra(
						sprout::next(first, pivot), last, arg, (sprout::distance(first, last) - pivot) / 2, k + pivot
						)
				;
		}
		template<typename RandomAccessIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<RandomAccessIterator>::value_type
		dft_element_gen_impl(
			RandomAccessIterator first, RandomAccessIterator last,
			typename std::iterator_traits<RandomAccessIterator>::value_type::value_type arg,
			std::random_access_iterator_tag*
			)
		{
			typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
			return first == last ? value_type()
				: sprout::detail::dft_element_gen_impl_ra(first, last, arg, sprout::distance(first, last) / 2)
				;
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
		dft_element_gen_impl_1(
			InputIterator first, InputIterator last,
			typename std::iterator_traits<InputIterator>::value_type::value_type arg,
			typename std::iterator_traits<InputIterator>::difference_type k = 0,
			typename std::iterator_traits<InputIterator>::value_type value
				= typename std::iterator_traits<InputIterator>::value_type(),
			typename std::iterator_traits<InputIterator>::value_type::value_type theta
				= typename std::iterator_traits<InputIterator>::value_type::value_type()
			)
		{
			typedef typename std::iterator_traits<InputIterator>::value_type value_type;
			using sprout::cos;
			using sprout::sin;
			return first == last ? value
				: value + sprout::detail::dft_element_gen_impl_1(
					sprout::next(first), last,
					arg,
					k + 1,
					*first * value_type(cos(theta), sin(theta)),
					arg * (k + 1)
					)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
		dft_element_gen_impl(
			InputIterator first, InputIterator last,
			typename std::iterator_traits<InputIterator>::value_type::value_type arg,
			std::input_iterator_tag*
			)
		{
			return sprout::detail::dft_element_gen_impl_1(first, last, arg);
		}

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
		dft_element_gen(
			InputIterator first, InputIterator last,
			typename std::iterator_traits<InputIterator>::value_type::value_type arg
			)
		{
			typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
			return sprout::detail::dft_element_gen_impl(first, last, arg, category());
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_DETAIL_DFT_ELEMENT_GEN_HPP
