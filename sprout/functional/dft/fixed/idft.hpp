#ifndef SPROUT_FUNCTIONAL_DFT_FIXED_IDFT_HPP
#define SPROUT_FUNCTIONAL_DFT_FIXED_IDFT_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/functional/dft/idft_element.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type idft_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::fixed_container_traits<Result>::difference_type offset,
				typename sprout::fixed_container_traits<Result>::size_type size,
				typename sprout::fixed_container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake_clone<Result>(
					result,
					sprout::size(result),
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? sprout::detail::idft_element_impl(first, last, Indexes - offset, input_size)
						: *sprout::next(sprout::fixed_begin(result), Indexes)
						)...
					);
			}
			template<typename InputIterator, typename Result>
			SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type idft(
				InputIterator first,
				InputIterator last,
				Result const& result
				)
			{
				return sprout::fixed::detail::idft_impl(
					first,
					last,
					result,
					typename sprout::index_range<0, sprout::fixed_container_traits<Result>::fixed_size>::type(),
					sprout::fixed_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT_DETAIL::distance(first, last)
					);
			}
		}	// namespace detail
		//
		// idft
		//
		template<typename InputIterator, typename Result>
		SPROUT_CONSTEXPR inline typename sprout::fixed::result_of::algorithm<Result>::type idft(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fixed::detail::idft(first, last, result);
		}
	}	// namespace fixed

	using sprout::fixed::idft;
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_DFT_FIXED_IDFT_HPP
