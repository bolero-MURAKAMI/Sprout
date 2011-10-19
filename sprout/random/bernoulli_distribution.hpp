#ifndef SPROUT_RANDOM_BERNOULLI_DISTRIBUTION_HPP
#define SPROUT_RANDOM_BERNOULLI_DISTRIBUTION_HPP

#include <iosfwd>
#include <sprout/config.hpp>
#include <sprout/random/random_result.hpp>

namespace sprout {
	namespace random {
		//
		// bernoulli_distribution
		//
		template<typename RealType = double>
		class bernoulli_distribution {
		public:
			typedef int input_type;
			typedef bool result_type;
		private:
			static SPROUT_CONSTEXPR bool arg_check_nothrow(RealType p_arg) {
				return p_arg >= 0 && p_arg <= 1;
			}
			static SPROUT_CONSTEXPR RealType arg_check(RealType p_arg) {
				return arg_check_nothrow(p_arg)
					? p_arg
					: throw "assert(p_arg >= 0 && p_arg <= 1)"
					;
			}
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef bernoulli_distribution distribution_type;
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
			RealType p_;
		private:
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, bernoulli_distribution> generate(
				sprout::random::random_result<Engine> const& rnd
				) const
			{
				return sprout::random::random_result<Engine, bernoulli_distribution>(
					RealType(rnd.result() - rnd.engine().min()) <= p_ * RealType(rnd.engine().max() - rnd.engine().min()),
					rnd.engine(),
					*this
					);
			}
		public:
			SPROUT_CONSTEXPR bernoulli_distribution()
				: p_(RealType(0.5))
			{}
			SPROUT_CONSTEXPR explicit bernoulli_distribution(RealType p_arg)
				: p_(arg_check(p_arg))
			{}
			SPROUT_CONSTEXPR explicit bernoulli_distribution(param_type const& parm)
				: p_(parm.p())
			{}
			SPROUT_CONSTEXPR RealType p() const {
				return p_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return false;
			}
			SPROUT_CONSTEXPR result_type max() const {
				return true;
			}
			SPROUT_CONSTEXPR param_type param() const {
				return param_type(p_);
			}
			void param(param_type const& parm) {
				p_ = parm.p();
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, bernoulli_distribution> operator()(Engine const& eng) const {
				return p_ == RealType(0)
					? sprout::random::random_result<Engine, bernoulli_distribution>(false, eng, *this)
					: generate(eng())
					;
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				bernoulli_distribution& rhs
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
				bernoulli_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			SPROUT_CONSTEXPR friend bool operator==(bernoulli_distribution const& lhs, bernoulli_distribution const& rhs) {
				return lhs.param() == rhs.param();
			}
			SPROUT_CONSTEXPR friend bool operator!=(bernoulli_distribution const& lhs, bernoulli_distribution const& rhs) {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::bernoulli_distribution;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_BERNOULLI_DISTRIBUTION_HPP

