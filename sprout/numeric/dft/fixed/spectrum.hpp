#ifndef SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/complex.hpp>
#include <sprout/math/sqrt.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename InputIterator, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			spectrum_impl(
				InputIterator first,
				InputIterator last,
				Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				using sprout::sqrt;
				using sprout::real;
				using sprout::imag;
				return sprout::remake<Result>(
					result,
					size,
					(Indexes >= offset && Indexes < offset + size && Indexes < offset + input_size
						? sqrt(
							real(*sprout::next(first, Indexes)) * real(*sprout::next(first, Indexes))
							+ imag(*sprout::next(first, Indexes)) * imag(*sprout::next(first, Indexes))
							)
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			spectrum(
				InputIterator first,
				InputIterator last,
				Result const& result
				)
			{
				return sprout::fixed::detail::spectrum_impl(
					first,
					last,
					result,
					sprout::index_range<0, sprout::container_traits<Result>::static_size>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					NS_SSCRISK_CEL_OR_SPROUT::distance(first, last)
					);
			}
		}	// namespace detail
		//
		// spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
		spectrum(
			InputIterator first,
			InputIterator last,
			Result const& result
			)
		{
			return sprout::fixed::detail::spectrum(first, last, result);
		}
	}	// namespace fixed

	using sprout::fixed::spectrum;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIXED_SPECTRUM_HPP
