/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUE_TRAITS_HPP
#define SPROUT_FUNCTIONAL_HASH_HASH_VALUE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl hash_value(...);
}	// namespace sprout_adl

namespace sprout_hash_detail {
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	call_hash_value(T const& v) {
		using sprout::hash_value;
		using sprout_adl::hash_value;
		return hash_value(v);
	}
}	// namespace sprout_hash_detail

namespace sprout {
	//
	// hash_value_traits
	//
	template<typename T>
	struct hash_value_traits {
	public:
		static SPROUT_CONSTEXPR std::size_t
		hash_value(T const& v) {
			return sprout_hash_detail::call_hash_value(v);
		}
	};
	template<typename T>
	struct hash_value_traits<T const>
		: public sprout::hash_value_traits<T>
	{};
	template<typename T>
	struct hash_value_traits<T volatile>
		: public sprout::hash_value_traits<T>
	{};
	template<typename T>
	struct hash_value_traits<T const volatile>
		: public sprout::hash_value_traits<T>
	{};
}	// namespace sprout

#include <sprout/functional/hash/hash_range.hpp>
#include <sprout/functional/hash/hash_value.hpp>

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_HASH_VALUE_TRAITS_HPP
