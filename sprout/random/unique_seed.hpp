#ifndef SPROUT_RANDOM_UNIQUE_SEED_HPP
#define SPROUT_RANDOM_UNIQUE_SEED_HPP

#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/preprocessor/unique_string.hpp>

//
// SPROUT_UNIQUE_SEED
//
#define SPROUT_UNIQUE_SEED (::sprout::hash_value(SPROUT_PP_UNIQUE_STRING))

#endif	// #ifndef SPROUT_RANDOM_UNIQUE_SEED_HPP

