#ifndef SPROUT_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP
#define SPROUT_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

#include <ios>
#include <istream>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>
#include <sprout/random/random_result.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename T, typename Engine>
			struct generate_uniform_real_result {
			public:
				T result;
				Engine engine;
			};

			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_false_1(
				sprout::random::random_result<Engine> const& rnd,
				T min_value,
				T max_value
				);
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_false_3(
				Engine const& eng,
				T min_value,
				T max_value,
				T result
				)
			{
				return result < max_value
					? sprout::random::detail::generate_uniform_real_result<T, Engine>{result, eng}
					: sprout::random::detail::generate_uniform_real_false_1(eng(), min_value, max_value)
					;
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_false_2(
				Engine const& eng,
				T min_value,
				T max_value,
				T numerator,
				T divisor
				)
			{
				return divisor > 0
					? numerator >= 0 && numerator <= divisor
						? sprout::random::detail::generate_uniform_real_false_3(
							eng,
							min_value,
							max_value,
							numerator / divisor * (max_value - min_value) + min_value
							)
						: throw "assert(numerator >= 0 && numerator <= divisor)"
					: throw "assert(divisor > 0)"
					;
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_false_1(
				sprout::random::random_result<Engine> const& rnd,
				T min_value,
				T max_value
				)
			{
				return sprout::random::detail::generate_uniform_real_false_2(
					rnd.engine(),
					min_value,
					max_value,
					static_cast<T>(rnd.result() - rnd.engine().min()),
					static_cast<T>(rnd.engine().max() - rnd.engine().min())
					);
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real(
				Engine const& eng,
				T min_value,
				T max_value,
				std::false_type
				)
			{
				return sprout::random::detail::generate_uniform_real_false_1(
					eng(),
					min_value,
					max_value
					);
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_true_1(
				sprout::random::random_result<Engine> const& rnd,
				T min_value,
				T max_value
				);
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_true_3(
				Engine const& eng,
				T min_value,
				T max_value,
				T result
				)
			{
				return result < max_value
					? sprout::random::detail::generate_uniform_real_result<T, Engine>{result, eng}
					: sprout::random::detail::generate_uniform_real_true_1(eng(), min_value, max_value)
					;
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_true_2(
				Engine const& eng,
				T min_value,
				T max_value,
				T numerator,
				T divisor
				)
			{
				return divisor > 0
					? numerator >= 0 && numerator <= divisor
						? sprout::random::detail::generate_uniform_real_true_3(
							eng,
							min_value,
							max_value,
							numerator / divisor * (max_value - min_value) + min_value
							)
						: throw "assert(numerator >= 0 && numerator <= divisor)"
					: throw "assert(divisor > 0)"
					;
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real_true_1(
				sprout::random::random_result<Engine> const& rnd,
				T min_value,
				T max_value
				)
			{
				typedef T result_type;
				typedef typename Engine::result_type base_result;
				return sprout::random::detail::generate_uniform_real_true_2(
					rnd.engine(),
					min_value,
					max_value,
					static_cast<T>(sprout::random::detail::subtract<base_result>()(rnd.result(), rnd.engine().min())),
					static_cast<T>(sprout::random::detail::subtract<base_result>()(rnd.engine().max(), rnd.engine().min())) + 1
					);
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real(
				Engine const& eng,
				T min_value,
				T max_value,
				std::true_type
				)
			{
				return sprout::random::detail::generate_uniform_real_true_1(
					eng(),
					min_value,
					max_value
					);
			}
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine> generate_uniform_real(
				Engine const& eng,
				T min_value,
				T max_value
				)
			{
				return sprout::random::detail::generate_uniform_real(
					eng,
					min_value,
					max_value,
					std::is_integral<typename Engine::result_type>()
					);
			}
		}	// namespace detail
		//
		// uniform_real_distribution
		//
		template<typename RealType = double>
		class uniform_real_distribution {
		public:
			typedef RealType input_type;
			typedef RealType result_type;
		private:
			static SPROUT_CONSTEXPR bool arg_check_nothrow(RealType min_arg, RealType max_arg) {
				return min_arg <= max_arg;
			}
			static SPROUT_CONSTEXPR RealType arg_check(RealType min_arg, RealType max_arg) {
				return arg_check_nothrow(min_arg, max_arg)
					? min_arg
					: throw "assert(min_arg <= max_arg)"
					;
			}
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef uniform_real_distribution distribution_type;
			private:
				static SPROUT_CONSTEXPR bool arg_check_nothrow(RealType min_arg, RealType max_arg) {
					return distribution_type::arg_check_nothrow(min_arg, max_arg);
				}
			private:
				RealType min_;
				RealType max_;
			public:
				SPROUT_CONSTEXPR param_type()
					: min_(RealType(0.0))
					, max_(RealType(1.0))
				{}
				SPROUT_CONSTEXPR explicit param_type(RealType min_arg, RealType max_arg = RealType(1.0))
					: min_(arg_check(min_arg, max_arg))
					, max_(max_arg)
				{}
				SPROUT_CONSTEXPR RealType a() const {
					return min_;
				}
				SPROUT_CONSTEXPR RealType b() const {
					return max_;
				}
				template<typename Elem, typename Traits>
				friend std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					RealType min;
					RealType max;
					if (lhs >> min >> std::ws >> max) {
						if (arg_check_nothrow(min, max)) {
							rhs.min_ = min;
							rhs.max_ = max;
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
					return lhs << rhs.min_ << " " << rhs.max_;
				}
				SPROUT_CONSTEXPR friend bool operator==(param_type const& lhs, param_type const& rhs) {
					return lhs.min_ == rhs.min_ && lhs.max_ == rhs.max_;
				}
				SPROUT_CONSTEXPR friend bool operator!=(param_type const& lhs, param_type const& rhs) {
					return !(lhs == rhs);
				}
			};
		private:
			result_type min_;
			result_type max_;
		private:
			template<typename Engine, typename Result>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_real_distribution> generate(Result const& rnd) const {
				return sprout::random::random_result<Engine, uniform_real_distribution>(
					rnd.result,
					rnd.engine,
					*this
					);
			}
		public:
			SPROUT_CONSTEXPR uniform_real_distribution()
				: min_(RealType(0.0))
				, max_(RealType(1.0))
			{}
			SPROUT_CONSTEXPR explicit uniform_real_distribution(RealType min_arg, RealType max_arg = RealType(1.0))
				: min_(arg_check(min_arg, max_arg))
				, max_(max_arg)
			{}
			SPROUT_CONSTEXPR explicit uniform_real_distribution(param_type const& parm)
				: min_(parm.a())
				, max_(parm.b())
			{}
			SPROUT_CONSTEXPR result_type a() const {
				return min_;
			}
			SPROUT_CONSTEXPR result_type b() const {
				return max_;
			}
			SPROUT_CONSTEXPR result_type min() const {
				return min_;
			}
			SPROUT_CONSTEXPR result_type max() const {
				return max_;
			}
			SPROUT_CONSTEXPR param_type param() const {
				return param_type(min_, max_);
			}
			void param(param_type const& parm) {
				min_ = parm.a();
				max_ = parm.b();
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_real_distribution> operator()(Engine const& eng) const {
				return generate<Engine>(sprout::random::detail::generate_uniform_real(eng, min_, max_));
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				uniform_real_distribution& rhs
				)
			{
				param_type parm;
				lhs >> parm;
				rhs.param(parm);
				return lhs;
			}
			template<typename Elem, typename Traits>
			friend std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				uniform_real_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			SPROUT_CONSTEXPR friend bool operator==(uniform_real_distribution const& lhs, uniform_real_distribution const& rhs) {
				return lhs.param() == rhs.param();
			}
			SPROUT_CONSTEXPR friend bool operator!=(uniform_real_distribution const& lhs, uniform_real_distribution const& rhs) {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::uniform_real_distribution;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

