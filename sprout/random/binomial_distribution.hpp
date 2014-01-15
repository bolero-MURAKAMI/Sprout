/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_BINOMIAL_DISTRIBUTION_HPP
#define SPROUT_RANDOM_BINOMIAL_DISTRIBUTION_HPP

#include <iosfwd>
#include <istream>
#include <sprout/config.hpp>
#include <sprout/array/array.hpp>
#include <sprout/cstdlib/abs.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/uniform_01.hpp>
#include <sprout/generator/functions.hpp>
#include <sprout/assert.hpp>
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
#	include <sprout/workaround/recursive_function_template.hpp>
#endif

namespace sprout {
	namespace random {
		namespace detail {
#		define SPROUT_BINOMIAL_TABLE_DEF \
			table_type{{ \
				1, \
				1, \
				2, \
				6, \
				24, \
				120 \
			}}

			template<typename RealType>
			struct binomial_table {
			public:
				typedef sprout::array<RealType, 10> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_BINOMIAL_TABLE_DEF)
					;
			};
			template<class RealType>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::random::detail::binomial_table<RealType>::table_type
			sprout::random::detail::binomial_table<RealType>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_BINOMIAL_TABLE_DEF)
				;

#		undef SPROUT_BINOMIAL_TABLE_DEF
		}	// namespace detail
		//
		// binomial_distribution
		//
		template<typename IntType = int, typename RealType = double>
		class binomial_distribution {
		public:
			typedef RealType input_type;
			typedef IntType result_type;
		private:
			struct btrd_type {
			public:
				RealType r;
				RealType nr;
				RealType npq;
				RealType b;
				RealType a;
				RealType c;
				RealType alpha;
				RealType v_r;
				RealType u_rv_r;
			};
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef binomial_distribution distribution_type;
			private:
				IntType t_;
				RealType p_;
			public:
				SPROUT_CONSTEXPR param_type()
					: t_(1)
					, p_(0.5)
				{}
				explicit SPROUT_CONSTEXPR param_type(IntType t_arg, RealType p_arg = RealType(0.5))
					: t_((SPROUT_ASSERT(t_arg >= IntType(0)), t_arg))
					, p_((SPROUT_ASSERT(RealType(0) <= p_arg && p_arg <= RealType(1)), p_arg))
				{}
				SPROUT_CONSTEXPR IntType t() const SPROUT_NOEXCEPT {
					return t_;
				}
				SPROUT_CONSTEXPR RealType p() const SPROUT_NOEXCEPT {
					return p_;
				}
				template<typename Elem, typename Traits>
				friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					IntType t;
					RealType p;
					if (lhs >> t >> std::ws >> p) {
						if (t >= IntType(0) && RealType(0) <= p && p <= RealType(1)) {
							rhs.t_ = t;
							rhs.p_ = p;
						} else {
							lhs.setstate(std::ios_base::failbit);
						}
					}
					return lhs;
				}
				template<typename Elem, typename Traits>
				friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
					std::basic_ostream<Elem, Traits>& lhs,
					param_type const& rhs
					)
				{
					return lhs << rhs.t_ << " " << rhs.p_;
				}
				friend SPROUT_CONSTEXPR bool operator==(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return lhs.t_ == rhs.t_ && lhs.p_ == rhs.p_;
				}
				friend SPROUT_CONSTEXPR bool operator!=(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return !(lhs == rhs);
				}
			};
		private:
			static SPROUT_CONSTEXPR IntType init_t(IntType t) {
				return t;
			}
			static SPROUT_CONSTEXPR RealType init_p(RealType p) {
				return RealType(0.5) < p ? 1 - p : p;
			}
			static SPROUT_CONSTEXPR IntType init_m(IntType t, RealType p) {
				return static_cast<IntType>((init_t(t) + 1) * init_p(p));
			}
			static SPROUT_CONSTEXPR btrd_type
			init_btrd_6(
				IntType, RealType, RealType r, RealType nr, RealType npq,
				RealType b, RealType a, RealType c, RealType alpha, RealType v_r
				)
			{
				return btrd_type{
					r, nr, npq,
					b, a, c, alpha, v_r,
					RealType(0.86) * v_r
				};
			}
			static SPROUT_CONSTEXPR btrd_type
			init_btrd_5(
				IntType t, RealType p, RealType r, RealType nr, RealType npq,
				RealType sqrt_npq, RealType b
				)
			{
				return init_btrd_6(
					t, p, r, nr, npq, b,
					RealType(-0.0873) + RealType(0.0248) * b + RealType(0.01) * p,
					t * p + RealType(0.5),
					(RealType(2.83) + RealType(5.1) / b) * sqrt_npq, RealType(0.92) - RealType(4.2) / b
					);
			}
			static SPROUT_CONSTEXPR btrd_type init_btrd_4(IntType t, RealType p, RealType r, RealType nr, RealType npq, RealType sqrt_npq) {
				return init_btrd_5(t, p, r, nr, npq, sqrt_npq, RealType(1.15) + RealType(2.53) * sqrt_npq);
			}
			static SPROUT_CONSTEXPR btrd_type init_btrd_3(IntType t, RealType p, RealType r, RealType nr, RealType npq) {
				return init_btrd_4(t, p, r, nr, npq, sprout::sqrt(npq));
			}
			static SPROUT_CONSTEXPR btrd_type init_btrd_2(IntType t, RealType p, RealType r) {
				return init_btrd_3(t, p, r, (t + 1) * r, t * p * (1 - p));
			}
			static SPROUT_CONSTEXPR btrd_type init_btrd_1(IntType t, RealType p) {
				return init_btrd_2(t, p, p / (1 - p));
			}
			static SPROUT_CONSTEXPR btrd_type init_btrd(IntType t, RealType p) {
				return init_btrd_1(init_t(t), init_p(p));
			}
			static SPROUT_CONSTEXPR RealType init_q_n(IntType t, RealType p) {
				return sprout::pow(1 - init_p(p), static_cast<RealType>(init_t(t)));
			}
			static SPROUT_CONSTEXPR bool init_use_inversion(IntType t, RealType p) {
				return init_m(t, p) < 11;
			}
			static SPROUT_CONSTEXPR RealType fc_1(RealType ikp1) {
				return (RealType(1) / 12 - (RealType(1) / 360 - (RealType(1) / 1260) * (ikp1 * ikp1)) * (ikp1 * ikp1)) * ikp1;
			}
			static SPROUT_CONSTEXPR RealType fc(IntType k) {
				return k < 10
					? sprout::random::detail::binomial_table<RealType>::table[k]
					: fc_1(RealType(1) / (k + 1))
					;
			}
		private:
			IntType t_;
			RealType p_;
			IntType m_;
			btrd_type btrd_;
			RealType q_n_;
		private:
			SPROUT_CONSTEXPR bool use_inversion() const {
				return m_ < 11;
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type
			invert(IntType t, RealType p, Engine& eng) const {
				RealType q = 1 - p;
				RealType s = p / q;
				RealType a = (t + 1) * s;
				RealType r = q_n_;
				RealType u = static_cast<RealType>(sprout::random::uniform_01<RealType>()(eng));
				IntType x = 0;
				while (u > r) {
					u = u - r;
					++x;
					r = ((a / x) - s) * r;
				}
				return x;
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type
			generate(Engine& eng) const {
				for (; ; ) {
					RealType u = RealType();
					RealType v = static_cast<RealType>(sprout::random::uniform_01<RealType>()(eng));
					if (v <= btrd_.u_rv_r) {
						RealType u = v / btrd_.v_r - RealType(0.43);
						return static_cast<result_type>(sprout::math::floor((2 * btrd_.a / (RealType(0.5) - sprout::math::abs(u)) + btrd_.b) * u + btrd_.c));
					}

					if (v >= btrd_.v_r) {
						u = static_cast<RealType>(sprout::random::uniform_01<RealType>()(eng)) - RealType(0.5);
					} else {
						u = v / btrd_.v_r - RealType(0.93);
						u = ((u < 0) ? -RealType(0.5) : RealType(0.5)) - u;
						v = static_cast<RealType>(sprout::random::uniform_01<RealType>()(eng)) * btrd_.v_r;
					}
					RealType us = RealType(0.5) - sprout::math::abs(u);
					IntType k = static_cast<IntType>(sprout::math::floor((2 * btrd_.a / us + btrd_.b) * u + btrd_.c));
					if (k < 0 || k > t_) {
						continue;
					}
					v = v * btrd_.alpha / (btrd_.a / (us * us) + btrd_.b);
					RealType km = sprout::math::abs(k - m_);
					if (km <= 15) {
						RealType f = RealType(1);
						if (m_ < k) {
							IntType i = m_;
							do {
								++i;
								f = f * (btrd_.nr / i - btrd_.r);
							} while (i != k);
						} else if (m_ > k) {
							IntType i = k;
							do {
								++i;
								v = v * (btrd_.nr / i - btrd_.r);
							} while (i != m_);
						}
						if (v <= f) {
							return k;
						} else {
							continue;
						}
					} else {
						v = sprout::math::log(v);
						RealType rho = (km / btrd_.npq) * (((km / RealType(3) + RealType(0.625)) * km + RealType(1) / 6) / btrd_.npq + RealType(0.5));
						RealType t = -km * km / (2 * btrd_.npq);
						if (v < t - rho) {
							return k;
						}
						if (v > t + rho) {
							continue;
						}
						IntType nm = t_ - m_ + 1;
						RealType h = (m_ + RealType(0.5)) * sprout::math::log((m_ + 1) / (btrd_.r * nm)) + fc(m_) + fc(t_ - m_);
						IntType nk = t_ - k + 1;
						if (v <= h + (t_ + 1) * sprout::math::log(static_cast<RealType>(nm) / nk)
							+ (k + RealType(0.5)) * sprout::math::log(nk * btrd_.r / (k + 1)) - fc(k) - fc(t_ - k)
							)
						{
							return k;
						} else {
							continue;
						}
					}
				}
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert_4(Engine const& eng, RealType u, RealType q, RealType s, RealType a, RealType r, IntType x = 0) const {
				return u > r
					? invert_4(eng, u - r, q, s, a, ((a / (x + 1)) - s) * r, x + 1)
					: sprout::random::random_result<Engine, binomial_distribution>(x, eng, *this)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert_3(IntType t, Engine const& eng, RealType u, RealType q, RealType s) const {
				return invert_4(eng, u, q, s, (t + 1) * s, q_n_);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert_2(IntType t, RealType p, Engine const& eng, RealType u, RealType q) const {
				return invert_3(t, eng, u, q, p / q);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert_1(IntType t, RealType p, Engine const& eng, RealType u) const {
				return invert_2(t, p, eng, u, 1 - p);
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert_0(IntType t, RealType p, Random const& rnd) const {
				return invert_1(t, p, sprout::generators::next_generator(rnd).engine(), sprout::generators::generated_value(rnd));
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert(IntType t, RealType p, Engine const& eng) const {
				return invert_0<Engine>(t, p, sprout::random::uniform_01<RealType>()(eng));
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert2_0(IntType t, sprout::random::random_result<Engine, binomial_distribution> const& rnd) const {
				return sprout::random::random_result<Engine, binomial_distribution>(
					t - sprout::generators::generated_value(rnd),
					sprout::generators::next_generator(rnd).engine(),
					sprout::generators::next_generator(rnd).distribution()
					);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			invert2(IntType t, RealType p, Engine const& eng) const {
				return invert2_0<Engine>(t, invert(t, p, eng));
			}
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_10(Engine const& eng, RealType v, IntType k, IntType nm, RealType h, IntType nk) const {
				return v <= h + (t_ + 1) * sprout::math::log(static_cast<RealType>(nm) / nk)
					+ (k + RealType(0.5)) * sprout::math::log(nk * btrd_.r / (k + 1)) - fc(k) - fc(t_ - k)
					? sprout::random::random_result<Engine, binomial_distribution>(k, eng, *this)
					: generate<D + 1>(eng)
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_10(Engine const&, RealType, IntType, IntType, RealType, IntType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_9(Engine const& eng, RealType v, IntType k, IntType nm) const {
				return generate_10<D + 1>(
					eng, v, k, nm, (m_ + RealType(0.5)) * sprout::math::log((m_ + 1) / (btrd_.r * nm)) + fc(m_) + fc(t_ - m_), t_ - k + 1
					);
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_9(Engine const&, RealType, IntType, IntType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_8(Engine const& eng, RealType v, IntType k, RealType rho, RealType t) const {
				return v < t - rho ? sprout::random::random_result<Engine, binomial_distribution>(k, eng, *this)
					: v > t + rho ? generate<D + 1>(eng)
					: generate_9<D + 1>(eng, v, k, t_ - m_ + 1)
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_8(Engine const&, RealType, IntType, RealType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_3(Engine const& eng, RealType v, IntType k, RealType f) const {
				return v <= f
					? sprout::random::random_result<Engine, binomial_distribution>(k, eng, *this)
					: generate<D + 1>(eng)
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_3(Engine const&, RealType, IntType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_2(Engine const& eng, RealType v, IntType k, RealType f, IntType i) const {
				return i != k
					? generate_7_2<D + 1>(eng, v * (btrd_.nr / (i + 1) - btrd_.r), k, f, i + 1)
					: generate_7_3<D + 1>(eng, v, k, f)
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_2(Engine const&, RealType, IntType, RealType, IntType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_1(Engine const& eng, RealType v, IntType k, RealType f, IntType i) const {
				return i != k
					? generate_7_1<D + 1>(eng, v, k, f * (btrd_.nr / (i + 1) - btrd_.r), i + 1)
					: generate_7_3<D + 1>(eng, v, k, f)
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_1(Engine const&, RealType, IntType, RealType, IntType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7(Engine const& eng, RealType v, IntType k, RealType f = RealType(1)) const {
				return m_ < k ? generate_7_1<D + 1>(eng, v, k, f * (btrd_.nr / (m_ + 1) - btrd_.r), m_ + 1)
					: m_ > k ? generate_7_2<D + 1>(eng, v * (btrd_.nr / (k + 1) - btrd_.r), k, f, k + 1)
					: generate_7_3<D + 1>(eng, v, k, f)
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7(Engine const&, RealType, IntType, RealType = RealType(1)) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_6(Engine const& eng, RealType v, IntType k, RealType km) const {
				return km <= 15
					? generate_7<D + 1>(eng, v, k)
					: generate_8<D + 1>(
						eng, sprout::math::log(v), k,
						(km / btrd_.npq) * (((km / RealType(3) + RealType(0.625)) * km + RealType(1) / 6) / btrd_.npq + RealType(0.5)),
						-km * km / (2 * btrd_.npq))
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_6(Engine const&, RealType, IntType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_5(Engine const& eng, RealType v, RealType us, IntType k) const {
				return k < 0 || k > t_
					? generate<D + 1>(eng)
					: generate_6<D + 1>(eng, v * btrd_.alpha / (btrd_.a / (us * us) + btrd_.b), k, sprout::abs(k - m_))
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_5(Engine const&, RealType, RealType, IntType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_4(Engine const& eng, RealType v, RealType u, RealType us) const {
				return generate_5<D + 1>(eng, v, us, static_cast<IntType>(sprout::math::floor((2 * btrd_.a / us + btrd_.b) * u + btrd_.c)));
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_4(Engine const&, RealType, RealType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_3(Engine const& eng, RealType v, RealType u) const {
				return generate_4<D + 1>(eng, v, u, 0.5 - sprout::abs(u));
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_3(Engine const&, RealType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_2(Random const& rnd, RealType v) const {
				return v >= btrd_.v_r
					? generate_3<D + 1>(
						sprout::generators::next_generator(rnd).engine(), v,
						sprout::generators::generated_value(rnd) - RealType(0.5)
						)
					: generate_3<D + 1>(
						sprout::generators::next_generator(rnd).engine(), sprout::generators::generated_value(rnd) * btrd_.v_r,
						((v / btrd_.v_r - RealType(0.93)) < 0 ? RealType(-0.5) : RealType(0.5)) - (v / btrd_.v_r - RealType(0.93))
						)
					;
			}
			template<int D, typename Engine, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_2(Random const&, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_1_1(Engine const& eng, RealType u) const {
				return sprout::random::random_result<Engine, binomial_distribution>(
					static_cast<IntType>(sprout::math::floor((2 * btrd_.a / (RealType(0.5) - sprout::abs(u)) + btrd_.b) * u + btrd_.c)),
					eng, *this
					);
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_1_1(Engine const&, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_1(Engine const& eng, RealType v) const {
				return v <= btrd_.u_rv_r
					? generate_1_1<D + 1>(eng, v / btrd_.v_r - RealType(0.43))
					: generate_2<D + 1, Engine>(sprout::random::uniform_01<RealType>()(eng), v)
					;
			}
			template<int D, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_1(Engine const&, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_0(Random const& rnd) const {
				return generate_1<D + 1>(sprout::generators::next_generator(rnd).engine(), sprout::generators::generated_value(rnd));
			}
			template<int D, typename Engine, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_0(Random const&) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D = 16, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate(Engine const& eng) const {
				return generate_0<D + 1, Engine>(sprout::random::uniform_01<RealType>()(eng));
			}
			template<int D = 16, typename Engine, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate(Engine const&) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
#else
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_10(Engine const& eng, RealType v, IntType k, IntType nm, RealType h, IntType nk) const {
				return v <= h + (t_ + 1) * sprout::math::log(static_cast<RealType>(nm) / nk)
					+ (k + RealType(0.5)) * sprout::math::log(nk * btrd_.r / (k + 1)) - fc(k) - fc(t_ - k)
					? sprout::random::random_result<Engine, binomial_distribution>(k, eng, *this)
					: generate(eng)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_9(Engine const& eng, RealType v, IntType k, IntType nm) const {
				return generate_10(
					eng, v, k, nm, (m_ + RealType(0.5)) * sprout::math::log((m_ + 1) / (btrd_.r * nm)) + fc(m_) + fc(t_ - m_), t_ - k + 1
					);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_8(Engine const& eng, RealType v, IntType k, RealType rho, RealType t) const {
				return v < t - rho ? sprout::random::random_result<Engine, binomial_distribution>(k, eng, *this)
					: v > t + rho ? generate(eng)
					: generate_9(eng, v, k, t_ - m_ + 1)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_3(Engine const& eng, RealType v, IntType k, RealType f) const {
				return v <= f
					? sprout::random::random_result<Engine, binomial_distribution>(k, eng, *this)
					: generate(eng)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_2(Engine const& eng, RealType v, IntType k, RealType f, IntType i) const {
				return i != k
					? generate_7_2(eng, v * (btrd_.nr / (i + 1) - btrd_.r), k, f, i + 1)
					: generate_7_3(eng, v, k, f)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7_1(Engine const& eng, RealType v, IntType k, RealType f, IntType i) const {
				return i != k
					? generate_7_1(eng, v, k, f * (btrd_.nr / (i + 1) - btrd_.r), i + 1)
					: generate_7_3(eng, v, k, f)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_7(Engine const& eng, RealType v, IntType k, RealType f = RealType(1)) const {
				return m_ < k ? generate_7_1(eng, v, k, f * (btrd_.nr / (m_ + 1) - btrd_.r), m_ + 1)
					: m_ > k ? generate_7_2(eng, v * (btrd_.nr / (k + 1) - btrd_.r), k, f, k + 1)
					: generate_7_3(eng, v, k, f)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_6(Engine const& eng, RealType v, IntType k, RealType km) const {
				return km <= 15
					? generate_7(eng, v, k)
					: generate_8(
						eng, sprout::math::log(v), k,
						(km / btrd_.npq) * (((km / RealType(3.0) + RealType(0.625)) * km + RealType(1.0) / 6) / btrd_.npq + RealType(0.5)),
						-km * km / (2 * btrd_.npq))
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_5(Engine const& eng, RealType v, RealType, RealType us, IntType k) const {
				return k < 0 || k > t_
					? generate(eng)
					: generate_6(eng, v * btrd_.alpha / (btrd_.a / (us * us) + btrd_.b), k, sprout::abs(k - m_))
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_4(Engine const& eng, RealType v, RealType u, RealType us) const {
				return generate_5(eng, v, u, us, static_cast<IntType>(sprout::math::floor((2 * btrd_.a / us + btrd_.b) * u + btrd_.c)));
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_3(Engine const& eng, RealType v, RealType u) const {
				return generate_4(eng, v, u, 0.5 - sprout::abs(u));
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_2(Random const& rnd, RealType v) const {
				return v >= btrd_.v_r
					? generate_3(
						sprout::generators::next_generator(rnd).engine(),
						v,
						sprout::generators::generated_value(rnd) - RealType(0.5)
						)
					: generate_3(
						sprout::generators::next_generator(rnd).engine(),
						sprout::generators::generated_value(rnd) * btrd_.v_r,
						((v / btrd_.v_r - RealType(0.93)) < 0 ? RealType(-0.5) : RealType(0.5)) - (v / btrd_.v_r - RealType(0.93))
						)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_1_1(Engine const& eng, RealType u) const {
				return sprout::random::random_result<Engine, binomial_distribution>(
					static_cast<IntType>(sprout::math::floor((2 * btrd_.a / (RealType(0.5) - sprout::abs(u)) + btrd_.b) * u + btrd_.c)),
					eng,
					*this
					);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_1(Engine const& eng, RealType v) const {
				return v <= btrd_.u_rv_r
					? generate_1_1(eng, v / btrd_.v_r - RealType(0.43))
					: generate_2<Engine>(sprout::random::uniform_01<RealType>()(eng), v)
					;
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate_0(Random const& rnd) const {
				return generate_1(sprout::generators::next_generator(rnd).engine(), sprout::generators::generated_value(rnd));
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate(Engine const& eng) const {
				return generate_0<Engine>(sprout::random::uniform_01<RealType>()(eng));
			}
#endif
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate2_0(IntType t, sprout::random::random_result<Engine, binomial_distribution> const& rnd) const {
				return sprout::random::random_result<Engine, binomial_distribution>(
					t - sprout::generators::generated_value(rnd),
					sprout::generators::next_generator(rnd).engine(),
					sprout::generators::next_generator(rnd).distribution()
					);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution>
			generate2(IntType t, Engine const& eng) const {
				return generate2_0<Engine>(t, generate(eng));
			}
			SPROUT_CXX14_CONSTEXPR void init() {
				m_ = init_m(t_, p_);
				if (use_inversion()) {
					q_n_ = init_q_n(t_, p_);
				} else {
					btrd_ = init_btrd(t_, p_);
				}
			}
		public:
			SPROUT_CONSTEXPR binomial_distribution()
				: t_(1)
				, p_(RealType(0.5))
				, m_(init_m(1, RealType(0.5)))
				, btrd_(!init_use_inversion(1, RealType(0.5)) ? init_btrd(1, RealType(0.5)) : btrd_type())
				, q_n_(init_use_inversion(1, RealType(0.5)) ? init_q_n(1, RealType(0.5)) : RealType())
			{}
			explicit SPROUT_CONSTEXPR binomial_distribution(IntType t_arg, RealType p_arg = RealType(0.5))
				: t_((SPROUT_ASSERT(t_arg >= IntType(0)), t_arg))
				, p_((SPROUT_ASSERT(RealType(0) <= p_arg && p_arg <= RealType(1)), p_arg))
				, m_(init_m(t_arg, p_arg))
				, btrd_(!init_use_inversion(t_arg, p_arg) ? init_btrd(t_arg, p_arg) : btrd_type())
				, q_n_(init_use_inversion(t_arg, p_arg) ? init_q_n(t_arg, p_arg) : RealType())
			{}
			explicit SPROUT_CONSTEXPR binomial_distribution(param_type const& parm)
				: t_(parm.t())
				, p_(parm.p())
				, m_(init_m(parm.t(), parm.p()))
				, btrd_(!init_use_inversion(parm.t(), parm.p()) ? init_btrd(parm.t(), parm.p()) : btrd_type())
				, q_n_(init_use_inversion(parm.t(), parm.p()) ? init_q_n(parm.t(), parm.p()) : RealType())
			{}
			SPROUT_CONSTEXPR result_type t() const SPROUT_NOEXCEPT {
				return t_;
			}
			SPROUT_CONSTEXPR result_type p() const SPROUT_NOEXCEPT {
				return p_;
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return 0;
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return t_;
			}
			SPROUT_CXX14_CONSTEXPR void reset() SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR param_type param() const SPROUT_NOEXCEPT {
				return param_type(t_, p_);
			}
			SPROUT_CXX14_CONSTEXPR void param(param_type const& parm) {
				t_ = parm.t();
				p_ = parm.p();
				init();
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng) const {
				return use_inversion() ? RealType(0.5) < p_
						? t_ - invert(t_, 1 - p_, eng)
						: invert(t_, p_, eng)
					: RealType(0.5) < p_ ? t_ - generate(eng)
					: generate(eng)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution> const operator()(Engine const& eng) const {
				return use_inversion() ? RealType(0.5) < p_
						? invert2(t_, 1 - p_, eng)
						: invert(t_, p_, eng)
					: RealType(0.5) < p_ ? generate2(t_, eng)
					: generate(eng)
					;
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng, param_type const& parm) const {
				return binomial_distribution(parm)(eng);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, binomial_distribution> const operator()(Engine const& eng, param_type const& parm) const {
				return binomial_distribution(parm)(eng);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				binomial_distribution& rhs
				)
			{
				param_type parm;
				if (lhs >> parm) {
					rhs.param(parm);
				}
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				binomial_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator==(binomial_distribution const& lhs, binomial_distribution const& rhs) SPROUT_NOEXCEPT {
				return lhs.param() == rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator!=(binomial_distribution const& lhs, binomial_distribution const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::binomial_distribution;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_BINOMIAL_DISTRIBUTION_HPP
