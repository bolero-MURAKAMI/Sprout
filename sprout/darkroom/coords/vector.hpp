#ifndef SPROUT_DARKROOM_COORDS_VECTOR_HPP
#define SPROUT_DARKROOM_COORDS_VECTOR_HPP

#include <cmath>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/darkroom/access/access.hpp>

namespace sprout {
	namespace darkroom {
		namespace coords {
			//
			// x
			// y
			// z
			//
			template<typename T>
			SPROUT_CONSTEXPR auto x(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<0>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<0>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<0>(sprout::forward<T>(t));
			}
			template<typename T>
			SPROUT_CONSTEXPR auto y(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<1>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<1>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<1>(sprout::forward<T>(t));
			}
			template<typename T>
			SPROUT_CONSTEXPR auto z(
				T&& t
				) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::darkroom::access::get<2>(sprout::forward<T>(t))))
				-> decltype(sprout::darkroom::access::get<2>(sprout::forward<T>(t)))
			{
				return sprout::darkroom::access::get<2>(sprout::forward<T>(t));
			}

			//
			// vector3d
			//
			typedef sprout::tuples::tuple<double, double, double> vector3d;

			//
			// length_sq
			//
			template<typename Vector>
			SPROUT_CONSTEXPR inline typename sprout::darkroom::access::unit<Vector>::type
			length_sq(Vector const& vec) {
				return sprout::darkroom::coords::x(vec) * sprout::darkroom::coords::x(vec)
					+ sprout::darkroom::coords::y(vec) * sprout::darkroom::coords::y(vec)
					+ sprout::darkroom::coords::z(vec) * sprout::darkroom::coords::z(vec)
					;
			}
			//
			// length
			//
			template<typename Vector>
			SPROUT_CONSTEXPR inline typename sprout::darkroom::access::unit<Vector>::type
			length(Vector const& vec) {
				using std::sqrt;
				return sqrt(sprout::darkroom::coords::length_sq(vec));
			}
			//
			// add
			//
			template<typename Vector1, typename Vector2>
			SPROUT_CONSTEXPR inline Vector1 add(Vector1 const& lhs, Vector2 const& rhs) {
				return sprout::tuples::remake<Vector1>(
					lhs,
					sprout::darkroom::coords::x(lhs) + sprout::darkroom::coords::x(rhs),
					sprout::darkroom::coords::y(lhs) + sprout::darkroom::coords::y(rhs),
					sprout::darkroom::coords::z(lhs) + sprout::darkroom::coords::z(rhs)
					);
			}
			//
			// sub
			//
			template<typename Vector1, typename Vector2>
			SPROUT_CONSTEXPR inline Vector1 sub(Vector1 const& lhs, Vector2 const& rhs) {
				return sprout::tuples::remake<Vector1>(
					lhs,
					sprout::darkroom::coords::x(lhs) - sprout::darkroom::coords::x(rhs),
					sprout::darkroom::coords::y(lhs) - sprout::darkroom::coords::y(rhs),
					sprout::darkroom::coords::z(lhs) - sprout::darkroom::coords::z(rhs)
					);
			}
			//
			// scale
			//
			template<typename Vector, typename Fac>
			SPROUT_CONSTEXPR inline Vector scale(Vector const& lhs, Fac const& rhs) {
				return sprout::tuples::remake<Vector>(
					lhs,
					sprout::darkroom::coords::x(lhs) * rhs,
					sprout::darkroom::coords::y(lhs) * rhs,
					sprout::darkroom::coords::z(lhs) * rhs
					);
			}
			//
			// dot
			//
			template<typename Vector>
			SPROUT_CONSTEXPR inline typename sprout::darkroom::access::unit<Vector>::type
			dot(Vector const& lhs, Vector const& rhs) {
				return sprout::darkroom::coords::x(lhs) * sprout::darkroom::coords::x(rhs)
					+ sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::y(rhs)
					+ sprout::darkroom::coords::z(lhs) * sprout::darkroom::coords::z(rhs)
					;
			}
			//
			// cross
			//
			template<typename Vector1, typename Vector2>
			SPROUT_CONSTEXPR inline Vector1 cross(Vector1 const& lhs, Vector2 const& rhs) {
				return sprout::tuples::remake<Vector1>(
					lhs,
					sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::z(rhs)
						- sprout::darkroom::coords::z(lhs) * sprout::darkroom::coords::y(rhs)
						,
					sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::x(rhs)
						- sprout::darkroom::coords::x(lhs) * sprout::darkroom::coords::y(rhs)
						,
					sprout::darkroom::coords::x(lhs) * sprout::darkroom::coords::y(rhs)
						- sprout::darkroom::coords::y(lhs) * sprout::darkroom::coords::x(rhs)
					);
			}
			//
			// normalize
			//
			namespace detail {
				template<typename Vector>
				SPROUT_CONSTEXPR inline Vector normalize_impl(
					Vector const& vec,
					typename sprout::darkroom::access::unit<Vector>::type const& len
					)
				{
					return sprout::tuples::remake<Vector>(
						vec,
						sprout::darkroom::coords::x(vec) / len,
						sprout::darkroom::coords::y(vec) / len,
						sprout::darkroom::coords::z(vec) / len
						);
				}
			}	// namespace detail
			template<typename Vector>
			SPROUT_CONSTEXPR inline Vector normalize(Vector const& vec) {
				return sprout::darkroom::coords::detail::normalize_impl(
					vec,
					sprout::darkroom::coords::length(vec)
					);
			}
			//
			// resize
			//
			template<typename Vector, typename Fac>
			SPROUT_CONSTEXPR inline Vector resize(Vector const& lhs, Fac const& rhs) {
				return sprout::darkroom::coords::detail::normalize_impl(
					lhs,
					sprout::darkroom::coords::length(lhs) / rhs
					);
			}
			//
			// reflect
			//
			template<typename Incident, typename Normal>
			SPROUT_CONSTEXPR inline Incident reflect(Incident const& incid, Normal const& nor) {
				return sprout::darkroom::coords::sub(
					incid,
					sprout::darkroom::coords::scale(nor, sprout::darkroom::coords::dot(incid, nor) * 2)
					);
			}

			//
			// normal_to_color
			//
			template<typename Color, typename Normal>
			SPROUT_CONSTEXPR Color normal_to_color(Normal const& nor) {
				return sprout::tuples::make<Color>(
					0.5 + sprout::darkroom::coords::x(nor) * 0.5,
					0.5 + sprout::darkroom::coords::y(nor) * 0.5,
					0.5 + sprout::darkroom::coords::z(nor) * 0.5
					);
			}
		}	// namespace coords
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_COORDS_VECTOR_HPP
