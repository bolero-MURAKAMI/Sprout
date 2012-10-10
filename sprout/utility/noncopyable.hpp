#ifndef SPROUT_UTILITY_NONCOPYABLE_HPP
#define SPROUT_UTILITY_NONCOPYABLE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace noncopyable_ {
		class noncopyable {
		public:
			SPROUT_CONSTEXPR noncopyable() = default;
			noncopyable(noncopyable const&) = delete;
			noncopyable& operator=(noncopyable const&) = delete;
		};
	}	// namespace noncopyable_
	//
	// noncopyable
	//
	typedef sprout::noncopyable_::noncopyable noncopyable;
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_NONCOPYABLE_HPP
