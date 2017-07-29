/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FFT_COEFFICIENT_ARRAY_HPP
#define SPROUT_NUMERIC_FFT_COEFFICIENT_ARRAY_HPP

#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/bit/bit_length.hpp>
#include <sprout/index_tuple/make_index_tuple.hpp>
#include <sprout/complex.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/constants.hpp>

namespace sprout {
	namespace detail
	{
		template<typename value_type, sprout::index_t... Indexes>
		inline SPROUT_CONSTEXPR sprout::array<sprout::complex<value_type>, sizeof...(Indexes)*2>
		make_fft_coefficients_impl(
			sprout::array<sprout::complex<value_type>, sizeof...(Indexes)> const& arr,
			sprout::complex<value_type> mul, sprout::index_tuple<Indexes...>
			)
		{
			return sprout::array<sprout::complex<value_type>, sizeof...(Indexes)*2>{ {
				arr[Indexes]..., (arr[Indexes] * mul)...
			} };
		}

		template<typename value_type, std::size_t N, std::size_t Size>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			N == 0,
			typename sprout::array<sprout::complex<value_type>, 1>
		>::type
			make_fft_coefficients_loop( bool ) {
			return typename sprout::array<sprout::complex<value_type>, 1>{ {
				{ static_cast<value_type>( 1 ) }
			} };
		}

		template<typename value_type, std::size_t N, std::size_t Size>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			N != 0,
			typename sprout::array<sprout::complex<value_type>, 1 << N>
		>::type
		make_fft_coefficients_loop(bool inverse)
		{
			return make_fft_coefficients_impl(
				make_fft_coefficients_loop<value_type, N - 1, Size>(inverse),
				{ 
					sprout::cos((inverse?-1:1)*sprout::math::two_pi<value_type>() / (1 << Size >> (N - 1))),
					sprout::sin((inverse?-1:1)*sprout::math::two_pi<value_type>() / (1 << Size >> (N - 1)))
				},
				sprout::make_index_tuple<1 << (N - 1)>()
				);
		}

		template<typename value_type, std::size_t Size>
		inline SPROUT_CONSTEXPR sprout::array<sprout::complex<value_type>, 1 << Size>
		make_fft_coefficients(bool inverse) {
			return make_fft_coefficients_loop<value_type, Size, Size>(inverse);
		}
	}	// namespace detail
	template<typename value_type, std::size_t Size>
	inline SPROUT_CONSTEXPR  sprout::array<sprout::complex<value_type>, Size>
	make_fft_coefficients() {
		return sprout::detail::make_fft_coefficients<value_type, sprout::bit_length(Size)-1>(false);
	}
	template<typename value_type, std::size_t Size>
	inline SPROUT_CONSTEXPR  sprout::array<sprout::complex<value_type>, Size>
	make_ifft_coefficients() {
		return sprout::detail::make_fft_coefficients<value_type, sprout::bit_length(Size)-1>(true);
	}
}	// namespce sprout

#endif	// SPROUT_NUMERIC_FFT_COEFFICIENT_ARRAY_HPP
