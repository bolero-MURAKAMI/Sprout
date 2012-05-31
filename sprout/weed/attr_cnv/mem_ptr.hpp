#ifndef SPROUT_WEED_ATTR_CNV_MEM_PTR_HPP
#define SPROUT_WEED_ATTR_CNV_MEM_PTR_HPP

#include <sprout/config.hpp>
#include <sprout/weed/attr_cnv/result_of/mem_ptr.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			//
			// mem_ptr
			//
			template<typename T, typename U>
			inline SPROUT_CONSTEXPR typename sprout::weed::attr_cnv::result_of::mem_ptr<T, U>::type
			mem_ptr(T const& t, U const& u) {
				return u(t);
			}
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_MEM_PTR_HPP
