/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_COMPOST_FORMATS_EFFECTED_EACH_HPP
#define SPROUT_COMPOST_FORMATS_EFFECTED_EACH_HPP

#include <sprout/config.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/compost/formats/left_channel.hpp>
#include <sprout/compost/formats/right_channel.hpp>
#include <sprout/compost/formats/stereo.hpp>

namespace sprout {
	namespace compost {
		namespace formats {
			//
			// effect_each_holder
			//
			template<typename LAdaptor, typename RAdaptor = void>
			class effect_each_holder {
			public:
				typedef LAdaptor left_adaptor_type;
				typedef RAdaptor right_adaptor_type;
			private:
				left_adaptor_type left_adaptor_;
				right_adaptor_type right_adaptor_;
			public:
				SPROUT_CONSTEXPR effect_each_holder(left_adaptor_type const& left_adaptor, right_adaptor_type const& right_adaptor)
					: left_adaptor_(left_adaptor), right_adaptor_(right_adaptor)
				{}
				SPROUT_CONSTEXPR left_adaptor_type const& left_adaptor() const {
					return left_adaptor_;
				}
				SPROUT_CONSTEXPR right_adaptor_type const& right_adaptor() const {
					return right_adaptor_;
				}
			};
			template<typename Adaptor>
			class effect_each_holder<Adaptor, void> {
			public:
				typedef Adaptor adaptor_type;
			private:
				adaptor_type adaptor_;
			public:
				explicit SPROUT_CONSTEXPR effect_each_holder(adaptor_type const& adaptor)
					: adaptor_(adaptor)
				{}
				SPROUT_CONSTEXPR adaptor_type const& adaptor() const {
					return adaptor_;
				}
			};

			//
			// effected_each_cannel_forwarder
			//
			class effected_each_cannel_forwarder {
			public:
				template<typename LAdaptor, typename RAdaptor>
				SPROUT_CONSTEXPR sprout::compost::formats::effect_each_holder<LAdaptor, RAdaptor>
				operator()(LAdaptor const& left_adaptor, RAdaptor const& right_adaptor) const {
					return sprout::compost::formats::effect_each_holder<LAdaptor, RAdaptor>(left_adaptor, right_adaptor);
				}
				template<typename Adaptor>
				SPROUT_CONSTEXPR sprout::compost::formats::effect_each_holder<Adaptor>
				operator()(Adaptor const& adaptor) const {
					return sprout::compost::formats::effect_each_holder<Adaptor>(adaptor);
				}
			};

			//
			// effected_each_cannel
			//
			namespace {
				SPROUT_STATIC_CONSTEXPR sprout::compost::formats::effected_each_cannel_forwarder effected_each_cannel = {};
			}	// anonymous-namespace

			//
			// operator|
			//
			template<typename Range, typename LAdaptor, typename RAdaptor>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::formats::effect_each_holder<LAdaptor, RAdaptor> const& rhs)
			-> decltype(
				sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel | rhs.left_adaptor()
					| sprout::compost::formats::stereo(sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel | rhs.right_adaptor())
				)
			{
				return sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel | rhs.left_adaptor()
					| sprout::compost::formats::stereo(sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel | rhs.right_adaptor())
					;
			}
			template<typename Range, typename Adaptor>
			inline SPROUT_CONSTEXPR auto
			operator|(Range&& lhs, sprout::compost::formats::effect_each_holder<Adaptor> const& rhs)
			-> decltype(
				sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel | rhs.adaptor()
					| sprout::compost::formats::stereo(sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel | rhs.adaptor())
				)
			{
				return sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::left_channel | rhs.adaptor()
					| sprout::compost::formats::stereo(sprout::lvalue_forward<Range>(lhs) | sprout::compost::formats::right_channel | rhs.adaptor())
					;
			}
		}	// namespace formats

		using sprout::compost::formats::effected_each_cannel;
	}	// namespace compost
}	// namespace sprout

#endif	// #ifndef SPROUT_COMPOST_FORMATS_EFFECTED_EACH_HPP
