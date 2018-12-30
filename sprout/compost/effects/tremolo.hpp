/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_TREMOLO_HPP
#define SPROUT_COMPOST_EFFECTS_TREMOLO_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/range/adaptor/transformed.hpp>
#include <sprout/range/adaptor/outdirected.hpp>
#include <sprout/range/adaptor/indexed.hpp>

namespace sprout {
	namespace compost {
		//
		// tremolo_outdirected_value
		//
		template<typename Value, typename IntType>
		struct tremolo_outdirected_value {
		public:
			typedef Value value_type;
			typedef IntType int_type;
		private:
			value_type depth_;
			value_type rate_;
			int_type samples_per_sec_;
		public:
			SPROUT_CONSTEXPR tremolo_outdirected_value(value_type const& depth, value_type const& rate, int_type samples_per_sec = 44100)
				: depth_(depth), rate_(rate), samples_per_sec_(samples_per_sec)
			{}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			operator()(Outdirected const& x) const {
				return (1 + depth_ * sprout::math::sin(sprout::math::two_pi<Value>() * rate_ * x.index() / samples_per_sec_)) * *x;
			}
		};

		namespace effects {
			//
			// tremolo_holder
			//
			template<typename T, typename IntType = int>
			class tremolo_holder {
			public:
				typedef T value_type;
				typedef IntType int_type;
			private:
				value_type depth_;
				value_type rate_;
				int_type samples_per_sec_;
			public:
				SPROUT_CONSTEXPR tremolo_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				tremolo_holder(tremolo_holder const&) = default;
				SPROUT_CONSTEXPR tremolo_holder(value_type const& depth, value_type const& rate, int_type samples_per_sec = 44100)
					: depth_(depth), rate_(rate), samples_per_sec_(samples_per_sec)
				{}
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
			// tremolo_forwarder
			//
			class tremolo_forwarder {
			public:
				template<typename T, typename IntType>
				SPROUT_CONSTEXPR sprout::compost::effects::tremolo_holder<T, IntType>
				operator()(T const& depth, T const& rate, IntType samples_per_sec) const {
					return sprout::compost::effects::tremolo_holder<T, IntType>(depth, rate, samples_per_sec);
				}
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::tremolo_holder<T>
				operator()(T const& depth, T const& rate) const {
					return sprout::compost::effects::tremolo_holder<T>(depth, rate);
				}
			};

			//
			// tremolo
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::tremolo_forwarder tremolo = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T, typename IntType>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::tremolo_holder<T, IntType> const& rhs)
			-> decltype(
				SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::tremolo_outdirected_value<T, IntType>(rhs.depth(), rhs.rate(), rhs.samples_per_sec())
						)
				)
			{
				return SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::tremolo_outdirected_value<T, IntType>(rhs.depth(), rhs.rate(), rhs.samples_per_sec())
						)
					;
			}
		}	// namespace effects

		using sprout::compost::effects::tremolo;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_TREMOLO_HPP
