/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/utility/pair/pair_fwd.hpp>
#include <sprout/type_traits/is_convert_constructible.hpp>
#include <sprout/tpp/algorithm/all_of.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>
#include <sprout/tuple/flexibly_construct.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t Index, typename Head, bool IsEmpty>
			class head_base;
			// EBO disabled
//			template<std::size_t Index, typename Head>
//			class head_base<Index, Head, true>
//				: public Head
//			{
//			public:
//				static SPROUT_CONSTEXPR Head& head(head_base& t) SPROUT_NOEXCEPT {
//					return t;
//				}
//				static SPROUT_CONSTEXPR Head const& head(head_base const& t) SPROUT_NOEXCEPT {
//					return t;
//				}
//			public:
//				SPROUT_CONSTEXPR head_base()
//					: Head()
//				{}
//				SPROUT_CONSTEXPR head_base(Head const& v)
//					: Head(v)
//				{}
//				template<typename UHead>
//				explicit SPROUT_CONSTEXPR head_base(UHead&& v)
//					: Head(sprout::forward<UHead>(v))
//				{}
//			};
			template<std::size_t Index, typename Head>
			class head_base<Index, Head, true> {
			public:
				static SPROUT_CONSTEXPR Head& head(head_base& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
				static SPROUT_CONSTEXPR Head const& head(head_base const& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
			private:
				Head head_;
			public:
				SPROUT_CONSTEXPR head_base()
					: head_()
				{}
				SPROUT_CONSTEXPR head_base(Head const& v)
					: head_(v)
				{}
				template<typename UHead>
				explicit SPROUT_CONSTEXPR head_base(UHead&& v)
					: head_(sprout::forward<UHead>(v))
				{}
			};
			template<std::size_t Index, typename Head>
			class head_base<Index, Head, false> {
			public:
				static SPROUT_CONSTEXPR Head& head(head_base& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
				static SPROUT_CONSTEXPR Head const& head(head_base const& t) SPROUT_NOEXCEPT {
					return t.head_;
				}
			private:
				Head head_;
			public:
				SPROUT_CONSTEXPR head_base()
					: head_()
				{}
				SPROUT_CONSTEXPR head_base(Head const& v)
					: head_(v)
				{}
				template<typename UHead>
				explicit SPROUT_CONSTEXPR head_base(UHead&& v)
					: head_(sprout::forward<UHead>(v))
				{}
			};

			template<std::size_t Index, typename... Types>
			class tuple_impl;
			template<std::size_t Index>
			class tuple_impl<Index> {
			public:
				template<typename...>
				friend class tuple;
				template<std::size_t, typename...>
				friend class sprout::tuples::detail::tuple_impl;
			protected:
				void swap(tuple_impl&) SPROUT_NOEXCEPT {}
			public:
				tuple_impl() = default;
				template<typename... UTypes>
				explicit SPROUT_CONSTEXPR tuple_impl(UTypes&&...) SPROUT_NOEXCEPT {}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl const&) = default;
				SPROUT_CONSTEXPR tuple_impl(tuple_impl&&) = default;
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...> const&) SPROUT_NOEXCEPT {}
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...>&&) SPROUT_NOEXCEPT {}
				tuple_impl& operator=(tuple_impl const&) = default;
				tuple_impl& operator=(tuple_impl&& t) = default;
				template<typename... UTypes>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UTypes...> const&) SPROUT_NOEXCEPT {
					return *this;
				}
				template<typename... UTypes>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UTypes...>&&) SPROUT_NOEXCEPT {
					return *this;
				}
			};
			template<std::size_t Index, typename Head, typename... Tail>
			class tuple_impl<Index, Head, Tail...>
				: public sprout::tuples::detail::tuple_impl<Index + 1, Tail...>
				, private sprout::tuples::detail::head_base<Index, Head, std::is_empty<Head>::value>
			{
			public:
				template<typename...>
				friend class tuple;
				template<std::size_t, typename...>
				friend class sprout::tuples::detail::tuple_impl;
			public:
				typedef sprout::tuples::detail::tuple_impl<Index + 1, Tail...> inherited_type;
				typedef sprout::tuples::detail::head_base<Index, Head, std::is_empty<Head>::value> base_type;
			public:
				static SPROUT_CONSTEXPR Head& head(tuple_impl& t) SPROUT_NOEXCEPT {
					return base_type::head(t);
				}
				static SPROUT_CONSTEXPR Head const& head(tuple_impl const& t) SPROUT_NOEXCEPT {
					return base_type::head(t);
				}
				static SPROUT_CONSTEXPR inherited_type& tail(tuple_impl& t) SPROUT_NOEXCEPT {
					return t;
				}
				static SPROUT_CONSTEXPR inherited_type const& tail(tuple_impl const& t) SPROUT_NOEXCEPT {
					return t;
				}
			public:
				void swap(tuple_impl& t)
				SPROUT_NOEXCEPT_EXPR(
					SPROUT_NOEXCEPT_EXPR(sprout::swap(head(std::declval<tuple_impl&>()), head(t)))
					&& SPROUT_NOEXCEPT_EXPR(std::declval<inherited_type&>().swap(tail(t)))
					)
				{
					sprout::swap(head(*this), head(t));
					inherited_type::swap(tail(t));
				}
			public:
				SPROUT_CONSTEXPR tuple_impl()
					: inherited_type()
					, base_type()
				{}
				explicit SPROUT_CONSTEXPR tuple_impl(Head const& h, Tail const&... tail)
					: inherited_type(tail...)
					, base_type(h)
				{}
				template<typename UHead, typename... UTail>
				explicit SPROUT_CONSTEXPR tuple_impl(UHead&& h, UTail&&... tail)
					: inherited_type(sprout::forward<UTail>(tail)...)
					, base_type(sprout::forward<UHead>(h))
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl const&) = default;
#if defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ == 8 && __GNUC_PATCHLEVEL__ <= 1))
				SPROUT_CONSTEXPR tuple_impl(tuple_impl&&) = default;
