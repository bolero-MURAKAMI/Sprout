/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FFT_CXX14_IFFT_HPP
#define SPROUT_NUMERIC_FFT_CXX14_IFFT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/complex.hpp>
#include <sprout/algorithm/cxx14/transform.hpp>
#include <sprout/numeric/fft/cxx14/fft.hpp>

namespace sprout {
	namespace detail {
		struct conj_value {
		public:
			template<typename Complex>
			SPROUT_CONSTEXPR Complex operator()(Complex const& x) const {
				return conj(x);
			}
		};

		template<typename Size>
		struct conj_div_value {
		private:
			Size n_;
		public:
			explicit SPROUT_CONSTEXPR conj_div_value(Size n)
				: n_(n)
			{}
			template<typename Complex>
			SPROUT_CONSTEXPR Complex operator()(Complex const& x) const {
				return conj(x) / typename Complex::value_type(n_);
			}
		};
		template<typename Size>
		SPROUT_CONSTEXPR sprout::detail::conj_div_value<Size>
		conj_div(Size n) {
			return sprout::detail::conj_div_value<Size>(n);
		}
	}	// namespace detail
	//
	// ifft
	//
	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	ifft(RandomAccessIterator first, RandomAccessIterator last) {
		sprout::transform(first, last, first, sprout::detail::conj_value());
		sprout::fft(first, last);
		sprout::transform(first, last, first, sprout::detail::conj_div(last - first));
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FFT_CXX14_IFFT_HPP
