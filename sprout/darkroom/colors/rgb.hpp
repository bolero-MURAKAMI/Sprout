#ifndef SPROUT_DARKROOM_COLORS_RGB_HPP
#define SPROUT_DARKROOM_COLORS_RGB_HPP

#include <cstdint>
#include <limits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/darkroom/access/access.hpp>

namespace sprout {
	namespace darkroom {
		namespace colors {
			//
			// r
			// g
			// b
			// a
			//
			template<typename T>
			SPROUT_CONSTEXPR auto r(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			SPROUT_CONSTEXPR auto g(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}
			template<typename T>
			SPROUT_CONSTEXPR auto b(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<2>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<2>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<2>(sprout::forward<T>(t));
			}
			template<typename T>
			SPROUT_CONSTEXPR auto a(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<3>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<3>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<3>(sprout::forward<T>(t));
			}

			//
			// rgb
			// rgb_f
			//
			typedef sprout::tuples::tuple<std::uint8_t, std::uint8_t, std::uint8_t> rgb;
			typedef sprout::tuples::tuple<double, double, double> rgb_f;

			//
			// mul
			//
			template<typename Color, typename Fac>
			SPROUT_CONSTEXPR inline Color mul(Color const& lhs, Fac const& rhs) {
				return sprout::tuples::remake_clone<Color>(
					lhs,
					sprout::darkroom::colors::r(lhs) * rhs,
					sprout::darkroom::colors::g(lhs) * rhs,
					sprout::darkroom::colors::b(lhs) * rhs
					);
			}
			//
			// add
			//
			template<typename Color1, typename Color2>
			SPROUT_CONSTEXPR inline Color1 add(Color1 const& lhs, Color2 const& rhs) {
				return sprout::tuples::remake_clone<Color1>(
					lhs,
					sprout::darkroom::colors::r(lhs) + sprout::darkroom::colors::r(rhs),
					sprout::darkroom::colors::g(lhs) + sprout::darkroom::colors::g(rhs),
					sprout::darkroom::colors::b(lhs) + sprout::darkroom::colors::b(rhs)
					);
			}
			//
			// filter
			//
			template<typename Color1, typename Color2>
			SPROUT_CONSTEXPR inline Color1 filter(Color1 const& lhs, Color2 const& rhs) {
				return sprout::tuples::remake_clone<Color1>(
					lhs,
					sprout::darkroom::colors::r(lhs) * sprout::darkroom::colors::r(rhs),
					sprout::darkroom::colors::g(lhs) * sprout::darkroom::colors::g(rhs),
					sprout::darkroom::colors::b(lhs) * sprout::darkroom::colors::b(rhs)
					);
			}

			//
			// rgb_f_to_rgb
			//
			template<typename RGB, typename RGB_F>
			SPROUT_CONSTEXPR inline RGB rgb_f_to_rgb(RGB_F const& col) {
				typedef typename sprout::darkroom::access::unit<RGB>::type unit_type;
				return sprout::tuples::make_clone<RGB>(
					sprout::darkroom::colors::r(col) < 0 ? std::numeric_limits<unit_type>::min()
						: sprout::darkroom::colors::r(col) > 1 ? std::numeric_limits<unit_type>::max()
						: sprout::darkroom::colors::r(col) * std::numeric_limits<unit_type>::max()
						,
					sprout::darkroom::colors::g(col) < 0 ? std::numeric_limits<unit_type>::min()
						: sprout::darkroom::colors::g(col) > 1 ? std::numeric_limits<unit_type>::max()
						: sprout::darkroom::colors::g(col) * std::numeric_limits<unit_type>::max()
						,
					sprout::darkroom::colors::b(col) < 0 ? std::numeric_limits<unit_type>::min()
						: sprout::darkroom::colors::b(col) > 1 ? std::numeric_limits<unit_type>::max()
						: sprout::darkroom::colors::b(col) * std::numeric_limits<unit_type>::max()
					);
			}
		}	// namespace colors
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_COLORS_RGB_HPP
