#ifndef SPROUT_RANDOM_GEOMETRIC_DISTRIBUTION_HPP
#define SPROUT_RANDOM_GEOMETRIC_DISTRIBUTION_HPP

#include <cmath>
#include <ios>
#include <limits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/uniform_01.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		SPROUT_CONSTEXPR T floor(T x) {
			return x >= T(0) ? std::floor(x) : -std::ceil(-x);
		}
		template<typename T>
		SPROUT_CONSTEXPR T ceil(T x) {
			return x >= T(0) ? std::ceil(x) : -std::floor(-x);
		}
	}	// namespace detail
	namespace random {
		//
		// geometric_distribution
		//
		template<typename IntType = int, typename RealType = double>
		class geometric_distribution {
		public:
			typedef RealType input_type;
			typedef IntType result_type;
		private:
			static SPROUT_CONSTEXPR bool arg_check_nothrow(RealType p_arg) {
				return RealType(0) < p_arg && p_arg < RealType(1);
			}
			static SPROUT_CONSTEXPR RealType arg_check(RealType p_arg) {
				return arg_check_nothrow(p_arg)
					? p_arg
					: throw std::invalid_argument("geometric_distribution<>: invalid argument (0 < p_arg && p_arg < 1)")
					;
			}
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef geometric_distribution distribution_type;
			private:
				static SPROUT_CONSTEXPR bool arg_check_nothrow(RealType p_arg) {
					return distribution_type::arg_check_nothrow(p_arg);
				}
			private:
				RealType p_;
			public:
				SPROUT_CONSTEXPR param_type()
					: p_(RealType(0.5))
				{}
				SPROUT_CONSTEXPR explicit param_type(RealType p_arg)
					: p_(arg_check(p_arg))
				{}
				SPROUT_CONSTEXPR RealType p() const {
					return p_;
				}
				template<typename Elem, typename Traits>
				friend std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					RealType p;
					if (lhs >> p) {
						if (arg_check_nothrow(p)) {
							rhs.p_ = p;
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
					return lhs << rhs.p_;
				}
				SPROUT_CONSTEXPR friend bool operator==(param_type const& lhs, param_type const& rhs) {
					return lhs.p_ == rhs.p_;
				}
				SPROUT_CONSTEXPR friend bool operator!=(param_type const& lhs, param_type const& rhs) {
					return !(lhs == rhs);
				}
			};
		private:
		public:
			static SPROUT_CONSTEXPR RealType init_log_1mp(RealType p) {
				using std::log;
				return log(1 - p);
			}
		private:
		public:
			RealType p_;
			RealType log_1mp_;
		private:
			template<typename Engine, typename Random>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, geometric_distribution> generate_1(Random const& rnd) const {
				using std::log;
				using std::floor;
				return sprout::random::random_result<Engine, geometric_distribution>(
					static_cast<IntType>(floor(log(RealType(1) - rnd.result()) / log_1mp_)),
					rnd.engine(),
					*this
					);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, geometric_distribution> generate(Engine const& eng) const {
				return generate_1<Engine>(sprout::random::uniform_01<RealType>()(eng));
			}
		public:
			SPROUT_CONSTEXPR geometric_distribution()
				: p_(RealType(0.5))
				, log_1mp_(init_log_1mp(RealType(0.5)))
			{}
			SPROUT_CONSTEXPR explicit geometric_distribution(RealType p_arg)
				: p_(arg_check(p_arg))
				, log_1mp_(init_log_1mp(p_arg))
			{}
			SPROUT_CONSTEXPR explicit geometric_distribution(param_type const& parm)
				: p_(parm.p())
				, log_1mp_(init_log_1mp(parm.p()))
			{}
			SPROUT_CONSTEXPR result_type p() const {
				return p_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return 0;
			}
			SPROUT_CONSTEXPR result_type max() const {
				return std::numeric_limits<result_type>::max();
			}
			SPROUT_CONSTEXPR param_type param() const {
				return param_type(p_);
			}
			void param(param_type const& parm) {
				p_ = parm.p();
				log_1mp_ = init_log_1mp(p_);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, geometric_distribution> operator()(Engine const& eng) const {
				return generate(eng);
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				geometric_distribution& rhs
				)
			{
				param_type parm;
				if (lhs >> parm) {
					rhs.param(parm);
				}
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				geometric_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			SPROUT_CONSTEXPR friend bool operator==(geometric_distribution const& lhs, geometric_distribution const& rhs) {
				return lhs.param() == rhs.param();
			}
			SPROUT_CONSTEXPR friend bool operator!=(geometric_distribution const& lhs, geometric_distribution const& rhs) {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::geometric_distribution;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_GEOMETRIC_DISTRIBUTION_HPP
