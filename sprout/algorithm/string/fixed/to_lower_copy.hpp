#ifndef SPROUT_ALGORITHM_STRING_FIXED_TO_LOWER_COPY_HPP
#define SPROUT_ALGORITHM_STRING_FIXED_TO_LOWER_COPY_HPP

#include <sprout/config.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>
#include <sprout/algorithm/fixed/transform.hpp>
#include <sprout/pit/pit.hpp>
#include <sprout/ctype/functor.hpp>

namespace sprout {
	namespace algorithm {
		namespace fixed {
			//
			// to_lower_copy
			//
			template<typename InputIterator, typename Result>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			to_lower_copy(InputIterator first, InputIterator last, Result const& result) {
				return sprout::fixed::transform(first, last, sprout::ctypes::to_lower<>(), result);
			}

			template<typename Result, typename InputIterator>
			inline SPROUT_CONSTEXPR typename sprout::fixed::result_of::algorithm<Result>::type
			to_lower_copy(InputIterator first, InputIterator last) {
				return sprout::algorithm::fixed::to_lower_copy(first, last, sprout::pit<Result>());
			}
		}	// namespace fixed

		using sprout::algorithm::fixed::to_lower_copy;
	}	// namespace algorithm

	namespace fixed {
		using sprout::algorithm::fixed::to_lower_copy;
	}	// namespace fixed

	using sprout::algorithm::fixed::to_lower_copy;
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_STRING_FIXED_TO_LOWER_COPY_HPP
