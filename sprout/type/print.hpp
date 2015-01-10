/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_PRINT_HPP
#define SPROUT_TYPE_PRINT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace types {
		namespace detail {
#if defined(_MSC_VER)
#	pragma warning(push, 3)
#	pragma warning(disable: 4307)
#elif defined(__MWERKS__)
#	pragma warn_hidevirtual on
			struct print_base {
				virtual void f() {}
			};
#endif

#if defined(__EDG_VERSION__)
			template<typename T>
			struct dependent_unsigned {
				static unsigned const value = 1;
			};
#endif
		}	// namespace detail

		//
		// print
		//
		template<typename T>
		struct print
			: public sprout::identity<T>
#if defined(__MWERKS__)
			, public sprout::types::detail::print_base
#endif
		{
#if defined(_MSC_VER)
			enum {
				n = sizeof(T) + -1
			};
#elif defined(__MWERKS__)
			void f(int);
#else
			enum {
				n =
#	if defined(__EDG_VERSION__)
					sprout::types::detail::dependent_unsigned<T>::value > -1
#	else
					sizeof(T) > -1
#	endif
			};
#endif
		};

#if defined(_MSC_VER)
#	pragma warning(pop)
#elif defined(__MWERKS__)
#	pragma warn_hidevirtual reset
#endif
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_PRINT_HPP
