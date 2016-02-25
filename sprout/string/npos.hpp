/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_STRING_NPOS_HPP
#define SPROUT_STRING_NPOS_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_uint.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	//
	// npos_t
	// npos
	//
	struct npos_t {
	public:
		template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
		struct get
			: public sprout::integral_constant<UIntType, UIntType(-1)>
		{};
	public:
		template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
		SPROUT_CONSTEXPR operator UIntType() const {
			return UIntType(-1);
		}
	};
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::npos_t npos = {};
	}	// anonymous-namespace

	//
	// operator==
	// operator!=
	// operator<
	// operator>
	// operator<=
	// operator>=
	//
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator==(UIntType const& lhs, sprout::npos_t rhs) {
		return lhs == UIntType(rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::npos_t lhs, UIntType const& rhs) {
		return rhs == lhs;
	}
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::npos_t, sprout::npos_t) {
		return true;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator!=(UIntType const& lhs, sprout::npos_t rhs) {
		return !(lhs == rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::npos_t lhs, UIntType const& rhs) {
		return !(lhs == rhs);
	}
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::npos_t lhs, sprout::npos_t rhs) {
		return !(lhs == rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<(UIntType const& lhs, sprout::npos_t rhs) {
		return lhs < UIntType(rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::npos_t lhs, UIntType const& rhs) {
		return rhs == lhs;
	}
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::npos_t, sprout::npos_t) {
		return false;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>(UIntType const& lhs, sprout::npos_t rhs) {
		return rhs < lhs;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::npos_t lhs, UIntType const& rhs) {
		return rhs < lhs;
	}
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::npos_t lhs, sprout::npos_t rhs) {
		return rhs < lhs;
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<=(UIntType const& lhs, sprout::npos_t rhs) {
		return !(rhs < lhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::npos_t lhs, UIntType const& rhs) {
		return !(rhs < lhs);
	}
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::npos_t lhs, sprout::npos_t rhs) {
		return !(rhs < lhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>=(UIntType const& lhs, sprout::npos_t rhs) {
		return !(lhs < rhs);
	}
	template<typename UIntType, typename sprout::enabler_if<sprout::is_uint<UIntType>::value>::type = sprout::enabler>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::npos_t lhs, UIntType const& rhs) {
		return !(lhs < rhs);
	}
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::npos_t lhs, sprout::npos_t rhs) {
		return !(lhs < rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_STRING_NPOS_HPP
