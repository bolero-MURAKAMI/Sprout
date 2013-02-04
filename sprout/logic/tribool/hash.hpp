#ifndef SPROUT_LOGIC_TRIBOOL_HASH_HPP
#define SPROUT_LOGIC_TRIBOOL_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/logic/tribool/tribool.hpp>

namespace sprout {
	//
	// hash_value
	//
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::logic::indeterminate_keyword_t) {
		return sprout::logic::tribool::indeterminate_value;
	}
	namespace logic {
		//
		// hash_value
		//
		inline SPROUT_CONSTEXPR std::size_t
		hash_value(sprout::logic::tribool const& v) {
			return sprout::to_hash(v.value);
		}
	}	// namespace logic
}	// namespace sprout

#endif	// #ifndef SPROUT_LOGIC_TRIBOOL_HASH_HPP
