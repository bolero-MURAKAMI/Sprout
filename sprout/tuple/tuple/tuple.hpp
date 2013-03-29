#ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/pair/pair_decl.hpp>
#include <sprout/type_traits/is_convert_constructible.hpp>
#include <sprout/tpp/algorithm/all_of.hpp>
#include <sprout/tuple/tuple/tuple_decl.hpp>
#include <sprout/tuple/tuple/flexibly_construct.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple
		//
		// tuple construction
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple()
			: impl_type()
		{}
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(Types const&... elements)
			: impl_type(elements...)
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(UTypes&&... elements)
			: impl_type(sprout::forward<UTypes>(elements)...)
		{}
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(tuple const&) = default;
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(tuple&&) = default;
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::tuple<UTypes...> const& t)
			: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...> const&>(t))
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::tuple<UTypes...>&& t)
			: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...>&&>(t))
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::pair<UTypes...> const& t)
			: impl_type(t.first, t.second)
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::pair<UTypes...>&& t)
			: impl_type(sprout::forward<typename sprout::pair<UTypes...>::first_type>(t.first), sprout::forward<typename sprout::pair<UTypes...>::second_type>(t.second))
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, UTypes&&... elements)
			: impl_type(sprout::forward<UTypes>(elements)...)
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const& t)
			: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...> const&>(t))
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&& t)
			: impl_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...>&&>(t))
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UTypes...> const& t)
			: impl_type(t.first, t.second)
		{}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<Types...>::tuple(sprout::tuples::flexibly_construct_t, sprout::pair<UTypes...>&& t)
			: impl_type(sprout::forward<typename sprout::pair<UTypes...>::first_type>(t.first), sprout::forward<typename sprout::pair<UTypes...>::second_type>(t.second))
		{}
		// tuple assignment
		template<typename... Types>
		sprout::tuples::tuple<Types...>& sprout::tuples::tuple<Types...>::operator=(tuple const& rhs) {
			static_cast<impl_type&>(*this) = rhs;
			return *this;
		}
		template<typename... Types>
		sprout::tuples::tuple<Types...>& sprout::tuples::tuple<Types...>::operator=(tuple&& rhs)
		SPROUT_NOEXCEPT_EXPR(sprout::tpp::all_of<std::is_nothrow_move_assignable<Types>...>::value)
		{
			static_cast<impl_type&>(*this) = sprout::move(rhs);
			return *this;
		}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		sprout::tuples::tuple<Types...>& sprout::tuples::tuple<Types...>::operator=(sprout::tuples::tuple<UTypes...> const& rhs) {
			static_cast<impl_type&>(*this) = rhs;
			return *this;
		}
		template<typename... Types>
		template<
			typename... UTypes,
			typename
		>
		sprout::tuples::tuple<Types...>& sprout::tuples::tuple<Types...>::operator=(sprout::tuples::tuple<UTypes...>&& rhs) {
			static_cast<impl_type&>(*this) = sprout::move(rhs);
			return *this;
		}
		// tuple swap
		template<typename... Types>
		inline void sprout::tuples::tuple<Types...>::swap(tuple& other)
		SPROUT_NOEXCEPT_EXPR(has_nothrow_swap::value)
		{
			impl_type::swap(other);
		}

		//
		// tuple
		//
		// tuple construction
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<>::tuple() = default;
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<>::tuple(tuple const&) = default;
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<>::tuple(tuple&&) = default;
		template<typename... UTypes>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<>::tuple(sprout::tuples::flexibly_construct_t, UTypes&&... elements) {}
		template<typename... UTypes>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<>::tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...> const& t) {}
		template<typename... UTypes>
		inline SPROUT_CONSTEXPR sprout::tuples::tuple<>::tuple(sprout::tuples::flexibly_construct_t, sprout::tuples::tuple<UTypes...>&& t) {}
		// tuple swap
		inline void sprout::tuples::tuple<>::swap(tuple&) SPROUT_NOEXCEPT {}

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
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_HPP
