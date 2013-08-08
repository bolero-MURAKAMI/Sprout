/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_BIND_UDL_HPP
#define SPROUT_FUNCTIONAL_BIND_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/functional/bind/placeholder.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/digits_to_int.hpp>

namespace sprout {
	//
	// placeholders_result
	// variadic_placeholders_result
	//
	template<char... Chars>
	struct placeholders_result
		: public sprout::identity<
			sprout::placeholder<sprout::detail::digits_to_int<int, Chars...>::value>
		>
	{};
	template<char... Chars>
	struct variadic_placeholders_result
		: public sprout::identity<
			sprout::placeholder<sprout::is_placeholder<decltype(sprout::placeholders::_va)>::value - sprout::detail::digits_to_int<int, Chars...>::value>
		>
	{};

	namespace placeholders {
		namespace udl {
			//
			// _
			// _tail
			//
			template<char... Chars>
			SPROUT_CONSTEXPR typename sprout::placeholders_result<Chars...>::type
			operator"" _() {
				typedef typename sprout::placeholders_result<Chars...>::type type;
				return type();
			}
			template<char... Chars>
			SPROUT_CONSTEXPR typename sprout::variadic_placeholders_result<Chars...>::type
			operator"" _tail() {
				typedef typename sprout::variadic_placeholders_result<Chars...>::type type;
				return type();
			}
		}	// namespace udl
	}	// namespace placeholders

	namespace udl {
		namespace placeholders {
			using sprout::placeholders::udl::operator"" _;
			using sprout::placeholders::udl::operator"" _tail;
		}	// namespace placeholders

		using sprout::placeholders::udl::operator"" _;
		using sprout::placeholders::udl::operator"" _tail;
	}	// namespace udl
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND_UDL_HPP
