/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_EFFECTS_PSEUDO_STEREO_HPP
#define SPROUT_COMPOST_EFFECTS_PSEUDO_STEREO_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/range/adaptor/transformed.hpp>
#include <sprout/range/adaptor/outdirected.hpp>
#include <sprout/range/adaptor/indexed.hpp>
#include <sprout/compost/formats/stereo.hpp>

namespace sprout {
	namespace compost {
		//
		// pseudo_stereo_outdirected_value
		//
		template<typename Value, typename IntType, bool IsLeft>
		struct pseudo_stereo_outdirected_value {
		public:
			typedef Value value_type;
			typedef IntType int_type;
		private:
			value_type delay_;
			int_type samples_per_sec_;
			int_type d_;
		private:
			template<bool Left, typename Outdirected>
			SPROUT_CONSTEXPR typename std::enable_if<
				Left,
				typename std::iterator_traits<Outdirected>::value_type
			>::type
			calc(Outdirected const& x) const {
				return x.index() + d_ >= 0 ? *x + x[d_]
					: 0
					;
			}
			template<bool Left, typename Outdirected>
			SPROUT_CONSTEXPR typename std::enable_if<
				!Left,
				typename std::iterator_traits<Outdirected>::value_type
			>::type
			calc(Outdirected const& x) const {
				return x.index() + d_ >= 0 ? *x - x[d_]
					: 0
					;
			}
		public:
			explicit SPROUT_CONSTEXPR pseudo_stereo_outdirected_value(
				value_type const& delay, int_type samples_per_sec = 44100
				)
				: delay_(delay), samples_per_sec_(samples_per_sec), d_(static_cast<int_type>(-delay * samples_per_sec_))
			{}
			template<typename Outdirected>
			SPROUT_CONSTEXPR typename std::iterator_traits<Outdirected>::value_type
			operator()(Outdirected const& x) const {
				return calc<IsLeft>(x);
			}
		};

		namespace effects {
			//
			// pseudo_stereo_holder
			//
			template<typename T, typename IntType = int>
			class pseudo_stereo_holder {
			public:
				typedef T value_type;
				typedef IntType int_type;
			private:
				value_type delay_;
				int_type samples_per_sec_;
			public:
				SPROUT_CONSTEXPR pseudo_stereo_holder() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
				pseudo_stereo_holder(pseudo_stereo_holder const&) = default;
				explicit SPROUT_CONSTEXPR pseudo_stereo_holder(
					value_type const& delay, int_type samples_per_sec = 44100
					)
					: delay_(delay), samples_per_sec_(samples_per_sec)
				{}
				SPROUT_CONSTEXPR value_type const& delay() const {
					return delay_;
				}
				SPROUT_CONSTEXPR int_type const& samples_per_sec() const {
					return samples_per_sec_;
				}
			};

			//
			// pseudo_stereo_forwarder
			//
			class pseudo_stereo_forwarder {
			public:
				template<typename T, typename IntType>
				SPROUT_CONSTEXPR sprout::compost::effects::pseudo_stereo_holder<T, IntType>
				operator()(T const& delay, IntType samples_per_sec) const {
					return sprout::compost::effects::pseudo_stereo_holder<T, IntType>(delay, samples_per_sec);
				}
				template<typename T>
				SPROUT_CONSTEXPR sprout::compost::effects::pseudo_stereo_holder<T>
				operator()(T const& delay) const {
					return sprout::compost::effects::pseudo_stereo_holder<T>(delay);
				}
			};

			//
			// pseudo_stereo
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::effects::pseudo_stereo_forwarder pseudo_stereo = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename T, typename IntType>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::effects::pseudo_stereo_holder<T, IntType> const& rhs)
			-> decltype(
				sprout::lvalue_forward<Range>(lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::pseudo_stereo_outdirected_value<T, IntType, true>(rhs.delay(), rhs.samples_per_sec())
						)
					| sprout::compost::formats::stereo(
						sprout::lvalue_forward<Range>(lhs)
							| sprout::adaptors::indexed | sprout::adaptors::outdirected
							| sprout::adaptors::transformed(
								sprout::compost::pseudo_stereo_outdirected_value<T, IntType, false>(rhs.delay(), rhs.samples_per_sec())
								)
						)
				)
			{
				return sprout::lvalue_forward<Range>(lhs)
					| sprout::adaptors::indexed | sprout::adaptors::outdirected
					| sprout::adaptors::transformed(
						sprout::compost::pseudo_stereo_outdirected_value<T, IntType, true>(rhs.delay(), rhs.samples_per_sec())
						)
					| sprout::compost::formats::stereo(
						sprout::lvalue_forward<Range>(lhs)
							| sprout::adaptors::indexed | sprout::adaptors::outdirected
							| sprout::adaptors::transformed(
								sprout::compost::pseudo_stereo_outdirected_value<T, IntType, false>(rhs.delay(), rhs.samples_per_sec())
								)
						)
					;
			}
		}	// namespace effects

		using sprout::compost::effects::pseudo_stereo;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_EFFECTS_PSEUDO_STEREO_HPP
