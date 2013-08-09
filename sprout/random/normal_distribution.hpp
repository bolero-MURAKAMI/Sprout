/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_NORMAL_DISTRIBUTION_HPP
#define SPROUT_RANDOM_NORMAL_DISTRIBUTION_HPP

#include <ios>
#include <istream>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/cos.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sqrt.hpp>
#include <sprout/random/uniform_01.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace random {
		//
		// normal_distribution
		//
		template<typename RealType = double>
		class normal_distribution {
		public:
			typedef RealType input_type;
			typedef RealType result_type;
		private:
			struct private_construct_t {};
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef normal_distribution distribution_type;
			private:
				RealType mean_;
				RealType sigma_;
			public:
				SPROUT_CONSTEXPR param_type()
					: mean_(RealType(0.0))
					, sigma_(RealType(1.0))
				{}
				explicit SPROUT_CONSTEXPR param_type(RealType mean_arg, RealType sigma_arg = RealType(1.0))
					: mean_(mean_arg)
					, sigma_((SPROUT_ASSERT(sigma_arg >= RealType(0)), sigma_arg))
				{}
				SPROUT_CONSTEXPR RealType mean() const SPROUT_NOEXCEPT {
					return mean_;
				}
				SPROUT_CONSTEXPR RealType sigma() const SPROUT_NOEXCEPT {
					return sigma_;
				}
				SPROUT_CONSTEXPR RealType stddev() const SPROUT_NOEXCEPT {
					return sigma_;
				}
				template<typename Elem, typename Traits>
				friend std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					RealType mean;
					RealType sigma;
					if (lhs >> mean >> std::ws >> sigma) {
						if (sigma >= RealType(0)) {
							rhs.mean_ = mean;
							rhs.sigma_ = sigma;
						} else {
							lhs.setstate(std::ios_base::failbit);
						}
					}
					return lhs;
				}
				template<typename Elem, typename Traits>
				friend std::basic_ostream<Elem, Traits>& operator<<(
					std::basic_ostream<Elem, Traits>& lhs,
					param_type const& rhs
					)
				{
					return lhs << rhs.mean_ << " " << rhs.sigma_;
				}
				friend SPROUT_CONSTEXPR bool operator==(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return lhs.mean_ == rhs.mean_ && lhs.sigma_ == rhs.sigma_;
				}
				friend SPROUT_CONSTEXPR bool operator!=(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return !(lhs == rhs);
				}
			};
		private:
			RealType mean_;
			RealType sigma_;
			RealType r1_;
			RealType r2_;
			RealType cached_rho_;
			bool valid_;
		private:
			SPROUT_CONSTEXPR normal_distribution(
				RealType mean, RealType sigma, RealType r1, RealType r2,
				RealType cached_rho, bool valid,
				private_construct_t
				)
				: mean_(mean)
				, sigma_(sigma)
				, r1_(r1)
				, r2_(r2)
				, cached_rho_(cached_rho)
				, valid_(valid)
			{}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution>
			generate_2(Engine const& eng, RealType r1, RealType r2, RealType cached_rho, bool valid) const {
				return sprout::random::random_result<Engine, normal_distribution>(
					cached_rho
						* (valid
							? sprout::cos(sprout::math::two_pi<result_type>() * r1)
							: sprout::sin(sprout::math::two_pi<result_type>() * r1)
							)
						* sigma_ + mean_,
					eng,
					normal_distribution(
						mean_,
						sigma_,
						r1,
						r2,
						cached_rho,
						valid,
						private_construct_t()
						)
					);
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution>
			generate_1_1(RealType r1, Random const& rnd) const {
				return generate_2(
					rnd.engine(), r1, rnd.result(),
					sprout::sqrt(-result_type(2) * sprout::math::log(result_type(1) - rnd.result())), true
					);
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution>
			generate_1(Random const& rnd) const {
				return generate_1_1<Engine>(rnd.result(), rnd());
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution>
			generate(Engine const& eng) const {
				return !valid_
					? generate_1<Engine>(sprout::random::uniform_01<RealType>()(eng))
					: generate_2(eng, r1_, r2_, cached_rho_, false)
					;
			}
		public:
			SPROUT_CONSTEXPR normal_distribution()
				: mean_(RealType(0.0))
				, sigma_(RealType(1.0))
				, r1_(0)
				, r2_(0)
				, cached_rho_(0)
				, valid_(false)
			{}
			explicit SPROUT_CONSTEXPR normal_distribution(RealType mean_arg, RealType sigma_arg = RealType(1.0))
				: mean_(mean_arg)
				, sigma_((SPROUT_ASSERT(sigma_arg >= RealType(0)), sigma_arg))
				, r1_(0)
				, r2_(0)
				, cached_rho_(0)
				, valid_(false)
			{}
			explicit SPROUT_CONSTEXPR normal_distribution(param_type const& parm)
				: mean_(parm.mean())
				, sigma_(parm.sigma())
				, r1_(0)
				, r2_(0)
				, cached_rho_(0)
				, valid_(false)
			{}
			SPROUT_CONSTEXPR result_type mean() const SPROUT_NOEXCEPT {
				return mean_;
			}
			SPROUT_CONSTEXPR result_type sigma() const SPROUT_NOEXCEPT {
				return sigma_;
			}
			SPROUT_CONSTEXPR result_type stddev() const SPROUT_NOEXCEPT {
				return sigma_;
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return -sprout::numeric_limits<RealType>::infinity();
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return sprout::numeric_limits<RealType>::infinity();
			}
			SPROUT_CONSTEXPR param_type param() const SPROUT_NOEXCEPT {
				return param_type(mean_, sigma_);
			}
			void param(param_type const& parm) {
				mean_ = parm.mean();
				sigma_ = parm.sigma();
				valid_ = false;
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution> operator()(Engine const& eng) const {
				return generate(eng);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				normal_distribution& rhs
				)
			{
				param_type parm;
				bool valid;
				RealType cached_rho;
				RealType r1;
				RealType r2;
				if (lhs >> parm >> std::ws >> valid >> std::ws >> cached_rho >> std::ws >> r1 >> std::ws >> r2) {
					rhs.param(parm);
					rhs.valid_ = valid;
					rhs.cached_rho_ = cached_rho;
					rhs.r1_ = r1;
					rhs.r2_ = r2;
				}
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				normal_distribution const& rhs
				)
			{
				return lhs << rhs.param() << " " << rhs.valid_ << " " << rhs.cached_rho_ << " " << rhs.r1_ << " " << rhs.r2_;
			}
			friend SPROUT_CONSTEXPR bool operator==(normal_distribution const& lhs, normal_distribution const& rhs) SPROUT_NOEXCEPT {
				return lhs.param() == rhs.param()
					&& lhs.valid_ == rhs.valid_
					&& lhs.cached_rho_ == rhs.cached_rho_
					&& lhs.r1_ == rhs.r1_ && lhs.r2_ == rhs.r2_
					;
			}
			friend SPROUT_CONSTEXPR bool operator!=(normal_distribution const& lhs, normal_distribution const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::normal_distribution;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_NORMAL_DISTRIBUTION_HPP
