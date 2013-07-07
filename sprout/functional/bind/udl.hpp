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
	//
	template<char... Chars>
	struct placeholders_result
		: public sprout::identity<
			sprout::placeholder<sprout::detail::digits_to_int<int, Chars...>::value>
		>
	{};

	namespace placeholders {
		namespace udl {
			//
			// _
			//
			template<char... Chars>
			SPROUT_CONSTEXPR typename sprout::placeholders_result<Chars...>::type
			operator"" _() {
				typedef typename sprout::placeholders_result<Chars...>::type type;
				return type();
			}
		}	// namespace udl
	}	// namespace placeholders

	namespace udl {
		namespace placeholders {
			using sprout::placeholders::udl::operator"" _;
		}	// namespace placeholders

		using sprout::placeholders::udl::operator"" _;
	}	// namespace udl
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_FUNCTIONAL_BIND_UDL_HPP
