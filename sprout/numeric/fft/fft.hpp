/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FFT_FFT_HPP
#define SPROUT_NUMERIC_FFT_FFT_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/complex.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// fft
	//
	template<typename RandomAccessIterator>
	inline SPROUT_CXX14_CONSTEXPR void
	fft(RandomAccessIterator first, RandomAccessIterator last) {
		typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
		typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
		typedef typename value_type::value_type elem_type;
		using sprout::real;
		using sprout::imag;
		difference_type const size = last - first;
		// scrambler
		for (difference_type i = 0, j = 1; j < size - 1; ++j) {
			for (difference_type k = size >> 1; k > (i ^= k); k >>= 1)
				;
			if (j < i) {
				sprout::swap(first[i], first[j]);
			}
		}
		// L shaped butterflies
		elem_type const theta = -(sprout::math::half_pi<elem_type>() / size);
		for (difference_type m = 4; m <= size; m <<= 1) {
			difference_type mq = m >> 2;
			// W == 1
			for (difference_type k = mq; k >= 1; k >>= 2) {
				for (difference_type j = mq - k; j < mq - (k >> 1); ++j) {
					difference_type j1 = j + mq;
					difference_type j2 = j1 + mq;
					difference_type j3 = j2 + mq;
					value_type x1 = first[j] - first[j1];
					first[j] += first[j1];
					value_type x3 = first[j3] - first[j2];
					first[j2] += first[j3];
					first[j1] = value_type(
						real(x1) - imag(x3),
						imag(x1) + real(x3)
						);
					first[j3] = value_type(
						real(x1) + imag(x3),
						imag(x1) - real(x3)
						);
				}
			}
			if (m == size) {
				continue;
			}
			difference_type irev = size >> 1;
			elem_type w1r = sprout::cos(theta * irev);
			for (difference_type k = mq; k >= 1; k >>= 2) {
				for (difference_type j = m + mq - k; j < m + mq - (k >> 1); ++j) {
					difference_type j1 = j + mq;
					difference_type j2 = j1 + mq;
					difference_type j3 = j2 + mq;
					value_type x1 = first[j] - first[j1];
					first[j] += first[j1];
					value_type x3 = first[j3] - first[j2];
					first[j2] += first[j3];
					elem_type x0r = real(x1) - imag(x3);
					elem_type x0i = imag(x1) + real(x3);
					first[j1] = value_type(
						w1r * (x0r + x0i),
						w1r * (x0i - x0r)
						);
					x0r = real(x1) + imag(x3);
					x0i = imag(x1) - real(x3);
					first[j3] = value_type(
						w1r * (-x0r + x0i),
						w1r * (-x0i - x0r)
						);
				}
			}
			for (difference_type i = 2 * m; i < size; i += m) {
				for (difference_type k = size >> 1; k > (irev ^= k); k >>= 1)
					;
				elem_type w1r = sprout::cos(theta * irev);
				elem_type w1i = sprout::sin(theta * irev);
				elem_type w3r = sprout::cos(theta * 3 * irev);
				elem_type w3i = sprout::sin(theta * 3 * irev);
				for (difference_type k = mq; k >= 1; k >>= 2) {
					for (difference_type j = i + mq - k; j < i + mq - (k >> 1); ++j) {
						difference_type j1 = j + mq;
						difference_type j2 = j1 + mq;
						difference_type j3 = j2 + mq;
						value_type x1 = first[j] - first[j1];
						first[j] += first[j1];
						value_type x3 = first[j3] - first[j2];
						first[j2] += first[j3];
						elem_type x0r = real(x1) - imag(x3);
						elem_type x0i = imag(x1) + real(x3);
						first[j1] = value_type(
							w1r * x0r - w1i * x0i,
							w1r * x0i + w1i * x0r
							);
						x0r = real(x1) + imag(x3);
						x0i = imag(x1) - real(x3);
						first[j3] = value_type(
							w3r * x0r - w3i * x0i,
							w3r * x0i + w3i * x0r
							);
					}
				}
			}
		}
		// radix 2 butterflies
		difference_type mq = size >> 1;
		for (difference_type k = mq; k >= 1; k >>= 2) {
			for (difference_type j = mq - k; j < mq - (k >> 1); ++j) {
				difference_type j1 = mq + j;
				value_type x0 = first[j] - first[j1];
				first[j] += first[j1];
				first[j1] = x0;
			}
		}
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FFT_FFT_HPP
