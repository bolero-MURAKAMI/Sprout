/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_CXX14_SAMPLE_HPP
#define SPROUT_ALGORITHM_CXX14_SAMPLE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/workaround/detail/uniform_int_distribution.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace detail {
		template<typename PopIterator, typename SampleIterator, typename Size, typename URNG>
		inline SPROUT_CXX14_CONSTEXPR SampleIterator
		sample_impl(
			PopIterator first, PopIterator last, std::input_iterator_tag*,
			SampleIterator out, std::random_access_iterator_tag*,
			Size n, URNG&& g
			)
		{
			typedef SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<Size> distribution_type;
			typedef typename distribution_type::param_type param_type;
			distribution_type dist = {};
			Size sample_size = 0;
			while (first != last && sample_size != n) {
				out[sample_size++] = *first++;
			}
			for (Size pop_size = sample_size; first != last; ++first, ++pop_size) {
				param_type const p(0, pop_size);
				Size const k = dist(g, p);
				if (k < n) {
					out[k] = *first;
				}
			}
			return out + sample_size;
		}
		template<typename PopIterator, typename SampleIterator, typename Size, typename URNG>
		inline SPROUT_CXX14_CONSTEXPR SampleIterator
		sample_impl(
			PopIterator first, PopIterator last, std::forward_iterator_tag*,
			SampleIterator out, std::output_iterator_tag*,
			Size n, URNG&& g
			)
		{
			typedef SPROUT_WORKAROUND_DETAIL_UNIFORM_INT_DISTRIBUTION<Size> distribution_type;
			typedef typename distribution_type::param_type param_type;
			distribution_type dist = {};
			Size unsampled_size = sprout::distance(first, last);
			for (n = NS_SSCRISK_CEL_OR_SPROUT::min(n, unsampled_size); n != 0; ++first ) {
				param_type const p(0, --unsampled_size);
				if (dist(g, p) < n) {
					*out++ = *first;
					--n;
				}
			}
			return out;
		}
	}	// namespace detail
	//
	// sample
	//
	template<typename PopIterator, typename SampleIterator, typename Size, typename URNG>
	inline SPROUT_CXX14_CONSTEXPR SampleIterator
	sample(PopIterator first, PopIterator last, SampleIterator out, Size n, URNG&& g) {
		typedef typename std::iterator_traits<PopIterator>::iterator_category* pop_category;
		typedef typename std::iterator_traits<SampleIterator>::iterator_category* sample_category;
		return sprout::detail::sample_impl(
			first, last, pop_category(),
			out, sample_category(),
			n, SPROUT_FORWARD(URNG, g)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_CXX14_SAMPLE_HPP
