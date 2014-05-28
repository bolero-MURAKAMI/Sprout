/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_UNIFORM_TYPES_HPP
#define SPROUT_TYPE_UNIFORM_TYPES_HPP

#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/iterator.hpp>
#include <sprout/type/iterator/index_iterator.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace types {
		//
		// uniform_types
		//
		template<typename T, std::size_t N>
		struct uniform_types {
		public:
			typedef uniform_types type;
			typedef sprout::types::index_iterator<uniform_types, 0> begin;
			typedef sprout::types::index_iterator<uniform_types, N> end;
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t static_size = N;
		};
		template<typename T, std::size_t N>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::types::uniform_types<T, N>::static_size;

		//
		// rebind_types
		//
		template<typename T, std::size_t N>
		struct rebind_types<sprout::types::uniform_types<T, N> > {
		public:
			template<typename Head, typename... Tail>
			struct apply {
			public:
				typedef sprout::types::uniform_types<Head, 1 + sizeof...(Tail)> type;
			};
		};
	}	// namespace types

	using sprout::types::uniform_types;
	using sprout::types::rebind_types;
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename T, std::size_t N>
	struct tuple_size<sprout::types::uniform_types<T, N> >
		: public sprout::integral_constant<std::size_t, N>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename T, std::size_t N>
	struct tuple_element<I, sprout::types::uniform_types<T, N> >
		: public std::conditional<(I < N), sprout::identity<T>, sprout::detail::nil_base>::type
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_TYPE_UNIFORM_TYPES_HPP
