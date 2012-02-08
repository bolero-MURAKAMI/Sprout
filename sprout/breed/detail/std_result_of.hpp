#ifndef SPROUT_BREED_DETAIL_STD_RESULT_OF_HPP
#define SPROUT_BREED_DETAIL_STD_RESULT_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename F>
			struct std_result_of
				: public std::result_of<F>
			{};
		}	// namespace detail
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_DETAIL_STD_RESULT_OF_HPP
