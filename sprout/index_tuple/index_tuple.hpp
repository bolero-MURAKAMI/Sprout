/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
#define SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_t.hpp>
#include <sprout/index_tuple/integer_sequence.hpp>

namespace sprout {
	//
	// index_tuple
	// uindex_tuple
	//
#if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
	template<sprout::index_t... Indexes>
	using index_tuple = sprout::integer_sequence<sprout::index_t, Indexes...>;

	template<sprout::uindex_t... Indexes>
	using uindex_tuple = sprout::integer_sequence<sprout::uindex_t, Indexes...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)

	namespace detail {
		template<typename T, template<T...> class Derived, T... Is>
		struct integer_sequence_another_base
			: public sprout::integer_sequence<T, Is...>
		{
		public:
			typedef Derived<Is...> type;
			template<T... Js>
			struct rebind
				: public Derived<Js...>
			{};
		public:
			static SPROUT_CONSTEXPR type make() SPROUT_NOEXCEPT {
				return type();
			}
		};
	}	// namespace detail

	template<sprout::index_t... Indexes>
	struct index_tuple
		: public sprout::detail::integer_sequence_another_base<sprout::index_t, sprout::index_tuple, Indexes...>
	{};
	template<sprout::uindex_t... Indexes>
	struct uindex_tuple
		: public sprout::detail::integer_sequence_another_base<sprout::uindex_t, sprout::uindex_tuple, Indexes...>
	{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES && !defined(SPROUT_WORKAROUND_NO_TEMPLATE_ARGUMENT_DEDUCTION_WITH_ALIASES)
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INDEX_TUPLE_HPP
