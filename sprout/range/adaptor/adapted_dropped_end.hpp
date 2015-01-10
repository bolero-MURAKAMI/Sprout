/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_ADAPTED_DROPPED_END_HPP
#define SPROUT_RANGE_ADAPTOR_ADAPTED_DROPPED_END_HPP

#include <sprout/config.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/range/adaptor/taken_end.hpp>
#include <sprout/range/adaptor/dropped_end.hpp>
#include <sprout/range/adaptor/jointed.hpp>

namespace sprout {
	namespace adaptors {
		//
		// adapt_drop_end_holder
		//
		template<typename Adaptor, typename Difference>
		class adapt_drop_end_holder {
		public:
			typedef Adaptor adaptor_type;
			typedef Difference difference_type;
		private:
			adaptor_type adaptor_;
			difference_type distance_;
		public:
			SPROUT_CONSTEXPR adapt_drop_end_holder(adaptor_type const& adaptor, difference_type distance)
				: adaptor_(adaptor), distance_(distance)
			{}
			SPROUT_CONSTEXPR adaptor_type const& adaptor() const {
				return adaptor_;
			}
			SPROUT_CONSTEXPR difference_type const& distance() const {
				return distance_;
			}
		};

		//
		// adapted_dropped_end_forwarder
		//
		class adapted_dropped_end_forwarder {
		public:
			template<typename Adaptor, typename Difference>
			SPROUT_CONSTEXPR sprout::adaptors::adapt_drop_end_holder<Adaptor, Difference>
			operator()(Adaptor const& adaptor, Difference distance) const {
				return sprout::adaptors::adapt_drop_end_holder<Adaptor, Difference>(adaptor, distance);
			}
		};

		//
		// adapted_dropped_end
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::adapted_dropped_end_forwarder adapted_dropped_end = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename Adaptor, typename Difference>
		inline SPROUT_CONSTEXPR auto
		operator|(Range&& lhs, sprout::adaptors::adapt_drop_end_holder<Adaptor, Difference> const& rhs)
		-> decltype(
			sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::dropped_end(rhs.distance()) | rhs.adaptor()
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken_end(rhs.distance()))
			)
		{
			return sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::dropped_end(rhs.distance()) | rhs.adaptor()
				| sprout::adaptors::jointed(sprout::lvalue_forward<Range>(lhs) | sprout::adaptors::taken_end(rhs.distance()))
				;
		}
	}	// namespace adaptors
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_ADAPTED_DROPPED_END_HPP
