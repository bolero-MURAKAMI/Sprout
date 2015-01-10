/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_NONCOPYABLE_HPP
#define SPROUT_UTILITY_NONCOPYABLE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace noncopyable_detail {
		class noncopyable {
		protected:
			SPROUT_CONSTEXPR noncopyable() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			~noncopyable() SPROUT_DEFAULTED_DESTRUCTOR_DECL
		private:
			noncopyable(noncopyable const&) SPROUT_DELETED_FUNCTION_DECL
			noncopyable& operator=(noncopyable const&) SPROUT_DELETED_FUNCTION_DECL
		};
	}	// namespace noncopyable_detail
	//
	// noncopyable
	//
	typedef sprout::noncopyable_detail::noncopyable noncopyable;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_NONCOPYABLE_HPP
