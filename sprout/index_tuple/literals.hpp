/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_LITERALS_HPP
#define SPROUT_INDEX_TUPLE_LITERALS_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/detail/udl_namespace.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <sprout/index_tuple/make_index_tuple.hpp>
#include <sprout/detail/digits_to_int.hpp>

namespace sprout {
	//
	// indexes_result
	// uindexes_result
	//
	template<char... Chars>
	struct indexes_result
		: public sprout::make_index_tuple<sprout::detail::digits_to_int<sprout::index_t, Chars...>::value>
	{};
	template<char... Chars>
	struct uindexes_result
		: public sprout::make_uindex_tuple<sprout::detail::digits_to_int<sprout::uindex_t, Chars...>::value>
	{};

	namespace literals {
		namespace indexes {
			//
			// _indexes
			// _uindexes
			//
			template<char... Chars>
			SPROUT_CONSTEXPR typename sprout::indexes_result<Chars...>::type
			operator"" _indexes() {
				return sprout::indexes_result<Chars...>::make();
			}
			template<char... Chars>
			SPROUT_CONSTEXPR typename sprout::uindexes_result<Chars...>::type
			operator"" _uindexes() {
				return sprout::uindexes_result<Chars...>::make();
			}
		}	// namespace indexes

		using sprout::literals::indexes::operator"" _indexes;
		using sprout::literals::indexes::operator"" _uindexes;
	}	// namespace literals

	using sprout::literals::indexes::operator"" _indexes;
	using sprout::literals::indexes::operator"" _uindexes;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_INDEX_TUPLE_LITERALS_HPP
