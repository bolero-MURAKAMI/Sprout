/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_SEED_ARRAY_HPP
#define SPROUT_RANDOM_SEED_ARRAY_HPP

#include <cstdint>
#include <iterator>
#include <initializer_list>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/array/make_array.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/container/indexes.hpp>
#include <sprout/iterator/type_traits/is_iterator_of.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/fixed/results.hpp>
#include <sprout/algorithm/fixed/copy.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/algorithm/cxx14/copy.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>
#include <sprout/range/algorithm/fixed/copy.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/detail/container_complate.hpp>
#include HDR_ALGORITHM_MIN_MAX_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	namespace random {
		namespace detail {
			template<typename UIntType>
			class seed_array_init {
			public:
				template<typename IntType>
				SPROUT_CONSTEXPR UIntType operator()(IntType const& x) const {
					return static_cast<UIntType>(x % (std::uint_least64_t(2) << 32));
				}
			};

			template<std::size_t N>
			class seed_array_impl {
			public:
				typedef std::uint_least32_t result_type;
			protected:
				typedef sprout::array<result_type, N> array_type;
			protected:
				array_type v;
			public:
				SPROUT_CONSTEXPR seed_array_impl() SPROUT_NOEXCEPT
					: v{{}}
				{}
				template<typename InputIterator>
				SPROUT_CONSTEXPR seed_array_impl(InputIterator begin, InputIterator end)
					: v(sprout::fixed::transform<array_type>(begin, end, sprout::random::detail::seed_array_init<result_type>()))
				{}
			};
		}	// namespace detail
		//
		// seed_array
		//
		template<std::size_t N>
		class seed_array
			: public sprout::random::detail::seed_array_impl<N>
		{
		private:
			typedef sprout::random::detail::seed_array_impl<N> impl_type;
		public:
			typedef typename impl_type::result_type result_type;
			typedef result_type value_type;
			typedef std::size_t size_type;
		private:
			using impl_type::v;
		private:
			static SPROUT_CONSTEXPR result_type tp(result_type x) {
				return x ^ (x >> 27);
			}
			static SPROUT_CONSTEXPR size_type tval(size_type n) {
				return (n >= 623) ? 11
					: (n >= 68) ? 7
					: (n >= 39) ? 5
					: (n >= 7) ? 3
					: (n - 1) / 2
					;
			}
			template<typename Result, sprout::index_t... Indexes>
			static SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type set2_impl(
				Result const& result,
				size_type kpn, size_type kqn, size_type kn,
				typename sprout::container_traits<Result>::value_type r3,
				typename sprout::container_traits<Result>::value_type r4,
				sprout::index_tuple<Indexes...>
				)
			{
				return sprout::remake<Result>(
					result,
					sprout::size(result),
					(Indexes == kn ? r4
						: (result[Indexes]
							^ (Indexes == kpn ? r3 : typename sprout::container_traits<Result>::value_type())
							^ (Indexes == kqn ? r4 : typename sprout::container_traits<Result>::value_type())
							)
						)...
					);
			}
			template<typename Result>
			static SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type set2(
				Result const& result,
				size_type kpn, size_type kqn, size_type kn,
				typename sprout::container_traits<Result>::value_type r3,
				typename sprout::container_traits<Result>::value_type r4_3
				)
			{
				return set2_impl(result, kpn, kqn, kn, r3, r3 - r4_3, sprout::container_indexes<Result>::make());
			}
			template<typename Result, sprout::index_t... Indexes>
			static SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type set1_impl(
				Result const& result,
				size_type kpn, size_type kqn, size_type kn,
				typename sprout::container_traits<Result>::value_type r1,
				typename sprout::container_traits<Result>::value_type r2,
				sprout::index_tuple<Indexes...>
				)
			{
				return sprout::remake<Result>(
					result,
					sprout::size(result),
					(Indexes == kn ? r2
						: (result[Indexes]
							+ (Indexes == kpn ? r1 : typename sprout::container_traits<Result>::value_type())
							+ (Indexes == kqn ? r2 : typename sprout::container_traits<Result>::value_type())
							)
						)...
					);
			}
			template<typename Result>
			static SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type set1(
				Result const& result,
				size_type kpn, size_type kqn, size_type kn,
				typename sprout::container_traits<Result>::value_type r1,
				typename sprout::container_traits<Result>::value_type r2_1
				)
			{
				return set1_impl(result, kpn, kqn, kn, r1, r1 + r2_1, sprout::container_indexes<Result>::make());
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type gen2(
				Result const& result,
				size_type n, size_type s, size_type m, size_type t, size_type p, size_type q,
				size_type k
				) const
			{
				return k < m + n ? gen2(
						set2(
							result, (k + p) % n, (k + q) % n, k % n,
							1566083941 * tp(result[k % n] + result[(k + p) % n] + result[(k + n - 1) % n]),
							k % n
							),
						n, s, m, t, p, q,
						k + 1
						)
					: sprout::deep_copy(result)
					;
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type gen1_2(
				Result const& result,
				size_type n, size_type s, size_type m, size_type t, size_type p, size_type q,
				size_type k
				) const
			{
				return k < m ? gen1_2(
						set1(
							result, (k + p) % n, (k + q) % n, k % n,
							1664525 * tp(result[k % n] ^ result[(k + p) % n] ^ result[(k - 1) % n]),
							k % n
							),
						n, s, m, t, p, q,
						k + 1
						)
					: sprout::deep_copy(result)
					;
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type gen1_1(
				Result const& result,
				size_type n, size_type s, size_type m, size_type t, size_type p, size_type q,
				size_type k
				) const
			{
				return k <= s ? gen1_1(
						set1(
							result, (k + p) % n, (k + q) % n, k % n,
							1664525 * tp(result[k % n] ^ result[(k + p) % n] ^ result[(k - 1) % n]),
							k % n + v[k - 1]
							),
						n, s, m, t, p, q,
						k + 1
						)
					: sprout::deep_copy(result)
					;
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type gen1_0(
				Result const& result,
				size_type n, size_type s, size_type p, size_type q
				) const
			{
				return set1(
					result, p, q, size_type(0),
					1664525 * tp(result[0] ^ result[p] ^ result[n - 1]),
					s
					);
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type gen_impl(
				Result const& result,
				size_type n, size_type s, size_type m, size_type t, size_type p, size_type q
				) const
			{
				return gen2(
					gen1_2(
						gen1_1(
							gen1_0(
								result,
								n, s, p, q
								),
							n, s, m, t, p, q,
							1
							),
						n, s, m, t, p, q,
						s + 1
						),
					n, s, m, t, p, q,
					m
					);
			}
			template<typename Result, typename TempResult>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type gen(
				Result const& result, TempResult const& temp_result,
				size_type n, size_type s, size_type m, size_type t
				) const
			{
				return sprout::range::fixed::copy(
					gen_impl(temp_result, n, s, m, t, (n - t) / 2, (n - t) / 2 + t),
					result
					);
			}
		public:
			SPROUT_CONSTEXPR seed_array() SPROUT_NOEXCEPT
				: impl_type()
			{}
			seed_array(seed_array const&) = default;
			template<typename T>
			SPROUT_INITIALIZER_LIST_CONSTEXPR seed_array(std::initializer_list<T> il)
				: impl_type(il.begin(), il.end())
			{}
			template<typename InputIterator>
			SPROUT_CONSTEXPR seed_array(InputIterator begin, InputIterator end)
				: impl_type(begin, end)
			{}
			template<typename InputRange>
			explicit SPROUT_CONSTEXPR seed_array(InputRange const& rng)
				: impl_type(sprout::begin(rng), sprout::end(rng))
			{}
			template<typename RandomAccessIterator>
			SPROUT_CXX14_CONSTEXPR void generate(RandomAccessIterator begin, RandomAccessIterator end) const {
				typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
				if (begin == end) {
					return;
				}
				sprout::fill(begin, end, static_cast<value_type>(0x8b8b8b8bu));
				size_type n = end - begin;
				size_type s = size();
				size_type m = NS_SSCRISK_CEL_OR_SPROUT::max(s + 1, n);
				size_type t = tval(n);
				size_type p = (n - t) / 2;
				size_type q = p + t;
				for (size_type k = 0; k < m; ++k) {
					size_type kn = k % n;
					size_type kpn = (k + p) % n;
					size_type kqn = (k + q) % n;
					size_type k1n = (k + n - 1) % n;
					value_type r1 = 1664525 * tp(begin[kn] ^ begin[kpn] ^ begin[k1n]);
					value_type r2 = r1 + (
						k == 0 ? s
						: k <= s ? (kn + v[k - 1])
						: kn
						);
					begin[kpn] += r1;
					begin[kqn] += r2;
					begin[kn] = r2;
				}
				for (size_type k = m; k < m + n; ++k) {
					size_type kn = k % n;
					size_type kpn = (k + p) % n;
					size_type kqn = (k + q) % n;
					size_type k1n = (k + n - 1) % n;
					value_type r3 = 1566083941 * tp(begin[kn] + begin[kpn] + begin[k1n]);
					value_type r4 = r3 - kn;
					begin[kpn] ^= r3;
					begin[kqn] ^= r4;
					begin[kn] = r4;
				}
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type generate(Result const& result) const {
				typedef typename sprout::container_traits<Result>::value_type value_type;
				typedef sprout::array<value_type, sprout::container_traits<Result>::static_size> temp_type;
				return !sprout::empty(result) ? gen(
						result, sprout::pit<temp_type>(static_cast<value_type>(0x8b8b8b8bu)),
						sprout::size(result), size(), sprout::max<size_type>(size() + 1, sprout::size(result)),
						tval(sprout::size(result))
						)
					: sprout::detail::container_complate(result)
					;
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type generate() const {
				return generate(sprout::pit<Result>());
			}
			SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
				return v.size();
			}
			template<
				typename OutputIterator,
				typename sprout::enabler_if<sprout::is_iterator_outputable<OutputIterator>::value>::type = sprout::enabler
			>
			SPROUT_CXX14_CONSTEXPR void param(OutputIterator dest) const {
				sprout::copy(v.begin(), v.end(), dest);
			}
			SPROUT_CONSTEXPR sprout::array<result_type, N> const& param() const {
				return v;
			}
			template<
				typename Result,
				typename sprout::enabler_if<!sprout::is_iterator_outputable<Result>::value>::type = sprout::enabler
			>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type param(Result const& result) const {
				return sprout::fixed::copy(v.begin(), v.end(), result);
			}
			template<typename Result>
			SPROUT_CONSTEXPR typename sprout::fixed::results::algorithm<Result>::type param() const {
				return sprout::fixed::copy<Result>(v.begin(), v.end());
			}
		};

		//
		// make_seed_array
		//
		template<typename... Args>
		inline SPROUT_CONSTEXPR sprout::random::seed_array<sizeof...(Args)>
		make_seed_array(Args&&... args) {
			return sprout::random::seed_array<sizeof...(Args)>(
				sprout::make_common_array(SPROUT_FORWARD(Args, args)...)
				);
		}
	}	// namespace random

	using sprout::random::seed_array;
	using sprout::random::make_seed_array;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_SEED_ARRAY_HPP
