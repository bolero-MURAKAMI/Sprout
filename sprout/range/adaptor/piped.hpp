/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_ADAPTOR_PIPED_HPP
#define SPROUT_RANGE_ADAPTOR_PIPED_HPP

#include <type_traits>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/lvalue_forward.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>

namespace sprout {
	namespace adaptors {
		namespace detail {
			template<typename Range>
			inline SPROUT_CONSTEXPR auto
			apply_adaptors_impl(Range&& range)
			-> decltype(SPROUT_FORWARD(Range, range))
			{
				return SPROUT_FORWARD(Range, range);
			}
			template<typename Range, typename Adaptor>
			inline SPROUT_CONSTEXPR auto
			apply_adaptors_impl(Range&& range, Adaptor const& adaptor)
			-> decltype(SPROUT_FORWARD(Range, range) | adaptor)
			{
				return SPROUT_FORWARD(Range, range) | adaptor;
			}
			template<typename Range, typename Adaptor, typename... Tail>
			inline SPROUT_CONSTEXPR auto
			apply_adaptors_impl(Range&& range, Adaptor const& adaptor, Tail const&... tail)
			-> decltype(sprout::adaptors::detail::apply_adaptors_impl(SPROUT_FORWARD(Range, range) | adaptor, tail...))
			{
				return sprout::adaptors::detail::apply_adaptors_impl(SPROUT_FORWARD(Range, range) | adaptor, tail...);
			}
		}	// namespace detail
		//
		// apply_adaptors
		//
		template<typename Range, typename... Adaptors>
		SPROUT_CONSTEXPR auto
		apply_adaptors(Range&& range, Adaptors const&... adaptors)
		-> decltype(sprout::adaptors::detail::apply_adaptors_impl(SPROUT_FORWARD(Range, range), adaptors...))
		{
			return sprout::adaptors::detail::apply_adaptors_impl(SPROUT_FORWARD(Range, range), adaptors...);
		}

		namespace detail {
			template<typename Range, typename AdaptorsTuple, sprout::index_t... Indexes>
			SPROUT_CONSTEXPR auto
			apply_adaptors_tuple_impl(Range&& range, AdaptorsTuple const& adaptors, sprout::index_tuple<Indexes...>)
			-> decltype(sprout::adaptors::apply_adaptors(SPROUT_FORWARD(Range, range), sprout::tuples::get<Indexes>(adaptors)...))
			{
				return sprout::adaptors::apply_adaptors(SPROUT_FORWARD(Range, range), sprout::tuples::get<Indexes>(adaptors)...);
			}
			template<typename Range, typename AdaptorsTuple>
			SPROUT_CONSTEXPR auto
			apply_adaptors_tuple(Range&& range, AdaptorsTuple const& adaptors)
			-> decltype(
				sprout::adaptors::detail::apply_adaptors_tuple_impl(
					SPROUT_FORWARD(Range, range), adaptors,
					sprout::make_index_tuple<sprout::tuples::tuple_size<AdaptorsTuple>::value>::make()
					)
				)
			{
				return sprout::adaptors::detail::apply_adaptors_tuple_impl(
					SPROUT_FORWARD(Range, range), adaptors,
					sprout::make_index_tuple<sprout::tuples::tuple_size<AdaptorsTuple>::value>::make()
					);
			}
		}	// namespace detail

		//
		// pipe_holder
		//
		template<typename... Adaptors>
		class pipe_holder {
		public:
			typedef sprout::tuples::tuple<Adaptors...> adaptors_type;
		private:
			adaptors_type adaptors_;
		public:
			explicit SPROUT_CONSTEXPR pipe_holder(Adaptors const&... adaptors)
				: adaptors_(adaptors...)
			{}
			SPROUT_CONSTEXPR adaptors_type const& adaptors() const {
				return adaptors_;
			}
			template<typename Range>
			SPROUT_CONSTEXPR auto
			apply(Range&& range) const
			-> decltype(sprout::adaptors::detail::apply_adaptors_tuple(SPROUT_FORWARD(Range, range), std::declval<pipe_holder const&>().adaptors()))
			{
				return sprout::adaptors::detail::apply_adaptors_tuple(SPROUT_FORWARD(Range, range), adaptors());
			}
		};

		//
		// piped_forwarder
		//
		class piped_forwarder {
		public:
			template<typename... Adaptors>
			SPROUT_CONSTEXPR sprout::adaptors::pipe_holder<Adaptors...>
			operator()(Adaptors const&... adaptors) const {
				return sprout::adaptors::pipe_holder<Adaptors...>(adaptors...);
			}
		};

		//
		// piped
		//
		namespace {
			SPROUT_STATIC_CONSTEXPR sprout::adaptors::piped_forwarder piped = {};
		}	// anonymous-namespace

		//
		// operator|
		//
		template<typename Range, typename... Adaptors>
		inline SPROUT_CONSTEXPR auto
		operator|(Range&& lhs, sprout::adaptors::pipe_holder<Adaptors...> const& rhs)
		-> decltype(rhs.apply(sprout::lvalue_forward<Range>(lhs)))
		{
			return rhs.apply(sprout::lvalue_forward<Range>(lhs));
		}
	}	// namespace adaptors
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ADAPTOR_PIPED_HPP
