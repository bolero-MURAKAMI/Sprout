#ifndef SPROUT_TYPE_TRAITS_COMMON_DECAY_HPP
#define SPROUT_TYPE_TRAITS_COMMON_DECAY_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// common_decay
	//
	template<typename... Types>
	struct common_decay
		: public std::decay<typename std::common_type<Types...>::type>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename... Types>
	using common_decay_ = typename sprout::common_decay<Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_COMMON_DECAY_HPP
