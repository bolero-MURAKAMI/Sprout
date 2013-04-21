#ifndef SPROUT_LOGIC_TRIBOOL_HASH_HPP
#define SPROUT_LOGIC_TRIBOOL_HASH_HPP

#include <cstddef>
#include <functional>
#include <sprout/config.hpp>
#include <sprout/logic/tribool/tribool.hpp>
#include <sprout/functional/hash.hpp>

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

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<>
	struct hash<sprout::logic::indeterminate_keyword_t>
		: public sprout::hash<sprout::logic::indeterminate_keyword_t>
	{};
	template<>
	struct hash<sprout::logic::tribool>
		: public sprout::hash<sprout::logic::tribool>
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_LOGIC_TRIBOOL_HASH_HPP
