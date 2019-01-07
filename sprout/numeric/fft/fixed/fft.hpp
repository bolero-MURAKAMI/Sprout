/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_FFT_FIXED_FFT_HPP
#define SPROUT_NUMERIC_FFT_FIXED_FFT_HPP

#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/index_tuple/make_index_tuple.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/complex.hpp>
#include <sprout/math/less.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/numeric/fft/coefficients.hpp>

namespace sprout {
	namespace fixed {
		namespace detail {
			template<typename value_type, std::size_t Size>
			inline SPROUT_CONSTEXPR sprout::complex<value_type>
			fft_element(
				sprout::array<sprout::complex<value_type>, Size> const& arr,
				std::size_t step, std::size_t i, std::size_t j, bool sub,
				sprout::array<sprout::complex<value_type>, Size> const& coeffs
				)
			{
				return sub
					? arr[i * step + j] - coeffs[j * (Size / 2 / step)] * arr[i * step + j + Size / 2]
					: arr[i * step + j] + coeffs[j * (Size / 2 / step)] * arr[i * step + j + Size / 2]
					;
			}
		
			template<typename value_type, std::size_t Size, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR sprout::array<sprout::complex<value_type>, Size>
			butterfly(
				sprout::array<sprout::complex<value_type>, Size> const& arr,
				std::size_t step, 
				sprout::array<sprout::complex<value_type>, Size> const& coeffs,
				sprout::index_tuple<Indexes...>
				)
			{
				return sprout::array<sprout::complex<value_type>, Size> { {
					fft_element(arr, step, Indexes / (step * 2), Indexes%step, (Indexes&step) != 0, coeffs)...
				} };
			}
		
			template<typename value_type, std::size_t Size>
			inline SPROUT_CONSTEXPR sprout::array<sprout::complex<value_type>, Size>
			fft_loop(
				sprout::array<sprout::complex<value_type>, Size> const& arr,
				std::size_t step,
				sprout::array<sprout::complex<value_type>, Size> const& coeffs
				)
			{
				return step == Size ? arr
					: fft_loop(butterfly(arr, step, coeffs, sprout::make_index_tuple<Size>()), step * 2, coeffs);
			}
		
			template<typename value_type, std::size_t Size>
			inline SPROUT_CONSTEXPR sprout::array<sprout::complex<value_type>, Size>
			fft(sprout::array<sprout::complex<value_type>, Size> const& arr) {
				return fft_loop(arr, 1, sprout::make_fft_coefficients<value_type, Size>());
			}
		
		
			template<typename Container, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR sprout::array<typename sprout::container_traits<Container>::value_type, sizeof...(Indexes)>
			make_input_impl(Container const& cont, sprout::index_tuple<Indexes...>) {
				return sprout::array<typename sprout::container_traits<Container>::value_type, sizeof...(Indexes)> { {
					(sprout::math::less(Indexes, cont.size())
						? *sprout::next(sprout::begin(cont), Indexes)
						: static_cast<typename sprout::container_traits<Container>::value_type>(0)
						)...
					} };
			}
			template<std::size_t Size, typename Container>
			inline SPROUT_CONSTEXPR sprout::array<typename sprout::container_traits<Container>::value_type, Size>
			make_input(Container const& cont) {
				return make_input_impl(cont, sprout::make_index_tuple<Size>());
			}
			template<typename value_type, std::size_t Size, typename Result, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			make_fft_result_impl(sprout::array<sprout::complex<value_type>, Size> const& cont, Result const& result, sprout::index_tuple<Indexes...>) {
				return remake<Result>(result, sprout::size(result), cont[Indexes]...);
			}
			template<typename value_type, std::size_t Size, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
			make_fft_result(sprout::array<sprout::complex<value_type>, Size> const& cont, Result const& result) {
				return make_fft_result_impl(cont, result, sprout::make_index_tuple<sprout::container_traits<Result>::static_size>());
			}
		}	// namespace detail
		//
		// fft
		// Algorithm: Stockham decimation-in-time
		//
		template<typename Container, typename Result>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		fft(Container const& cont, Result const& result) {
			return sprout::fixed::detail::make_fft_result(
				sprout::fixed::detail::fft(sprout::fixed::detail::make_input<sprout::container_traits<Result>::static_size>(cont)), result
			);
		}

		template<typename Result, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type
		fft(Container const& cont) {
			return sprout::fixed::fft(cont, sprout::pit<Result>());
		}
	}	// namespace fixed

	using sprout::fixed::fft;
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_FFT_FIXED_FFT_HPP
