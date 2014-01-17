/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_UNIFORM_SMALLINT_HPP
#define SPROUT_RANDOM_UNIFORM_SMALLINT_HPP

#include <iosfwd>
#include <istream>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/random/uniform_01.hpp>
#include <sprout/random/results.hpp>
#include <sprout/assert.hpp>

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
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef uniform_smallint distribution_type;
			private:
				IntType min_;
				IntType max_;
			public:
				SPROUT_CONSTEXPR param_type()
					: min_(0)
					, max_(sprout::numeric_limits<IntType>::max())
				{}
				explicit SPROUT_CONSTEXPR param_type(IntType min_arg, IntType max_arg = sprout::numeric_limits<IntType>::max())
					: min_((SPROUT_ASSERT(min_arg <= max_arg), min_arg))
					, max_(max_arg)
				{}
				SPROUT_CONSTEXPR IntType a() const SPROUT_NOEXCEPT {
					return min_;
				}
				SPROUT_CONSTEXPR IntType b() const SPROUT_NOEXCEPT {
					return max_;
				}
				template<typename Elem, typename Traits>
				friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					IntType min;
					IntType max;
					if (lhs >> min >> std::ws >> max) {
						if (min <= max) {
							rhs.min_ = min;
							rhs.max_ = max;
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
					return lhs << rhs.min_ << " " << rhs.max_;
				}
				friend SPROUT_CONSTEXPR bool operator==(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return lhs.min_ == rhs.min_ && lhs.max_ == rhs.max_;
				}
				friend SPROUT_CONSTEXPR bool operator!=(param_type const& lhs, param_type const& rhs) SPROUT_NOEXCEPT {
					return !(lhs == rhs);
				}
			};
		private:
			IntType min_;
			IntType max_;
		private:
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type generate(
				Engine& eng,
				std::true_type
				) const
			{
				typedef typename Engine::result_type base_result;
				typedef typename std::make_unsigned<base_result>::type base_unsigned;
				typedef typename std::make_unsigned<result_type>::type range_type;
				range_type range = sprout::random::detail::subtract<result_type>()(max_, min_);
				base_unsigned base_range = sprout::random::detail::subtract<result_type>()(eng.max(), eng.min());
				base_unsigned val = sprout::random::detail::subtract<base_result>()(static_cast<base_result>(eng()), eng.min());
				return range >= base_range
					? sprout::random::detail::add<range_type, result_type>()(static_cast<range_type>(val), min_)
					: sprout::random::detail::add<range_type, result_type>()(static_cast<range_type>(val % (static_cast<base_result>(range) + 1)), min_)
					;
			}
			template<class Engine>
			SPROUT_CXX14_CONSTEXPR result_type generate(
				Engine& eng,
				std::false_type
				) const
			{
				typedef typename Engine::result_type base_result;
				typedef typename std::make_unsigned<result_type>::type range_type;
				range_type range = sprout::random::detail::subtract<result_type>()(max_, min_);
				base_result val = sprout::random::uniform_01<base_result>()(eng);
				range_type offset = static_cast<range_type>(val * (static_cast<base_result>(range) + 1));
				return offset > range
					? max_
					: sprout::random::detail::add<range_type, result_type>()(offset, min_)
					;
			}
			template<typename Engine, typename EngineResult, typename RangeType, typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_true_2(
				Engine const&,
				EngineResult const& rnd,
				RangeType range,
				BaseUnsigned base_range,
				BaseUnsigned val
				) const
			{
				return range >= base_range
					? sprout::random::random_result<Engine, uniform_smallint>(
						sprout::random::detail::add<RangeType, result_type>()(static_cast<RangeType>(val), min_),
						sprout::random::next(rnd),
						*this
						)
					: sprout::random::random_result<Engine, uniform_smallint>(
						sprout::random::detail::add<RangeType, result_type>()(static_cast<RangeType>(val % (static_cast<BaseUnsigned>(range) + 1)), min_),
						sprout::random::next(rnd),
						*this
						)
					;
			}
			template<typename Engine, typename EngineResult, typename RangeType, typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_true_1(
				Engine const& eng,
				EngineResult const& rnd,
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
					BaseUnsigned(sprout::random::detail::subtract<base_result>()(sprout::random::result(rnd), eng.min()))
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
			template<typename Engine, typename Random, typename RangeType>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_false_2(
				Engine const&,
				Random const& rnd,
				RangeType range,
				RangeType offset
				) const
			{
				return offset > range
					? sprout::random::random_result<Engine, uniform_smallint>(
						max_,
						sprout::random::next(rnd).engine(),
						*this
						)
					: sprout::random::random_result<Engine, uniform_smallint>(
						sprout::random::detail::add<RangeType, result_type>()(offset, min_),
						sprout::random::next(rnd).engine(),
						*this
						)
					;
			}
			template<typename Engine, typename Random, typename RangeType>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> generate_false_1(
				Engine const& eng,
				Random const& rnd,
				RangeType range
				) const
			{
				typedef typename Engine::result_type base_result;
				return generate_false_2(
					eng,
					rnd,
					static_cast<RangeType>(sprout::random::detail::subtract<result_type>()(max_, min_)),
					static_cast<RangeType>(sprout::random::result(rnd) * (static_cast<base_result>(range) + 1))
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
					static_cast<range_type>(sprout::random::detail::subtract<result_type>()(max_, min_))
					);
			}
		public:
			SPROUT_CONSTEXPR uniform_smallint() SPROUT_NOEXCEPT
				: min_(0)
				, max_(sprout::numeric_limits<IntType>::max())
			{}
			explicit SPROUT_CONSTEXPR uniform_smallint(IntType min_arg, IntType max_arg = sprout::numeric_limits<IntType>::max())
				: min_((SPROUT_ASSERT(min_arg <= max_arg), min_arg))
				, max_(max_arg)
			{}
			explicit SPROUT_CONSTEXPR uniform_smallint(param_type const& parm) SPROUT_NOEXCEPT
				: min_(parm.a())
				, max_(parm.b())
			{}
			SPROUT_CONSTEXPR result_type a() const SPROUT_NOEXCEPT {
				return min_;
			}
			SPROUT_CONSTEXPR result_type b() const SPROUT_NOEXCEPT {
				return max_;
			}
			SPROUT_CONSTEXPR result_type min() const SPROUT_NOEXCEPT {
				return min_;
			}
			SPROUT_CONSTEXPR result_type max() const SPROUT_NOEXCEPT {
				return max_;
			}
			SPROUT_CXX14_CONSTEXPR void reset() SPROUT_NOEXCEPT {}
			SPROUT_CONSTEXPR param_type param() const SPROUT_NOEXCEPT {
				return param_type(min_, max_);
			}
			SPROUT_CXX14_CONSTEXPR void param(param_type const& parm) {
				min_ = parm.a();
				max_ = parm.b();
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng) const {
				typedef typename Engine::result_type base_result;
				return generate(eng, typename std::is_integral<base_result>::type());
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> const operator()(Engine const& eng) const {
				typedef typename Engine::result_type base_result;
				return generate(eng, typename std::is_integral<base_result>::type());
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng, param_type const& parm) const {
				return uniform_smallint(parm)(eng);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_smallint> const operator()(Engine const& eng, param_type const& parm) const {
				return uniform_smallint(parm)(eng);
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
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
			friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(
				std::basic_ostream<Elem, Traits>& lhs,
				uniform_smallint const& rhs
				)
			{
				return lhs << rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator==(uniform_smallint const& lhs, uniform_smallint const& rhs) SPROUT_NOEXCEPT {
				return lhs.param() == rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator!=(uniform_smallint const& lhs, uniform_smallint const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::uniform_smallint;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_UNIFORM_SMALLINT_HPP
