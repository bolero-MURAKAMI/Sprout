/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FFT_FIXED_IFFT_HPP
#define SPROUT_NUMERIC_FFT_FIXED_IFFT_HPP

#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/complex.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/numeric/fft/coefficients.hpp>


namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename value_type, std::size_t Size, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
				make_ifft_result_impl(sprout::array<sprout::complex<value_type>, Size> const& container, Result const& result, sprout::index_tuple<Indexes...>) {
				return remake<Result>(result, sprout::size(result), (container[Indexes] / static_cast<value_type>(Size))...);
			}
			template<typename value_type, std::size_t Size, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
				make_ifft_result(sprout::array<sprout::complex<value_type>, Size> const& container, Result const& result) {
				return make_ifft_result_impl(container, result, sprout::make_index_tuple<sprout::container_traits<Result>::static_size>());
			}

			template<typename value_type, std::size_t Size>
			inline SPROUT_CONSTEXPR sprout::array<sprout::complex<value_type>, Size>
			ifft(sprout::array<sprout::complex<value_type>, Size> const& arr) {
				return sprout::fixed::detail::fft_loop(arr, 1, sprout::make_ifft_coefficients<value_type, Size>());
			}
		}	// namespace detail
		//
		// ifft
		// Algorithm: Stockham decimation-in-time
		//
		template<
			typename ForwardIterator, typename Result,
			typename sprout::container_traits<Result>::size_type Size
				= sprout::container_traits<Result>::static_size
		>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		ifft(ForwardIterator first, ForwardIterator last, Result const& result) {
			return sprout::fixed::detail::make_ifft_result(
				sprout::fixed::detail::ifft(sprout::fixed::detail::make_input<Size>(first, last)), result
			);
		}

		template<typename Result, typename ForwardIterator>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		ifft(ForwardIterator first, ForwardIterator last) {
			return sprout::fixed::ifft(first, last, sprout::pit<Result>());
		}
	}	// namespace fixed

	using sprout::fixed::ifft;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FFT_FIXED_IFFT_HPP
