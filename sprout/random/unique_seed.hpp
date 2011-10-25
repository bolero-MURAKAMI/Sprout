#ifndef SPROUT_RANDOM_UNIQUE_SEED_HPP
#define SPROUT_RANDOM_UNIQUE_SEED_HPP

#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	include <cstddef>
#	include <type_traits>
#endif
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/preprocessor/unique_string.hpp>

//
// SPROUT_UNIQUE_SEED
//
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR
#	define SPROUT_UNIQUE_SEED (::std::integral_constant< ::std::size_t, ::sprout::hash_value(SPROUT_PP_UNIQUE_STRING)>::value)
#else
#	define SPROUT_UNIQUE_SEED (::sprout::hash_value(SPROUT_PP_UNIQUE_STRING))
#endif

#endif	// #ifndef SPROUT_RANDOM_UNIQUE_SEED_HPP

