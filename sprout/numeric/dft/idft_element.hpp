#ifndef SPROUT_NUMERIC_DFT_IDFT_ELEMENT_HPP
#define SPROUT_NUMERIC_DFT_IDFT_ELEMENT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/numeric/dft/detail/dft_element_gen.hpp>

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename Size>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
		idft_element_impl(
			InputIterator first, InputIterator last, typename std::iterator_traits<InputIterator>::difference_type i,
			Size size
			)
		{
			typedef typename std::iterator_traits<InputIterator>::value_type value_type;
			typedef typename value_type::value_type elem_type;
			return sprout::detail::dft_element_gen(
				first, last,
				sprout::math::two_pi<elem_type>() * i / size
				)
				/ static_cast<elem_type>(size)
				;
		}
	}	// namespace detail
	//
	// idft_element
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type
	idft_element(	InputIterator first, InputIterator last, typename std::iterator_traits<InputIterator>::difference_type i) {
		return sprout::detail::idft_element_impl(
			first, last, i,
			sprout::distance(first, last)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_IDFT_ELEMENT_HPP