#else
				SPROUT_CONSTEXPR tuple_impl(tuple_impl&& t)
				SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_constructible<Head>::value && std::is_nothrow_move_constructible<inherited_type>::value)
					: inherited_type(sprout::move(tail(t)))
					, base_type(sprout::forward<Head>(head(t)))
				{}
#endif
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...> const& t)
					: inherited_type(sprout::tuples::detail::tuple_impl<Index, UTypes...>::tail(t))
					, base_type(sprout::tuples::detail::tuple_impl<Index, UTypes...>::head(t))
				{}
				template<typename UHead, typename... UTail>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UHead, UTail...>&& t)
					: inherited_type(sprout::move(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::tail(t)))
					, base_type(sprout::forward<UHead>(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::head(t)))
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index> const&)
					: inherited_type()
					, base_type()
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index>&&)
					: inherited_type()
					, base_type()
				{}
				tuple_impl& operator=(tuple_impl const& t) {
					head(*this) = head(t);
					tail(*this) = tail(t);
					return *this;
				}
				tuple_impl& operator=(tuple_impl&& t)
				SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<Head>::value && std::is_nothrow_move_assignable<inherited_type>::value)
				{
					head(*this) = sprout::forward<Head>(head(t));
					tail(*this) = sprout::move(tail(t));
					return *this;
				}
				template<typename... UTypes>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UTypes...> const& t) {
					head(*this) = sprout::tuples::detail::tuple_impl<Index, UTypes...>::head(t);
					tail(*this) = sprout::tuples::detail::tuple_impl<Index, UTypes...>::tail(t);
					return *this;
				}
				template<typename UHead, typename... UTail>
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>&& t) {
					head(*this) = sprout::forward<UHead>(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::head(t));
					tail(*this) = sprout::move(sprout::tuples::detail::tuple_impl<Index, UHead, UTail...>::tail(t));
					return *this;
				}
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index> const&) {
					*this = sprout::move(tuple_impl());
					return *this;
				}
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index>&&) {
					*this = sprout::move(tuple_impl());
					return *this;
				}
			};
		}	// namespace detail

		//
		// tuple
		//
		template<typename... Types>
		class tuple
			: public sprout::tuples::detail::tuple_impl<0, Types...>
		{
		private:
			typedef sprout::tuples::detail::tuple_impl<0, Types...> impl_type;
		private:
			template<typename TndexTuple, typename... Utypes>
			struct is_flexibly_convert_constructible_impl;
			template<sprout::index_t... Indexes, typename... Utypes>
			struct is_flexibly_convert_constructible_impl<sprout::index_tuple<Indexes...>, Utypes...>
				: public sprout::tpp::all_of<
					sprout::is_convert_constructible<
						typename sprout::tppack_at<Indexes, Types...>::type,
						typename sprout::tppack_at<Indexes, Utypes...>::type
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
				: public std::integral_constant<
					bool,
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
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple()
				: impl_type()
			{}
			explicit SPROUT_CONSTEXPR tuple(Types const&... elements)
				: impl_type(elements...)
			{}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			explicit SPROUT_CONSTEXPR tuple(UTypes&&... elements)
				: impl_type(sprout::forward<UTypes>(elements)...)
			{}
			SPROUT_CONSTEXPR tuple(tuple const&) = default;
			SPROUT_CONSTEXPR tuple(tuple&&) = default;
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes const&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...> const& t)
				: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...> const&>(t))
			{}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<sprout::is_convert_constructible<Types, UTypes&&>...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...>&& t)
				: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...>&&>(t))
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
				: impl_type(sprout::forward<UTypes>(elements)...)
			{}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					is_clvref_flexibly_convert_constructible<UTypes...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const& t)
				: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...> const&>(t))
			{}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					is_rvref_flexibly_convert_constructible<UTypes...>::value
				>::type
			>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&& t)
				: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...>&&>(t))
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
			tuple& operator=(tuple const& rhs) {
				static_cast<impl_type&>(*this) = rhs;
				return *this;
			}
			tuple& operator=(tuple&& rhs)
			SPROUT_NOEXCEPT_EXPR(sprout::tpp::all_of<std::is_nothrow_move_assignable<Types>...>::value)
			{
				static_cast<impl_type&>(*this) = sprout::move(rhs);
				return *this;
			}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<std::is_assignable<Types&, UTypes const&>...>::value
				>::type
			>
			tuple& operator=(sprout::tuples::tuple<UTypes...> const& rhs) {
				static_cast<impl_type&>(*this) = rhs;
				return *this;
			}
			template<
				typename... UTypes,
				typename = typename std::enable_if<
					sizeof...(Types) == sizeof...(UTypes) && sprout::tpp::all_of<std::is_assignable<Types&, UTypes&&>...>::value
				>::type
			>
			tuple& operator=(sprout::tuples::tuple<UTypes...>&& rhs) {
				static_cast<impl_type&>(*this) = sprout::move(rhs);
				return *this;
			}
			// tuple swap
			void swap(tuple& other)
			SPROUT_NOEXCEPT_EXPR(sprout::tpp::all_of_c<SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(sprout::swap(std::declval<Types&>(), std::declval<Types&>()), false)...>::value)
			{
				impl_type::swap(other);
			}
		};
		template<>
		class tuple<> {
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple() = default;
			SPROUT_CONSTEXPR tuple(tuple const&) = default;
			SPROUT_CONSTEXPR tuple(tuple&&) = default;
			template<typename... UTypes>
			explicit SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, UTypes&&...) {}
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const&) {}
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&&) {}
			template<typename UType1, typename UType2>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2> const&) {}
			template<typename UType1, typename UType2>
			SPROUT_CONSTEXPR tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UType1, UType2>&&) {}
			// tuple swap
			void swap(tuple&) SPROUT_NOEXCEPT {}
		};

		//
		// swap
		//
		template<typename... Types>
		inline void
		swap(sprout::tuples::tuple<Types...>& lhs, sprout::tuples::tuple<Types...>& rhs)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
		{
			lhs.swap(rhs);
		}

		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<typename Head, typename... Tail>
			struct tuple_element_impl<0, sprout::tuples::tuple<Head, Tail...> > {
			public:
				typedef Head type;
			};
			template<std::size_t I, typename Head, typename... Tail>
			struct tuple_element_impl<I, sprout::tuples::tuple<Head, Tail...> >
				: public sprout::tuples::detail::tuple_element_impl<I - 1, sprout::tuples::tuple<Tail...> >
			{};
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
		: public std::integral_constant<std::size_t, sizeof...(Types)>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::tuples::tuple<Types...> >
		: public sprout::tuples::detail::tuple_element_impl<I, sprout::tuples::tuple<Types...> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_DECL_HPP
