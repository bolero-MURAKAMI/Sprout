/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TYPE_TUPLE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type/iterator.hpp>
#include <sprout/type/iterator/index_iterator.hpp>
#include <sprout/type/type_tuple_decl.hpp>

namespace sprout {
	namespace types {
		//
		// type_tuple
		//
		template<typename... Types>
		struct type_tuple {
		public:
			typedef type_tuple type;
			typedef sprout::types::index_iterator<type_tuple, 0> begin;
			typedef sprout::types::index_iterator<type_tuple, sizeof...(Types)> end;
		public:
			template<typename... UTypes>
			struct apply
				: public sprout::identity<type_tuple<Types..., UTypes...> >
			{};
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t static_size = sizeof...(Types);
		};
		template<typename... Types>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::types::type_tuple<Types...>::static_size;
	}	// namespace types

	using sprout::types::type_tuple;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
