#ifndef SPROUT_TYPE_FUNCTIONAL_LESS_HPP
#define SPROUT_TYPE_FUNCTIONAL_LESS_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// less
		//
		template<typename T, typename U>
		struct less
			: public std::integral_constant<bool, ((T::value) < (U::value))>
		{};

		//
		// less_
		//
		struct less_ {
		public:
			template<typename T, typename U>
			struct apply
				: public sprout::types::less<T, U>
			{};
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_FUNCTIONAL_LESS_HPP
