/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_SUB_ARRAY_CONTAINER_HPP
#define SPROUT_SUB_ARRAY_CONTAINER_HPP

#include <utility>
#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>

namespace sprout {
	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits<sprout::sub_array<Container> > {
	private:
		typedef typename sprout::sub_array<Container>::internal_type internal_type;
		typedef typename sprout::container_construct_traits<internal_type>::copied_type internal_copied_type;
	public:
		typedef sprout::sub_array<internal_copied_type> copied_type;
	private:
		static SPROUT_CONSTEXPR copied_type
		make_impl(internal_copied_type const& internal_copied) {
			return copied_type(internal_copied, sprout::begin(internal_copied), sprout::end(internal_copied));
		}
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type
		remake_impl(
			Cont&& cont,
			typename sprout::container_traits<sprout::sub_array<Container> >::difference_type size,
			internal_copied_type const& internal_copied
			)
		{
			return copied_type(
				internal_copied,
				sprout::next(sprout::begin(internal_copied), sprout::internal_begin_offset(cont)),
				sprout::next(sprout::begin(internal_copied), sprout::internal_begin_offset(cont) + size)
				);
		}
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type
		deep_copy(Cont&& cont) {
			return copied_type(
				sprout::deep_copy(sprout::get_internal(cont)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont)
				);
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type
		make(Args&&... args) {
			return make_impl(
				sprout::make<internal_type>(SPROUT_FORWARD(Args, args)...)
				);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type
		remake(Cont&& cont, typename sprout::container_traits<sprout::sub_array<Container> >::difference_type size, Args&&... args) {
			return remake_impl(
				SPROUT_FORWARD(Cont, cont),
				size,
				sprout::remake<internal_type>(cont, size, SPROUT_FORWARD(Args, args)...)
				);
		}
	};

	//
	// container_transform_traits
	//
	template<typename Container>
	struct container_transform_traits<sprout::sub_array<Container> > {
	private:
		typedef typename sprout::sub_array<Container>::internal_type internal_type;
		typedef typename sprout::container_construct_traits<internal_type>::copied_type internal_copied_type;
	public:
		template<typename sprout::container_traits<sprout::sub_array<Container> >::size_type Size>
		struct rebind_size {
		public:
			typedef sprout::sub_array<
				typename sprout::container_transform_traits<internal_copied_type>::template rebind_size<Size>::type
			> type;
		};
		template<typename Type>
		struct rebind_type {
		public:
			typedef sprout::sub_array<
				typename sprout::container_transform_traits<internal_copied_type>::template rebind_type<Type>::type
			> type;
		};
	};

	//
	// sub_container_traits
	//
	template<typename Container>
	struct sub_container_traits<sprout::sub_array<Container> > {
	private:
		static typename sprout::sub_array<Container>::param_type
		call(sprout::sub_array<Container>& cont) {
			return cont.get_internal();
		}
		static SPROUT_CONSTEXPR typename sprout::sub_array<Container>::const_param_type
		call(sprout::sub_array<Container> const& cont) {
			return cont.get_internal();
		}
	public:
		template<typename Cont>
		struct internal {
		public:
			typedef decltype(call(std::declval<Cont&&>())) type;
		};
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR typename internal<Cont>::type
		get_internal(Cont&& cont) {
			return call(SPROUT_FORWARD(Cont, cont));
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_SUB_ARRAY_CONTAINER_HPP
