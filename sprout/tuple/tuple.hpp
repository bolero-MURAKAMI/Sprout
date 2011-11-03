#ifndef SPROUT_TUPLE_TUPLE_HPP
#define SPROUT_TUPLE_TUPLE_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/utility/operation.hpp>

namespace sprout {
	namespace tuples {
		namespace detail {
			template<std::size_t Index, typename Head, bool IsEmpty>
			class head_base;
			template<std::size_t Index, typename Head>
			class head_base<Index, Head, true>
				: public Head
			{
			public:
				static SPROUT_CONSTEXPR Head& head(head_base& t) SPROUT_NOEXCEPT {
					return t;
				}
				static SPROUT_CONSTEXPR Head const& head(head_base const& t) SPROUT_NOEXCEPT {
					return t;
				}
			public:
				SPROUT_CONSTEXPR head_base()
					: Head()
				{}
				SPROUT_CONSTEXPR head_base(Head const& v)
					: Head(v)
				{}
				template<typename UHead>
				SPROUT_CONSTEXPR head_base(UHead&& v)
					: Head(sprout::forward<UHead>(v))
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
				SPROUT_CONSTEXPR head_base(UHead&& v)
					: head_(sprout::forward<UHead>(v))
				{}
			};

			template<std::size_t Index, typename... Types>
			class tuple_impl; 
			template<std::size_t Index>
			class tuple_impl<Index> {
			public:
				template<std::size_t, typename...>
				friend class sprout::tuples::detail::tuple_impl;
			protected:
				void swap(tuple_impl&) SPROUT_NOEXCEPT {}
			public:
				tuple_impl() = default;
				template<typename... UTypes>
				SPROUT_CONSTEXPR explicit tuple_impl(UTypes&&... args) SPROUT_NOEXCEPT {}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl const&) = default;
				SPROUT_CONSTEXPR tuple_impl(tuple_impl&&) = default;
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...> const& t) SPROUT_NOEXCEPT {}
				template<typename... UTypes>
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index, UTypes...>&& t) SPROUT_NOEXCEPT {}
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
			protected:
				void swap(tuple_impl& t) SPROUT_NOEXCEPT_EXPR(
					SPROUT_NOEXCEPT_EXPR(swap(std::declval<Head&>(), std::declval<Head&>()))
					&& SPROUT_NOEXCEPT_EXPR(tail(t).swap(tail(t)))
					)
				{
					using std::swap;
					swap(head(*this), head(t));
					inherited_type::swap(tail(t));
				}
			public:
				SPROUT_CONSTEXPR tuple_impl()
					: inherited_type()
					, base_type()
				{}
				SPROUT_CONSTEXPR explicit tuple_impl(const Head& h, Tail const&... tail)
					: inherited_type(tail...)
					, base_type(h)
				{}
				template<typename UHead, typename... UTail>
				SPROUT_CONSTEXPR explicit tuple_impl(UHead&& h, UTail&&... tail)
					: inherited_type(sprout::forward<UTail>(tail)...)
					, base_type(sprout::forward<UHead>(h))
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl const&) = default;
				SPROUT_CONSTEXPR tuple_impl(tuple_impl&& t)
				SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_constructible<Head>::value && std::is_nothrow_move_constructible<inherited_type>::value)
					: inherited_type(sprout::move(tail(t)))
					, base_type(sprout::forward<Head>(head(t)))
				{}
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
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index> const& t)
					: inherited_type()
					, base_type()
				{}
				SPROUT_CONSTEXPR tuple_impl(tuple_impl<Index>&& t)
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
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index> const& t) {
					*this = sprout::move(tuple_impl());
					return *this;
				}
				tuple_impl& operator=(sprout::tuples::detail::tuple_impl<Index>&& t) {
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
		public:
			typedef sprout::tuples::detail::tuple_impl<0, Types...> inherited_type;
		public:
			// tuple construction
			SPROUT_CONSTEXPR tuple()
				: inherited_type()
			{}
			SPROUT_CONSTEXPR explicit tuple(Types const&... elements)
				: inherited_type(elements...)
			{}
			template<typename... UTypes>
			SPROUT_CONSTEXPR explicit tuple(UTypes&&... elements)
				: inherited_type(sprout::forward<UTypes>(elements)...)
			{}
			SPROUT_CONSTEXPR tuple(tuple const &) = default;
			SPROUT_CONSTEXPR tuple(tuple&&) = default;
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...> const& t)
				: inherited_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...> const&>(t))
			{}
			template<typename... UTypes>
			SPROUT_CONSTEXPR tuple(sprout::tuples::tuple<UTypes...>&& t)
				: inherited_type(static_cast<sprout::tuples::detail::tuple_impl<0, UTypes...>&&>(t))
			{}
			// tuple assignment
			tuple& operator=(const tuple& rhs) {
				static_cast<inherited_type&>(*this) = rhs;
				return *this;
			}
			tuple& operator=(tuple&& rhs) SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_assignable<inherited_type>::value) {
				static_cast<inherited_type&>(*this) = sprout::move(rhs);
				return *this;
			}
			template<typename... UTypes>
			tuple& operator=(sprout::tuples::tuple<UTypes...> const& rhs) {
				static_cast<inherited_type&>(*this) = rhs;
				return *this;
			}
			template<typename... UTypes>
			tuple& operator=(sprout::tuples::tuple<UTypes...>&& rhs) {
				static_cast<inherited_type&>(*this) = sprout::move(rhs);
				return *this;
			}
			// tuple swap
			void swap(tuple& other) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(other.swap(other))) {
				inherited_type::swap(other);
			}
		};
		template<>
		class tuple<> {
		public:
			// tuple swap
			void swap(tuple&) SPROUT_NOEXCEPT {}
		};

		//
		// ignore_t
		//
		struct ignore_t {
			template<typename T>
			ignore_t const& operator=(T const&) const {
				return *this;
			}
		};
		//
		// ignore
		//
		static SPROUT_CONSTEXPR ignore_t ignore{};

		//
		// make_tuple
		//
		template<typename... Types>
		SPROUT_CONSTEXPR inline sprout::tuples::tuple<typename std::decay<Types>::type...> make_tuple(Types&&... args) {
			return sprout::tuples::tuple<typename std::decay<Types>::type...>(sprout::forward<Types>(args)...);
		}
		//
		// forward_as_tuple
		//
		template<typename... Types>
		SPROUT_CONSTEXPR inline sprout::tuples::tuple<Types&&...> forward_as_tuple(Types&&... args) SPROUT_NOEXCEPT {
			return sprout::tuples::tuple<Types&&...>(sprout::forward<Types>(args)...);
		}
		//
		// tie
		//
		template<typename... Types>
		inline sprout::tuples::tuple<Types&...> tie(Types&... args) SPROUT_NOEXCEPT {
			return sprout::tuples::tuple<Types&...>(args...);
		}

		//
		// swap
		//
		template<typename... Types>
		inline void swap(
			sprout::tuples::tuple<Types...>& lhs,
			sprout::tuples::tuple<Types...>& rhs
			) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
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
	using sprout::tuples::ignore;
	using sprout::tuples::make_tuple;
	using sprout::tuples::forward_as_tuple;
	using sprout::tuples::tie;
	using sprout::tuples::swap;
}	// namespace sprout

