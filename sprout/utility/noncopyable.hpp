#ifndef SPROUT_UTILITY_NONCOPYABLE_HPP
#define SPROUT_UTILITY_NONCOPYABLE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace noncopyable_ {
		class noncopyable {
		protected:
			SPROUT_CONSTEXPR noncopyable() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			~noncopyable() SPROUT_DEFAULTED_DESTRUCTOR_DECL
		private:
			noncopyable(noncopyable const&) SPROUT_DELETED_FUNCTION_DECL
			noncopyable& operator=(noncopyable const&) SPROUT_DELETED_FUNCTION_DECL
		};
	}	// namespace noncopyable_
	//
	// noncopyable
	//
	typedef sprout::noncopyable_::noncopyable noncopyable;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_NONCOPYABLE_HPP
