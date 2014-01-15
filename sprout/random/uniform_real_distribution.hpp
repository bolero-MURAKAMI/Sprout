/*=============================================================================
	Copyright (c) 2011-2014 Bolero MURAKAMI
	https://github.com/bolero-MURAKAMI/Sprout

	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP
#define SPROUT_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

#include <ios>
#include <istream>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/generator/functions.hpp>
#include <sprout/assert.hpp>

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
			inline SPROUT_CXX14_CONSTEXPR T
			generate_uniform_real(
				Engine& eng, T min_value, T max_value,
				std::false_type
				)
			{
				for(;;) {
					typedef T result_type;
					typedef typename Engine::result_type base_result;
					result_type numerator = static_cast<T>(static_cast<base_result>(eng()) - eng.min());
					result_type divisor = static_cast<T>(eng.max() - eng.min());
					SPROUT_ASSERT(divisor > 0);
					SPROUT_ASSERT(numerator >= 0 && numerator <= divisor);
					result_type result = numerator / divisor * (max_value - min_value) + min_value;
					if (result < max_value) {
						return result;
					}
				}
			}
			template<typename Engine, typename T>
			inline SPROUT_CXX14_CONSTEXPR T
			generate_uniform_real(
				Engine& eng, T min_value, T max_value,
				std::true_type
				)
			{
				for(;;) {
					typedef T result_type;
					typedef typename Engine::result_type base_result;
					result_type numerator = static_cast<T>(sprout::random::detail::subtract<base_result>()(static_cast<base_result>(eng()), eng.min()));
					result_type divisor = static_cast<T>(sprout::random::detail::subtract<base_result>()(eng.max(), eng.min())) + 1;
					SPROUT_ASSERT(divisor > 0);
					SPROUT_ASSERT(numerator >= 0 && numerator <= divisor);
					result_type result = numerator / divisor * (max_value - min_value) + min_value;
					if (result < max_value) {
						return result;
					}
				}
			}
			template<typename Engine, typename T>
			inline SPROUT_CXX14_CONSTEXPR T
			generate_uniform_real(
				Engine& eng, T min_value, T max_value
				)
			{
				return sprout::random::detail::generate_uniform_real(
					eng, min_value, max_value,
					typename std::is_integral<typename Engine::result_type>::type()
					);
			}

#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
			template<int D = 16, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_false_1(
				EngineResult const& rnd,
				T min_value, T max_value
				);
			template<int D = 16, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_false_1(
				EngineResult const& rnd,
				T min_value, T max_value
				);
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_false_3(
				Engine const& eng,
				T min_value, T max_value,
				T result
				)
			{
				return result < max_value
					? sprout::random::detail::generate_uniform_real_result<T, Engine>{result, eng}
					: sprout::random::detail::generate_uniform_real_false_1<D + 1>(eng(), min_value, max_value)
					;
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_false_3(
				Engine const&,
				T, T,
				T
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_false_2(
				Engine const& eng,
				T min_value, T max_value,
				T numerator, T divisor
				)
			{
				return SPROUT_ASSERT(divisor > 0), SPROUT_ASSERT(numerator >= 0 && numerator <= divisor),
					sprout::random::detail::generate_uniform_real_false_3<D + 1>(
						eng,
						min_value, max_value,
						numerator / divisor * (max_value - min_value) + min_value
						)
					;
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_false_2(
				Engine const&,
				T, T,
				T, T
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_false_1(
				EngineResult const& rnd,
				T min_value, T max_value
				)
			{
				return sprout::random::detail::generate_uniform_real_false_2<D + 1>(
					sprout::generators::next_generator(rnd),
					min_value, max_value,
					static_cast<T>(sprout::generators::generated_value(rnd) - sprout::generators::next_generator(rnd).min()),
					static_cast<T>(sprout::generators::next_generator(rnd).max() - sprout::generators::next_generator(rnd).min())
					);
			}
			template<int D, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_false_1(
				EngineResult const&,
				T, T
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D = 16, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_true_1(
				EngineResult const& rnd,
				T min_value, T max_value
				);
			template<int D = 16, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_true_1(
				EngineResult const& rnd,
				T min_value, T max_value
				);
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_true_3(
				Engine const& eng,
				T min_value, T max_value,
				T result
				)
			{
				return result < max_value
					? sprout::random::detail::generate_uniform_real_result<T, Engine>{result, eng}
					: sprout::random::detail::generate_uniform_real_true_1<D + 1>(eng(), min_value, max_value)
					;
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_true_3(
				Engine const&,
				T, T,
				T
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_true_2(
				Engine const& eng,
				T min_value, T max_value,
				T numerator, T divisor
				)
			{
				return SPROUT_ASSERT(divisor > 0), SPROUT_ASSERT(numerator >= 0 && numerator <= divisor),
					sprout::random::detail::generate_uniform_real_true_3<D + 1>(
						eng,
						min_value, max_value,
						numerator / divisor * (max_value - min_value) + min_value
						)
					;
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_true_2(
				Engine const&,
				T, T,
				T, T
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_true_1(
				EngineResult const& rnd,
				T min_value, T max_value
				)
			{
				typedef typename EngineResult::result_type base_result;
				return sprout::random::detail::generate_uniform_real_true_2<D + 1>(
					sprout::generators::next_generator(rnd),
					min_value, max_value,
					static_cast<T>(sprout::random::detail::subtract<base_result>()(sprout::generators::generated_value(rnd), sprout::generators::next_generator(rnd).min())),
					static_cast<T>(sprout::random::detail::subtract<base_result>()(sprout::generators::next_generator(rnd).max(), sprout::generators::next_generator(rnd).min())) + 1
					);
			}
			template<int D, typename EngineResult, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_true_1(
				EngineResult const&,
				T, T
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
#else
			template<typename EngineResult, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_false_1(
				EngineResult const& rnd,
				T min_value, T max_value
				);
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_false_3(
				Engine const& eng,
				T min_value, T max_value,
				T result
				)
			{
				return result < max_value
					? sprout::random::detail::generate_uniform_real_result<T, Engine>{result, eng}
					: sprout::random::detail::generate_uniform_real_false_1(eng(), min_value, max_value)
					;
			}
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_false_2(
				Engine const& eng,
				T min_value, T max_value,
				T numerator, T divisor
				)
			{
				return SPROUT_ASSERT(divisor > 0), SPROUT_ASSERT(numerator >= 0 && numerator <= divisor),
					sprout::random::detail::generate_uniform_real_false_3(
						eng,
						min_value, max_value,
						numerator / divisor * (max_value - min_value) + min_value
						)
					;
			}
			template<typename EngineResult, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_false_1(
				EngineResult const& rnd,
				T min_value, T max_value
				)
			{
				return sprout::random::detail::generate_uniform_real_false_2(
					sprout::generators::next_generator(rnd),
					min_value, max_value,
					static_cast<T>(sprout::generators::generated_value(rnd) - sprout::generators::next_generator(rnd).min()),
					static_cast<T>(sprout::generators::next_generator(rnd).max() - sprout::generators::next_generator(rnd).min())
					);
			}
			template<typename EngineResult, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_true_1(
				EngineResult const& rnd,
				T min_value, T max_value
				);
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_true_3(
				Engine const& eng,
				T min_value, T max_value,
				T result
				)
			{
				return result < max_value
					? sprout::random::detail::generate_uniform_real_result<T, Engine>{result, eng}
					: sprout::random::detail::generate_uniform_real_true_1(eng(), min_value, max_value)
					;
			}
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real_true_2(
				Engine const& eng,
				T min_value, T max_value,
				T numerator, T divisor
				)
			{
				return SPROUT_ASSERT(divisor > 0), SPROUT_ASSERT(numerator >= 0 && numerator <= divisor),
					sprout::random::detail::generate_uniform_real_true_3(
						eng,
						min_value, max_value,
						numerator / divisor * (max_value - min_value) + min_value
						)
					;
			}
			template<typename EngineResult, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, typename EngineResult::engine_type>
			generate_uniform_real_true_1(
				EngineResult const& rnd,
				T min_value, T max_value
				)
			{
				typedef typename EngineResult::result_type base_result;
				return sprout::random::detail::generate_uniform_real_true_2(
					sprout::generators::next_generator(rnd),
					min_value, max_value,
					static_cast<T>(sprout::random::detail::subtract<base_result>()(sprout::generators::generated_value(rnd), sprout::generators::next_generator(rnd).min())),
					static_cast<T>(sprout::random::detail::subtract<base_result>()(sprout::generators::next_generator(rnd).max(), sprout::generators::next_generator(rnd).min())) + 1
					);
			}
#endif
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real(
				Engine const& eng,
				T min_value, T max_value,
				std::false_type
				)
			{
				return sprout::random::detail::generate_uniform_real_false_1(
					eng(),
					min_value, max_value
					);
			}
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real(
				Engine const& eng,
				T min_value, T max_value,
				std::true_type
				)
			{
				return sprout::random::detail::generate_uniform_real_true_1(
					eng(),
					min_value, max_value
					);
			}
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_real_result<T, Engine>
			generate_uniform_real(
				Engine const& eng,
				T min_value, T max_value
				)
			{
				return sprout::random::detail::generate_uniform_real(
					eng,
					min_value, max_value,
					typename std::is_integral<typename Engine::result_type>::type()
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
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef uniform_real_distribution distribution_type;
			private:
				RealType min_;
				RealType max_;
			public:
				SPROUT_CONSTEXPR param_type()
					: min_(RealType(0.0))
					, max_(RealType(1.0))
				{}
				explicit SPROUT_CONSTEXPR param_type(RealType min_arg, RealType max_arg = RealType(1.0))
					: min_((SPROUT_ASSERT(min_arg <= max_arg), min_arg))
					, max_(max_arg)
				{}
				SPROUT_CONSTEXPR RealType a() const SPROUT_NOEXCEPT {
					return min_;
				}
				SPROUT_CONSTEXPR RealType b() const SPROUT_NOEXCEPT {
					return max_;
				}
				template<typename Elem, typename Traits>
				friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
					std::basic_istream<Elem, Traits>& lhs,
					param_type& rhs
					)
				{
					RealType min;
					RealType max;
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
			RealType min_;
			RealType max_;
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
			SPROUT_CONSTEXPR uniform_real_distribution() SPROUT_NOEXCEPT
				: min_(RealType(0.0))
				, max_(RealType(1.0))
			{}
			explicit SPROUT_CONSTEXPR uniform_real_distribution(RealType min_arg, RealType max_arg = RealType(1.0))
				: min_((SPROUT_ASSERT(min_arg <= max_arg), min_arg))
				, max_(max_arg)
			{}
			explicit SPROUT_CONSTEXPR uniform_real_distribution(param_type const& parm) SPROUT_NOEXCEPT
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
				return sprout::random::detail::generate_uniform_real(eng, min_, max_);
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_real_distribution> const operator()(Engine const& eng) const {
				return generate<Engine>(sprout::random::detail::generate_uniform_real(eng, min_, max_));
			}
			template<typename Engine>
			SPROUT_CXX14_CONSTEXPR result_type operator()(Engine& eng, param_type const& parm) const {
				return sprout::random::detail::generate_uniform_real(eng, parm.a(), parm.b());
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_real_distribution> const operator()(Engine const& eng, param_type const& parm) const {
				return generate<Engine>(sprout::random::detail::generate_uniform_real(eng, parm.a(), parm.b()));
			}
			template<typename Elem, typename Traits>
			friend SPROUT_NON_CONSTEXPR std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				uniform_real_distribution& rhs
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
				uniform_real_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator==(uniform_real_distribution const& lhs, uniform_real_distribution const& rhs) SPROUT_NOEXCEPT {
				return lhs.param() == rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator!=(uniform_real_distribution const& lhs, uniform_real_distribution const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::uniform_real_distribution;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP
