/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_AUTO_PAN_HPP
#define SPROUT_COMPOST_EFFECTS_AUTO_PAN_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/range/adaptor/transformed.hpp>
#include <sprout/range/adaptor/outdirected.hpp>
#include <sprout/range/adaptor/indexed.hpp>
#include <sprout/compost/formats/stereo.hpp>

namespace sprout {
	namespace compost {
		//
		// auto_pan_outdirected_value
		//
		template<typename Value, typename IntType, bool IsLeft>
		struct auto_pan_outdirected_value {
		public:
			typedef Value value_type;
			typedef IntType int_type;
		private:
			value_type depth_;
			value_type rate_;
			int_type samples_per_sec_;
		private:
			template<bool Left, typename Outdirected>
			SPROUT_CONSTEXPR typename std::enable_if<
				Left,
				typename std::iterator_traits<Outdirected>::value_type
			>::type
			calc(Outdirected const& x) const {
				return (1 + depth_ * sprout::sin(sprout::math::two_pi<Value>() * rate_ * x.index() / samples_per_sec_)) * *x;
			}
			template<bool Left, typename Outdirected>
			SPROUT_CONSTEXPR typename std::enable_if<
				!Left,
				typename std::iterator_traits<Outdirected>::value_type
			>::type
			calc(Outdirected const& x) const {
				return (1 + depth_ * sprout::sin(sprout::math::two_pi<Value>() * rate_ * x.index() / samples_per_sec_ + sprout::math::pi<Value>())) * *x;
			}
		public:
			SPROUT_CONSTEXPR auto_pan_outdirected_value(
				value_type const& depth, value_type const& rate,
				int_type samples_per_sec = 44100
				)
				: depth_(depth), rate_(rate), samples_per_sec_(samples_per_sec)
			{}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			operator()(Outdirected const& x) const {
				return calc<IsLeft>(x);
			}
		};

		namespace effects {
			//
			// auto_pan_holder
			//
			template<typename T, typename IntType = int>
			class auto_pan_holder {
			public:
				typedef T value_type;
				typedef IntType int_type;
			private:
				value_type depth_;
				value_type rate_;
				int_type samples_per_sec_;
			public:
				SPROUT_CONSTEXPR auto_pan_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				auto_pan_holder(auto_pan_holder const&) = default;
				SPROUT_CONSTEXPR auto_pan_holder(
					value_type const& depth, value_type const& rate,
					int_type samples_per_sec = 44100
					)
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
			// auto_pan_forwarder
			//
			class auto_pan_forwarder {
			public:
				template<typename T, typename IntType>
				SPROUT_CONSTEXPR sprout::compost::effects::auto_pan_holder<T, IntType>
				operator()(T const& depth, T const& rate, IntType samples_per_sec) const {
					return sprout::compost::effects::auto_pan_holder<T, IntType>(depth, rate, samples_per_sec);
				}
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::auto_pan_holder<T>
				operator()(T const& depth, T const& rate) const {
					return sprout::compost::effects::auto_pan_holder<T>(depth, rate);
				}
			};

			//
			// auto_pan
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::auto_pan_forwarder auto_pan = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T, typename IntType>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::auto_pan_holder<T, IntType> const& rhs)
			-> decltype(
				SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::auto_pan_outdirected_value<T, IntType, true>(rhs.depth(), rhs.rate(), rhs.samples_per_sec())
						)
					| sprout::compost::formats::stereo(
						SPROUT_FORWARD(Range, lhs)
							| sprout::adaptors::indexed | sprout::adaptors::outdirected
							| sprout::adaptors::transformed(
								sprout::compost::auto_pan_outdirected_value<T, IntType, false>(rhs.depth(), rhs.rate(), rhs.samples_per_sec())
								)
						)
				)
			{
				return SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::auto_pan_outdirected_value<T, IntType, true>(rhs.depth(), rhs.rate(), rhs.samples_per_sec())
						)
					| sprout::compost::formats::stereo(
						SPROUT_FORWARD(Range, lhs)
							| sprout::adaptors::indexed | sprout::adaptors::outdirected
							| sprout::adaptors::transformed(
								sprout::compost::auto_pan_outdirected_value<T, IntType, false>(rhs.depth(), rhs.rate(), rhs.samples_per_sec())
								)
						)
					;
			}
		}	// namespace effects

		using sprout::compost::effects::auto_pan;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_AUTO_PAN_HPP
