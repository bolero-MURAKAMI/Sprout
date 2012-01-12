#ifndef SPROUT_UTILITY_ENABLER_IF_HPP
#define SPROUT_UTILITY_ENABLER_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// enabler_t
	// enabler
	//
	typedef void* enabler_t;
	extern enabler_t enabler;
	//
	// enabler_if
	//
	template<bool C>
	class enabler_if
		: public std::enable_if<C, enabler_t&>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_ENABLER_IF_HPP
