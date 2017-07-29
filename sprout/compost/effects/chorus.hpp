/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_CHORUS_HPP
#define SPROUT_COMPOST_EFFECTS_CHORUS_HPP

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
		// chorus_outdirected_value
		//
		template<typename Value, typename IntType>
		struct chorus_outdirected_value {
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
				return *x + (m >= 0 && (m + 1 < x.base().get() || x.base().get() < 0)
					? delta * x[m + 1 - x.index()] + (1 - delta) * x[m - x.index()]
					: 0
					)
					;
			}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			calc_1(Outdirected const& x, value_type const& t) const {
				return calc_2(x, static_cast<typename Outdirected::index_type>(t), t - static_cast<typename Outdirected::index_type>(t));
			}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			calc(Outdirected const& x, value_type const& tau) const {
				return calc_1(x, x.index() - tau);
			}
		public:
			SPROUT_CONSTEXPR chorus_outdirected_value(
				value_type const& d, value_type const& depth, value_type const& rate,
				int_type samples_per_sec = 44100
				)
				: d_(d), depth_(depth), rate_(rate), samples_per_sec_(samples_per_sec)
			{}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			operator()(Outdirected const& x) const {
				return calc(x, d_ + depth_ * sprout::sin(sprout::math::two_pi<Value>() * rate_ * x.index() / samples_per_sec_));
			}
		};

		namespace effects {
			//
			// chorus_holder
			//
			template<typename T, typename IntType = int>
			class chorus_holder {
			public:
				typedef T value_type;
				typedef IntType int_type;
			private:
				value_type d_;
				value_type depth_;
				value_type rate_;
				int_type samples_per_sec_;
			public:
				SPROUT_CONSTEXPR chorus_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				chorus_holder(chorus_holder const&) = default;
				SPROUT_CONSTEXPR chorus_holder(
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
			// chorus_forwarder
			//
			class chorus_forwarder {
			public:
				template<typename T, typename IntType>
				SPROUT_CONSTEXPR sprout::compost::effects::chorus_holder<T, IntType>
				operator()(T const& d, T const& depth, T const& rate, IntType samples_per_sec) const {
					return sprout::compost::effects::chorus_holder<T, IntType>(d, depth, rate, samples_per_sec);
				}
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::chorus_holder<T>
				operator()(T const& d, T const& depth, T const& rate) const {
					return sprout::compost::effects::chorus_holder<T>(d, depth, rate);
				}
			};

			//
			// chorus
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::chorus_forwarder chorus = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T, typename IntType>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::chorus_holder<T, IntType> const& rhs)
			-> decltype(
				SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::valued(sprout::size(SPROUT_FORWARD(Range, lhs)))
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::chorus_outdirected_value<T, IntType>(
							rhs.d(), rhs.depth(), rhs.rate(), rhs.samples_per_sec()
							)
						)
				)
			{
				return SPROUT_FORWARD(Range, lhs)
					| sprout::adaptors::valued(sprout::size(SPROUT_FORWARD(Range, lhs)))
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::chorus_outdirected_value<T, IntType>(
							rhs.d(), rhs.depth(), rhs.rate(), rhs.samples_per_sec()
							)
						)
					;
			}
		}	// namespace effects

		using sprout::compost::effects::chorus;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_CHORUS_HPP
