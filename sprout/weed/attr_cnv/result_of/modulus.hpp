#ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_MODULUS_HPP
#define SPROUT_WEED_ATTR_CNV_RESULT_OF_MODULUS_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/weed/attr_cnv/result_of/times.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace result_of {
				//
				// modulus
				//
				template<std::size_t Limit, typename T, typename = void>
				struct modulus
					: public sprout::weed::attr_cnv::result_of::times<Limit, T>
				{};
			}	// namespace result_of
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_MODULUS_HPP
