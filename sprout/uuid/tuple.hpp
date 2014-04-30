/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UUID_TUPLE_HPP
#define SPROUT_UUID_TUPLE_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/uuid/uuid.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I>
	inline SPROUT_CONSTEXPR sprout::uuids::uuid::value_type&
	tuple_get(sprout::uuids::uuid& t) SPROUT_NOEXCEPT {
		static_assert(I < 16, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR sprout::uuids::uuid::value_type const&
	tuple_get(sprout::uuids::uuid const& t) SPROUT_NOEXCEPT {
		static_assert(I < 16, "tuple_get: index out of range");
		return t[I];
	}
	template<std::size_t I>
	inline SPROUT_CONSTEXPR sprout::uuids::uuid::value_type&&
	tuple_get(sprout::uuids::uuid&& t) SPROUT_NOEXCEPT {
		return sprout::move(sprout::tuples::get<I>(t));
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<>
	struct tuple_size<sprout::uuids::uuid> {
	public:
		typedef sprout::integral_constant<std::size_t, 16> type;
		SPROUT_STATIC_CONSTEXPR std::size_t value = type::value;
	};

	//
	// tuple_element
	//
	template<std::size_t I>
	struct tuple_element<I, sprout::uuids::uuid> {
		static_assert(I < 16, "tuple_element<>: index out of range");
	public:
		typedef sprout::uuids::uuid::value_type type;
	};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_UUID_TUPLE_HPP