namespace std {
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
}	// namespace std

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		template<typename T>
		struct tuple_size
			: public std::tuple_size<T>
		{};

		//
		// tuple_element
		//
		template<std::size_t I, typename T>
		struct tuple_element
			: public std::tuple_element<I, T>
		{};

		//
		// get
		//
		template<std::size_t I, typename T>
		SPROUT_CONSTEXPR auto get(
			T&& t
			) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::get<I>(sprout::forward<T>(t))))
			-> decltype(std::get<I>(sprout::forward<T>(t)))
		{
			return std::get<I>(sprout::forward<T>(t));
		}
		//
		// get
		//
		namespace detail {
			template<std::size_t I, typename Head, typename... Tail>
			SPROUT_CONSTEXPR typename std::add_lvalue_reference<Head>::type get_helper(
				sprout::tuples::detail::tuple_impl<I, Head, Tail...>& t
				) SPROUT_NOEXCEPT
			{
				return sprout::tuples::detail::tuple_impl<I, Head, Tail...>::head(t);
			}
			template<std::size_t I, typename Head, typename... Tail>
			SPROUT_CONSTEXPR typename std::add_lvalue_reference<typename std::add_const<Head>::type>::type get_helper(
				sprout::tuples::detail::tuple_impl<I, Head, Tail...> const& t
				) SPROUT_NOEXCEPT
			{
				return sprout::tuples::detail::tuple_impl<I, Head, Tail...>::head(t);
			}
		}	// namespace detail
		template<std::size_t I, typename... Types>
		SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type& get(
			sprout::tuples::tuple<Types...>& t
			) SPROUT_NOEXCEPT
		{
			return sprout::tuples::detail::get_helper<I>(t);
		}
		template<std::size_t I, typename... Types>
		SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&& get(
			sprout::tuples::tuple<Types...>&& t
			) SPROUT_NOEXCEPT
		{
			return sprout::forward<typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type&&>(
				sprout::tuples::get<I>(t)
				);
		}
		template<std::size_t I, typename... Types>
		SPROUT_CONSTEXPR typename sprout::tuples::tuple_element<I, sprout::tuples::tuple<Types...> >::type const& get(
			sprout::tuples::tuple<Types...> const& t
			) SPROUT_NOEXCEPT
		{
			return sprout::tuples::detail::get_helper<I>(t);
		}
	}	// namespace tuples

	using sprout::tuples::tuple_size;
	using sprout::tuples::tuple_element;
	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_HPP
