/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_TRAITS_CONSTRUCT_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_TRAITS_CONSTRUCT_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/internal_begin.hpp>
#include <sprout/container/internal_end.hpp>
#include <sprout/container/internal_begin_offset.hpp>
#include <sprout/container/internal_end_offset.hpp>
#include <sprout/container/internal_begin_offset_backward.hpp>
#include <sprout/container/internal_end_offset_backward.hpp>
#include <sprout/iterator/remake_iterator.hpp>
#include <sprout/iterator/type_traits/category.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/tpp/algorithm/all_of.hpp>

namespace sprout {
	//
	// container_construct_traits
	//
	namespace detail {
		template<typename Container, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_fixed_container<Container>::value,
			typename sprout::container_construct_traits<Container>::copied_type
		>::type
		default_make_container(Args&&... args) {
			typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
			return copied_type{{SPROUT_FORWARD(Args, args)...}};
		}
		template<typename Container, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::is_fixed_container<Container>::value,
			typename sprout::container_construct_traits<Container>::copied_type
		>::type
		default_make_container(Args&&... args) {
			typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
			return copied_type{SPROUT_FORWARD(Args, args)...};
		}

		template<typename Container, typename Cont, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::is_fixed_container<Container>::value,
			typename sprout::container_construct_traits<Container>::copied_type
		>::type
		default_remake_container(Cont&&, typename sprout::container_traits<Container>::difference_type, Args&&... args) {
			return sprout::container_construct_traits<Container>::make(SPROUT_FORWARD(Args, args)...);
		}
		template<typename Container, typename Cont, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::is_fixed_container<Container>::value
				&& !(sizeof...(Args) == 2 && sprout::tpp::all_of<sprout::is_input_iterator<typename std::remove_reference<Args>::type>...>::value)
				,
			typename sprout::container_construct_traits<Container>::copied_type
		>::type
		default_remake_container(Cont&&, typename sprout::container_traits<Container>::difference_type, Args&&... args) {
			return sprout::container_construct_traits<Container>::make(SPROUT_FORWARD(Args, args)...);
		}
		template<typename Container, typename Cont, typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			!sprout::is_fixed_container<Container>::value,
			typename sprout::container_construct_traits<Container>::copied_type
		>::type
		default_remake_container(Cont&& cont, typename sprout::container_traits<Container>::difference_type, InputIterator first, InputIterator last) {
			typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
			return copied_type(
				sprout::make_remake_iterator(
					sprout::internal_begin(cont), first,
					first, last,
					sprout::internal_begin_offset(cont), sprout::internal_end_offset(cont)
					),
				sprout::make_remake_iterator(
					sprout::internal_end(cont), last,
					first, last,
					sprout::internal_begin_offset_backward(cont), sprout::internal_end_offset_backward(cont)
					)
				);
		}

		template<typename Container>
		struct container_construct_traits_impl {
		public:
			typedef Container copied_type;
		public:
			template<typename Cont>
			static SPROUT_CONSTEXPR copied_type
			deep_copy(Cont&& cont) {
				return SPROUT_FORWARD(Cont, cont);
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type
			make(Args&&... args) {
				return sprout::detail::default_make_container<Container>(SPROUT_FORWARD(Args, args)...);
			}
			template<typename Cont, typename... Args>
			static SPROUT_CONSTEXPR copied_type
			remake(Cont&& cont, typename sprout::container_traits<Container>::difference_type size, Args&&... args) {
				return sprout::detail::default_remake_container<Container>(
					SPROUT_FORWARD(Cont, cont), size,
					SPROUT_FORWARD(Args, args)...
					);
			}
		};
	}	// namespace detail

	template<typename Container>
	struct container_construct_traits
		: public sprout::detail::container_construct_traits_impl<Container>
	{};
	template<typename Container>
	struct container_construct_traits<Container const>
		: public sprout::container_construct_traits<Container>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_CONSTRUCT_TRAITS_HPP
