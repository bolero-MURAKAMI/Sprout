/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP
#define SPROUT_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/iterator/phase_spectrum_iterator.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/math/less.hpp>
#include <sprout/numeric/dft/phase_spectrum_value.hpp>
#include <sprout/detail/container_complate.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename RandomAccessIterator, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			phase_spectrum_impl_ra(
				RandomAccessIterator first, RandomAccessIterator, Result const& result,
				sprout::index_tuple<Indexes...>,
				typename sprout::container_traits<Result>::difference_type offset,
				typename sprout::container_traits<Result>::size_type size,
				typename sprout::container_traits<Result>::size_type input_size
				)
			{
				return sprout::remake<Result>(
					result, size,
					(Indexes >= offset && sprout::math::less(Indexes, offset + size) && sprout::math::less(Indexes, offset + input_size)
						? sprout::phase_spectrum_value(first[Indexes])
						: *sprout::next(sprout::internal_begin(result), Indexes)
						)...
					);
			}
			template<typename RandomAccessIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			phase_spectrum(
				RandomAccessIterator first, RandomAccessIterator last, Result const& result,
				std::random_access_iterator_tag*
				)
			{
				return sprout::fixed::detail::phase_spectrum_impl_ra(
					first, last, result,
					sprout::container_indexes<Result>::make(),
					sprout::internal_begin_offset(result),
					sprout::size(result),
					sprout::distance(first, last)
					);
			}

			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size == sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			phase_spectrum_impl(
				InputIterator, InputIterator, Result const& result,
				typename sprout::container_traits<Result>::size_type,
				Args const&... args
				)
			{
				return sprout::remake<Result>(result, sprout::size(result), args...);
			}
			template<typename InputIterator, typename Result, typename... Args>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::container_traits<Result>::static_size != sizeof...(Args),
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			phase_spectrum_impl(
				InputIterator first, InputIterator last, Result const& result,
				typename sprout::container_traits<Result>::size_type size,
				Args const&... args
				)
			{
				return first != last && sizeof...(Args) < size
					? sprout::fixed::detail::phase_spectrum_impl(
						sprout::next(first), last, result, size,
						args..., sprout::phase_spectrum_value(*first)
						)
					: sprout::detail::container_complate(result, args...)
					;
			}
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			phase_spectrum(
				InputIterator first, InputIterator last, Result const& result,
				std::forward_iterator_tag*
				)
			{
				return sprout::fixed::detail::phase_spectrum_impl(first, last, result, sprout::size(result));
			}

			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			phase_spectrum(InputIterator first, InputIterator last, Result const& result) {
				typedef typename std::iterator_traits<InputIterator>::iterator_category* category;
				return sprout::fixed::detail::phase_spectrum(first, last, result, category());
			}

			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::is_fixed_container<Result>::value,
				typename sprout::fixed::results::algorithm<Result>::type
			>::type
			phase_spectrum(InputIterator first, InputIterator last, Result const& result) {
				return sprout::remake<Result>(
					result, sprout::size(result),
					sprout::make_phase_spectrum_iterator(first),
					sprout::make_phase_spectrum_iterator(last)
					);
			}
		}	// namespace detail
		//
		// phase_spectrum
		//
		template<typename InputIterator, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		phase_spectrum(InputIterator first, InputIterator last, Result const& result) {
			return sprout::fixed::detail::phase_spectrum(first, last, result);
		}

		template<typename Result, typename InputIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		phase_spectrum(InputIterator first, InputIterator last) {
			return sprout::fixed::phase_spectrum(first, last, sprout::pit<Result>());
		}
	}	// namespace fixed

	template<
		typename InputIterator, typename Result,
		typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	phase_spectrum(InputIterator first, InputIterator last, Result const& result) {
		return sprout::fixed::phase_spectrum(first, last, result);
	}

	template<typename Result, typename InputIterator>
	inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
	phase_spectrum(InputIterator first, InputIterator last) {
		return sprout::fixed::phase_spectrum<Result>(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_FIXED_PHASE_SPECTRUM_HPP
