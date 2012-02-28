#ifndef SPROUT_RANDOM_NORMAL_DISTRIBUTION_HPP
#define SPROUT_RANDOM_NORMAL_DISTRIBUTION_HPP

#include <cmath>
#include <limits>
#include <ios>
#include <istream>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/random/uniform_01.hpp>
#include <sprout/random/random_result.hpp>

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
			struct private_constructor_tag {};
		private:
			static SPROUT_CONSTEXPR bool arg_check_nothrow(RealType mean_arg, RealType sigma_arg) {
				return sigma_arg >= RealType(0);
			}
			static SPROUT_CONSTEXPR RealType arg_check(RealType mean_arg, RealType sigma_arg) {
				return arg_check_nothrow(mean_arg, sigma_arg)
					? mean_arg
					: throw std::invalid_argument("normal_distribution<>: invalid argument (sigma_arg >= 0)")
					;
			}
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef normal_distribution distribution_type;
			private:
				static SPROUT_CONSTEXPR bool arg_check_nothrow(RealType mean_arg, RealType sigma_arg) {
					return distribution_type::arg_check_nothrow(mean_arg, sigma_arg);
				}
			private:
				RealType mean_;
				RealType sigma_;
			public:
				SPROUT_CONSTEXPR param_type()
					: mean_(RealType(0.0))
					, sigma_(RealType(1.0))
				{}
				SPROUT_CONSTEXPR explicit param_type(RealType mean_arg, RealType sigma_arg = RealType(1.0))
					: mean_(arg_check(mean_arg, sigma_arg))
					, sigma_(sigma_arg)
				{}
				SPROUT_CONSTEXPR RealType mean() const {
					return mean_;
				}
				SPROUT_CONSTEXPR RealType sigma() const {
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
						if (arg_check_nothrow(mean, sigma)) {
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
				SPROUT_CONSTEXPR friend bool operator==(param_type const& lhs, param_type const& rhs) {
					return lhs.mean_ == rhs.mean_ && lhs.sigma_ == rhs.sigma_;
				}
				SPROUT_CONSTEXPR friend bool operator!=(param_type const& lhs, param_type const& rhs) {
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
				RealType mean,
				RealType sigma,
				RealType r1,
				RealType r2,
				RealType cached_rho,
				bool valid,
				private_constructor_tag
				)
				: mean_(mean)
				, sigma_(sigma)
				, r1_(r1)
				, r2_(r2)
				, cached_rho_(cached_rho)
				, valid_(valid)
			{}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution> generate_2(Engine const& eng, RealType r1, RealType r2, RealType cached_rho, bool valid) const {
				using std::sin;
				using std::cos;
				return sprout::random::random_result<Engine, normal_distribution>(
					cached_rho
						* (valid
							? cos(result_type(2) * sprout::math::pi<result_type>() * r1)
							: sin(result_type(2) * sprout::math::pi<result_type>() * r1)
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
						private_constructor_tag()
						)
					);
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution> generate_1_1(RealType r1, Random const& rnd) const {
				using std::sqrt;
				using std::log;
				return generate_2(rnd.engine(), r1, rnd.result(), sqrt(-result_type(2) * log(result_type(1) - rnd.result())), true);
			}
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution> generate_1(Random const& rnd) const {
				return generate_1_1<Engine>(rnd.result(), rnd());
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, normal_distribution> generate(Engine const& eng) const {
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
			SPROUT_CONSTEXPR explicit normal_distribution(RealType mean_arg, RealType sigma_arg = RealType(1.0))
				: mean_(arg_check(mean_arg, sigma_arg))
				, sigma_(sigma_arg)
				, r1_(0)
				, r2_(0)
				, cached_rho_(0)
				, valid_(false)
			{}
			SPROUT_CONSTEXPR explicit normal_distribution(param_type const& parm)
				: mean_(parm.mean())
				, sigma_(parm.sigma())
				, r1_(0)
				, r2_(0)
				, cached_rho_(0)
				, valid_(false)
			{}
			SPROUT_CONSTEXPR result_type mean() const {
				return mean_;
			}
			SPROUT_CONSTEXPR result_type sigma() const {
				return sigma_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return -std::numeric_limits<RealType>::infinity();
			}
			SPROUT_CONSTEXPR result_type max() const {
				return std::numeric_limits<RealType>::infinity();
			}
			SPROUT_CONSTEXPR param_type param() const {
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
			SPROUT_CONSTEXPR friend bool operator==(normal_distribution const& lhs, normal_distribution const& rhs) {
				return lhs.param() == rhs.param() && lhs.valid_ == rhs.valid_ && lhs.cached_rho_ == rhs.cached_rho_ && lhs.r1_ == rhs.r1_ && lhs.r2_ == rhs.r2_;
			}
			SPROUT_CONSTEXPR friend bool operator!=(normal_distribution const& lhs, normal_distribution const& rhs) {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::normal_distribution;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_NORMAL_DISTRIBUTION_HPP
