#ifndef SPROUT_RANDOM_UNIFORM_SMALLINT_HPP
#define SPROUT_RANDOM_UNIFORM_SMALLINT_HPP

#include <iosfwd>
#include <istream>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/uniform_01.hpp>

namespace sprout {
	namespace random {
		//
		// uniform_smallint
		//
		template<typename IntType = int>
		class uniform_smallint {
		public:
			typedef IntType input_type;
			typedef IntType result_type;
		private:
			static SPROUT_CONSTEXPR bool arg_check_nothrow(IntType min_arg, IntType max_arg) {
				return min_arg <= max_arg;
			}
			static SPROUT_CONSTEXPR IntType arg_check(IntType min_arg, IntType max_arg) {
				return arg_check_nothrow(min_arg, max_arg)
					? min_arg
					: throw std::invalid_argument("uniform_smallint<>: invalid argument (min_arg <= max_arg)")
					;
			}
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef uniform_smallint distribution_type;
			private:
				static SPROUT_CONSTEXPR bool arg_check_nothrow(IntType min_arg, IntType max_arg) {
					return distribution_type::arg_check_nothrow(min_arg, max_arg);
				}
			private:
				IntType min_;
				IntType max_;
			public:
				SPROUT_CONSTEXPR param_type()
					: min_(0)
					, max_(9)
				{}
				explicit SPROUT_CONSTEXPR param_type(IntType min_arg, IntType max_arg = 9)
					: min_(arg_check(min_arg, max_arg))
					, max_(max_arg)
				{}
				SPROUT_CONSTEXPR IntType a() const {
					return min_;
				}
				SPROUT_CONSTEXPR IntType b() const {
					return max_;
				}
				template<typename Elem, typename Traits>
				friend std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					IntType min;
					IntType max;
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
				friend SPROUT_CONSTEXPR bool operator==(param_type const& lhs, param_type const& rhs) {
					return lhs.min_ == rhs.min_ && lhs.max_ == rhs.max_;
				}
				friend SPROUT_CONSTEXPR bool operator!=(param_type const& lhs, param_type const& rhs) {
					return !(lhs == rhs);
				}
			};
		private:
			IntType min_;
			IntType max_;
		private:
			template<typename Engine, typename RangeType, typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_true_2(
				Engine const& eng,
				sprout::random::random_result<Engine> const& rnd,
				RangeType range,
				BaseUnsigned base_range,
				BaseUnsigned val
				) const
			{
				return range >= base_range
					? sprout::random::random_result<Engine, uniform_smallint>(
						sprout::random::detail::add<RangeType, result_type>()(static_cast<RangeType>(val), min_),
						rnd.engine(),
						*this
						)
					: sprout::random::random_result<Engine, uniform_smallint>(
						sprout::random::detail::add<RangeType, result_type>()(static_cast<RangeType>(val % (static_cast<BaseUnsigned>(range) + 1)), min_),
						rnd.engine(),
						*this
						)
					;
			}
			template<typename Engine, typename RangeType, typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_true_1(
				Engine const& eng,
				sprout::random::random_result<Engine> const& rnd,
				RangeType range,
				BaseUnsigned base_range
				) const
			{
				typedef typename Engine::result_type base_result;
				return generate_true_2(
					eng,
					rnd,
					range,
					base_range,
					BaseUnsigned(sprout::random::detail::subtract<base_result>()(rnd.result(), eng.min()))
					);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate(
				Engine const& eng,
				std::true_type
				) const
			{
				typedef typename Engine::result_type base_result;
				typedef typename std::make_unsigned<base_result>::type base_unsigned;
				typedef typename std::make_unsigned<result_type>::type range_type;
				return generate_true_1(
					eng,
					eng(),
					range_type(sprout::random::detail::subtract<result_type>()(max_, min_)),
					base_unsigned(sprout::random::detail::subtract<result_type>()(eng.max(), eng.min()))
					);
			}
			template<typename Engine, typename RangeType>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_false_2(
				Engine const& eng,
				sprout::random::random_result<Engine, sprout::random::uniform_01<typename Engine::result_type> > const& rnd,
				RangeType range,
				RangeType offset
				) const
			{
				return offset > range
					? sprout::random::random_result<Engine, uniform_smallint>(
						max_,
						rnd.engine(),
						*this
						)
					: sprout::random::random_result<Engine, uniform_smallint>(
						sprout::random::detail::add<RangeType, result_type>()(offset , min_),
						rnd.engine(),
						*this
						)
					;
			}
			template<typename Engine, typename RangeType>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_false_1(
				Engine const& eng,
				sprout::random::random_result<Engine, sprout::random::uniform_01<typename Engine::result_type> > const& rnd,
				RangeType range
				) const
			{
				typedef typename Engine::result_type base_result;
				return generate_false_2(
					eng,
					rnd,
					RangeType(sprout::random::detail::subtract<result_type>()(max_, min_)),
					RangeType(static_cast<RangeType>(rnd.result() * (static_cast<base_result>(range) + 1)))
					);
			}
			template<class Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate(
				Engine const& eng,
				std::false_type
				) const
			{
				typedef typename Engine::result_type base_result;
				typedef typename std::make_unsigned<result_type>::type range_type;
				return generate_false_1(
					eng,
					sprout::random::uniform_01<base_result>()(eng),
					range_type(sprout::random::detail::subtract<result_type>()(max_, min_))
					);
			}
		public:
			SPROUT_CONSTEXPR uniform_smallint()
				: min_(0)
				, max_(9)
			{}
			explicit SPROUT_CONSTEXPR uniform_smallint(IntType min_arg, IntType max_arg = 9)
				: min_(arg_check(min_arg, max_arg))
				, max_(max_arg)
			{}
			explicit SPROUT_CONSTEXPR uniform_smallint(param_type const& parm)
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
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> operator()(Engine const& eng) const {
				typedef typename Engine::result_type base_result;
				return generate(eng, typename std::is_integral<base_result>::type());
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				uniform_smallint& rhs
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
				uniform_smallint const& rhs
				)
			{
				return lhs << rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator==(uniform_smallint const& lhs, uniform_smallint const& rhs) {
				return lhs.param() == rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator!=(uniform_smallint const& lhs, uniform_smallint const& rhs) {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::uniform_smallint;
}	// namespace sprout

#endif // #ifndef SPROUT_RANDOM_UNIFORM_SMALLINT_HPP
