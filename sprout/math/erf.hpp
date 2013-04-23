#ifndef SPROUT_MATH_ERF_HPP
#define SPROUT_MATH_ERF_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/itrunc.hpp>
#include <sprout/math/fractional_part.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl_3(T x, T y) {
				return x < 0 ? -y
					: y
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl_2_b(T x, T w, T t, int k) {
				return sprout::math::detail::erf_impl_3(
					x,
					T(1) - sprout::detail::pow_n(
						k == 0 ? (((((((((((
								-2.9734388465e-10 * t + 2.69776334046e-9) * t
								+ -6.40788827665e-9) * t + -1.6678201321e-8) * t + -2.1854388148686e-7) * t
								+ 2.66246030457984e-6) * t + 1.612722157047886e-5) * t + -2.5616361025506629e-4) * t
								+ 1.5380842432375365e-4) * t + 0.00815533022524927908) * t + -0.01402283663896319337) * t
								+ -0.19746892495383021487) * t + 0.71511720328842845913
							: k == 1 ? (((((((((((
								-1.951073787e-11 * t + -3.2302692214e-10) * t
								+ 5.22461866919e-9) * t + 3.42940918551e-9) * t + -3.5772874310272e-7) * t
								+ 1.9999935792654e-7) * t + 2.687044575042908e-5) * t + -1.1843240273775776e-4) * t
								+ -8.0991728956032271e-4) * t + 0.00661062970502241174) * t + 0.00909530922354827295) * t
								+ -0.2016007277849101314) * t + 0.51169696718727644908
							: k == 2 ? (((((((((((
								3.147682272e-11 * t + -4.8465972408e-10) * t
								+ 6.3675740242e-10) * t + 3.377623323271e-8) * t + -1.5451139637086e-7) * t
								+ -2.03340624738438e-6) * t + 1.947204525295057e-5) * t + 2.854147231653228e-5) * t
								+ -0.00101565063152200272) * t + 0.00271187003520095655) * t + 0.02328095035422810727) * t
								+ -0.16725021123116877197) * t + 0.32490054966649436974
							: k == 3 ? (((((((((((
								2.31936337e-11 * t + -6.303206648e-11) * t
								+ -2.64888267434e-9) * t + 2.050708040581e-8) * t + 1.1371857327578e-7) * t
								+ -2.11211337219663e-6) * t + 3.68797328322935e-6) * t + 9.823686253424796e-5) * t
								+ -6.5860243990455368e-4) * t + -7.5285814895230877e-4) * t + 0.02585434424202960464) * t
								+ -0.11637092784486193258) * t + 0.18267336775296612024
							: (((((((((((
								-3.67789363e-12 * t + 2.0876046746e-10) * t
								+ -1.93319027226e-9) * t + -4.35953392472e-9) * t + 1.8006992266137e-7) * t
								+ -7.8441223763969e-7) * t + -6.75407647949153e-6) * t + 8.428418334440096e-5) * t
								+ -1.7604388937031815e-4) * t + -0.0023972961143507161) * t + 0.0206412902387602297) * t
								+ -0.06905562880005864105) * t + 0.09084526782065478489
						,
						16
						)
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl_2_a_1(T x, T w, T t, int k) {
				return sprout::math::detail::erf_impl_3(
					x,
					k == 0 ? ((((((((((((
							5.958930743e-11 * t + -1.13739022964e-9) * t
							+ 1.466005199839e-8) * t + -1.635035446196e-7) * t + 1.6461004480962e-6) * t
							+ -1.492559551950604e-5) * t + 1.2055331122299265e-4) * t + -8.548326981129666e-4) * t
							+ 0.00522397762482322257) * t + -0.0268661706450773342) * t + 0.11283791670954881569) * t
							+ -0.37612638903183748117) * t + 1.12837916709551257377) * w
						: k == 1 ? ((((((((((((
							2.372510631e-11 * t + -4.5493253732e-10) * t
							+ 5.90362766598e-9) * t + -6.642090827576e-8) * t + 6.7595634268133e-7) * t
							+ -6.21188515924e-6) * t + 5.10388300970969e-5) * t + -3.7015410692956173e-4) * t
							+ 0.00233307631218880978) * t + -0.0125498847718219221) * t + 0.05657061146827041994) * t
							+ -0.2137966477645600658) * t + 0.84270079294971486929) * w
						: k == 2 ? ((((((((((((
							9.49905026e-12 * t + -1.8310229805e-10) * t
							+ 2.39463074e-9) * t + -2.721444369609e-8) * t + 2.8045522331686e-7) * t
							+ -2.61830022482897e-6) * t + 2.195455056768781e-5) * t + -1.6358986921372656e-4) * t
							+ 0.00107052153564110318) * t + -0.00608284718113590151) * t + 0.02986978465246258244) * t
							+ -0.13055593046562267625) * t + 0.67493323603965504676) * w
						: k == 3 ? ((((((((((((
							3.82722073e-12 * t + -7.421598602e-11) * t
							+ 9.793057408e-10) * t + -1.126008898854e-8) * t + 1.1775134830784e-7) * t
							+ -1.1199275838265e-6) * t + 9.62023443095201e-6) * t + -7.404402135070773e-5) * t
							+ 5.0689993654144881e-4) * t + -0.00307553051439272889) * t + 0.01668977892553165586) * t
							+ -0.08548534594781312114) * t + 0.56909076642393639985) * w
						: ((((((((((((
							1.55296588e-12 * t + -3.032205868e-11) * t
							+ 4.0424830707e-10) * t + -4.71135111493e-9) * t + 5.011915876293e-8) * t
							+ -4.8722516178974e-7) * t + 4.30683284629395e-6) * t + -3.445026145385764e-5) * t
							+ 2.4879276133931664e-4) * t + -0.00162940941748079288) * t + 0.00988786373932350462) * t
							+ -0.05962426839442303805) * t + 0.49766113250947636708) * w
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl_2_a(T x, T w, T t) {
				return sprout::math::detail::erf_impl_2_a_1(x, w, sprout::fractional_part(t), sprout::itrunc(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl_1(T x, T w) {
				return w < T(2.2) ? sprout::math::detail::erf_impl_2_a(x, w, w * w)
					: w < T(6.9) ? sprout::math::detail::erf_impl_2_b(x, w, sprout::fractional_part(w), sprout::itrunc(w) - 2)
					: sprout::math::detail::erf_impl_3(x, T(1))
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			erf_impl(T x) {
				return sprout::math::detail::erf_impl_1(x, x < 0 ? -x : x);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			erf(FloatType x) {
				typedef typename sprout::math::detail::float_compute<FloatType>::type type;
				return x == 0 ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() ? FloatType(1)
					: x == -std::numeric_limits<FloatType>::infinity() ? FloatType(-1)
					: static_cast<FloatType>(sprout::math::detail::erf_impl(static_cast<type>(x)))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			erf(IntType x) {
				return sprout::math::detail::erf(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::erf;
	}	// namespace math

	using sprout::math::erf;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ERF_HPP
