/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_LGAMMA_HPP
#define SPROUT_MATH_LGAMMA_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/math/itrunc.hpp>
#include <sprout/math/is_integer.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			inline SPROUT_CONSTEXPR float
			builtin_lgamma(float x) {
				return __builtin_lgammaf(x);
			}
			inline SPROUT_CONSTEXPR double
			builtin_lgamma(double x) {
				return __builtin_lgamma(x);
			}
			inline SPROUT_CONSTEXPR long double
			builtin_lgamma(long double x) {
				return __builtin_lgammal(x);
			}
#endif

			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_3(T x, T y) {
				return x < 0 ? sprout::math::log(sprout::math::pi<T>() / sprout::math::fabs(x * sprout::math::sin(x * sprout::math::pi<T>()))) - y
					: y
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_d_1(T x, T w, T v, T t) {
				return sprout::math::detail::lgamma_impl_3(
					x,
					(((((-0.00163312359200500807 * t + 8.3644533703385956e-4) * t + -5.9518947575728181e-4) * t
						+ 7.9365057505415415e-4) * t + -0.00277777777735463043) * t + 0.08333333333333309869) * v + 0.91893853320467274178
						+ ((w - T(0.5)) * sprout::math::log(w) - w)
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_d(T x, T w, T v) {
				return sprout::math::detail::lgamma_impl_2_d_1(x, w, v, v * v);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_c_1(T x, T t, int k) {
				return sprout::math::detail::lgamma_impl_3(
					x,
					k == 0 ? (((((((((((
							1.16333640008e-8 * t + -8.33156123568e-8) * t
							+ 3.832869977018e-7) * t + -1.5814047847688e-6) * t + 6.50106723241e-6) * t
							+ -2.74514060128677e-5) * t + 1.209015360925566e-4) * t + -5.666333178228163e-4) * t
							+ 0.0029294103665559733) * t + -0.0180340086069185819) * t + 0.1651788780501166204) * t
							+ 1.1031566406452431944) * t + 1.2009736023470742248
						: k == 1 ? (((((((((((
							1.3842760642e-9 * t + -6.9417501176e-9) * t
							+ 3.42976459827e-8) * t + -1.785317236779e-7) * t + 9.525947257118e-7) * t
							+ -5.2483007560905e-6) * t + 3.02364659535708e-5) * t + -1.858396115473822e-4) * t
							+ 0.0012634378559425382) * t + -0.0102594702201954322) * t + 0.1243625515195050218) * t
							+ 1.3888709263595291174) * t + 2.4537365708424422209
						: k == 2 ? (((((((((((
							1.298977078e-10 * t + -8.02957489e-10) * t
							+ 4.945484615e-9) * t + -3.17563534834e-8) * t + 2.092136698089e-7) * t
							+ -1.4252023958462e-6) * t + 1.01652510114008e-5) * t + -7.74550502862323e-5) * t
							+ 6.537746948291078e-4) * t + -0.006601491253552183) * t + 0.0996711934948138193) * t
							+ 1.6110931485817511402) * t + 3.9578139676187162939
						: k == 3 ? (((((((((((
							1.83995642e-11 * t + -1.353537034e-10) * t
							+ 9.984676809e-10) * t + -7.6346363974e-9) * t + 5.99311464148e-8) * t
							+ -4.868554120177e-7) * t + 4.1441957716669e-6) * t + -3.77160856623282e-5) * t
							+ 3.805693126824884e-4) * t + -0.0045979851178130194) * t + 0.0831422678749791178) * t
							+ 1.7929113303999329439) * t + 5.6625620598571415285
						: (((((((((((
							3.4858778e-12 * t + -2.97587783e-11) * t
							+ 2.557677575e-10) * t + -2.2705728282e-9) * t + 2.0702499245e-8) * t
							+ -1.954426390917e-7) * t + 1.9343161886722e-6) * t + -2.0479024910257e-5) * t
							+ 2.405181940241215e-4) * t + -0.0033842087561074799) * t + 0.0713079483483518997) * t
							+ 1.9467574842460867884) * t + 7.5343642367587329552
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_c(T x, T w, int k) {
				return sprout::math::detail::lgamma_impl_2_c_1(x, w - (static_cast<T>(k) + 3.5), k);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_b_2(T x, T t, int k) {
				return sprout::math::detail::lgamma_impl_3(
					x,
					k == 0 ? ((((((((((((
							-4.587497028e-11 * t + 1.902363396e-10) * t
							+ 8.6377323367e-10) * t + 1.15513678861e-8) * t + -2.556403058605e-8) * t
							+ -1.5236723372486e-7) * t + -3.1680510638574e-6) * t + 1.22903704923381e-6) * t
							+ 2.334372474572637e-5) * t + 0.00111544038088797696) * t + 0.00344717051723468982) * t
							+ 0.03198287045148788384) * t + -0.32705333652955399526) * t + 0.40120442440953927615
						: k == 1 ? ((((((((((((
							-5.184290387e-11 * t + -8.3355121068e-10) * t
							+ -2.56167239813e-9) * t + 1.455875381397e-8) * t + 1.3512178394703e-7) * t
							+ 2.9898826810905e-7) * t + -3.58107254612779e-6) * t + -2.445260816156224e-5) * t
							+ -4.417127762011821e-5) * t + 0.00112859455189416567) * t + 0.00804694454346728197) * t
							+ 0.04919775747126691372) * t + -0.24818372840948854178) * t + 0.11071780856646862561
						: k == 2 ? ((((((((((((
							3.0279161576e-10 * t + 1.60742167357e-9) * t
							+ -4.05596009522e-9) * t + -5.089259920266e-8) * t + -2.029496209743e-8) * t
							+ 1.35130272477793e-6) * t + 3.91430041115376e-6) * t + -2.871505678061895e-5) * t
							+ -2.3052137536922035e-4) * t + 4.5534656385400747e-4) * t + 0.01153444585593040046) * t
							+ 0.07924014651650476036) * t + -0.12152192626936502982) * t + -0.07916438300260539592
						: k == 3 ? ((((((((((((
							-5.091914958e-10 * t + -1.15274986907e-9) * t
							+ 1.237873512188e-8) * t + 2.937383549209e-8) * t + -3.0621450667958e-7) * t
							+ -7.7409414949954e-7) * t + 8.16753874325579e-6) * t + 2.412433382517375e-5) * t
							+ -2.60612176060637e-4) * t + -9.1000087658659231e-4) * t + 0.01068093850598380797) * t
							+ 0.11395654404408482305) * t + 0.07209569059984075595) * t + -0.10971041451764266684
						: k == 4 ? ((((((((((((
							4.0119897187e-10 * t + -1.3224526679e-10) * t
							+ -1.002723190355e-8) * t + 2.569249716518e-8) * t + 2.0336011868466e-7) * t
							+ -1.1809768272606e-6) * t + -3.00660303810663e-6) * t + 4.402212897757763e-5) * t
							+ -1.462405876235375e-5) * t + -0.0016487379559600128) * t + 0.00513927520866443706) * t
							+ 0.13843580753590579416) * t + 0.32730190978254056722) * t + 0.08588339725978624973
						: k == 5 ? ((((((((((((
							-1.5413428348e-10 * t + 6.4905779353e-10) * t
							+ 1.60702811151e-9) * t + -2.655645793815e-8) * t + 7.619544277956e-8) * t
							+ 4.7604380765353e-7) * t + -4.90748870866195e-6) * t + 8.21513040821212e-6) * t
							+ 1.4804944070262948e-4) * t + -0.00122152255762163238) * t + -8.7425289205498532e-4) * t
							+ 0.1443870369965796831) * t + 0.61315889733595543766) * t + 0.55513708159976477557
						: ((((((((((((
							1.049740243e-11 * t + -2.5832017855e-10) * t
							+ 1.39591845075e-9) * t + -2.1177278325e-10) * t + -5.082950464905e-8) * t
							+ 3.7801785193343e-7) * t + -7.3982266659145e-7) * t + -1.088918441519888e-5) * t
							+ 1.2491810452478905e-4) * t + -4.9171790705139895e-4) * t + -0.0042570708944826646) * t
							+ 0.13595080378472757216) * t + 0.89518356003149514744) * t + 1.31073912535196238583
					);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_b_1(T x, T t, int k) {
				return sprout::math::detail::lgamma_impl_2_b_2(x, t - (static_cast<T>(k) - T(3.5)), k);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_b(T x, T t) {
				return sprout::math::detail::lgamma_impl_2_b_1(x, t, sprout::math::itrunc(t) + 4);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_2_a(T x, T w, int k) {
				return sprout::math::detail::lgamma_impl_3(
					x,
					-sprout::math::log(
						k == 0 ? ((((((((((
								9.967270908702825e-5 * w + -1.9831672170162227e-4) * w
								+ -0.00117085315349625822) * w + 0.00722012810948319552) * w + -0.0096221300936780297) * w
								+ -0.04219772092994235254) * w + 0.16653861065243609743) * w + -0.04200263501129018037) * w
								+ -0.65587807152061930091) * w + 0.57721566490153514421) * w + 0.99999999999999999764) * w
							: ((((((((((
								4.67209725901142e-5 * w + -6.812300803992063e-5) * w
								+ -0.00132531159076610073) * w + 0.0073352117810720277) * w + -0.00968095666383935949) * w
								+ -0.0421764281187354028) * w + 0.16653313644244428256) * w + -0.04200165481709274859) * w
								+ -0.65587818792782740945) * w + 0.57721567315209190522) * w + 0.99999999973565236061) * w
						)
					);
			}

			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl_1(T x, T w) {
				return w < T(0.5) ? sprout::math::detail::lgamma_impl_2_a(x, w, w < T(0.25) ? 0 : 1)
					: w < T(3.5) ? sprout::math::detail::lgamma_impl_2_b(x, w - T(4.5) / (w + T(0.5)))
					: w < T(8) ? sprout::math::detail::lgamma_impl_2_c(x, w, sprout::math::itrunc(w) - 3)
					: sprout::math::detail::lgamma_impl_2_d(x, w, T(1) / w)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			lgamma_impl(T x) {
				return sprout::math::detail::lgamma_impl_1(x, x < 0 ? -x : x);
			}
		}	// namespace detail
		//
		// lgamma
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		lgamma(FloatType x) {
			return sprout::math::isnan(x) ? x
				: x <= 0 && sprout::math::is_integer(x) ? sprout::numeric_limits<FloatType>::infinity()
				: x == -sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
				: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
//#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
//				: sprout::math::detail::builtin_lgamma(x)
//#else
				: x == 1 ? FloatType(0)
				: x == 2 ? FloatType(0)
				: static_cast<FloatType>(sprout::math::detail::lgamma_impl(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x)))
//#endif
				;
		}

		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR double
		lgamma(IntType x) {
			return sprout::math::lgamma(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::lgamma;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LGAMMA_HPP
