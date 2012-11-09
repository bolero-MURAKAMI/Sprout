#ifndef SPROUT_COMPOST_EFFECTS_VIBRATO_HPP
#define SPROUT_COMPOST_EFFECTS_VIBRATO_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/range/adaptor/transformed.hpp>
#include <sprout/range/adaptor/outdirected.hpp>
#include <sprout/range/adaptor/indexed.hpp>
#include <sprout/range/adaptor/valued.hpp>

namespace sprout {
	namespace compost {
		//
		// vibrato_outdirected_value
		//
		template<typename Value, typename IntType>
		struct vibrato_outdirected_value {
		public:
			typedef Value value_type;
			typedef IntType int_type;
		private:
			value_type d_;
			value_type depth_;
			value_type rate_;
			int_type samples_per_sec_;
		private:
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			calc_2(Outdirected const& x, typename Outdirected::index_type m, value_type const& delta) const {
				return m >= 0 && (m + 1 < x.base().get() || x.base().get() < 0)
					? delta * x[m + 1 - x.index()] + (1 - delta) * x[m - x.index()]
					: *x
					;
			}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			calc_1(Outdirected const& x, value_type const& tau, value_type const& t) const {
				return calc_2(x, static_cast<typename Outdirected::index_type>(t), t - static_cast<typename Outdirected::index_type>(t));
			}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			calc(Outdirected const& x, value_type const& tau) const {
				return calc_1(x, tau, x.index() - tau);
			}
		public:
			SPROUT_CONSTEXPR vibrato_outdirected_value(
				value_type const& d, value_type const& depth, value_type const& rate,
				int_type samples_per_sec = 44100
				)
				: d_(d), depth_(depth), rate_(rate), samples_per_sec_(samples_per_sec)
			{}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			operator()(Outdirected const& x) const {
				return calc(x, d_ + depth_ * sprout::math::sin(2 * sprout::math::pi<Value>() * rate_ * x.index() / samples_per_sec_));
			}
		};

		namespace effects {
			//
			// vibrato_holder
			//
			template<typename T, typename IntType = int>
			class vibrato_holder {
			public:
				typedef T value_type;
				typedef IntType int_type;
			private:
				value_type d_;
				value_type depth_;
				value_type rate_;
				int_type samples_per_sec_;
			public:
				vibrato_holder() = default;
				vibrato_holder(vibrato_holder const&) = default;
				SPROUT_CONSTEXPR vibrato_holder(
					value_type const& d, value_type const& depth, value_type const& rate,
					int_type samples_per_sec = 44100
					)
					: d_(d), depth_(depth), rate_(rate), samples_per_sec_(samples_per_sec)
				{}
				SPROUT_CONSTEXPR value_type const& d() const {
					return d_;
				}
				SPROUT_CONSTEXPR value_type const& depth() const {
					return depth_;
				}
				SPROUT_CONSTEXPR value_type const& rate() const {
					return rate_;
				}
				SPROUT_CONSTEXPR int_type const& samples_per_sec() const {
					return samples_per_sec_;
				}
			};

			//
			// vibrato_forwarder
			//
			class vibrato_forwarder {
			public:
				template<typename T, typename IntType>
				SPROUT_CONSTEXPR sprout::compost::effects::vibrato_holder<T, IntType>
				operator()(T const& d, T const& depth, T const& rate, IntType samples_per_sec) {
					return sprout::compost::effects::vibrato_holder<T, IntType>(d, depth, rate, samples_per_sec);
				}
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::vibrato_holder<T>
				operator()(T const& d, T const& depth, T const& rate) {
					return sprout::compost::effects::vibrato_holder<T>(d, depth, rate);
				}
			};

			//
			// vibrato
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::vibrato_forwarder vibrato{};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T, typename IntType>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::vibrato_holder<T, IntType> const& rhs)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::valued(sprout::size(sprout::forward<Range>(lhs)))
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::vibrato_outdirected_value<T, IntType>(
							rhs.d(), rhs.depth(), rhs.rate(), rhs.samples_per_sec()
							)
						)
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::valued(sprout::size(sprout::forward<Range>(lhs)))
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::vibrato_outdirected_value<T, IntType>(
							rhs.d(), rhs.depth(), rhs.rate(), rhs.samples_per_sec()
							)
						)
					;
			}
		}	// namespace effects
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_VIBRATO_HPP
