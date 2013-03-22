#ifndef SPROUT_RATIONAL_EXCEPTIONS_HPP
#define SPROUT_RATIONAL_EXCEPTIONS_HPP

#include <stdexcept>
#include <sprout/config.hpp>

namespace sprout {
	//
	// bad_rational
	//
	class bad_rational
		: public std::domain_error
	{
	public:
		explicit bad_rational()
			: std::domain_error("bad rational: zero denominator")
		{}
	};
}	// namespace sprout

#endif	// SPROUT_RATIONAL_EXCEPTIONS_HPP
