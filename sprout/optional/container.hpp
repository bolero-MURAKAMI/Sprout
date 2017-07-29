/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_CONTAINER_HPP
#define SPROUT_OPTIONAL_CONTAINER_HPP

#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/optional/optional.hpp>
#include <sprout/container/traits.hpp>

namespace sprout {
	//
	// container_construct_traits
	//
	template<typename T>
	struct container_construct_traits<sprout::optional<T> > {
	public:
		typedef sprout::optional<T> copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type
		deep_copy(Cont&& cont) {
			return SPROUT_FORWARD(Cont, cont);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type
		make(Args&&... args) {
			return copied_type(SPROUT_FORWARD(Args, args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type
		remake(Cont&&, typename sprout::container_traits<sprout::optional<T> >::difference_type, Args&&... args) {
			return copied_type(SPROUT_FORWARD(Args, args)...);
		}
	};

	//
	// container_transform_traits
	//
	template<typename T>
	struct container_transform_traits<sprout::optional<T> > {
	public:
		template<typename Type>
		struct rebind_type {
		public:
			typedef sprout::optional<Type> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_CONTAINER_HPP
