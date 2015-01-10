/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_INDEX_TUPLE_INTEGER_SEQUENCE_HPP
#define SPROUT_INDEX_TUPLE_INTEGER_SEQUENCE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	//
	// integer_sequence
	//
	template<typename T, T... Is>
	struct integer_sequence {
	public:
		typedef integer_sequence type;
		template<T... J>
		struct rebind
			: public integer_sequence<T, J...>
		{};
	public:
		static SPROUT_CONSTEXPR type make() SPROUT_NOEXCEPT {
			return type();
		}
	public:
		typedef T value_type;
		template<typename Seq>
		struct transfer
			: public Seq::template rebind<Is...>
		{};
	public:
		SPROUT_STATIC_CONSTEXPR std::size_t static_size = sizeof...(Is);
	public:
		static SPROUT_CONSTEXPR size_t size() SPROUT_NOEXCEPT {
			return static_size;
		}
	};
	template<typename T, T... Is>
	SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::integer_sequence<T, Is...>::static_size;
}	// namespace sprout

#endif	// #ifndef SPROUT_INDEX_TUPLE_INTEGER_SEQUENCE_HPP
