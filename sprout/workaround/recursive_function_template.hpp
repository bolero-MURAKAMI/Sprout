/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WORKAROUND_RECURSIVE_FUNCTION_TEMPLATE_HPP
#define SPROUT_WORKAROUND_RECURSIVE_FUNCTION_TEMPLATE_HPP

#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/any_convertible.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/preprocessor/stringize.hpp>
#include <sprout/detail/predef.hpp>

//
// SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_LIMIT
//
#ifndef SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_LIMIT
#	if SPROUT_CLANG_OR_LATER(3, 3, 0)
#		define SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_LIMIT 256
#	else
#		define SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_LIMIT 512
#	endif
#endif

//
// SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL
// SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL
//
#define SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(DEPTH) \
	typename sprout::enabler_if<((DEPTH) < SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_LIMIT - 1)>::type
#define SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(DEPTH) \
	typename sprout::enabler_if<((DEPTH) >= SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_LIMIT - 1)>::type

//
// SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE
// SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK
//
#define SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE(DEPTH) \
	SPROUT_RECURSIVE_FUNCTION_TEMPLATE_CONTINUE_DECL(DEPTH) = sprout::enabler
#define SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK(DEPTH) \
	SPROUT_RECURSIVE_FUNCTION_TEMPLATE_BREAK_DECL(DEPTH) = sprout::enabler

//
// SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_EXCEEDED_MESSAGE
//
#define SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_EXCEEDED_MESSAGE \
	"recursive template instantiation exceeded maximum depth of " SPROUT_PP_STRINGIZE(SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_LIMIT)

namespace sprout {
	//
	// recursive_function_template_instantiation_exeeded
	//
	class recursive_function_template_instantiation_exeeded
		: public std::runtime_error
	{
	public:
		recursive_function_template_instantiation_exeeded() SPROUT_NOEXCEPT
			: std::runtime_error(SPROUT_RECURSIVE_FUNCTION_TEMPLATE_INSTANTIATION_EXCEEDED_MESSAGE)
		{}
	};

	//
	// throw_recursive_function_template_instantiation_exeeded
	//
	template<typename T = sprout::any_convertible>
	inline SPROUT_CONSTEXPR T
	throw_recursive_function_template_instantiation_exeeded() {
		return throw sprout::recursive_function_template_instantiation_exeeded(), T();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T&&
	throw_recursive_function_template_instantiation_exeeded(T&& t) {
		return throw sprout::recursive_function_template_instantiation_exeeded(), SPROUT_FORWARD(T, t);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_WORKAROUND_RECURSIVE_FUNCTION_TEMPLATE_HPP
