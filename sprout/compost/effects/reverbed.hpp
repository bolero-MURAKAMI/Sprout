/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_REVERBED_HPP
#define SPROUT_COMPOST_EFFECTS_REVERBED_HPP

#include <cstddef>
#include <iterator>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/pow.hpp>
#include <sprout/range/adaptor/transformed.hpp>
#include <sprout/range/adaptor/outdirected.hpp>
#include <sprout/range/adaptor/indexed.hpp>

namespace sprout {
	namespace compost {
		//
		// reverb_outdirected_value
		//
		template<typename Value, typename IntType>
		struct reverb_outdirected_value {
		public:
			typedef Value value_type;
			typedef IntType int_type;
		private:
			value_type attenuation_;
			value_type delay_;
			std::size_t repeat_;
			int_type samples_per_sec_;
		private:
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			calc_1(Outdirected const& x, std::size_t i, typename Outdirected::index_type m) const {
				return m >= 0 ? sprout::math::pow(attenuation_, i) * x[m - x.index()]
					: 0
					;
			}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			calc(Outdirected const& x, std::size_t i = 1) const {
				return i <= repeat_
					? calc_1(x, i, static_cast<typename Outdirected::index_type>(x.index() - i * delay_ * samples_per_sec_)) + calc(x, i + 1)
					: 0
					;
			}
		public:
			SPROUT_CONSTEXPR reverb_outdirected_value(
				value_type const& attenuation, value_type const& delay,
				std::size_t repeat = 2, int_type samples_per_sec = 44100
				)
				: attenuation_(attenuation), delay_(delay), repeat_(repeat), samples_per_sec_(samples_per_sec)
			{}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			operator()(Outdirected const& x) const {
				return *x + calc(x);
			}
		};

		namespace effects {
			//
			// reverb_holder
			//
			template<typename T, typename IntType = int>
			class reverb_holder {
			public:
				typedef T value_type;
				typedef IntType int_type;
			private:
				value_type attenuation_;
				value_type delay_;
				std::size_t repeat_;
				int_type samples_per_sec_;
			public:
				SPROUT_CONSTEXPR reverb_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				reverb_holder(reverb_holder const&) = default;
				SPROUT_CONSTEXPR reverb_holder(
					value_type const& attenuation, value_type const& delay,
					std::size_t repeat = 2, int_type samples_per_sec = 44100
					)
					: attenuation_(attenuation), delay_(delay), repeat_(repeat), samples_per_sec_(samples_per_sec)
				{}
				SPROUT_CONSTEXPR value_type const& attenuation() const {
					return attenuation_;
				}
				SPROUT_CONSTEXPR value_type const& delay() const {
					return delay_;
				}
				SPROUT_CONSTEXPR std::size_t const& repeat() const {
					return repeat_;
				}
				SPROUT_CONSTEXPR int_type const& samples_per_sec() const {
					return samples_per_sec_;
				}
			};

			//
			// reverbed_forwarder
			//
			class reverbed_forwarder {
			public:
				template<typename T, typename IntType>
				SPROUT_CONSTEXPR sprout::compost::effects::reverb_holder<T, IntType>
				operator()(T const& attenuation, T const& delay, std::size_t repeat, IntType samples_per_sec) const {
					return sprout::compost::effects::reverb_holder<T, IntType>(attenuation, delay, repeat, samples_per_sec);
				}
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::reverb_holder<T>
				operator()(T const& attenuation, T const& delay, std::size_t repeat = 2) const {
					return sprout::compost::effects::reverb_holder<T>(attenuation, delay, repeat);
				}
			};

			//
			// reverbed
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::reverbed_forwarder reverbed = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T, typename IntType>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::reverb_holder<T, IntType> const& rhs)
			-> decltype(
				sprout::forward<Range>(lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::reverb_outdirected_value<T, IntType>(
							rhs.attenuation(), rhs.delay(), rhs.repeat(), rhs.samples_per_sec()
							)
						)
				)
			{
				return sprout::forward<Range>(lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::reverb_outdirected_value<T, IntType>(
							rhs.attenuation(), rhs.delay(), rhs.repeat(), rhs.samples_per_sec()
							)
						)
					;
			}
		}	// namespace effects

		using sprout::compost::effects::reverbed;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_REVERBED_HPP
