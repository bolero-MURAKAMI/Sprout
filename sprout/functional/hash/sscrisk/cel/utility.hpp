#ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_UTILITY_HPP
#define SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_UTILITY_HPP

#include <cstddef>
#include <sscrisk/cel/utility.hpp>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_value_traits.hpp>
#include <sprout/functional/hash/hash_values.hpp>

namespace sprout {
	//
	// hash_value_traits
	//
	template<typename T1, typename T2>
	struct hash_value_traits<sscrisk::cel::pair<T1, T2> > {
	public:
		static SPROUT_CONSTEXPR std::size_t
		hash_value(sscrisk::cel::pair<T1, T2> const& v) {
			return sprout::hash_values(v.first, v.second);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_SSCRISK_CEL_UTILITY_HPP
