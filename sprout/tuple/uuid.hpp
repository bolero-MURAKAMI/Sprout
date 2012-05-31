#ifndef SPROUT_TUPLE_UUID_HPP
#define SPROUT_TUPLE_UUID_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/uuid/uuid.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I>
		inline SPROUT_CONSTEXPR sprout::uuids::uuid::value_type&
		get(sprout::uuids::uuid& t) SPROUT_NOEXCEPT {
			static_assert(I < 16, "get: index out of range");
			return t[I];
		}
		template<std::size_t I>
		inline SPROUT_CONSTEXPR sprout::uuids::uuid::value_type const&
		get(sprout::uuids::uuid const& t) SPROUT_NOEXCEPT {
			static_assert(I < 16, "get: index out of range");
			return t[I];
		}
		template<std::size_t I>
		inline SPROUT_CONSTEXPR sprout::uuids::uuid::value_type&&
		get(sprout::uuids::uuid&& t) SPROUT_NOEXCEPT {
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_UUID_HPP
