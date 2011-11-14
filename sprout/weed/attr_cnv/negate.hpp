#ifndef SPROUT_WEED_ATTR_CNV_NEGATE_HPP
#define SPROUT_WEED_ATTR_CNV_NEGATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>
#include <sprout/weed/attr_cnv/result_of/negate.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			//
			// negate
			//
			// !unused -> unused
			template<typename T>
			SPROUT_CONSTEXPR inline typename std::enable_if<
				sprout::weed::traits::is_unused<T>::value,
				typename sprout::weed::attr_cnv::result_of::negate<T>::type
			>::type negate(T const& t, bool cond) {
				return sprout::weed::unused();
			}
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_NEGATE_HPP
