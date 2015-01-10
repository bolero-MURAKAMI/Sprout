/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_DETAIL_SEED_IMPL_HPP
#define SPROUT_RANDOM_DETAIL_SEED_IMPL_HPP

#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/array.hpp>
#include <sprout/pit.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/random/detail/const_mod.hpp>
#include <sprout/detail/integer/static_log2.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename IntType, IntType m>
			struct seed_log
				: public std::conditional<
					m == 0,
					sprout::integral_constant<int, sprout::numeric_limits<IntType>::digits>,
					sprout::integral_constant<int, sprout::detail::static_log2<m>::value>
				>::type
			{};
			template<typename IntType, IntType m, int log>
			struct seed_k
				: public sprout::integral_constant<
					int,
					(log + ((~(IntType(2) << (log - 1)) & m)? 32 : 31)) / 32
				>
			{};

			template<typename IntType, IntType m, int log, int k, typename Array>
			inline SPROUT_CONSTEXPR IntType
			seed_one_int_impl(Array const& arr, IntType s, int j) {
				return j < k ? sprout::random::detail::seed_one_int_impl<IntType, m, k>(
						arr,
						sprout::random::detail::const_mod<IntType, m>::mult_add(
							IntType(1) << 32 * j,
							sprout::random::detail::const_mod<IntType, m>::apply(IntType(arr[j + 3])),
							s
							),
						j + 1
						)
					: s
					;
			}
			template<typename IntType, IntType m, typename Sseq>
			inline SPROUT_CONSTEXPR IntType
			seed_one_int(Sseq const& seq) {
				typedef typename sprout::random::detail::seed_log<IntType, m>::type log_t;
				typedef typename sprout::random::detail::seed_k<IntType, m, log_t::value>::type k_t;
				return sprout::random::detail::seed_one_int_impl<IntType, m, k_t::value>(
					seq.generate(sprout::pit<sprout::array<std::uint_least32_t, log_t::value / 32 + 4> >()),
					0, 0
					);
			}
			template<typename IntType, IntType m, typename Sseq>
			inline SPROUT_CXX14_CONSTEXPR IntType
			seed_one_int(Sseq& seq) {
				typedef typename sprout::random::detail::seed_log<IntType, m>::type log_t;
				typedef typename sprout::random::detail::seed_k<IntType, m, log_t::value>::type k_t;
				sprout::array<std::uint_least32_t, log_t::value / 32 + 4> arr{{}};
				seq.generate(arr.begin(), arr.begin() + (k_t::value + 3));
				IntType s = 0;
				for (int j = 0; j < k_t::value; ++j) {
					IntType digit = sprout::random::detail::const_mod<IntType, m>::apply(IntType(arr[j + 3]));
					IntType mult = IntType(1) << 32 * j;
					s = sprout::random::detail::const_mod<IntType, m>::mult_add(mult, digit, s);
				}
				return s;
			}

			template<typename IntType, IntType m, int log, int k, typename InputIterator>
			inline SPROUT_CONSTEXPR IntType
			get_one_int_impl(InputIterator first, InputIterator last, IntType s, int j) {
				return j < k
					? first != last
						? sprout::random::detail::get_one_int_impl<IntType, m, k>(
							sprout::next(first), last,
							sprout::random::detail::const_mod<IntType, m>::mult_add(
								IntType(1) << 32 * j,
								sprout::random::detail::const_mod<IntType, m>::apply(IntType(*first)),
								s
								),
							j + 1
							)
						: throw std::invalid_argument("Not enough elements in call to seed.")
					: s
					;
			}
			template<typename IntType, IntType m, typename InputIterator>
			inline SPROUT_CONSTEXPR IntType
			get_one_int(InputIterator first, InputIterator last) {
				typedef typename sprout::random::detail::seed_log<IntType, m>::type log_t;
				typedef typename sprout::random::detail::seed_k<IntType, m, log_t::value>::type k_t;
				return sprout::random::detail::get_one_int_impl<IntType, m, k_t::value>(
					first, last,
					0, 0
					);
			}
		}	// namespace detail
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_DETAIL_SEED_IMPL_HPP
