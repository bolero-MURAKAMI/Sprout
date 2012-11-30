#ifndef SPROUT_INTEGER_LIMITED_HPP
#define SPROUT_INTEGER_LIMITED_HPP

#include <limits>
#include <sprout/config.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>

namespace sprout {
	namespace limited {
		//
		// plus
		//
		template<typename T, typename U>
		inline SPROUT_CONSTEXPR typename sprout::arithmetic_promote<T, U>::type
		plus(T const& lhs, U const& rhs) {
			typedef typename sprout::arithmetic_promote<T, U>::type type;
			return lhs > 0 && rhs > 0 && std::numeric_limits<type>::max() - lhs < rhs
					? std::numeric_limits<type>::max()
				: lhs < 0 && rhs < 0 && std::numeric_limits<type>::min() - lhs > rhs
					? std::numeric_limits<type>::min()
				: lhs + rhs
				;
		}

		//
		// multiplies
		//
		template<typename T, typename U>
		inline SPROUT_CONSTEXPR typename sprout::arithmetic_promote<T, U>::type
		multiplies(T const& lhs, U const& rhs) {
			typedef typename sprout::arithmetic_promote<T, U>::type type;
			return lhs > 0 && rhs > 0 && std::numeric_limits<type>::max() / lhs + (std::numeric_limits<type>::max() % lhs ? 1 : 0) <= rhs
					? std::numeric_limits<type>::max()
				: lhs > 0 && rhs < 0 && std::numeric_limits<type>::min() / rhs + (std::numeric_limits<type>::min() % rhs ? 1 : 0) <= lhs
					? std::numeric_limits<type>::min()
				: lhs < 0 && rhs > 0 && std::numeric_limits<type>::min() / lhs + (std::numeric_limits<type>::min() % lhs ? 1 : 0) <= rhs
					? std::numeric_limits<type>::min()
				: lhs < 0 && rhs < 0 && -(std::numeric_limits<type>::min() / rhs + (std::numeric_limits<type>::min() % rhs ? 1 : 0)) >= lhs
					? std::numeric_limits<type>::max()
				: lhs * rhs
				;
		}
	}	// namespace limited
}	// namespace sprout

#endif	// #ifndef SPROUT_INTEGER_LIMITED_HPP
