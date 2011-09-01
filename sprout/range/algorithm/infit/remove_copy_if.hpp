#ifndef SPROUT_RANGE_ALGORITHM_INFIT_REMOVE_COPY_IF_HPP
#define SPROUT_RANGE_ALGORITHM_INFIT_REMOVE_COPY_IF_HPP

#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/algorithm/infit/remove_copy_if.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace range {
		namespace infit {
			//
			// remove_copy_if
			//
			template<typename Input, typename Result, typename Predicate>
			SPROUT_CONSTEXPR inline sprout::sub_array<typename sprout::fixed_container_traits<Result>::fixed_container_type> remove_copy_if(
				Input const& input,
				Result const& result,
				Predicate pred
				)
			{
				return sprout::infit::remove_copy_if(sprout::begin(input), sprout::end(input), result, pred);
			}
		}	// namespace infit
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_ALGORITHM_INFIT_REMOVE_COPY_IF_HPP
