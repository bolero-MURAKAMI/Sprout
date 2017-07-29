/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_POISSON_DISTRIBUTION_HPP
#define SPROUT_RANDOM_POISSON_DISTRIBUTION_HPP

#include <istream>
#include <ostream>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/cstdlib/abs.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/uniform_01.hpp>
#include <sprout/random/results.hpp>
#include <sprout/assert.hpp>
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
#	include <sprout/workaround/recursive_function_template.hpp>
#endif

namespace sprout {
	namespace random {
		namespace detail {
#		define SPROUT_POISSON_TABLE_DEF \
			{{ \
				0.0, \
				0.0, \
				0.69314718055994529, \
				1.7917594692280550, \
				3.1780538303479458, \
				4.7874917427820458, \
				6.5792512120101012, \
				8.5251613610654147, \
				10.604602902745251, \
				12.801827480081469 \
			}}

			template<typename RealType>
			struct poisson_table {
			public:
				typedef sprout::array<RealType, 10> table_type;
			public:
				SPROUT_STATIC_CONSTEXPR table_type table
					SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_INNER(SPROUT_POISSON_TABLE_DEF)
					;
			};
			template<typename RealType>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::random::detail::poisson_table<RealType>::table_type
			sprout::random::detail::poisson_table<RealType>::table
				SPROUT_STATIC_CONSTEXPR_DATA_MEMBER_OUTER(SPROUT_POISSON_TABLE_DEF)
				;

#		undef SPROUT_POISSON_TABLE_DEF
		}	// namespace detail
		//
		// poisson_distribution
		//
		template<typename IntType = int, typename RealType = double>
		class poisson_distribution {
		public:
			typedef RealType input_type;
			typedef IntType result_type;
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef poisson_distribution distribution_type;
			private:
				RealType mean_;
			public:
				SPROUT_CONSTEXPR param_type()
					: mean_(RealType(1))
				{}
				param_type(param_type const&) = default;
				explicit SPROUT_CONSTEXPR param_type(RealType mean_arg)
					: mean_((SPROUT_ASSERT(RealType(0) < mean_arg), mean_arg))
				{}
				SPROUT_CONSTEXPR RealType mean() const SPROUT_NOEXCEPT {
					return mean_;
				}
				template<typename Elem, typename Traits>
				friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					RealType mean;
					if (lhs >> mean) {
						if (RealType(0) < mean) {
							rhs.mean_ = mean;
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
					return lhs << rhs.mean_;
				}
				friend SPROUT_CONSTEXPR bool operator==(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return lhs.mean_ == rhs.mean_;
				}
				friend SPROUT_CONSTEXPR bool operator!=(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return !(lhs == rhs);
				}
			};
			struct ptrd_type {
			public:
				RealType v_r;
				RealType a;
				RealType b;
				RealType smu;
				RealType inv_alpha;
			};
		private:
			static SPROUT_CONSTEXPR bool use_inversion_check(RealType mean) {
				return mean < 10;
			}
			static SPROUT_CONSTEXPR ptrd_type init_ptrd_2(RealType smu, RealType b) {
				return ptrd_type{
					0.9277 - 3.6224 / (b - 2),
					-0.059 + 0.02483 * b,
					b,
					smu,
					1.1239 + 1.1328 / (b - 3.4)
					};
			}
			static SPROUT_CONSTEXPR ptrd_type init_ptrd_1(RealType smu) {
				return init_ptrd_2(smu, 0.931 + 2.53 * smu);
			}
			static SPROUT_CONSTEXPR ptrd_type init_ptrd(RealType mean) {
				return use_inversion_check(mean) ? ptrd_type()
					: init_ptrd_1(sprout::sqrt(mean))
					;
			}
			static SPROUT_CONSTEXPR RealType init_exp_mean(RealType mean) {
				return !use_inversion_check(mean) ? RealType()
					: sprout::exp(-mean)
					;
			}
			static SPROUT_CONSTEXPR RealType log_factorial(IntType k) {
				return sprout::random::detail::poisson_table<RealType>::table[k];
			}
			static SPROUT_CONSTEXPR RealType log_sqrt_2pi() {
				return 0.91893853320467267;
			}
			static SPROUT_CONSTEXPR RealType generate_us(RealType u) {
				return 0.5 - sprout::abs(u);
			}
		private:
			RealType mean_;
			ptrd_type ptrd_;
			RealType exp_mean_;
		private:
			SPROUT_CONSTEXPR bool use_inversion() const {
				return use_inversion_check(mean_);
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type do_invert(Engine& eng) const {
				RealType u = sprout::random::uniform_01<RealType>()(eng);
				IntType x = 0;
				RealType p = exp_mean_;
				while (u > p) {
					u -= p;
					++x;
					p = p * mean_ / x;
				}
				return x;
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> invert_2(Random const& rnd, RealType u, IntType x, RealType p) const {
				return !(u > p) ? sprout::random::random_result<Engine, poisson_distribution>(x, sprout::random::next(rnd).engine(), *this)
					: invert_2<Engine>(rnd, u - p, x + 1, p * mean_ / (x + 1))
					;
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> invert_1(Random const& rnd, IntType x, RealType p) const {
				return invert_2<Engine>(rnd, sprout::random::result(rnd), x, p);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> invert(Engine const& eng) const {
				return invert_1<Engine>(sprout::random::uniform_01<RealType>()(eng), 0, exp_mean_);
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type do_generate(Engine& eng) const {
				for (; ; ) {
					RealType v = sprout::random::uniform_01<RealType>()(eng);
					if (v <= 0.86 * ptrd_.v_r) {
						RealType u = v / ptrd_.v_r - 0.43;
						return static_cast<IntType>(sprout::floor((2 * ptrd_.a / (0.5 - sprout::abs(u)) + ptrd_.b) * u + mean_ + 0.445));
					}
					RealType u = RealType();
					if (v >= ptrd_.v_r) {
						u = sprout::random::uniform_01<RealType>()(eng) - 0.5;
					} else {
						u = v / ptrd_.v_r - 0.93;
						u = ((u < 0) ? -0.5 : 0.5) - u;
						v = sprout::random::uniform_01<RealType>()(eng) * ptrd_.v_r;
					}
					RealType us = 0.5 - sprout::abs(u);
					if (us < 0.013 && v > us) {
						continue;
					}
					RealType k = sprout::floor((2 * ptrd_.a / us + ptrd_.b) * u + mean_ + 0.445);
					v = v * ptrd_.inv_alpha / (ptrd_.a / (us * us) + ptrd_.b);
					if ((k >= 10 && sprout::log(v * ptrd_.smu) <= (k + 0.5) * sprout::log(mean_ / k) - mean_ - log_sqrt_2pi() + k - (1 / 12. - (1 / 360. - 1 / (1260. * k * k)) / (k * k)) / k)
						|| (k >= 0 && sprout::log(v) <= k * sprout::log(mean_) - mean_ - log_factorial(static_cast<IntType>(k)))
						)
					{
						return static_cast<IntType>(k);
					}
				}
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_4(Random const& rnd, RealType u) const {
				return sprout::random::random_result<Engine, poisson_distribution>(
					static_cast<IntType>(sprout::floor((2 * ptrd_.a / (0.5 - sprout::abs(u)) + ptrd_.b) * u + mean_ + 0.445)),
					sprout::random::next(rnd).engine(),
					*this
					);
			}
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_3(Random const& rnd, RealType k, RealType v) const {
				return (k >= 10 && sprout::log(v * ptrd_.smu) <= (k + 0.5) * sprout::log(mean_ / k) - mean_ - log_sqrt_2pi() + k - (1 / 12. - (1 / 360. - 1 / (1260. * k * k)) / (k * k)) / k)
						|| (k >= 0 && sprout::log(v) <= k * sprout::log(mean_) - mean_ - log_factorial(static_cast<IntType>(k)))
						? sprout::random::random_result<Engine, poisson_distribution>(static_cast<IntType>(k), sprout::random::next(rnd).engine(), *this)
					: generate_1<Engine, D + 1>(rnd())
					;
			}
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_3(Random const&, RealType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_2(Random const& rnd, RealType v, RealType u, RealType us) const {
				return us < 0.013 && v > us ? generate_1<Engine, D + 1>(rnd())
					: generate_3<Engine, D + 1>(
						rnd,
						sprout::floor((2 * ptrd_.a / us + ptrd_.b) * u + mean_ + 0.445),
						v * ptrd_.inv_alpha / (ptrd_.a / (us * us) + ptrd_.b)
						)
					;
			}
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_2(Random const&, RealType, RealType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1_3(Random const& rnd, RealType, RealType u) const {
				return generate_2<Engine, D + 1>(rnd, sprout::random::result(rnd), ((u < 0) ? -0.5 : 0.5) - u, generate_us(((u < 0) ? -0.5 : 0.5) - u));
			}
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1_3(Random const&, RealType, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1_2(Random const& rnd, RealType v) const {
				return generate_2<Engine, D + 1>(rnd, v, sprout::random::result(rnd) - 0.5, generate_us(sprout::random::result(rnd) - 0.5));
			}
			template<typename Engine, int D, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1_2(Random const&, RealType) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<typename Engine, int D = 16, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1(Random const& rnd) const {
				return sprout::random::result(rnd) <= 0.86 * ptrd_.v_r ? generate_4<Engine>(rnd, sprout::random::result(rnd) / ptrd_.v_r - 0.43)
					: sprout::random::result(rnd) >= ptrd_.v_r
						? generate_1_2<Engine, D + 1>(rnd(), sprout::random::result(rnd))
					: generate_1_3<Engine, D + 1>(rnd(), sprout::random::result(rnd), sprout::random::result(rnd) / ptrd_.v_r - 0.93)
					;
			}
			template<typename Engine, int D = 16, typename Random, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1(Random const&) const {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
#else
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_3(Random const& rnd, RealType k, RealType v) const {
				return (k >= 10 && sprout::log(v * ptrd_.smu) <= (k + 0.5) * sprout::log(mean_ / k) - mean_ - log_sqrt_2pi() + k - (1 / 12. - (1 / 360. - 1 / (1260. * k * k)) / (k * k)) / k)
						|| (k >= 0 && sprout::log(v) <= k * sprout::log(mean_) - mean_ - log_factorial(static_cast<IntType>(k)))
						? sprout::random::random_result<Engine, poisson_distribution>(static_cast<IntType>(k), sprout::random::next(rnd).engine(), *this)
					: generate_1<Engine>(rnd())
					;
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_2(Random const& rnd, RealType v, RealType u, RealType us) const {
				return us < 0.013 && v > us ? generate_1<Engine>(rnd())
					: generate_3<Engine>(
						rnd,
						sprout::floor((2 * ptrd_.a / us + ptrd_.b) * u + mean_ + 0.445),
						v * ptrd_.inv_alpha / (ptrd_.a / (us * us) + ptrd_.b)
						)
					;
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1_3(Random const& rnd, RealType v, RealType u) const {
				return generate_2<Engine>(rnd, sprout::random::result(rnd), ((u < 0) ? -0.5 : 0.5) - u, generate_us(((u < 0) ? -0.5 : 0.5) - u));
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1_2(Random const& rnd, RealType v) const {
				return generate_2<Engine>(rnd, v, sprout::random::result(rnd) - 0.5, generate_us(sprout::random::result(rnd) - 0.5));
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate_1(Random const& rnd) const {
				return sprout::random::result(rnd) <= 0.86 * ptrd_.v_r ? generate_4<Engine>(rnd, sprout::random::result(rnd) / ptrd_.v_r - 0.43)
					: sprout::random::result(rnd) >= ptrd_.v_r
						? generate_1_2<Engine>(rnd(), sprout::random::result(rnd))
					: generate_1_3<Engine>(rnd(), sprout::random::result(rnd), sprout::random::result(rnd) / ptrd_.v_r - 0.93)
					;
			}
#endif
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> generate(Engine const& eng) const {
				return generate_1<Engine>(sprout::random::uniform_01<RealType>()(eng));
			}
		public:
			SPROUT_CONSTEXPR poisson_distribution()
				: mean_(RealType(1))
				, ptrd_(init_ptrd(RealType(1)))
				, exp_mean_(init_exp_mean(RealType(1)))
			{}
			poisson_distribution(poisson_distribution const&) = default;
			explicit SPROUT_CONSTEXPR poisson_distribution(RealType mean_arg)
				: mean_((SPROUT_ASSERT(RealType(0) < mean_arg), mean_arg))
				, ptrd_(init_ptrd(mean_arg))
				, exp_mean_(init_exp_mean(mean_arg))
			{}
			explicit SPROUT_CONSTEXPR poisson_distribution(param_type const& parm)
				: mean_(parm.mean())
				, ptrd_(init_ptrd(parm.mean()))
				, exp_mean_(init_exp_mean(parm.mean()))
			{}
			SPROUT_CONSTEXPR result_type mean() const SPROUT_NOEXCEPT {
				return mean_;
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return 0;
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return sprout::numeric_limits<result_type>::max();
			}
			SPROUT_CXX14_CONSTEXPR void reset() SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR param_type param() const SPROUT_NOEXCEPT {
				return param_type(mean_);
			}
			SPROUT_CXX14_CONSTEXPR void param(param_type const& parm) {
				mean_ = parm.mean();
				ptrd_ = init_ptrd(mean_);
				exp_mean_ = init_exp_mean(mean_);
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng) const {
				return use_inversion() ? do_invert(eng)
					: do_generate(eng)
					;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> const operator()(Engine const& eng) const {
				return use_inversion() ? invert(eng)
					: generate(eng)
					;
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng, param_type const& parm) const {
				return poisson_distribution(parm)(eng);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, poisson_distribution> const operator()(Engine const& eng, param_type const& parm) const {
				return poisson_distribution(parm)(eng);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				poisson_distribution& rhs
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
				poisson_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator==(poisson_distribution const& lhs, poisson_distribution const& rhs) SPROUT_NOEXCEPT {
				return lhs.param() == rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator!=(poisson_distribution const& lhs, poisson_distribution const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::poisson_distribution;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_POISSON_DISTRIBUTION_HPP
