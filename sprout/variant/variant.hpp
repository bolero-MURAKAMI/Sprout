/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_VARIANT_HPP
#define SPROUT_VARIANT_VARIANT_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type_traits/common_decay.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/type/algorithm/find_index.hpp>
#include <sprout/functional/type_traits/has_type.hpp>
#include <sprout/functional/type_traits/weak_result_type.hpp>
#include <sprout/variant/variant_fwd.hpp>
#include <sprout/variant/visitor_result.hpp>
#include <sprout/math/less.hpp>

namespace sprout {
	namespace detail {
		template<typename... Types>
		class variant_impl {
			template<typename...>
			friend class variant;
		protected:
			typedef sprout::tuples::tuple<Types...> tuple_type;
			typedef sprout::types::type_tuple<typename std::decay<Types>::type...> decayed_tuple_type;
		private:
			template<typename T, sprout::index_t... Indexes>
			static SPROUT_CONSTEXPR tuple_type init(T&& operand, sprout::index_tuple<Indexes...>) {
				return sprout::tuples::make<tuple_type>(
					sprout::tuples::flexibly_construct,
					typename sprout::tuples::tuple_element<Indexes, tuple_type>::type()...,
					sprout::forward<T>(operand)
					);
			}
		protected:
			tuple_type tuple_;
			int which_;
		protected:
			SPROUT_CONSTEXPR variant_impl()
				: tuple_()
				, which_()
			{}
			template<typename T, typename Index>
			SPROUT_CONSTEXPR variant_impl(T&& operand, Index)
				: tuple_(init(sprout::forward<T>(operand), sprout::make_index_tuple<Index::value>::make()))
				, which_(Index::value)
			{
				static_assert(Index::value < sizeof...(Types), "variant<>: invalid operand");
			}
		public:
			SPROUT_CXX14_CONSTEXPR void swap(variant_impl& other)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(tuple_, other.tuple_)))
			{
				sprout::swap(tuple_, other.tuple_);
				sprout::swap(which_, other.which_);
			}
			variant_impl& operator=(variant_impl const&) = default;
		};
	}	// namespace detail
	//
	// variant
	//
	template<typename... Types>
	class variant
		: private sprout::detail::variant_impl<Types...>
	{
	private:
		typedef sprout::detail::variant_impl<Types...> impl_type;
		typedef typename impl_type::decayed_tuple_type decayed_tuple_type;
	public:
		typedef typename impl_type::tuple_type tuple_type;
	private:
		template<typename Visitor, typename Tuple, typename IndexTuple>
		struct visitor_result_impl_2;
		template<typename Visitor, typename Tuple, sprout::index_t... Indexes>
		struct visitor_result_impl_2<Visitor, Tuple, sprout::index_tuple<Indexes...> >
			: public Visitor::template visitor_result<
				decltype((std::declval<Visitor>())(sprout::tuples::get<Indexes>(std::declval<Tuple>())))...
			>
		{};
		template<typename Visitor, typename Tuple, typename IndexTuple>
		struct visitor_result_impl_1;
		template<typename Visitor, typename Tuple, sprout::index_t... Indexes>
		struct visitor_result_impl_1<Visitor, Tuple, sprout::index_tuple<Indexes...> >
			: public sprout::common_decay<
				decltype((std::declval<Visitor>())(sprout::tuples::get<Indexes>(std::declval<Tuple>())))...
			>
		{};
		template<typename Visitor, typename Tuple, typename = void>
		struct visitor_result_impl;
		template<typename Visitor, typename Tuple>
		struct visitor_result_impl<
			Visitor, Tuple,
			typename std::enable_if<
				sprout::has_result_type<sprout::weak_result_type<Visitor> >::value
			>::type
		> {
		public:
			typedef typename sprout::weak_result_type<Visitor>::result_type type;
		};
		template<typename Visitor, typename Tuple>
		struct visitor_result_impl<
			Visitor, Tuple,
			typename std::enable_if<
				sprout::has_visitor_result<Visitor>::value
					&& !sprout::has_result_type<sprout::weak_result_type<Visitor> >::value
			>::type
		>
			: public visitor_result_impl_2<Visitor, Tuple, typename sprout::tuple_indexes<Tuple>::type>
		{};
		template<typename Visitor, typename Tuple>
		struct visitor_result_impl<
			Visitor, Tuple,
			typename std::enable_if<
				!sprout::has_visitor_result<Visitor>::value
					&& !sprout::has_result_type<sprout::weak_result_type<Visitor> >::value
			>::type
		>
			: public visitor_result_impl_1<Visitor, Tuple, typename sprout::tuple_indexes<Tuple>::type>
		{};
	public:
		// visitation support
		template<typename Visitor, typename Visitable>
		struct visitor_result
			: public visitor_result_impl<Visitor, typename Visitable::tuple_type>
		{};
		template<typename Visitor, typename Visitable>
		struct visitor_result<Visitor, Visitable const>
			: public visitor_result_impl<Visitor, typename Visitable::tuple_type const>
		{};
		template<typename Visitor, typename Visitable>
		struct visitor_result<Visitor, Visitable volatile>
			: public visitor_result_impl<Visitor, typename Visitable::tuple_type volatile>
		{};
		template<typename Visitor, typename Visitable>
		struct visitor_result<Visitor, Visitable const volatile>
			: public visitor_result_impl<Visitor, typename Visitable::tuple_type const volatile>
		{};
	private:
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			I == sizeof...(Types),
			bool
		>::type eq(tuple_type const&, tuple_type const&, int) {
			return false;
		}
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			I != sizeof...(Types),
			bool
		>::type eq(tuple_type const& l, tuple_type const& r, int which) {
			return I == which
				? sprout::tuples::get<I>(l) == sprout::tuples::get<I>(r)
				: eq<I + 1>(l, r, which)
				;
		}
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			static_cast<std::size_t>(I) == sizeof...(Types),
			bool
		>::type lt(tuple_type const&, tuple_type const&, int) {
			return false;
		}
		template<int I>
		static SPROUT_CONSTEXPR typename std::enable_if<
			static_cast<std::size_t>(I) != sizeof...(Types),
			bool
		>::type lt(tuple_type const& l, tuple_type const& r, int which) {
			return I == which
				? sprout::tuples::get<I>(l) < sprout::tuples::get<I>(r)
				: lt<I + 1>(l, r, which)
				;
		}
		template<int I, typename Elem, typename Traits>
		static SPROUT_NON_CONSTEXPR typename std::enable_if<
			static_cast<std::size_t>(I) == sizeof...(Types),
			std::basic_ostream<Elem, Traits>&
		>::type output(std::basic_ostream<Elem, Traits>& os, tuple_type const&, int) {
			return os;
		}
		template<int I, typename Elem, typename Traits>
		static SPROUT_NON_CONSTEXPR typename std::enable_if<
			static_cast<std::size_t>(I) != sizeof...(Types),
			std::basic_ostream<Elem, Traits>&
		>::type output(std::basic_ostream<Elem, Traits>& os, tuple_type const& t, int which) {
			return I == which
				? os << sprout::tuples::get<I>(t)
				: output<I + 1>(os, t, which)
				;
		}
		template<typename Result, int I, typename Tuple, typename Visitor>
		static SPROUT_CONSTEXPR typename std::enable_if<
			I == sizeof...(Types) - 1,
			Result
		>::type visit(Tuple&& t, Visitor&& v, int) {
			return sprout::forward<Visitor>(v)(sprout::tuples::get<I>(sprout::forward<Tuple>(t)));
		}
		template<typename Result, int I, typename Tuple, typename Visitor>
		static SPROUT_CONSTEXPR typename std::enable_if<
			I != sizeof...(Types) - 1,
			Result
		>::type visit(Tuple&& t, Visitor&& v, int which) {
			return I == which
				? sprout::forward<Visitor>(v)(sprout::tuples::get<I>(sprout::forward<Tuple>(t)))
				: visit<Result, I + 1>(sprout::forward<Tuple>(t), sprout::forward<Visitor>(v), which)
				;
		}
	private:
		using impl_type::tuple_;
		using impl_type::which_;
	public:
		// construct/copy/destruct
		SPROUT_CONSTEXPR variant()
			: impl_type()
		{}
		variant(variant const&) = default;
		variant(variant&&) = default;
		template<typename T>
		SPROUT_CONSTEXPR variant(T&& operand)
			: impl_type(
				sprout::forward<T>(operand),
				sprout::types::find_index<decayed_tuple_type, typename std::decay<T>::type>()
				)
		{}
		// modifiers
		SPROUT_CXX14_CONSTEXPR void swap(variant& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::declval<impl_type&>().swap(other)))
		{
			impl_type::swap(other);
		}
		SPROUT_CXX14_CONSTEXPR variant& operator=(variant const& rhs) {
			static_cast<impl_type&>(*this) = rhs;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR variant& operator=(variant&& rhs)
		SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<impl_type>::value)
		{
			static_cast<impl_type&>(*this) = sprout::move(rhs);
			return *this;
		}
		template<typename T>
		SPROUT_CXX14_CONSTEXPR variant& operator=(T&& rhs) {
			static_cast<impl_type&>(*this) = variant(sprout::forward<T>(rhs));
			return *this;
		}
		// queries
		SPROUT_CONSTEXPR int which() const {
			return which_;
		}
		SPROUT_CONSTEXPR bool empty() const {
			return false;
		}
		// relational
		friend SPROUT_CONSTEXPR bool operator==(variant const& lhs, variant const& rhs) {
			return lhs.which_ == rhs.which_ && eq<0>(lhs.tuple_, rhs.tuple_, lhs.which_);
		}
		friend SPROUT_CONSTEXPR bool operator!=(variant const& lhs, variant const& rhs) {
			return !(lhs == rhs);
		}
		friend SPROUT_CONSTEXPR bool operator<(variant const& lhs, variant const& rhs) {
			return lhs.which_ < rhs.which_
				|| (lhs.which_ == rhs.which_ && lt<0>(lhs.tuple_, rhs.tuple_, lhs.which_))
				;
		}
		friend SPROUT_CONSTEXPR bool operator>(variant const& lhs, variant const& rhs) {
			return rhs < lhs;
		}
		friend SPROUT_CONSTEXPR bool operator<=(variant const& lhs, variant const& rhs) {
			return !(rhs < lhs);
		}
		friend SPROUT_CONSTEXPR bool operator>=(variant const& lhs, variant const& rhs) {
			return !(lhs < rhs);
		}

		template<typename Elem, typename Traits>
		friend SPROUT_NON_CONSTEXPR std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& lhs, variant const& rhs) {
			return output<0>(lhs, rhs.tuple_, rhs.which_);
		}
		// get support
		template<std::size_t I>
		SPROUT_CONSTEXPR typename std::enable_if<
			I != sizeof...(Types),
			typename sprout::tuples::tuple_element<I, tuple_type>::type const&
		>::type get_at() const {
			return (SPROUT_ASSERT(I == which_), true) ? sprout::tuples::get<I>(tuple_)
				: sprout::tuples::get<I>(tuple_)
				;
		}
		template<std::size_t I>
		SPROUT_CXX14_CONSTEXPR typename std::enable_if<
			I != sizeof...(Types),
			typename sprout::tuples::tuple_element<I, tuple_type>::type&
		>::type get_at() {
			return (SPROUT_ASSERT(I == which_), true) ? sprout::tuples::get<I>(tuple_)
				: sprout::tuples::get<I>(tuple_)
				;
		}
		template<typename U>
		SPROUT_CONSTEXPR typename std::enable_if<
			sprout::types::find_index<tuple_type, U>::value != sizeof...(Types),
			U const&
		>::type get() const {
			return get_at<sprout::types::find_index<tuple_type, U>::value>();
		}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR typename std::enable_if<
			sprout::types::find_index<tuple_type, U>::value != sizeof...(Types),
			U&
		>::type get() {
			return get_at<sprout::types::find_index<tuple_type, U>::value>();
		}
		// visitation support
		template<typename Visitor>
		SPROUT_CONSTEXPR typename visitor_result<typename std::remove_reference<Visitor>::type, variant const>::type
		apply_visitor(Visitor&& visitor) const {
			typedef typename visitor_result<typename std::remove_reference<Visitor>::type, variant const>::type result_type;
			return SPROUT_ASSERT(0 <= which_ && sprout::math::less(which_, sizeof...(Types))),
				visit<result_type, 0>(tuple_, sprout::forward<Visitor>(visitor), which_)
				;
		}
		template<typename Visitor>
		SPROUT_CXX14_CONSTEXPR typename visitor_result<typename std::remove_reference<Visitor>::type, variant>::type
		apply_visitor(Visitor&& visitor) {
			typedef typename visitor_result<typename std::remove_reference<Visitor>::type, variant>::type result_type;
			return SPROUT_ASSERT(0 <= which_ && sprout::math::less(which_, sizeof...(Types))),
				visit<result_type, 0>(tuple_, sprout::forward<Visitor>(visitor), which_)
				;
		}
	};

	//
	// swap
	//
	template<typename... Types>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::variant<Types...>& lhs, sprout::variant<Types...>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_VARIANT_HPP
