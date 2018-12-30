/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_CONTAINER_HPP
#define SPROUT_VALARRAY_CONTAINER_HPP

#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/valarray/valarray.hpp>
#include <sprout/container/traits.hpp>

namespace sprout {
	//
	// container_construct_traits
	//
	template<typename T, std::size_t N>
	struct container_construct_traits<sprout::valarray<T, N> > {
	public:
		typedef sprout::valarray<T, N> copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type
		deep_copy(Cont&& cont) {
			return SPROUT_FORWARD(Cont, cont);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type
		make(Args&&... args) {
			typedef sprout::detail::make_construct_impl<copied_type> impl_type;
			return impl_type::make(SPROUT_FORWARD(Args, args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type
		remake(Cont&&, typename sprout::container_traits<sprout::valarray<T, N> >::difference_type size, Args&&... args) {
			typedef sprout::detail::make_construct_impl<copied_type> impl_type;
			return impl_type::sized_make(static_cast<typename copied_type::size_type>(size), SPROUT_FORWARD(Args, args)...);
		}
	};

	//
	// container_transform_traits
	//
	template<typename T, std::size_t N>
	struct container_transform_traits<sprout::valarray<T, N> > {
	public:
		template<typename sprout::container_traits<sprout::valarray<T, N> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::valarray<T, Size> type;
		};
		template<typename Type>
		struct rebind_type {
		public:
			typedef sprout::valarray<Type, N> type;
		};
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_CONTAINER_HPP
