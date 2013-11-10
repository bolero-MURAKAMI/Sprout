/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_SHUFFLE_ORDER_HPP
#define SPROUT_RANDOM_SHUFFLE_ORDER_HPP

#include <cstddef>
#include <cstdint>
#include <ios>
#include <istream>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/array/array.hpp>
#include <sprout/array/comparison.hpp>
#include <sprout/operation/fixed/set.hpp>
#include <sprout/math/compare.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/linear_congruential.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>
#include <sprout/random/type_traits.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename UniformRandomNumberGenerator, std::size_t k>
			class shuffle_order_engine_member {
			protected:
				typedef UniformRandomNumberGenerator base_type;
				typedef typename base_type::result_type result_type;
			public:
				base_type rng_;
				sprout::array<result_type, k> v_;
				result_type y_;
			public:
				SPROUT_CXX14_CONSTEXPR shuffle_order_engine_member& operator=(shuffle_order_engine_member const& rhs) {
					rng_ = rhs.rng_;
					v_ = rhs.v_;
					y_ = rhs.y_;
					return *this;
				}
			};
		}	// namespace detail
		//
		// shuffle_order_engine
		//
		template<typename UniformRandomNumberGenerator, std::size_t k>
		class shuffle_order_engine
			: private sprout::random::detail::shuffle_order_engine_member<UniformRandomNumberGenerator, k>
		{
			static_assert(
				sprout::numeric_limits<typename UniformRandomNumberGenerator::result_type>::is_integer,
				"sprout::numeric_limits<typename UniformRandomNumberGenerator::result_type>::is_integer"
				);
			static_assert(k > 0, "k > 0");
		private:
			typedef sprout::random::detail::shuffle_order_engine_member<UniformRandomNumberGenerator, k> member_type;
		public:
			typedef UniformRandomNumberGenerator base_type;
			typedef typename base_type::result_type result_type;
		private:
			struct private_construct_t {};
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t buffer_size = k;
			SPROUT_STATIC_CONSTEXPR std::size_t table_size = k;
		public:
			static SPROUT_CONSTEXPR result_type static_min() SPROUT_NOEXCEPT {
				return base_type::static_min();
			}
			static SPROUT_CONSTEXPR result_type static_max() SPROUT_NOEXCEPT {
				return base_type::static_max();
			}
		private:
			template<typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Args) == k),
				member_type
			>::type init_member_1(Random const& rnd, Args const&... args) {
				return member_type{
					rnd.engine(),
					sprout::array<result_type, k>{{args...}},
					rnd.result()
					};
			}
			template<typename Random, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				(sizeof...(Args) < k),
				member_type
			>::type init_member_1(Random const& rnd, Args const&... args) {
				return init_member_1(rnd(), args..., rnd.result());
			}
			static SPROUT_CONSTEXPR member_type init_member(base_type const& rng) {
				return init_member_1(rng());
			}
		private:
			using member_type::rng_;
			using member_type::v_;
			using member_type::y_;
		private:
			SPROUT_CONSTEXPR shuffle_order_engine(
				base_type const& rng,
				sprout::array<result_type, k> const& v,
				result_type y,
				private_construct_t
				)
				: member_type{rng, v, y}
			{}
			template<typename Random, typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<shuffle_order_engine>
			generate_1(Random const& rnd, BaseUnsigned j) const {
				return sprout::random::random_result<shuffle_order_engine>(
					v_[j],
					shuffle_order_engine(
						rnd.engine(),
						sprout::fixed::set(v_, j, rnd.result()),
						v_[j],
						private_construct_t()
						)
					);
			}
			template<typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<shuffle_order_engine>
			generate(BaseUnsigned brange, BaseUnsigned off) const {
				return generate_1(
					rng_(),
					k == 1 ? BaseUnsigned(0)
						: sprout::math::less(brange, sprout::numeric_limits<BaseUnsigned>::max() / k) ? BaseUnsigned(k * off / (brange + 1))
						: sprout::math::less(brange, sprout::numeric_limits<std::uintmax_t>::max() / k)
							? static_cast<BaseUnsigned>(static_cast<std::uintmax_t>(off) * k / (static_cast<std::uintmax_t>(brange) + 1))
//						: static_cast<BaseUnsigned>(sprout::random::detail::muldiv(off, k, static_cast<std::uintmax_t>(brange) + 1)) // ???
						: (SPROUT_ASSERT_MSG(0, "Sorry, not implemented."), sprout::random::random_result<shuffle_order_engine>())
					);
			}
		public:
			SPROUT_CONSTEXPR shuffle_order_engine()
				: member_type(init_member(base_type()))
			{}
			explicit SPROUT_CONSTEXPR shuffle_order_engine(result_type seed)
				: member_type(init_member(base_type(seed)))
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CXX14_CONSTEXPR shuffle_order_engine(Sseq& seq)
				: member_type(init_member(base_type(seq)))
			{}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			explicit SPROUT_CONSTEXPR shuffle_order_engine(Sseq const& seq)
				: member_type(init_member(base_type(seq)))
			{}
			template<typename InputIterator>
			SPROUT_CONSTEXPR shuffle_order_engine(InputIterator first, InputIterator last)
				: member_type(init_member(base_type(first, last)))
			{}
			explicit SPROUT_CONSTEXPR shuffle_order_engine(base_type const& rng)
				: member_type(init_member(rng))
			{}
			SPROUT_CXX14_CONSTEXPR void seed() {
				member_type::operator=(init_member(base_type()));
			}
			SPROUT_CXX14_CONSTEXPR void seed(result_type seed) {
				member_type::operator=(init_member(base_type(seed)));
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq& seq) {
				member_type::operator=(init_member(base_type(seq)));
			}
			template<typename Sseq, typename sprout::enabler_if<sprout::random::is_seed_seq<Sseq>::value>::type = sprout::enabler>
			SPROUT_CXX14_CONSTEXPR void seed(Sseq const& seq) {
				member_type::operator=(init_member(base_type(seq)));
			}
			template<typename InputIterator>
			SPROUT_CXX14_CONSTEXPR void seed(InputIterator first, InputIterator last) {
				member_type::operator=(init_member(base_type(first, last)));
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return rng_.min();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return rng_.max();
			}
			SPROUT_CXX14_CONSTEXPR result_type operator()() {
				typedef typename std::make_unsigned<result_type>::type base_unsigned;
				base_unsigned const brange = sprout::random::detail::subtract<result_type>()(max(), min());
				base_unsigned const off = sprout::random::detail::subtract<result_type>()(y_, min());
				base_unsigned j = k == 1 ? base_unsigned(0)
					: sprout::math::less(brange, sprout::numeric_limits<base_unsigned>::max() / k) ? base_unsigned(k * off / (brange + 1))
					: sprout::math::less(brange, sprout::numeric_limits<std::uintmax_t>::max() / k)
						? static_cast<base_unsigned>(static_cast<std::uintmax_t>(off) * k / (static_cast<std::uintmax_t>(brange) + 1))
//					: static_cast<base_unsigned>(sprout::random::detail::muldiv(off, k, static_cast<std::uintmax_t>(brange) + 1)) // ???
					: (SPROUT_ASSERT_MSG(0, "Sorry, not implemented."), base_unsigned(0))
					;
				y_ = v_[j];
				v_[j] = static_cast<result_type>(rng_());
				return y_;
			}
			SPROUT_CONSTEXPR sprout::random::random_result<shuffle_order_engine> const operator()() const {
				typedef typename std::make_unsigned<result_type>::type base_unsigned;
				return generate(
					base_unsigned(sprout::random::detail::subtract<result_type>()(max(), min())),
					base_unsigned(sprout::random::detail::subtract<result_type>()(y_, min()))
					);
			}
			SPROUT_CONSTEXPR base_type const& base() const SPROUT_NOEXCEPT {
				return rng_;
			}
			friend SPROUT_CONSTEXPR bool operator==(shuffle_order_engine const& lhs, shuffle_order_engine const& rhs) SPROUT_NOEXCEPT {
				return lhs.rng_ == rhs.rng_ && lhs.y_ == rhs.y_ && lhs.v_ == rhs.v_;
			}
			friend SPROUT_CONSTEXPR bool operator!=(shuffle_order_engine const& lhs, shuffle_order_engine const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				shuffle_order_engine& rhs
				)
			{
				lhs >> rhs.rng_;
				for (std::size_t i = 0; i < k; ++i) {
					lhs >> std::ws >> rhs.v_[i];
				}
				lhs >> std::ws >> rhs.y_;
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				shuffle_order_engine const& rhs
				)
			{
				lhs << rhs.rng_;
				for (std::size_t i = 0; i < k; ++i) {
					lhs << ' ' << rhs.v_[i];
				}
				lhs << ' ' << rhs.y_;
				return lhs;
			}
		};
		template<typename UniformRandomNumberGenerator, std::size_t k>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::random::shuffle_order_engine<UniformRandomNumberGenerator, k>::buffer_size;
		template<typename UniformRandomNumberGenerator, std::size_t k>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::random::shuffle_order_engine<UniformRandomNumberGenerator, k>::table_size;

		//
		// knuth_b
		// kreutzer1986
		//
		typedef sprout::random::shuffle_order_engine<sprout::random::minstd_rand0, 256> knuth_b;
		typedef sprout::random::shuffle_order_engine<sprout::random::linear_congruential_engine<std::uint_fast32_t, 1366, 150889, 714025>, 97> kreutzer1986;
	}	// namespace random

	using sprout::random::shuffle_order_engine;
	using sprout::random::knuth_b;
	using sprout::random::kreutzer1986;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_SHUFFLE_ORDER_HPP
