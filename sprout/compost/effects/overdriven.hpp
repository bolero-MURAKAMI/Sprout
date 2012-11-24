#ifndef SPROUT_COMPOST_EFFECTS_OVERDRIVEN_HPP
#define SPROUT_COMPOST_EFFECTS_OVERDRIVEN_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/atan.hpp>
#include <sprout/range/adaptor/transformed.hpp>
#include <sprout/compost/effects/changed_volume.hpp>

namespace sprout {
	namespace compost {
		//
		// overdrive_clip_value
		//
		template<typename T = void>
		struct overdrive_clip_value {
		public:
			typedef T argument_type;
			typedef T result_type;
		public:
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return x >= 0 ? sprout::math::atan(x) / sprout::math::half_pi<T>()
					: sprout::math::atan(x) / sprout::math::half_pi<T>() / 10
					;
			}
		};
		template<>
		struct overdrive_clip_value<void> {
		public:
			template<typename T>
			SPROUT_CONSTEXPR T
			operator()(T const& x) const {
				return sprout::compost::overdrive_clip_value<T>()(x);
			}
		};

		namespace effects {
			//
			// overdrive_holder
			//
			template<typename T>
			class overdrive_holder {
			public:
				typedef T value_type;
			private:
				value_type gain_;
				value_type level_;
			public:
				overdrive_holder() = default;
				overdrive_holder(overdrive_holder const&) = default;
				SPROUT_CONSTEXPR overdrive_holder(value_type const& gain, value_type const& level)
					: gain_(gain) , level_(level)
				{}
				SPROUT_CONSTEXPR value_type const& gain() const {
					return gain_;
				}
				SPROUT_CONSTEXPR value_type const& level() const {
					return level_;
				}
			};

			//
			// overdriven_forwarder
			//
			class overdriven_forwarder {
			public:
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::overdrive_holder<T>
				operator()(T const& gain, T const& level) {
					return sprout::compost::effects::overdrive_holder<T>(gain, level);
				}
			};

			//
			// overdriven
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::overdriven_forwarder overdriven{};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::overdrive_holder<T> const& rhs)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::compost::effects::changed_volume(rhs.gain())
					| sprout::adaptors::transformed(sprout::compost::overdrive_clip_value<>())
					| sprout::compost::effects::changed_volume(rhs.level())
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::compost::effects::changed_volume(rhs.gain())
					| sprout::adaptors::transformed(sprout::compost::overdrive_clip_value<>())
					| sprout::compost::effects::changed_volume(rhs.level())
					;
			}
		}	// namespace effects

		using sprout::compost::effects::overdriven;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_OVERDRIVEN_HPP
