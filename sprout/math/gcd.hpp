/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_GCD_HPP
#define SPROUT_MATH_GCD_HPP

#include <climits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/array/array.hpp>
#include <sprout/cstdlib/abs.hpp>
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
#	include <sprout/workaround/recursive_function_template.hpp>
#endif

namespace sprout {
	namespace math {
		namespace detail {
			template<typename RingType>
			inline SPROUT_CONSTEXPR RingType
			gcd_euclidean(RingType a, RingType b) {
				return a == static_cast<RingType>(0) ? b
					: b % a == static_cast<RingType>(0) ? a
					: sprout::math::detail::gcd_euclidean(a % (b % a), b % a)
					;
			}

			template<typename IntType>
			inline SPROUT_CONSTEXPR IntType
			gcd_integer_impl(IntType result) {
				return result < static_cast<IntType>(0) ? -result : result;
			}
			template<typename IntType>
			inline SPROUT_CONSTEXPR IntType
			gcd_integer(IntType const& a, IntType const& b) {
				return sprout::math::detail::gcd_integer_impl(
					sprout::math::detail::gcd_euclidean(a, b)
					);
			}
#ifdef SPROUT_WORKAROUND_NOT_TERMINATE_RECURSIVE_CONSTEXPR_FUNCTION_TEMPLATE
			template<int D = 16, typename BuiltInUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_1(unsigned shifts, sprout::array<BuiltInUnsigned, 2> const& r, unsigned which);
			template<int D = 16, typename BuiltInUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_1(unsigned shifts, sprout::array<BuiltInUnsigned, 2> const& r, unsigned which);
			template<int D, typename BuiltInUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(D)>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_2(unsigned shifts, sprout::array<BuiltInUnsigned, 2> const& r, unsigned which) {
				return r[which] ? sprout::math::detail::gcd_binary_2_1<D + 1>(shifts, r, which)
					: r[!which] << shifts
					;
			}
			template<int D, typename BuiltInUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(D)>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_2(unsigned, sprout::array<BuiltInUnsigned, 2> const&, unsigned) {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
			template<int D, typename BuiltInUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(D)>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_1(unsigned shifts, sprout::array<BuiltInUnsigned, 2> const& r, unsigned which) {
				return !(r[which] & 1u) ? sprout::math::detail::gcd_binary_2_1<D + 2>(
						shifts,
						which ? sprout::array<BuiltInUnsigned, 2>{{r[0], BuiltInUnsigned(r[1] >> 1)}}
							: sprout::array<BuiltInUnsigned, 2>{{BuiltInUnsigned(r[0] >> 1), r[1]}}
							,
						which
						)
					: r[!which] > r[which] ? sprout::math::detail::gcd_binary_2_2<D + 1>(
						shifts,
						which ^ 1u ? sprout::array<BuiltInUnsigned, 2>{{r[0], BuiltInUnsigned(r[1] - r[0])}}
							: sprout::array<BuiltInUnsigned, 2>{{BuiltInUnsigned(r[0] - r[1]), r[1]}}
							,
						which ^ 1u
						)
					: sprout::math::detail::gcd_binary_2_2<D + 1>(
						shifts,
						which ? sprout::array<BuiltInUnsigned, 2>{{r[0], BuiltInUnsigned(r[1] - r[0])}}
							: sprout::array<BuiltInUnsigned, 2>{{BuiltInUnsigned(r[0] - r[1]), r[1]}}
							,
						which
						)
					;
			}
			template<int D, typename BuiltInUnsigned, SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(D)>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_1(unsigned, sprout::array<BuiltInUnsigned, 2> const&, unsigned) {
				return sprout::throw_recursive_function_template_instantiation_exeeded();
			}
#else
			template<typename BuiltInUnsigned>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_1(unsigned shifts, sprout::array<BuiltInUnsigned, 2> const& r, unsigned which);
			template<typename BuiltInUnsigned>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_2(unsigned shifts, sprout::array<BuiltInUnsigned, 2> const& r, unsigned which) {
				return r[which] ? sprout::math::detail::gcd_binary_2_1(shifts, r, which)
					: r[!which] << shifts
					;
			}
			template<typename BuiltInUnsigned>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_2_1(unsigned shifts, sprout::array<BuiltInUnsigned, 2> const& r, unsigned which) {
				return !(r[which] & 1u) ? sprout::math::detail::gcd_binary_2_1(
						shifts,
						which ? sprout::array<BuiltInUnsigned, 2>{{r[0], BuiltInUnsigned(r[1] >> 1)}}
							: sprout::array<BuiltInUnsigned, 2>{{BuiltInUnsigned(r[0] >> 1), r[1]}}
							,
						which
						)
					: r[!which] > r[which] ? sprout::math::detail::gcd_binary_2_2(
						shifts,
						which ^ 1u ? sprout::array<BuiltInUnsigned, 2>{{r[0], BuiltInUnsigned(r[1] - r[0])}}
							: sprout::array<BuiltInUnsigned, 2>{{BuiltInUnsigned(r[0] - r[1]), r[1]}}
							,
						which ^ 1u
						)
					: sprout::math::detail::gcd_binary_2_2(
						shifts,
						which ? sprout::array<BuiltInUnsigned, 2>{{r[0], BuiltInUnsigned(r[1] - r[0])}}
							: sprout::array<BuiltInUnsigned, 2>{{BuiltInUnsigned(r[0] - r[1]), r[1]}}
							,
						which
						)
					;
			}
#endif
			template<typename BuiltInUnsigned>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary_1(BuiltInUnsigned u, BuiltInUnsigned v, unsigned shifts = 0) {
				return (!(u & 1u) && !(v & 1u)) ? sprout::math::detail::gcd_binary_1(u >> 1, v >> 1, shifts + 1)
					: sprout::math::detail::gcd_binary_2_1(
						shifts, sprout::array<BuiltInUnsigned, 2>{{u, v}}, static_cast<bool>(u & 1u)
						)
					;
			}
			template<typename BuiltInUnsigned>
			inline SPROUT_CONSTEXPR BuiltInUnsigned
			gcd_binary(BuiltInUnsigned u, BuiltInUnsigned v) {
				return u && v ? sprout::math::detail::gcd_binary_1(u, v)
					: u + v
					;
			}

			template<typename T, bool IsSpecialized, bool IsSigned>
			struct gcd_optimal_evaluator_helper_t {
			public:
				SPROUT_CONSTEXPR T operator()(T const& a, T const& b) const {
					return sprout::math::detail::gcd_euclidean(a, b);
				}
			};
			template<typename T>
			struct gcd_optimal_evaluator_helper_t<T, true, true> {
			public:
				SPROUT_CONSTEXPR T operator()(T const& a, T const& b) const {
					return sprout::math::detail::gcd_integer(a, b);
				}
			};

			template<typename T>
			struct gcd_optimal_evaluator {
			public:
				SPROUT_CONSTEXPR T operator()(T const& a, T const& b) const {
					typedef sprout::numeric_limits<T> limits_type;
					typedef sprout::math::detail::gcd_optimal_evaluator_helper_t<
						T, limits_type::is_specialized, limits_type::is_signed
					> helper_type;
					return helper_type().operator()(a, b);
				}
			};

#		define SPROUT_PRIVATE_GCD_UF(Ut) \
			template<> \
			struct gcd_optimal_evaluator<Ut> { \
			public: \
				SPROUT_CONSTEXPR Ut operator()(Ut a, Ut b) const { \
					return sprout::math::detail::gcd_binary(a, b); \
				} \
			}
			SPROUT_PRIVATE_GCD_UF(unsigned char);
			SPROUT_PRIVATE_GCD_UF(unsigned short);
			SPROUT_PRIVATE_GCD_UF(unsigned);
			SPROUT_PRIVATE_GCD_UF(unsigned long);
			SPROUT_PRIVATE_GCD_UF(unsigned long long);
#		if CHAR_MIN == 0
			SPROUT_PRIVATE_GCD_UF(char);
#		endif
		#undef SPROUT_PRIVATE_GCD_UF

#		define SPROUT_PRIVATE_GCD_SF(St, Ut) \
			template<> \
			struct gcd_optimal_evaluator<St> { \
			public: \
				SPROUT_CONSTEXPR St operator()(St a, St b) const { \
					using sprout::abs; \
					return static_cast<St>(sprout::math::detail::gcd_optimal_evaluator<Ut>().operator()( \
						static_cast<Ut>(abs(a)), static_cast<Ut>(abs(b)) \
						)); \
				} \
			}
			SPROUT_PRIVATE_GCD_SF(signed char, unsigned char);
			SPROUT_PRIVATE_GCD_SF(short, unsigned short);
			SPROUT_PRIVATE_GCD_SF(int, unsigned);
			SPROUT_PRIVATE_GCD_SF(long, unsigned long);
#		if CHAR_MIN < 0
			SPROUT_PRIVATE_GCD_SF(char, unsigned char);
#		endif
			SPROUT_PRIVATE_GCD_SF(long long, unsigned long long);
		#undef SPROUT_PRIVATE_GCD_SF

			template<typename T>
			inline SPROUT_CONSTEXPR T
			gcd_optimal(T const& a, T const& b) {
				return sprout::math::detail::gcd_optimal_evaluator<T>().operator()(a, b);
			}
		}	// namespace detail

		//
		// gcd_evaluator
		//
		template<typename IntType = void>
		class gcd_evaluator {
		public:
			typedef IntType result_type;
			typedef IntType first_argument_type;
			typedef IntType second_argument_type;
		public:
			SPROUT_CONSTEXPR IntType
			operator()(IntType const& a, IntType const& b) const {
				return sprout::math::detail::gcd_optimal(a, b);
			}
		};
		template<>
		class gcd_evaluator<void> {
		public:
			template<typename IntType>
			SPROUT_CONSTEXPR IntType
			operator()(IntType const& a, IntType const& b) const {
				return sprout::math::detail::gcd_optimal(a, b);
			}
		};

		//
		// gcd
		//
		template<typename IntType>
		inline SPROUT_CONSTEXPR IntType
		gcd(IntType const& a, IntType const& b) {
			return sprout::math::gcd_evaluator<IntType>().operator()(a, b);
		}
	}	// namespace math

	using sprout::math::gcd;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_GCD_HPP
