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
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::pair<UTypes...> const& t)
			: impl_type(t.first, t.second)
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::pair<UTypes...>&& t)
			: impl_type(sprout::forward<typename sprout::pair<UTypes...>::first_type>(t.first), sprout::forward<typename sprout::pair<UTypes...>::second_type>(t.second))
		{}

		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UTypes...> const& t)
			: impl_type(t.first, t.second)
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UTypes...>&& t)
			: impl_type(sprout::forward<typename sprout::pair<UTypes...>::first_type>(t.first), sprout::forward<typename sprout::pair<UTypes...>::second_type>(t.second))
		{}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
