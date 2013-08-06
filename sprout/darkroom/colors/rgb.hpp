#ifndef SPROUT_DARKROOM_COLORS_RGB_HPP
#define SPROUT_DARKROOM_COLORS_RGB_HPP

#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
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
			inline SPROUT_CONSTEXPR auto
			r(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			g(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			b(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<2>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<2>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<2>(sprout::forward<T>(t));
			}
			template<typename T>
			inline SPROUT_CONSTEXPR auto
			a(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<3>(sprout::forward<T>(t))))
			-> decltype(sprout::darkroom::access::get<3>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<3>(sprout::forward<T>(t));
			}

			//
			// rgb_t
			// rgb
			//
			typedef sprout::tuples::tuple<std::uint8_t, std::uint8_t, std::uint8_t> rgb_t;

			inline SPROUT_CONSTEXPR sprout::darkroom::colors::rgb_t
			rgb(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0) {
				return sprout::darkroom::colors::rgb_t(r, g, b);
			}

			//
			// rgb_f_t
			// rgb_f
			//
			typedef sprout::tuples::tuple<double, double, double> rgb_f_t;

			inline SPROUT_CONSTEXPR sprout::darkroom::colors::rgb_f_t
			rgb_f(double r = 0, double g = 0, double b = 0) {
				return sprout::darkroom::colors::rgb_f_t(r, g, b);
			}

			//
			// mul
			//
			template<typename Color, typename Fac>
			inline SPROUT_CONSTEXPR Color
			mul(Color const& lhs, Fac const& rhs) {
				return sprout::tuples::remake<Color>(
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
			inline SPROUT_CONSTEXPR Color1
			add(Color1 const& lhs, Color2 const& rhs) {
				return sprout::tuples::remake<Color1>(
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
			inline SPROUT_CONSTEXPR Color1
			filter(Color1 const& lhs, Color2 const& rhs) {
				return sprout::tuples::remake<Color1>(
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
			inline SPROUT_CONSTEXPR RGB
			rgb_f_to_rgb(RGB_F const& col) {
				typedef typename sprout::darkroom::access::unit<RGB>::type unit_type;
				return sprout::tuples::make<RGB>(
					sprout::darkroom::colors::r(col) < 0 ? sprout::numeric_limits<unit_type>::min()
						: sprout::darkroom::colors::r(col) > 1 ? sprout::numeric_limits<unit_type>::max()
						: sprout::darkroom::colors::r(col) * sprout::numeric_limits<unit_type>::max()
						,
					sprout::darkroom::colors::g(col) < 0 ? sprout::numeric_limits<unit_type>::min()
						: sprout::darkroom::colors::g(col) > 1 ? sprout::numeric_limits<unit_type>::max()
						: sprout::darkroom::colors::g(col) * sprout::numeric_limits<unit_type>::max()
						,
					sprout::darkroom::colors::b(col) < 0 ? sprout::numeric_limits<unit_type>::min()
						: sprout::darkroom::colors::b(col) > 1 ? sprout::numeric_limits<unit_type>::max()
						: sprout::darkroom::colors::b(col) * sprout::numeric_limits<unit_type>::max()
					);
			}
		}	// namespace colors
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_COLORS_RGB_HPP
