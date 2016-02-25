/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STATEFUL_TYPE_INDEX_HPP
#define SPROUT_STATEFUL_TYPE_INDEX_HPP

#include <typeinfo>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash.hpp>
#include <sprout/stateful/typed_id.hpp>

namespace sprout {
#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

	class type_index {
	private:
		int id_;
	public:
		template<typename T>
		explicit SPROUT_CONSTEXPR type_index(sprout::typed_id<T>) SPROUT_NOEXCEPT
			: id_(sprout::typed_id<T>::value)
		{}
		explicit SPROUT_CONSTEXPR type_index(int id) SPROUT_NOEXCEPT
			: id_(id)
		{}
		SPROUT_CONSTEXPR bool
		operator==(sprout::type_index const& rhs) const SPROUT_NOEXCEPT {
			return id_ == rhs.id_;
		}
		SPROUT_CONSTEXPR bool
		operator!=(sprout::type_index const& rhs) const SPROUT_NOEXCEPT {
			return !(*this == rhs);
		}
		SPROUT_CONSTEXPR bool
		operator<(sprout::type_index const& rhs) const SPROUT_NOEXCEPT {
			return id_ < rhs.id_;
		}
		SPROUT_CONSTEXPR bool
		operator<=(sprout::type_index const& rhs) const SPROUT_NOEXCEPT {
			return !(rhs < *this);
		}
		SPROUT_CONSTEXPR bool
		operator>(sprout::type_index const& rhs) const SPROUT_NOEXCEPT {
			return rhs < *this;
		}
		SPROUT_CONSTEXPR bool
		operator>=(sprout::type_index const& rhs) const SPROUT_NOEXCEPT {
			return !(*this < rhs);
		}
		SPROUT_CONSTEXPR std::size_t
		hash_code() const SPROUT_NOEXCEPT {
			return sprout::hash_value(id_);
		}
	} ;

#endif
}	// namespace sprout

#ifndef SPROUT_CONFIG_DISABLE_CONSTEXPR

namespace sprout {
	//
	// hash_value
	//
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::type_index const& v) {
		return v.hash_code();
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
	template<>
	struct hash<sprout::type_index>
		: public sprout::hash<sprout::type_index>
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif

#endif	// #ifndef SPROUT_STATEFUL_TYPE_INDEX_HPP
