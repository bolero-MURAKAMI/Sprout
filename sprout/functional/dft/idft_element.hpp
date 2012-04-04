#ifndef SPROUT_FUNCTIONAL_DFT_FIXED_IDFT_ELEMENT_HPP
#define SPROUT_FUNCTIONAL_DFT_FIXED_IDFT_ELEMENT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/functional/dft/detail/dft_element_gen.hpp>
#include <sprout/math/constants.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename InputIterator, typename Size>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type idft_element_impl(
			InputIterator first,
			InputIterator last,
			typename std::iterator_traits<InputIterator>::difference_type i,
			Size size
			)
		{
			typedef typename std::iterator_traits<InputIterator>::value_type value_type;
			typedef typename value_type::value_type elem_type;
			return sprout::detail::dft_element_gen(
				first,
				last,
				2 * sprout::math::pi<elem_type>() * i / size
				)
				/ static_cast<elem_type>(size)
				;
		}
	}	// namespace detail
	//
	// idft_element
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::value_type idft_element(
		InputIterator first,
		InputIterator last,
		typename std::iterator_traits<InputIterator>::difference_type i
		)
	{
		return sprout::detail::idft_element_impl(
			first,
			last,
			i,
			NS_SSCRISK_CEL_OR_SPROUT::distance(first, last)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_DFT_FIXED_IDFT_ELEMENT_HPP
