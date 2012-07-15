#ifndef SPROUT_TUPLE_TUPLE_IGNORE_HPP
#define SPROUT_TUPLE_TUPLE_IGNORE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace tuples {
		//
		// ignore_t
		//
		struct ignore_t {
		public:
			template<typename T>
			ignore_t const& operator=(T const&) const {
				return *this;
			}
		};
		//
		// ignore
		//
		SPROUT_STATIC_CONSTEXPR ignore_t ignore{};
	}	// namespace tuples

	using sprout::tuples::ignore_t;
	using sprout::tuples::ignore;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_IGNORE_HPP
