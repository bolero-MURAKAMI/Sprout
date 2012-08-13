#ifndef SPROUT_DARKROOM_MATERIALS_TEXTURE_MAP_HPP
#define SPROUT_DARKROOM_MATERIALS_TEXTURE_MAP_HPP

#include <cstddef>
#include <cstdint>
#include <sprout/config.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/utility/value_holder.hpp>
#include <sprout/darkroom/materials/interpolation.hpp>

namespace sprout {
	namespace darkroom {
		namespace materials {
			//
			// texture_map_interpolation
			//
			typedef sprout::darkroom::materials::interpolation_type texture_map_interpolation;
			//
			// texture_map_placement
			//
			struct texture_map_placement {
			public:
				enum values {
					tile,
					once
				};
			};
			//
			// texture_map
			//
			template<typename Texture, typename Scale = double>
			class texture_map {
			public:
				typedef Texture texture_type;
				typedef typename texture_type::value_type result_type;
				typedef Scale unit_type;
				typedef sprout::darkroom::materials::interpolation_type interpolation_type;
				typedef sprout::darkroom::materials::texture_map_placement texture_map_placement;
			private:
				sprout::value_holder<texture_type const&> texture_;
				unit_type scale_;
				unit_type offset_u_;
				unit_type offset_v_;
				result_type default_color_;
				interpolation_type::values interpolation_value_;
				texture_map_placement::values placement_value_;
			private:
				SPROUT_CONSTEXPR bool is_nearest() const {
					return interpolation_value_ == interpolation_type::nearest_neighbor;
				}
				SPROUT_CONSTEXPR bool is_bilinear() const {
					return interpolation_value_ == interpolation_type::bilinear;
				}
				SPROUT_CONSTEXPR bool is_bicubic() const {
					return interpolation_value_ == interpolation_type::bicubic;
				}
				SPROUT_CONSTEXPR bool is_tile() const {
					return placement_value_ == texture_map_placement::tile;
				}
				SPROUT_CONSTEXPR bool is_once() const {
					return placement_value_ == texture_map_placement::once;
				}
				SPROUT_CONSTEXPR result_type get_color(unit_type const& x, unit_type const& y) const {
					return is_tile()
						? texture_.get()(
							x < 0
								? texture_.get().width() - 1 - static_cast<std::size_t>(-x) % texture_.get().width()
								: static_cast<std::size_t>(x) % texture_.get().width()
								,
							y < 0
								? texture_.get().height() - 1 - static_cast<std::size_t>(-y) % texture_.get().height()
								: static_cast<std::size_t>(y) % texture_.get().height()
							)
						: x < 0 || x >= texture_.get().width()
							|| y < 0 || y >= texture_.get().height()
							? default_color_
							: texture_.get()(static_cast<std::size_t>(x), static_cast<std::size_t>(y))
						;
				}
				template<typename Unit>
				SPROUT_CONSTEXPR result_type calc_nearest(Unit const& x, Unit const& y) const {
					return get_color(x, y);
				}
				template<typename Unit>
				SPROUT_CONSTEXPR result_type calc_bilinear_1(
					Unit const& x, Unit const& x0,
					Unit const& y, Unit const& y0
					) const
				{
					return sprout::darkroom::materials::bilinear_interpolate(
						get_color(x0, y0), get_color(x0 + 1, y0),
						get_color(x0, y0 + 1), get_color(x0 + 1, y0 + 1),
						x - x0, y - y0
						);
				}
				template<typename Unit>
				SPROUT_CONSTEXPR result_type calc_bilinear(Unit const& x, Unit const& y) const {
					return calc_bilinear_1(
						x, sprout::floor(x),
						y, sprout::floor(y)
						);
				}
				template<typename Unit>
				SPROUT_CONSTEXPR result_type calc(Unit const& x, Unit const& y) const {
					return is_nearest() ? calc_nearest(x, y)
						: calc_bilinear(x, y)
						;
				}
			public:
				explicit SPROUT_CONSTEXPR texture_map(
					texture_type const& texture,
					unit_type const& scale = 1,
					unit_type const& offset_u = 0,
					unit_type const& offset_v = 0,
					result_type const& default_color = result_type(),
					interpolation_type::values interpolation_value = interpolation_type::nearest_neighbor,
					texture_map_placement::values placement_value = texture_map_placement::tile
					)
					: texture_(texture)
					, scale_(scale)
					, offset_u_(offset_u)
					, offset_v_(offset_v)
					, default_color_(default_color)
					, interpolation_value_(interpolation_value)
					, placement_value_(placement_value)
				{}
				template<typename Unit>
				SPROUT_CONSTEXPR result_type operator()(Unit const& u, Unit const& v) const {
					return calc(
						(u - offset_u_ + scale_ / 2) / scale_ * texture_.get().width(),
						(-(v - offset_v_) + scale_ / 2) / scale_ * texture_.get().height()
						);
				}
			};
			//
			// make_texture_map
			//
			template<typename Texture>
			inline SPROUT_CONSTEXPR sprout::darkroom::materials::texture_map<Texture>
			make_texture_map(Texture const& texture) {
				return sprout::darkroom::materials::texture_map<Texture>(texture);
			}
			template<typename Texture, typename Unit>
			inline SPROUT_CONSTEXPR sprout::darkroom::materials::texture_map<Texture, Unit>
			make_texture_map(
				Texture const& texture,
				Unit const& scale,
				Unit const& offset_u = 0,
				Unit const& offset_v = 0,
				typename sprout::darkroom::materials::texture_map<Texture, Unit>::result_type const& default_color
					= typename sprout::darkroom::materials::texture_map<Texture, Unit>::result_typ()
					,
				sprout::darkroom::materials::interpolation_type::values interpolation_value
					= sprout::darkroom::materials::interpolation_type::nearest_neighbor
					,
				sprout::darkroom::materials::texture_map_placement::values placement_value
					= sprout::darkroom::materials::texture_map_placement::tile
				)
			{
				return sprout::darkroom::materials::texture_map<Texture, Unit>(
					texture,
					scale,
					offset_u,
					offset_v,
					default_color,
					interpolation_value,
					placement_value
					);
			}
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_TEXTURE_MAP_HPP
