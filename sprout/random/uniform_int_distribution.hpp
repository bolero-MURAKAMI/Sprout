#ifndef SPROUT_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
#define SPROUT_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP

#include <limits>
#include <ios>
#include <istream>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/random/detail/signed_unsigned_tools.hpp>
#include <sprout/random/detail/uniform_int_float.hpp>
#include <sprout/random/random_result.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename T, typename Engine>
			struct generate_uniform_int_result {
			public:
				T result;
				Engine engine;
			};

#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
			template<int D = 16, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(Engine const& eng, T min_value, T max_value, std::true_type);
			template<int D = 16, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(Engine const& eng, T min_value, T max_value, std::true_type);
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, BaseUnsigned bucket_size
				);
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, BaseUnsigned bucket_size
				);
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1_1(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, BaseUnsigned bucket_size, BaseUnsigned result
				)
			{
				typedef T result_type;
				return result <= static_cast<BaseUnsigned>(range)
					? sprout::random::detail::generate_uniform_int_result<T, Engine>{
						sprout::random::detail::add<BaseUnsigned, result_type>()(result, min_value),
						eng
						}
					: sprout::random::detail::generate_uniform_int_true_3_1<D + 1>(
						eng(), min_value, range,
						bmin, brange, bucket_size
						)
					;
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1_1(
				Engine const&, T, RangeType,
				BaseResult, BaseUnsigned, BaseUnsigned, BaseUnsigned
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, BaseUnsigned bucket_size
				)
			{
				return sprout::random::detail::generate_uniform_int_true_3_1_1<D + 1>(
					rnd.engine(), min_value, range,
					bmin, brange, bucket_size,
					sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin) / bucket_size
					);
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1(
				sprout::random::random_result<Engine> const&, T, RangeType,
				BaseResult, BaseUnsigned, BaseUnsigned
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				)
			{
				return sprout::random::detail::generate_uniform_int_true_3_1<D + 1>(
					eng(), min_value, range,
					bmin, brange,
					brange == std::numeric_limits<BaseUnsigned>::max()
						? brange / (static_cast<BaseUnsigned>(range) + 1) + (
							brange % (static_cast<BaseUnsigned>(range) + 1) == static_cast<BaseUnsigned>(range) ? 1 : 0
							)
						: (brange + 1) / (static_cast<BaseUnsigned>(range) + 1)
					);
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3(
				Engine const&, T, RangeType,
				BaseResult, BaseUnsigned
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				);
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				);
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_4(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType result, RangeType result_increment
				)
			{
				typedef T result_type;
				return result < result_increment || result > range
					? sprout::random::detail::generate_uniform_int_true_2<D + 1>(eng, min_value, range, bmin, brange)
					: sprout::random::detail::generate_uniform_int_result<T, Engine>{
						random::detail::add<RangeType, result_type>()(result, min_value),
						eng
						}
					;
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_4(
				Engine const&, T, RangeType,
				BaseResult, BaseUnsigned, RangeType, RangeType
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_3(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType result, RangeType mult, RangeType result_increment
				)
			{
				return std::numeric_limits<RangeType>::max() / mult < result_increment
					? sprout::random::detail::generate_uniform_int_true_2<D + 1>(eng, min_value, range, bmin, brange)
					: sprout::random::detail::generate_uniform_int_true_2_4<D + 1>(
						eng, min_value, range,
						bmin, brange, result + (result_increment * mult), result_increment * mult
						)
					;
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_3(
				Engine const&, T, RangeType,
				BaseResult, BaseUnsigned, RangeType, RangeType, RangeType
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, typename Result, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_2(
				Engine const&, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType result, RangeType mult, Result const& result_increment_base
				)
			{
				return sprout::random::detail::generate_uniform_int_true_2_3<D + 1>(
					result_increment_base.engine, min_value, range,
					bmin, brange, result, mult, result_increment_base.result
					);
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, typename Result, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_2(
				Engine const&, T, RangeType,
				BaseResult, BaseUnsigned, RangeType, RangeType, Result const&
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType limit,
				RangeType result = RangeType(0), RangeType mult = RangeType(1)
				);
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType limit,
				RangeType result = RangeType(0), RangeType mult = RangeType(1)
				);
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType limit, RangeType result, RangeType mult
				)
			{
				return mult * RangeType(brange) == range - mult + 1
					? sprout::random::detail::generate_uniform_int_result<T, Engine>{
						static_cast<T>(
							result + static_cast<RangeType>(sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin) * mult)
							),
						rnd.engine()
						}
					: sprout::random::detail::generate_uniform_int_true_2_1<D + 1>(
						rnd.engine(), min_value, range,
						bmin, brange, limit,
						result + static_cast<RangeType>(sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin) * mult),
						mult * (RangeType(brange) + RangeType(1))
						)
					;
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1_1(
				sprout::random::random_result<Engine> const&, T, RangeType,
				BaseResult, BaseUnsigned, RangeType, RangeType, RangeType
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType limit,
				RangeType result, RangeType mult
				)
			{
				return mult <= limit
					? sprout::random::detail::generate_uniform_int_true_2_1_1<D + 1>(
						eng(), min_value, range,
						bmin, brange, limit,
						result, mult
						)
					: sprout::random::detail::generate_uniform_int_true_2_2<D + 1>(
						eng, min_value, range,
						bmin, brange,
						result, mult,
						sprout::random::detail::generate_uniform_int<D + 1>(
							eng,
							static_cast<RangeType>(0),
							static_cast<RangeType>(range / mult),
							std::true_type()
							)
						)
					;
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1(
				Engine const&, T, RangeType,
				BaseResult, BaseUnsigned, RangeType,
				RangeType, RangeType
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				)
			{
				return sprout::random::detail::generate_uniform_int_true_2_1<D + 1>(
					eng, min_value, range,
					bmin, brange,
					range == std::numeric_limits<RangeType>::max()
						? range / (RangeType(brange) + 1) + (
							range % (RangeType(brange) + 1) == RangeType(brange) ? 1 : 0
							)
						: (range + 1) / (RangeType(brange) + 1)
					);
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2(
				Engine const&, T, RangeType,
				BaseResult, BaseUnsigned
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename BaseResult, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_1_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, BaseResult bmin
				)
			{
				typedef T result_type;
				typedef typename std::make_unsigned<BaseResult>::type base_unsigned;
				return sprout::random::detail::generate_uniform_int_result<T, Engine>{
					sprout::random::detail::add<base_unsigned, result_type>()(
						base_unsigned(sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin)),
						min_value
						),
					rnd.engine()
					};
			}
			template<int D, typename Engine, typename T, typename BaseResult, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_1_1(
				sprout::random::random_result<Engine> const&, T, BaseResult
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_1(
				Engine const& eng, T min_value, T, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				)
			{
				return range == 0 ? sprout::random::detail::generate_uniform_int_result<T, Engine>{min_value, eng}
					: brange == range ? sprout::random::detail::generate_uniform_int_true_1_1<D + 1>(eng(), min_value, bmin)
					: brange < range ? sprout::random::detail::generate_uniform_int_true_2<D + 1>(eng, min_value, range, bmin, brange)
					: sprout::random::detail::generate_uniform_int_true_3<D + 1>(eng, min_value, range, bmin, brange)
					;
			}
			template<int D, typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_1(
				Engine const&, T, T, RangeType,
				BaseResult, BaseUnsigned
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(
				Engine const& eng, T min_value, T max_value, std::true_type
				)
			{
				typedef T result_type;
				typedef typename std::make_unsigned<T>::type range_type;
				typedef typename Engine::result_type base_result;
				typedef typename std::make_unsigned<base_result>::type base_unsigned;
				return sprout::random::detail::generate_uniform_int_true_1<D + 1>(
					eng, min_value, max_value,
					range_type(sprout::random::detail::subtract<result_type>()(max_value, min_value)),
					base_result(eng.min()),
					base_unsigned(sprout::random::detail::subtract<base_result>()(eng.max(), eng.min()))
					);
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(
				Engine const&, T, T, std::true_type
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename Engine, typename T, typename Result, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_false_1(Result const& rnd) {
				return sprout::random::detail::generate_uniform_int_result<T, Engine>{
					rnd.result, rnd.engine.base()
					};
			}
			template<int D, typename Engine, typename T, typename Result, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_false_1(Result const& rnd) {
				return sprout::random::detail::generate_uniform_int_result<T, Engine>{
					rnd.result, rnd.engine.base()
					};
			}
			template<int D, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(
				Engine const& eng, T min_value, T max_value, std::false_type
				)
			{
				return sprout::random::detail::generate_uniform_int_false_1<D + 1, Engine, T>(
					sprout::random::detail::generate_uniform_int<D + 1>(
						sprout::random::detail::uniform_int_float<Engine>(eng),
						min_value, max_value,
						std::true_type()
						)
					);
			}
			template<int D = 16, typename Engine, typename T, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(
				Engine const&, T, T, std::false_type
				)
			{
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
#else
			template<typename Engine, typename T>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(Engine const& eng, T min_value, T max_value, std::true_type);
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, BaseUnsigned bucket_size
				);
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1_1(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, BaseUnsigned bucket_size, BaseUnsigned result
				)
			{
				typedef T result_type;
				return result <= static_cast<BaseUnsigned>(range)
					? sprout::random::detail::generate_uniform_int_result<T, Engine>{
						sprout::random::detail::add<BaseUnsigned, result_type>()(result, min_value),
						eng
						}
					: sprout::random::detail::generate_uniform_int_true_3_1(
						eng(), min_value, range,
						bmin, brange, bucket_size
						)
					;
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, BaseUnsigned bucket_size
				)
			{
				return sprout::random::detail::generate_uniform_int_true_3_1_1(
					rnd.engine(), min_value, range,
					bmin, brange, bucket_size,
					sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin) / bucket_size
					);
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_3(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				)
			{
				return sprout::random::detail::generate_uniform_int_true_3_1(
					eng(), min_value, range,
					bmin, brange,
					brange == std::numeric_limits<BaseUnsigned>::max()
						? brange / (static_cast<BaseUnsigned>(range) + 1) + (
							brange % (static_cast<BaseUnsigned>(range) + 1) == static_cast<BaseUnsigned>(range) ? 1 : 0
							)
						: (brange + 1) / (static_cast<BaseUnsigned>(range) + 1)
					);
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				);
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_4(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType result, RangeType result_increment
				)
			{
				typedef T result_type;
				return result < result_increment || result > range
					? sprout::random::detail::generate_uniform_int_true_2(eng, min_value, range, bmin, brange)
					: sprout::random::detail::generate_uniform_int_result<T, Engine>{
						random::detail::add<RangeType, result_type>()(result, min_value),
						eng
						}
					;
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_3(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType result, RangeType mult, RangeType result_increment
				)
			{
				return std::numeric_limits<RangeType>::max() / mult < result_increment
					? sprout::random::detail::generate_uniform_int_true_2(eng, min_value, range, bmin, brange)
					: sprout::random::detail::generate_uniform_int_true_2_4(
						eng, min_value, range,
						bmin, brange, result + (result_increment * mult), result_increment * mult
						)
					;
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned, typename Result>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_2(
				Engine const&, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType result, RangeType mult, Result const& result_increment_base
				)
			{
				return sprout::random::detail::generate_uniform_int_true_2_3(
					result_increment_base.engine, min_value, range,
					bmin, brange, result, mult, result_increment_base.result
					);
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType limit,
				RangeType result = RangeType(0), RangeType mult = RangeType(1)
				);
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType limit, RangeType result, RangeType mult
				)
			{
				return mult * RangeType(brange) == range - mult + 1
					? sprout::random::detail::generate_uniform_int_result<T, Engine>{
						static_cast<T>(
							result + static_cast<RangeType>(sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin) * mult)
							),
						rnd.engine()
						}
					: sprout::random::detail::generate_uniform_int_true_2_1(
						rnd.engine(), min_value, range,
						bmin, brange, limit,
						result + static_cast<RangeType>(sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin) * mult),
						mult * (RangeType(brange) + RangeType(1))
						)
					;
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2_1(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange, RangeType limit,
				RangeType result, RangeType mult
				)
			{
				return mult <= limit
					? sprout::random::detail::generate_uniform_int_true_2_1_1(
						eng(), min_value, range,
						bmin, brange, limit,
						result, mult
						)
					: sprout::random::detail::generate_uniform_int_true_2_2(
						eng, min_value, range,
						bmin, brange,
						result, mult,
						sprout::random::detail::generate_uniform_int(
							eng,
							static_cast<RangeType>(0),
							static_cast<RangeType>(range / mult),
							std::true_type()
							)
						)
					;
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_2(
				Engine const& eng, T min_value, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				)
			{
				return sprout::random::detail::generate_uniform_int_true_2_1(
					eng, min_value, range,
					bmin, brange,
					range == std::numeric_limits<RangeType>::max()
						? range / (RangeType(brange) + 1) + (
							range % (RangeType(brange) + 1) == RangeType(brange) ? 1 : 0
							)
						: (range + 1) / (RangeType(brange) + 1)
					);
			}
			template<typename Engine, typename T, typename BaseResult>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_1_1(
				sprout::random::random_result<Engine> const& rnd, T min_value, BaseResult bmin
				)
			{
				typedef T result_type;
				typedef typename std::make_unsigned<BaseResult>::type base_unsigned;
				return sprout::random::detail::generate_uniform_int_result<T, Engine>{
					sprout::random::detail::add<base_unsigned, result_type>()(
						base_unsigned(sprout::random::detail::subtract<BaseResult>()(rnd.result(), bmin)),
						min_value
						),
					rnd.engine()
					};
			}
			template<typename Engine, typename T, typename RangeType, typename BaseResult, typename BaseUnsigned>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_true_1(
				Engine const& eng, T min_value, T, RangeType range,
				BaseResult bmin, BaseUnsigned brange
				)
			{
				return range == 0 ? sprout::random::detail::generate_uniform_int_result<T, Engine>{min_value, eng}
					: brange == range ? sprout::random::detail::generate_uniform_int_true_1_1(eng(), min_value, bmin)
					: brange < range ? sprout::random::detail::generate_uniform_int_true_2(eng, min_value, range, bmin, brange)
					: sprout::random::detail::generate_uniform_int_true_3(eng, min_value, range, bmin, brange)
					;
			}
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(
				Engine const& eng, T min_value, T max_value, std::true_type
				)
			{
				typedef T result_type;
				typedef typename std::make_unsigned<T>::type range_type;
				typedef typename Engine::result_type base_result;
				typedef typename std::make_unsigned<base_result>::type base_unsigned;
				return sprout::random::detail::generate_uniform_int_true_1(
					eng, min_value, max_value,
					range_type(sprout::random::detail::subtract<result_type>()(max_value, min_value)),
					base_result(eng.min()),
					base_unsigned(sprout::random::detail::subtract<base_result>()(eng.max(), eng.min()))
					);
			}
			template<typename Engine, typename T, typename Result>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int_false_1(Result const& rnd) {
				return sprout::random::detail::generate_uniform_int_result<T, Engine>{
					rnd.result, rnd.engine.base()
					};
			}
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(
				Engine const& eng, T min_value, T max_value, std::false_type
				)
			{
				return sprout::random::detail::generate_uniform_int_false_1<Engine, T>(
					sprout::random::detail::generate_uniform_int(
						sprout::random::detail::uniform_int_float<Engine>(eng),
						min_value, max_value,
						std::true_type()
						)
					);
			}
#endif
			template<typename Engine, typename T>
			inline SPROUT_CONSTEXPR sprout::random::detail::generate_uniform_int_result<T, Engine>
			generate_uniform_int(
				Engine const& eng, T min_value, T max_value
				)
			{
				return sprout::random::detail::generate_uniform_int(
					eng, min_value, max_value,
					std::is_integral<typename Engine::result_type>()
					);
			}
		}	// namespace detail
		//
		// uniform_int_distribution
		//
		template<typename IntType = int>
		class uniform_int_distribution {
		public:
			typedef IntType input_type;
			typedef IntType result_type;
		public:
			//
			// param_type
			//
			class param_type {
			public:
				typedef uniform_int_distribution distribution_type;
			private:
				IntType min_;
				IntType max_;
			public:
				SPROUT_CONSTEXPR param_type()
					: min_(0)
					, max_(9)
				{}
				explicit SPROUT_CONSTEXPR param_type(IntType min_arg, IntType max_arg = 9)
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
				friend std::basic_istream<Elem, Traits>& operator>>(
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
				friend std::basic_ostream<Elem, Traits>& operator<<(
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
			template<typename Engine, typename Result>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_int_distribution> generate(Result const& rnd) const {
				return sprout::random::random_result<Engine, uniform_int_distribution>(
					rnd.result,
					rnd.engine,
					*this
					);
			}
		public:
			SPROUT_CONSTEXPR uniform_int_distribution()
				: min_(0)
				, max_(9)
			{}
			explicit SPROUT_CONSTEXPR uniform_int_distribution(IntType min_arg, IntType max_arg = 9)
				: min_((SPROUT_ASSERT(min_arg <= max_arg), min_arg))
				, max_(max_arg)
			{}
			explicit SPROUT_CONSTEXPR uniform_int_distribution(param_type const& parm)
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
			SPROUT_CONSTEXPR param_type param() const SPROUT_NOEXCEPT {
				return param_type(min_, max_);
			}
			void param(param_type const& parm) {
				min_ = parm.a();
				max_ = parm.b();
			}
			template<typename Engine>
			SPROUT_CONSTEXPR sprout::random::random_result<Engine, uniform_int_distribution> operator()(Engine const& eng) const {
				return generate<Engine>(sprout::random::detail::generate_uniform_int(eng, min_, max_));
			}
			template<typename Elem, typename Traits>
			friend std::basic_istream<Elem, Traits>& operator>>(
				std::basic_istream<Elem, Traits>& lhs,
				uniform_int_distribution& rhs
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
				uniform_int_distribution const& rhs
				)
			{
				return lhs << rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator==(uniform_int_distribution const& lhs, uniform_int_distribution const& rhs) SPROUT_NOEXCEPT {
				return lhs.param() == rhs.param();
			}
			friend SPROUT_CONSTEXPR bool operator!=(uniform_int_distribution const& lhs, uniform_int_distribution const& rhs) SPROUT_NOEXCEPT {
				return !(lhs == rhs);
			}
		};
	}	// namespace random

	using sprout::random::uniform_int_distribution;
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
