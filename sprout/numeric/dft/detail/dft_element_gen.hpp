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
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
		dft_element_gen(
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
			return first != last
				? value + sprout::detail::dft_element_gen(
					sprout::next(first),
					last,
					arg,
					k + 1,
					*first * value_type(cos(theta), sin(theta)),
					arg * (k + 1)
					)
				: value
				;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_DETAIL_DFT_ELEMENT_GEN_HPP
