#ifndef SPROUT_MATH_LCM_HPP
#define SPROUT_MATH_LCM_HPP

#include <climits>
#include <limits>
#include <sprout/config.hpp>
#include <sprout/math/gcd.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename RingType>
			inline SPROUT_CONSTEXPR RingType
			lcm_euclidean_impl(RingType a, RingType b, RingType temp) {
				return temp != static_cast<RingType>(0) ? (a / temp * b)
					: static_cast<RingType>(0)
					;
			}
			template<typename RingType>
			inline SPROUT_CONSTEXPR RingType
			lcm_euclidean(RingType a, RingType b) {
				return sprout::math::detail::lcm_euclidean_impl(
					a, b, sprout::math::detail::gcd_euclidean(a, b)
					);
			}

			template<typename IntType>
			inline SPROUT_CONSTEXPR IntType
			lcm_integer_impl(IntType result) {
				return result < static_cast<IntType>(0) ? -result : result;
			}
			template<typename IntType>
			inline SPROUT_CONSTEXPR IntType
			lcm_integer(IntType const& a, IntType const& b) {
				return sprout::math::detail::lcm_integer_impl(
					sprout::math::detail::lcm_euclidean(a, b)
					);
			}

			template<typename T, bool IsSpecialized, bool IsSigned>
			struct lcm_optimal_evaluator_helper_t {
			public:
				SPROUT_CONSTEXPR T operator()(T const& a, T const& b) const {
					return sprout::math::detail::lcm_euclidean(a, b);
				}
			};
			template<typename T>
			struct lcm_optimal_evaluator_helper_t<T, true, true> {
			public:
				SPROUT_CONSTEXPR T operator()(T const& a, T const& b) const {
					return sprout::math::detail::lcm_integer(a, b);
				}
			};

			template<typename T>
			struct lcm_optimal_evaluator {
			public:
				SPROUT_CONSTEXPR T operator()(T const& a, T const& b) const {
					typedef std::numeric_limits<T> limits_type;
					typedef sprout::math::detail::lcm_optimal_evaluator_helper_t<
						T, limits_type::is_specialized, limits_type::is_signed
					> helper_type;
					return helper_type().operator()(a, b);
				}
			};

			template<typename T>
			inline SPROUT_CONSTEXPR T
			lcm_optimal(T const& a, T const& b) {
				return sprout::math::detail::lcm_optimal_evaluator<T>().operator()(a, b);
			}
		}  // namespace detail

		//
		// lcm_evaluator
		//
		template<typename IntType>
		class lcm_evaluator {
		public:
			typedef IntType result_type;
			typedef IntType first_argument_type;
			typedef IntType second_argument_type;
		public:
			SPROUT_CONSTEXPR result_type
			operator()(first_argument_type const& a, second_argument_type const& b) const {
				return sprout::math::detail::lcm_optimal(a, b);
			}
		};

		//
		// lcm
		//
		template<typename IntType>
		inline SPROUT_CONSTEXPR IntType
		lcm(IntType const& a, IntType const& b) {
			return sprout::math::lcm_evaluator<IntType>().operator()(a, b);
		}
	}  // namespace math
}  // namespace boost

#endif  // SPROUT_MATH_LCM_HPP
