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
			: impl_type(sprout::forward<typename sprout::pair<UType1, UType2>::first_type>(t.first), sprout::forward<typename sprout::pair<UType1, UType2>::second_type>(t.second))
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
			: impl_type(sprout::forward<typename sprout::pair<UType1, UType2>::first_type>(t.first), sprout::forward<typename sprout::pair<UType1, UType2>::second_type>(t.second))
		{}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
