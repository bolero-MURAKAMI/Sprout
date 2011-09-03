#ifndef SPROUT_DETAIL_FUNCTIONAL_HPP
#define SPROUT_DETAIL_FUNCTIONAL_HPP

#include <functional>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		//
		// less
		//
		template<typename T>
		class less
			: public std::binary_function<T, T, bool>
		{
		public:
			SPROUT_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const {
				return lhs < rhs;
			}
		};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_FUNCTIONAL_HPP
