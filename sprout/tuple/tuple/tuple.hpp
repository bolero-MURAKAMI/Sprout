/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/pair/pair_decl.hpp>
#include <sprout/tuple/tuple/tuple_decl.hpp>
#include <sprout/tuple/flexibly_construct.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple
		//
		// tuple construction
		template<typename... Types>
		template<
			typename UType1, typename UType2,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::pair<UType1, UType2> const& t)
			: impl_type(t.first, t.second)
		{}
		template<typename... Types>
		template<
			typename UType1, typename UType2,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::pair<UType1, UType2>&& t)
			: impl_type(SPROUT_FORWARD(UType1, t.first), SPROUT_FORWARD(UType2, t.second))
		{}

		template<typename... Types>
		template<
			typename UType1, typename UType2,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2> const& t)
			: impl_type(t.first, t.second)
		{}
		template<typename... Types>
		template<
			typename UType1, typename UType2,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2>&& t)
			: impl_type(SPROUT_FORWARD(UType1, t.first), SPROUT_FORWARD(UType2, t.second))
		{}
		// tuple assignment
		template<typename... Types>
		template<
			typename UType1, typename UType2,
			typename
		>
		inline SPROUT_CXX14_CONSTEXPR sprout::tuples::tuple<Types...>&
		sprout::tuples::tuple<Types...>::operator=(sprout::pair<UType1, UType2> const& rhs) {
			sprout::tuples::detail::tuple_impl<0, Types...>::head(*this) = rhs.first;
			sprout::tuples::detail::tuple_impl<1, Types...>::head(*this) = rhs.second;
			return *this;
		}
		template<typename... Types>
		template<
			typename UType1, typename UType2,
			typename
		>
		inline SPROUT_CXX14_CONSTEXPR sprout::tuples::tuple<Types...>&
		sprout::tuples::tuple<Types...>::operator=(sprout::pair<UType1, UType2>&& rhs) {
			sprout::tuples::detail::tuple_impl<0, Types...>::head(*this) = sprout::move(rhs.first);
			sprout::tuples::detail::tuple_impl<1, Types...>::head(*this) = sprout::move(rhs.second);
			return *this;
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
