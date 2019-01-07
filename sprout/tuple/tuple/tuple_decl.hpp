/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP

#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/detail/nil_base.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/swallow.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/utility/pair/pair_fwd.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_nothrow_copy_constructible.hpp>
#include <sprout/type_traits/is_convert_constructible.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/tpp/algorithm/all_of.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>
#include <sprout/tuple/flexibly_construct.hpp>
#include <sprout/tuple/default_construct.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<typename... Types>
			class tuple_access;

			struct from_tuple_construct_t {};

			template<sprout::index_t I, typename IdentityType>
			struct element_holder {
			public:
				typedef typename IdentityType::type value_type;
			private:
				value_type value_;
			public:
				explicit SPROUT_CONSTEXPR element_holder()
					: value_()
				{}
				element_holder(element_holder const&) = default;
				element_holder(element_holder&&) = default;
				template<typename T>
				explicit SPROUT_CONSTEXPR element_holder(T&& value)
					: value_(SPROUT_FORWARD(T, value))
				{}
				explicit SPROUT_CONSTEXPR element_holder(sprout::tuples::default_construct_t)
					: value_()
				{}
			protected:
				static SPROUT_CONSTEXPR value_type&
				get(element_holder& t) {
					return t.value_;
				}
				static SPROUT_CONSTEXPR value_type&&
				get(element_holder&& t) {
					return sprout::move(t.value_);
				}
				static SPROUT_CONSTEXPR value_type const&
				get(element_holder const& t) {
					return t.value_;
				}
			};

			template<typename IndexTuple, typename... Types>
			class tuple_base;
			template<sprout::index_t... Indexes, typename... Types>
			class tuple_base<sprout::index_tuple<Indexes...>, Types...>
				: public sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >...
			{
				template<typename IndexTuple, typename... UTypes>
				friend class sprout::tuples::detail::tuple_base;
			protected:
				template<sprout::index_t I, typename IdentityType>
				static IdentityType element_helper(sprout::tuples::detail::element_holder<I, IdentityType> const&);
				template<sprout::index_t I>
				static sprout::detail::nil_base element_helper(...);
				template<std::size_t I>
				struct element
					: public sprout::identity<decltype(element_helper<I>(std::declval<tuple_base>()))>::type
				{};
				struct size
					: public sprout::integral_constant<std::size_t, sizeof...(Types)>
				{};
			public:
				SPROUT_CONSTEXPR tuple_base()
					: sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >()...
				{}
				template<typename... UTypes>
				explicit SPROUT_CONSTEXPR tuple_base(UTypes&&... args)
					: sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >(SPROUT_FORWARD(UTypes, args))...
				{}
				template<typename Tuple>
				SPROUT_CONSTEXPR tuple_base(sprout::tuples::detail::from_tuple_construct_t, Tuple&& t)
					: sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >(std::decay<Tuple>::type::template get<Indexes>(SPROUT_FORWARD(Tuple, t)))...
				{}

				template<
					typename... UTypes, sprout::index_t... Is, sprout::index_t... Js,
					typename sprout::enabler_if<(sizeof...(Types) == sizeof...(UTypes))>::type = sprout::enabler
				>
				explicit SPROUT_CONSTEXPR tuple_base(sprout::tuples::flexibly_construct_t, sprout::index_tuple<Is...>, sprout::index_tuple<Js...>, UTypes&&... args)
					: sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >(SPROUT_FORWARD(UTypes, args))...
				{}
				template<
					typename... UTypes, sprout::index_t... Is, sprout::index_t... Js,
					typename sprout::enabler_if<(sizeof...(Types) > sizeof...(UTypes))>::type = sprout::enabler
				>
				explicit SPROUT_CONSTEXPR tuple_base(sprout::tuples::flexibly_construct_t, sprout::index_tuple<Is...>, sprout::index_tuple<Js...>, UTypes&&... args)
					: sprout::tuples::detail::element_holder<Is, sprout::identity<typename sprout::pack_element<Is, Types...>::type> >(SPROUT_FORWARD(UTypes, args))...
					, sprout::tuples::detail::element_holder<Js, sprout::identity<typename sprout::pack_element<Js, Types...>::type> >()...
				{}
				template<
					typename... UTypes, sprout::index_t... Is, sprout::index_t... Js,
					typename sprout::enabler_if<(sizeof...(Types) < sizeof...(UTypes))>::type = sprout::enabler
				>
				explicit SPROUT_CONSTEXPR tuple_base(sprout::tuples::flexibly_construct_t, sprout::index_tuple<Is...>, sprout::index_tuple<Js...>, UTypes&&... args)
					: sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >(sprout::pack_get<Indexes>(SPROUT_FORWARD(UTypes, args)...))...
				{}

				template<
					typename Tuple, sprout::index_t... Is, sprout::index_t... Js,
					typename sprout::enabler_if<(sizeof...(Types) == std::decay<Tuple>::type::size::value)>::type = sprout::enabler
				>
				explicit SPROUT_CONSTEXPR tuple_base(sprout::tuples::detail::from_tuple_construct_t, sprout::tuples::flexibly_construct_t, sprout::index_tuple<Is...>, sprout::index_tuple<Js...>, Tuple&& t)
					: sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >(std::decay<Tuple>::type::template get<Indexes>(SPROUT_FORWARD(Tuple, t)))...
				{}
				template<
					typename Tuple, sprout::index_t... Is, sprout::index_t... Js,
					typename sprout::enabler_if<(sizeof...(Types) > std::decay<Tuple>::type::size::value)>::type = sprout::enabler
				>
				explicit SPROUT_CONSTEXPR tuple_base(sprout::tuples::detail::from_tuple_construct_t, sprout::tuples::flexibly_construct_t, sprout::index_tuple<Is...>, sprout::index_tuple<Js...>, Tuple&& t)
					: sprout::tuples::detail::element_holder<Is, sprout::identity<typename sprout::pack_element<Is, Types...>::type> >(std::decay<Tuple>::type::template get<Is>(SPROUT_FORWARD(Tuple, t)))...
					, sprout::tuples::detail::element_holder<Js, sprout::identity<typename sprout::pack_element<Js, Types...>::type> >()...
				{}
				template<
					typename Tuple, sprout::index_t... Is, sprout::index_t... Js,
					typename sprout::enabler_if<(sizeof...(Types) < std::decay<Tuple>::type::size::value)>::type = sprout::enabler
				>
				explicit SPROUT_CONSTEXPR tuple_base(sprout::tuples::detail::from_tuple_construct_t, sprout::tuples::flexibly_construct_t, sprout::index_tuple<Is...>, sprout::index_tuple<Js...>, Tuple&& t)
					: sprout::tuples::detail::element_holder<Indexes, sprout::identity<Types> >(std::decay<Tuple>::type::template get<Indexes>(SPROUT_FORWARD(Tuple, t)))...
				{}
			private:
				template<std::size_t I, typename IdentityType>
				static SPROUT_CONSTEXPR typename element<I>::type&
				get_impl(sprout::tuples::detail::element_holder<I, IdentityType>& value) {
					return sprout::tuples::detail::element_holder<I, IdentityType>::get(value);
				}
				template<std::size_t I, typename IdentityType>
				static SPROUT_CONSTEXPR typename element<I>::type&&
				get_impl(sprout::tuples::detail::element_holder<I, IdentityType>&& value) {
					return sprout::tuples::detail::element_holder<I, IdentityType>::get(sprout::move(value));
				}
				template<std::size_t I, typename IdentityType>
				static SPROUT_CONSTEXPR typename element<I>::type const&
				get_impl(sprout::tuples::detail::element_holder<I, IdentityType> const& value) {
					return sprout::tuples::detail::element_holder<I, IdentityType>::get(value);
				}
			protected:
				template<std::size_t I>
				static SPROUT_CONSTEXPR typename element<I>::type&
				get(tuple_base& t) {
					return get_impl<I>(t);
				}
				template<std::size_t I>
				static SPROUT_CONSTEXPR typename element<I>::type&&
				get(tuple_base&& t) {
					return get_impl<I>(sprout::move(t));
				}
				template<std::size_t I>
				static SPROUT_CONSTEXPR typename element<I>::type const&
				get(tuple_base const& t) {
					return get_impl<I>(t);
				}
			};
		}	// namespace detail

		template<typename... Types>
		class tuple
			: public sprout::tuples::detail::tuple_base<typename sprout::make_index_tuple<sizeof...(Types)>::type, Types...>
		{
			template<typename... UTypes>
			friend class sprout::tuples::tuple;
			template<typename... UTypes>
			friend class sprout::tuples::detail::tuple_access;
		private:
			typedef typename sprout::make_index_tuple<sizeof...(Types)>::type index_tuple_type;
			typedef sprout::tuples::detail::tuple_base<index_tuple_type, Types...> base_type;
		private:
			template<typename IndexTuple, typename... Utypes>
			struct is_flexibly_convert_constructible_impl;
			template<sprout::index_t... Indexes, typename... Utypes>
			struct is_flexibly_convert_constructible_impl<sprout::index_tuple<Indexes...>, Utypes...>
				: public sprout::tpp::all_of<
					sprout::is_convert_constructible<
						typename sprout::pack_element<Indexes, Types...>::type,
						typename sprout::pack_element<Indexes, Utypes...>::type
					>...
				>
			{};

			template<typename IndexTuple, typename... Utypes>
			struct is_flexibly_assignable_impl;
			template<sprout::index_t... Indexes, typename... Utypes>
			struct is_flexibly_assignable_impl<sprout::index_tuple<Indexes...>, Utypes...>
				: public sprout::tpp::all_of<
					std::is_assignable<
						typename sprout::pack_element<Indexes, Types...>::type,
						typename sprout::pack_element<Indexes, Utypes...>::type
					>...
				>
			{};
		public:
			template<typename... UTypes>
			struct is_flexibly_convert_constructible
				: public is_flexibly_convert_constructible_impl<
					typename sprout::make_index_tuple<(sizeof...(UTypes) < sizeof...(Types) ? sizeof...(UTypes) : sizeof...(Types))>::type,
					UTypes...
				>
			{};
			template<typename... UTypes>
			struct is_rvref_flexibly_convert_constructible
				: public is_flexibly_convert_constructible<UTypes&&...>
			{};
			template<typename... UTypes>
			struct is_clvref_flexibly_convert_constructible
				: public is_flexibly_convert_constructible<UTypes const&...>
			{};

			template<typename... UTypes>
			struct is_fixedly_convert_constructible
				: public sprout::bool_constant<
					(sizeof...(UTypes) == sizeof...(Types) && is_flexibly_convert_constructible<UTypes...>::value)
				>
			{};
			template<typename... UTypes>
			struct is_rvref_fixedly_convert_constructible
				: public is_fixedly_convert_constructible<UTypes&&...>
			{};
			template<typename... UTypes>
			struct is_clvref_fixedly_convert_constructible
				: public is_fixedly_convert_constructible<UTypes const&...>
			{};

			template<typename... UTypes>
			struct is_flexibly_assignable
				: public is_flexibly_assignable_impl<
					typename sprout::make_index_tuple<(sizeof...(UTypes) < sizeof...(Types) ? sizeof...(UTypes) : sizeof...(Types))>::type,
					UTypes...
				>
			{};
			template<typename... UTypes>
			struct is_rvref_flexibly_assignable
				: public is_flexibly_assignable<UTypes&&...>
			{};
			template<typename... UTypes>
			struct is_clvref_flexibly_assignable
				: public is_flexibly_assignable<UTypes const&...>
			{};

			template<typename... UTypes>
			struct is_fixedly_assignable
				: public sprout::bool_constant<
					(sizeof...(UTypes) == sizeof...(Types) && is_flexibly_assignable<UTypes...>::value)
				>
			{};
			template<typename... UTypes>
			struct is_rvref_fixedly_assignable
				: public is_fixedly_assignable<UTypes&&...>
			{};
			template<typename... UTypes>
			struct is_clvref_fixedly_assignable
				: public is_fixedly_assignable<UTypes const&...>
			{};
		private:
			template<sprout::index_t... Indexes>
			SPROUT_CXX14_CONSTEXPR void
			swap_impl(tuple& other, sprout::index_tuple<Indexes...>) {
				sprout::swallow({(sprout::swap(base_type::template get<Indexes>(*this), base_type::template get<Indexes>(other)), 0)...});
			}
			template<typename Tuple>
			SPROUT_CXX14_CONSTEXPR void
			assign(Tuple&& t) {
				assign_impl(SPROUT_FORWARD(Tuple, t), index_tuple_type());
			}
			template<typename Tuple, sprout::index_t... Indexes>
			SPROUT_CXX14_CONSTEXPR void
			assign_impl(Tuple&& t, sprout::index_tuple<Indexes...>) {
				typedef typename std::decay<Tuple>::type type;
				sprout::swallow({((base_type::template get<Indexes>(*this) = sprout::move(type::template get<Indexes>(SPROUT_FORWARD(Tuple, t)))), 0)...});
			}
			template<sprout::index_t... Indexes>
			SPROUT_CONSTEXPR std::tuple<Types...>
			to_std_tuple(sprout::index_tuple<Indexes...>) const {
				return std::tuple<Types...>(base_type::template get<Indexes>(*this)...);
			}
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple()
				: base_type()
			{}
			explicit SPROUT_CONSTEXPR tuple(Types const&... elements)
				: base_type(elements...)
			{}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			explicit SPROUT_CONSTEXPR tuple(UTypes&&... elements)
				: base_type(SPROUT_FORWARD(UTypes, elements)...)
			{}
			tuple(tuple const&) = default;
			tuple(tuple&&) = default;
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes const&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...> const& t)
				: base_type(sprout::tuples::detail::from_tuple_construct_t(), t)
			{}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...>&& t)
				: base_type(sprout::tuples::detail::from_tuple_construct_t(), sprout::move(t))
			{}
			template<
				typename UType1, typename UType2,
				typename = typename std::enable_if<
					is_clvref_fixedly_convert_constructible<UType1, UType2>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::pair<UType1, UType2> const& t);
			template<
				typename UType1, typename UType2,
				typename = typename std::enable_if<
					is_rvref_fixedly_convert_constructible<UType1, UType2>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::pair<UType1, UType2>&& t);
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					is_rvref_flexibly_convert_constructible<UTypes...>::value
				>::type
			>
			explicit SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, UTypes&&... elements)
				: base_type(
					sprout::tuples::flexibly_construct_t(),
					sprout::index_range<0, sizeof...(UTypes)>::make(),
					sprout::index_range<sizeof...(UTypes), sizeof...(Types)>::make(),
					SPROUT_FORWARD(UTypes, elements)...
					)
			{}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					is_clvref_flexibly_convert_constructible<UTypes...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const& t)
				: base_type(
					sprout::tuples::detail::from_tuple_construct_t(), sprout::tuples::flexibly_construct_t(),
					sprout::index_range<0, sizeof...(UTypes)>::make(),
					sprout::index_range<sizeof...(UTypes), sizeof...(Types)>::make(),
					t
					)
			{}

			template<
				typename... UTypes,
				typename = typename std::enable_if<
					is_rvref_flexibly_convert_constructible<UTypes...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&& t)
				: base_type(
					sprout::tuples::detail::from_tuple_construct_t(), sprout::tuples::flexibly_construct_t(),
					sprout::index_range<0, sizeof...(UTypes)>::make(),
					sprout::index_range<sizeof...(UTypes), sizeof...(Types)>::make(),
					sprout::move(t)
					)
			{}
			template<
				typename UType1, typename UType2,
				typename = typename std::enable_if<
					is_clvref_flexibly_convert_constructible<UType1, UType2>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2> const& t);
			template<
				typename UType1, typename UType2,
				typename = typename std::enable_if<
					is_rvref_flexibly_convert_constructible<UType1, UType2>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2>&& t);
			// tuple assignment
			SPROUT_CXX14_CONSTEXPR tuple&
			operator=(tuple const& rhs) {
				assign(rhs);
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR tuple&
			operator=(tuple&& rhs)
			SPROUT_NOEXCEPT_IF(sprout::tpp::all_of<std::is_nothrow_move_assignable<Types>...>::value)
			{
				assign(sprout::move(rhs));
				return *this;
			}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<std::is_assignable<Types&, UTypes const&>...>::value
				>::type
			>
			SPROUT_CXX14_CONSTEXPR tuple&
			operator=(sprout::tuples::tuple<UTypes...> const& rhs) {
				assign(rhs);
				return *this;
			}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<std::is_assignable<Types&, UTypes&&>...>::value
				>::type
			>
			SPROUT_CXX14_CONSTEXPR tuple&
			operator=(sprout::tuples::tuple<UTypes...>&& rhs) {
				assign(sprout::move(rhs));
				return *this;
			}
			template<
				typename UType1, typename UType2,
				typename = typename std::enable_if<
					is_clvref_fixedly_assignable<UType1, UType2>::value
				>::type
			>
			SPROUT_CXX14_CONSTEXPR tuple& operator=(sprout::pair<UType1, UType2> const& rhs);
			template<
				typename UType1, typename UType2,
				typename = typename std::enable_if<
					is_rvref_fixedly_assignable<UType1, UType2>::value
				>::type
			>
			SPROUT_CXX14_CONSTEXPR tuple& operator=(sprout::pair<UType1, UType2>&& rhs);
			// tuple swap
			SPROUT_CXX14_CONSTEXPR void
			swap(tuple& other)
			SPROUT_NOEXCEPT_IF(sprout::tpp::all_of_c<SPROUT_NOEXCEPT_EXPR(sprout::swap(std::declval<Types&>(), std::declval<Types&>()))...>::value)
			{
				swap_impl(other, index_tuple_type());
			}

			SPROUT_EXPLICIT_CONVERSION SPROUT_CONSTEXPR operator std::tuple<Types...>() const
			SPROUT_NOEXCEPT_IF(sprout::tpp::all_of<sprout::is_nothrow_copy_constructible<Types>...>::value)
			{
				return to_std_tuple(index_tuple_type());;
			}
		};
		template<>
		class tuple<> {
			template<typename... UTypes>
			friend class sprout::tuples::detail::tuple_access;
		protected:
			template<std::size_t I>
			struct element
				: public sprout::detail::nil_base
			{};
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			tuple(tuple const&) = default;
			tuple(tuple&&) = default;
			template<typename... UTypes>
			explicit SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, UTypes&&...) SPROUT_NOEXCEPT {}
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const&) SPROUT_NOEXCEPT {}
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&&) SPROUT_NOEXCEPT {}
			template<typename UType1, typename UType2>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2> const&) SPROUT_NOEXCEPT {}
			template<typename UType1, typename UType2>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2>&&) SPROUT_NOEXCEPT {}
			// tuple swap
			SPROUT_CXX14_CONSTEXPR void swap(tuple&) SPROUT_NOEXCEPT {}

			SPROUT_CONSTEXPR operator std::tuple<>() const SPROUT_NOEXCEPT {
				return std::tuple<>();;
			}
		};

		//
		// swap
		//
		template<typename... Types>
		inline SPROUT_CXX14_CONSTEXPR void
		swap(sprout::tuples::tuple<Types...>& lhs, sprout::tuples::tuple<Types...>& rhs)
		SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
		{
			lhs.swap(rhs);
		}

		namespace detail {
			template<typename... Types>
			class tuple_access {
			public:
				template<std::size_t I>
				struct element
					: public sprout::tuples::tuple<Types...>::template element<I>
				{};
				struct size
					: public sprout::integral_constant<std::size_t, sizeof...(Types)>
				{};
			public:
				template<std::size_t I>
				static SPROUT_CONSTEXPR typename element<I>::type&
				get(sprout::tuples::tuple<Types...>& t) {
					return sprout::tuples::tuple<Types...>::template get<I>(t);
				}
				template<std::size_t I>
				static SPROUT_CONSTEXPR typename element<I>::type&&
				get(sprout::tuples::tuple<Types...>&& t) {
					return sprout::tuples::tuple<Types...>::template get<I>(sprout::move(t));
				}
				template<std::size_t I>
				static SPROUT_CONSTEXPR typename element<I>::type const&
				get(sprout::tuples::tuple<Types...> const& t) {
					return sprout::tuples::tuple<Types...>::template get<I>(t);
				}
			};
		}	// namespace detail
	}	// namespace tuples

	using sprout::tuples::tuple;
	using sprout::tuples::swap;
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::tuples::tuple<Types...> >
		: public sprout::integral_constant<std::size_t, sizeof...(Types)>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::tuples::tuple<Types...> >
//		: public sprout::pack_element<I, Types...>
		: public sprout::tuples::detail::tuple_access<Types...>::template element<I>
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP
