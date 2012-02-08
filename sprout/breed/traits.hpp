#ifndef SPROUT_BREED_TRAITS_HPP
#define SPROUT_BREED_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/args.hpp>
#include <sprout/breed/domain.hpp>
#include <sprout/breed/transform/pass_through.hpp>
#include <sprout/breed/detail/template_arity.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename T, typename Void = void>
			struct if_vararg {};
			template<typename T>
			struct if_vararg<T, typename T::breed_is_vararg_>
				: public T
			{};

			template<typename T, typename Void = void>
			struct is_callable2_
				: public std::false_type
			{};
			template<typename T>
			struct is_callable2_<T, typename T::breed_is_callable_>
				: public std::true_type
			{};
			template<typename T, long Arity = sprout::breed::detail::template_arity<T>::value>
			struct is_callable_
				: public sprout::breed::detail::is_callable2_<T>
			{};
		}	// namespace detail
		//
		// is_callable
		//
		template<typename T>
		struct is_callable
			: public sprout::breed::detail::is_callable_<T>
		{};
		template<>
		struct is_callable<sprout::breed::_>
			: public std::true_type
		{};
		template<>
		struct is_callable<sprout::breed::callable>
			: public std::false_type
		{};
		template<typename PrimitiveTransform, typename X>
		struct is_callable<sprout::breed::transform<PrimitiveTransform, X> >
			: public std::false_type
		{};

		namespace detail {
			template<typename T, typename Void>
			struct is_transform_
				: public std::false_type
			{};
			template<typename T>
			struct is_transform_<T, typename T::breed_is_transform_>
				: public std::true_type
			{};
		}	// namespace detail
		//
		// is_transform
		//
		template<typename T>
		struct is_transform
			: public sprout::breed::detail::is_transform_<T>
		{};

		namespace detail {
			template<typename T, typename Void>
			struct is_aggregate_
				: public std::is_pod<T>
			{};
			template<typename Tag, typename Args, long N>
			struct is_aggregate_<sprout::breed::expr<Tag, Args, N>, void>
				: public std::false_type
			{};
			template<typename Tag, typename Args, long N>
			struct is_aggregate_<sprout::breed::basic_expr<Tag, Args, N>, void>
				: public std::false_type
			{};
			template<typename T>
			struct is_aggregate_<T, typename T::breed_is_aggregate_>
				: public std::true_type
			{};
		}	// namespace detail
		//
		// is_transform
		//
		template<typename T>
		struct is_aggregate
			: public sprout::breed::detail::is_aggregate_<T>
		{};

		//
		// is_transform
		//
		template<typename T, typename Void>
		struct is_expr
			: public std::false_type
		{};
		template<typename T>
		struct is_expr<T, typename T::breed_is_expr_>
			: public std::true_type
		{};
		template<typename T>
		struct is_expr<T&, void>
			: public is_expr<T>
		{};

		//
		// tag_of
		//
		template<typename Expr>
		struct tag_of {
		public:
			typedef typename Expr::breed_tag type;
		};
		template<typename Expr>
		struct tag_of<Expr&> {
		public:
			typedef typename Expr::breed_tag type;
		};

		//
		// arity_of
		//
		template<typename Expr>
		struct arity_of
			: public Expr::breed_arity
		{};
		template<typename Expr>
		struct arity_of<Expr&>
			: public Expr::breed_arity
		{};

		namespace result_of {
			//
			// as_expr
			//
			template<typename T, typename Domain>
			struct as_expr {
			public:
				typedef typename Domain::template as_expr<T>::result_type type;
			};

			//
			// as_child
			//
			template<typename T, typename Domain>
			struct as_child {
			public:
				typedef typename Domain::template as_child<T>::result_type type;
			};

			//
			// child
			//
			template<typename Expr, typename N>
			struct child
				: public child_c<Expr, N::value>
			{};

			//
			// value
			//
			template<typename Expr>
			struct value {
				static_assert(0 == Expr::breed_arity_c, "0 == Expr::breed_arity_c");
			public:
				typedef typename Expr::template breed_child<0>::type value_type;
				typedef typename sprout::breed::detail::term_traits<value_type>::value_type type;
			};
			template<typename Expr>
			struct value<Expr&> {
				static_assert(0 == Expr::breed_arity_c, "0 == Expr::breed_arity_c");
			public:
				typedef typename Expr:template breed_child<0>::type value_type;
				typedef typename sprout::breed::detail::term_traits<value_type>::reference type;
			};
			template<typename Expr>
			struct value<Expr const&> {
				static_assert(0 == Expr::breed_arity_c, "0 == Expr::breed_arity_c");
			public:
				typedef typename Expr:template breed_child<0>::type value_type;
				typedef typename sprout::breed::detail::term_traits<value_type>::const_reference type;
			};

			//
			// left
			//
			template<typename Expr>
			struct left
				: public sprout::breed::result_of::child_c<Expr, 0>
			{};
			//
			// right
			//
			template<typename Expr>
			struct right
				: public child_c<Expr, 1>
			{};
		}	// namespace result_of

		//
		// terminal
		//
		template<typename T>
		struct terminal
			: public sprout::breed::transform<sprout::breed::terminal<T>, int>
		{
		public:
			typedef sprout::breed::tag::terminal breed_tag;
			typedef sprout::breed::expr<sprout::breed::tag::terminal, sprout::breed::term<T>, 0> type;
			typedef sprout::breed::basic_expr<sprout::breed::tag::terminal, sprout::breed::term<T>, 0> breed_grammar;
		public:
			template<long N>
			struct breed_child
				: public sprout::tppack_at<N, T>
			{};
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			public:
				typedef Expr result_type;
			public:
#ifdef SPROUT_BREED_STRICT_RESULT_OF
				SPROUT_CONSTEXPR result_type
#else
				SPROUT_CONSTEXPR typename impl::expr_param
#endif
				operator()(
					typename impl::expr_param e,
					typename impl::state_param,
					typename impl::data_param
					) const
				{
					return e;
				}
			};
		};

		//
		// if_else_
		//
		template<typename T, typename U, typename V>
		struct if_else_
			: public sprout::breed::transform<if_else_<T, U, V>, int>
		{
		public:
			typedef sprout::breed::tag::if_else_ breed_tag;
			typedef sprout::breed::expr<
				sprout::breed::tag::if_else_, sprout::breed::sprout::breed::list<T, U, V>,
				3
			> type;
			typedef sprout::breed::basic_expr<
				sprout::breed::tag::if_else_,
				sprout::breed::sprout::breed::list<T, U, V>,
				3
			> breed_grammar;
		public:
			template<long N>
			struct breed_child
				: public sprout::tppack_at<N, T, U, V>
			{};
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::detail::pass_through_impl<sprout::breed::if_else_, Expr, State, Data>
			{};
		};

		//
		// nullary_expr
		//
		template<typename Tag, typename T>
		struct nullary_expr
			: public sprout::breed::transform<sprout::breed::nullary_expr<Tag, T>, int>
		{
		public:
			typedef Tag breed_tag;
			typedef sprout::breed::expr<Tag, sprout::breed::term<T>, 0> type;
			typedef sprout::breed::basic_expr<Tag, sprout::breed::term<T>, 0> breed_grammar;
		public:
			template<long N>
			struct breed_child
				: public sprout::tppack_at<N, T>
			{};
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::transform_impl<Expr, State, Data>
			{
			public:
				typedef Expr result_type;
			public:
#ifdef SPROUT_BREED_STRICT_RESULT_OF
				SPROUT_CONSTEXPR result_type
#else
				SPROUT_CONSTEXPR typename impl::expr_param
#endif
				operator()(
					typename impl::expr_param e,
					typename impl::state_param,
					typename impl::data_param
					) const
				{
					return e;
				}
			};
		};

		//
		// unary_expr
		//
		template<typename Tag, typename T>
		struct unary_expr
			: public sprout::breed::transform<sprout::breed::unary_expr<Tag, T>, int>
		{
		public:
			typedef Tag breed_tag;
			typedef sprout::breed::expr<Tag, sprout::breed::sprout::breed::list<T>, 1> type;
			typedef sprout::breed::basic_expr<Tag, sprout::breed::sprout::breed::list<T>, 1> breed_grammar;
		public:
			template<long N>
			struct breed_child
				: public sprout::tppack_at<N, T>
			{};
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::detail::pass_through_impl<sprout::breed::unary_expr, Expr, State, Data>
			{};
		};

		//
		// binary_expr
		//
		template<typename Tag, typename T, typename U>
		struct binary_expr
			: public sprout::breed::transform<sprout::breed::binary_expr<Tag, T, U>, int>
		{
		public:
			typedef Tag breed_tag;
			typedef sprout::breed::expr<Tag, sprout::breed::list<T, U>, 2> type;
			typedef sprout::breed::basic_expr<Tag, sprout::breed::list<T, U>, 2> breed_grammar;
		public:
			template<long N>
			struct breed_child
				: public sprout::tppack_at<N, T, U>
			{};
		public:
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::detail::pass_through_impl<binary_expr, Expr, State, Data>
			{};
		};

#		define SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(op) \
		template<typename T> \
		struct op \
			: public sprout::breed::transform<op<T>, int> \
		{ \
		public: \
			typedef sprout::breed::tag::op breed_tag; \
			typedef sprout::breed::expr<sprout::breed::tag::op, sprout::breed::list<T>, 1> type; \
			typedef sprout::breed::basic_expr<sprout::breed::tag::op, sprout::breed::list<T>, 1> breed_grammar; \
		public: \
			template<long N> \
			struct breed_child \
				: public sprout::tppack_at<N, T> \
			{}; \
		public: \
			template<typename Expr, typename State, typename Data> \
			struct impl \
				: public sprout::breed::detail::pass_through_impl<op, Expr, State, Data> \
			{}; \
		};
#		define SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(op) \
		template<typename T, typename U> \
		struct op \
			: public sprout::breed::transform<op<T, U>, int> \
		{ \
		public: \
			typedef sprout::breed::tag::op breed_tag; \
			typedef sprout::breed::expr<sprout::breed::tag::op, sprout::breed::list<T, U>, 2> type; \
			typedef sprout::breed::basic_expr<sprout::breed::tag::op, sprout::breed::list<T, U>, 2> breed_grammar; \
		public: \
			template<long N> \
			struct breed_child \
				: public sprout::tppack_at<N, T, U> \
			{}; \
		public: \
			template<typename Expr, typename State, typename Data> \
			struct impl \
				: public sprout::breed::detail::pass_through_impl<op, Expr, State, Data> \
			{}; \
		};

		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(unary_plus)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(negate)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(dereference)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(complement)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(address_of)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(logical_not)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(pre_inc)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(pre_dec)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(post_inc)
		SPROUT_BREED_DEFINE_UNARY_METAFUNCTION(post_dec)

		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(shift_left)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(shift_right)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(multiplies)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(divides)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(modulus)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(plus)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(minus)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(less)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(greater)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(less_equal)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(greater_equal)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(equal_to)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(not_equal_to)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(logical_or)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(logical_and)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(bitwise_or)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(bitwise_and)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(bitwise_xor)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(comma)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(mem_ptr)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(shift_left_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(shift_right_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(multiplies_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(divides_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(modulus_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(plus_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(minus_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(bitwise_or_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(bitwise_and_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(bitwise_xor_assign)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(subscript)
		SPROUT_BREED_DEFINE_BINARY_METAFUNCTION(member)

#		undef SPROUT_BREED_DEFINE_UNARY_METAFUNCTION
#		undef SPROUT_BREED_DEFINE_BINARY_METAFUNCTION

		//
		// function
		//
		template<typename... Args>
		struct function
			: public sprout::breed::transform<
				sprout::breed::function<Args...>,
				int
			>
		{
		public:
			typedef sprout::breed::tag::function breed_tag;
			typedef sprout::breed::expr<
				sprout::breed::tag::function, sprout::breed::list<Args...>,
				sizeof...(Args)
			> type;
			typedef sprout::breed::basic_expr<
				sprout::breed::tag::function, sprout::breed::list<Args...>,
				sizeof...(Args)
			> breed_grammar;
		public:
			template<long N>
			struct breed_child {
			public:
				typedef std::conditional<
					N < sizeof...(Args),
					sprout::tppack_at<N, Args...>,
					sprout::breed::detail::if_vararg<typename sprout::tppack_at<sizeof...(Args) - 1, Args...>::type>
				>::type::type 
			};
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::detail::pass_through_impl<function, Expr, State, Data>
			{};
		};

		//
		// nary_expr
		//
		template<typename Tag, typename... Args>
		struct nary_expr
			: public sprout::breed::transform<
				sprout::breed::nary_expr<Tag, Args...>,
				int
			>
		{
		public:
			typedef Tag breed_tag;
			typedef sprout::breed::expr<
				Tag,
				sprout::breed::list<Args...>,
				sizeof...(Args)
			> type;
			typedef sprout::breed::basic_expr<
				Tag,
				sprout::breed::list<Args...>,
				sizeof...(Args)
			> breed_grammar;
		public:
			template<long N>
			struct breed_child {
			public:
				typedef std::conditional<
					N < sizeof...(Args),
					sprout::tppack_at<N, Args...>,
					sprout::breed::detail::if_vararg<typename sprout::tppack_at<sizeof...(Args) - 1, Args...>::type>
				>::type::type 
			};
			template<typename Expr, typename State, typename Data>
			struct impl
				: public sprout::breed::detail::pass_through_impl<sprout::breed::nary_expr, Expr, State, Data>
			{};
		};

		namespace detail {
			template<template<typename...> class T, typename... Args>
			struct is_callable_<T<Args...>, sizeof...(Args)>
				: public std::is_same<
					typename sprout::tppack_at<sizeof...(Args) - 1, Args...>::type,
					sprout::breed::callable
				>
			{};
		}	// namespace detail

		namespace result_of {
			//
			// child_c
			//
			template<typename Expr, long N>
			struct child_c {
				static_assert(0 != Expr::proto_arity_c, "0 != Expr::proto_arity_c");
			public:
				typedef typename Expr::template breed_child<N>::type value_type;
				typedef typename sprout::breed::detail::expr_traits<value_type>::value_type type;
			};
			template<typename Expr, long N>
			struct child_c<Expr&, N> {
				static_assert(0 != Expr::proto_arity_c, "0 != Expr::proto_arity_c");
			public:
				typedef typename Expr::template breed_child<N>::type value_type;
				typedef typename detail::expr_traits<value_type>::reference type;
			public:
				static type call(Expr& e) {
					return e.proto_base().breed child<N>();
				}
			};
			template<typename Expr, long N>
			struct child_c<Expr const&, N> {
				static_assert(0 != Expr::proto_arity_c, "0 != Expr::proto_arity_c");
			public:
				typedef typename Expr::template breed_child<N>::type value_type;
				typedef typename detail::expr_traits<value_type>::const_reference type;
			public:
				static SPROUT_CONSTEXPR type call(Expr const& e) {
					return e.proto_base().breed child<N>();
				}
			};
		}	// namespace result_of

		namespace functional {
			//
			// as_expr
			//
			template<typename Domain>
			struct as_expr {
			public:
				SPROUT_BREED_CALLABLE()
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename T>
				struct result<This(T)> {
					typedef typename Domain::template as_expr<T>::result_type type;
				};
				template<typename This, typename T>
				struct result<This(T&)> {
					typedef typename Domain::template as_expr<T>::result_type type;
				};
			public:
				template<typename T>
				SPROUT_CONSTEXPR typename std::add_const<
					typename result<sprout::breed::as_expr(T const&)>::type
				>::type operator()(T const& t) const {
					return typename Domain::template as_expr<T const>()(t);
				}
				template<typename T>
				typename std::add_const<
					typename result<sprout::breed::as_expr(T&)>::type
				>::type operator()(T& t) const {
					return typename Domain::template as_expr<T>()(t);
				}
			};

			//
			// as_child
			//
			template<typename Domain>
			struct as_child {
			public:
				SPROUT_BREED_CALLABLE()
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename T>
				struct result<This(T)> {
				public:
					typedef typename Domain::template as_child<T>::result_type type;
				};
				template<typename This, typename T>
				struct result<This(T&)> {
				public:
					typedef typename Domain::template as_child<T>::result_type type;
				};
			public:
				template<typename T>
				SPROUT_CONSTEXPR typename std::add_const<
					typename result<as_child(T const&)>::type
				>::type operator()(T const& t) const {
					return typename Domain::template as_child<T const>()(t);
				}
				template<typename T>
				typename std::add_const<
					typename result<as_child(T&)>::type
				>::type operator()(T& t) const {
					return typename Domain::template as_child<T const>()(t);
				}
			};

			//
			// child_c
			//
			template<long N>
			struct child_c {
			public:
				SPROUT_BREED_CALLABLE()
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename Expr>
				struct result<This(Expr)> {
				public:
					typedef typename result_of::child_c<Expr, N>::type type;
				};
			public:
				template<typename Expr>
				SPROUT_CONSTEXPR typename result_of::child_c<Expr const&, N>::type operator()(Expr const& e) const {
					return result_of::child_c<Expr const&, N>::call(e);
				}
				template<typename Expr>
				typename result_of::child_c<Expr const&, N>::type operator()(Expr& e) const {
					return result_of::child_c<Expr&, N>::call(e);
				}
			};

			//
			// child
			//
			template<typename N>
			struct child {
			public:
				SPROUT_BREED_CALLABLE()
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename Expr>
				struct result<This(Expr)> {
				public:
					typedef typename result_of::child<Expr, N>::type type;
				};
			public:
				template<typename Expr>
				SPROUT_CONSTEXPR typename result_of::child<Expr const&, N>::type operator()(Expr const& e) const {
					return result_of::child<Expr const&, N>::call(e);
				}
				template<typename Expr>
				typename result_of::child<Expr&, N>::type operator()(Expr const& e) const {
					return result_of::child<Expr&, N>::call(e);
				}
			};

			//
			// value
			//
			struct value {
			public:
				SPROUT_BREED_CALLABLE()
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename Expr>
				struct result<This(Expr)> {
				public:
					typedef typename result_of::value<Expr>::type type;
				};
			public:
				template<typename Expr>
				SPROUT_CONSTEXPR typename result_of::value<Expr const&>::type operator()(Expr const& e) const {
					return e.breed_base().template child<0>();
				}
				template<typename Expr>
				typename result_of::value<Expr&>::type operator()(Expr& e) const {
					return e.breed_base().template child<0>();
				}
			};

			//
			// left
			//
			struct left {
			public:
				SPROUT_BREED_CALLABLE()
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename Expr>
				struct result<This(Expr)> {
				public:
					typedef typename result_of::left<Expr>::type type;
				};
			public:
				template<typename Expr>
				SPROUT_CONSTEXPR typename result_of::value<Expr const&>::type operator()(Expr const& e) const {
					return e.breed_base().template child<0>();
				}
				template<typename Expr>
				typename result_of::value<Expr&>::type operator()(Expr& e) const {
					return e.breed_base().template child<0>();
				}
			};

			//
			// right
			//
			struct right {
			public:
				SPROUT_BREED_CALLABLE()
			public:
				template<typename Sig>
				struct result;
				template<typename This, typename Expr>
				struct result<This(Expr)> {
				public:
					typedef typename result_of::right<Expr>::type type;
				};
			public:
				template<typename Expr>
				SPROUT_CONSTEXPR typename result_of::value<Expr const&>::type operator()(Expr const& e) const {
					return e.breed_base().template child<1>();
				}
				template<typename Expr>
				typename result_of::value<Expr&>::type operator()(Expr& e) const {
					return e.breed_base().template child<1>();
				}
			};
		}	// namespace functional

		//
		// as_expr
		//
		template<typename T>
		SPROUT_CONSTEXPR typename std::add_const<
			typename sprout::breed::result_of::as_expr<T const, sprout::breed::default_domain>::type
		>::type as_expr(T const& t) {
			return sprout::breed::default_domain::as_expr<T const>()(t);
		}
		template<typename T>
		typename std::add_const<
			typename sprout::breed::result_of::as_expr<T, sprout::breed::default_domain>::type
		>::type as_expr(T& t) {
			return sprout::breed::default_domain::as_expr<T>()(t);
		}
		template<typename Domain, typename T>
		SPROUT_CONSTEXPR typename std::add_const<
			typename sprout::breed::result_of::as_expr<T const, Domain>::type
		>::type as_expr(T const& t) {
			return typename Domain::template as_expr<T const>()(t);
		}
		template<typename Domain, typename T>
		typename std::add_const<
			typename sprout::breed::result_of::as_expr<T, Domain>::type
		>::type as_expr(T& t) {
			return typename Domain::template as_expr<T>()(t);
		}

		//
		// as_child
		//
		template<typename T>
		SPROUT_CONSTEXPR typename std::add_const<
			typename sprout::breed::result_of::as_child<T const, sprout::breed::default_domain>::type
		>::type as_child(T const& t)
		{
			return sprout::breed::default_domain::as_child<T const>()(t);
		}
		template<typename T>
		typename std::add_const<
			typename sprout::breed::result_of::as_child<T, sprout::breed::default_domain>::type
		>::type as_child(T& t)
		{
			return sprout::breed::default_domain::as_child<T>()(t);
		}
		template<typename Domain, typename T>
		SPROUT_CONSTEXPR typename std::add_const<
			typename sprout::breed::result_of::as_child<T const, Domain>::type
		>::type as_child(T const& t)
		{
			return typename Domain::template as_child<T const>()(t);
		}
		template<typename Domain, typename T>
		typename std::add_const<
			typename sprout::breed::result_of::as_child<T, Domain>::type
		>::type as_child(T& t)
		{
			return typename Domain::template as_child<T>()(t);
		}

		//
		// child
		//
		template<typename N, typename Expr>
		SPROUT_CONSTEXPR typename sprout::breed::result_of::child<Expr const&, N>::type child(Expr const& e) {
			return sprout::breed::result_of::child<Expr const&, N>::call(e);
		}
		template<typename N, typename Expr>
		typename sprout::breed::result_of::child<Expr&, N>::type child(Expr& e) {
			return sprout::breed::result_of::child<Expr&, N>::call(e);
		}
		template<typename Expr2>
		SPROUT_CONSTEXPR typename sprout::breed::detail::expr_traits<
			typename Expr2::breed_base_expr:template breed_child<0>::type
		>::const_reference child(Expr2 const& expr2) {
			return expr2.breed_base().template child<0>();
		}
		template<typename Expr2>
		typename sprout::breed::detail::expr_traits<
			typename Expr2::breed_base_expr:template breed_child<0>::type
		>::reference child(Expr2& expr2) {
			return expr2.breed_base().template child<0>();
		}

		//
		// child_c
		//
		template<long N, typename Expr>
		SPROUT_CONSTEXPR typename sprout::breed::result_of::child_c<Expr const&, N>::type child_c(Expr const& e) {
			return sprout::breed::result_of::child_c<Expr const&, N>::call(e);
		}
		template<long N, typename Expr>
		typename sprout::breed::result_of::child_c<Expr&, N>::type child_c(Expr& e) {
			return sprout::breed::result_of::child_c<Expr&, N>::call(e);
		}

		//
		// value
		//
		template<typename Expr>
		SPROUT_CONSTEXPR typename sprout::breed::result_of::value<Expr const&>::type value(Expr const& e) {
			return e.breed_base().template child<0>();
		}
		template<typename Expr>
		typename sprout::breed::result_of::value<Expr&>::type value(Expr& e) {
			return e.breed_base().template child<0>();
		}

		//
		// left
		//
		template<typename Expr>
		SPROUT_CONSTEXPR typename sprout::breed::result_of::left<Expr const&>::type left(Expr const& e) {
			return e.breed_base().template child<0>();
		}
		template<typename Expr>
		typename sprout::breed::result_of::left<Expr&>::type left(Expr& e) {
			return e.breed_base().template child<0>();
		}

		//
		// right
		//
		template<typename Expr>
		SPROUT_CONSTEXPR typename sprout::breed::result_of::right<Expr const&>::type right(Expr const& e) {
			return e.breed_base().template child<1>();
		}
		template<typename Expr>
		typename sprout::breed::result_of::right<Expr&>::type right(Expr& e) {
			return e.breed_base().template child<1>();
		}

		//
		// is_callable
		//
		template<typename Domain>
		struct is_callable<sprout::breed::functional::as_expr<Domain> >
			: public std::true_type
		{};
		template<typename Domain>
		struct is_callable<sprout::breed::functional::as_child<Domain> >
			: public std::true_type
		{};
		template<long N>
		struct is_callable<sprout::breed::functional::child_c<N> >
			: public std::true_type
		{};
		template<typename N>
		struct is_callable<sprout::breed::functional::child<N> >
			: public std::true_type
		{};
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_TRAITS_HPP
