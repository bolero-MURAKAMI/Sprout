/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_HASH_HPP
#define SPROUT_VARIANT_HASH_HPP

#include <functional>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash.hpp>
#include <sprout/variant/variant.hpp>
#include <sprout/variant/static_visitor.hpp>
#include <sprout/variant/apply_visitor.hpp>

namespace sprout {
	namespace detail {
		class variant_hash_visitor
			: public sprout::static_visitor<std::size_t>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR std::size_t operator()(T const& t) const {
				return sprout::to_hash(t);
			}
		};
	}	// namespace detail
	//
	// hash_value
	//
	template<typename... Types>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::variant<Types...> const& v) {
		return sprout::hash_combine(
			sprout::apply_visitor(sprout::detail::variant_hash_visitor(), v),
			v.which()
			);
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<typename... Types>
	struct hash<sprout::variant<Types...> >
		: public sprout::hash<sprout::variant<Types...> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_VARIANT_HASH_HPP
