#ifndef SPROUT_BREED_EXPR_HPP
#define SPROUT_BREED_EXPR_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/args.hpp>
#include <sprout/breed/traits.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			struct not_a_valid_type {
			private:
				SPROUT_CONSTEXPR not_a_valid_type() {}
			};

			template<typename Tag, typename Arg>
			struct address_of_hack {
			public:
				typedef sprout::breed::detail::not_a_valid_type type;
			};
			template<typename Expr>
			struct address_of_hack<sprout::breed::tag::address_of, Expr&> {
				typedef Expr* type;
			};

			template<typename T, typename Expr, typename Arg>
			SPROUT_CONSTEXPR Expr make_terminal(T const& t, Expr*, sprout::breed::term<Arg> const*) {
				return Expr(t);
			}
			template<typename T, typename Expr, typename Arg, std::size_t N>
			SPROUT_CONSTEXPR Expr make_terminal(T const (&t)[N], Expr const*, sprout::breed::term<Arg[N]> const*) {
				return SPROUT_ASSERT_MSG(0, "Sorry, not implemented."), Expr();
			}

			template<typename T, typename U>
			struct same_cv {
			public:
				typedef U type;
			};
			template<typename T, typename U>
			struct same_cv<T const, U> {
			public:
				typedef U const type;
			};
		}	// namespace detail

		namespace result_of {
			namespace detail {
				template<typename Expr, typename Domain, typename... Args>
				struct funop_impl {
				public:
					typedef typename sprout::breed::base_expr<
						Domain,
						sprout::breed::tag::function,
						sprout::breed::list<
							Expr const&,
							typename sprout::breed::result_of::as_child<Args, Domain>::type...
						>
					>::type type;
				public:
					static SPROUT_CONSTEXPR type const call(
						Expr const& e,
						Args const&... args
						) const
					{
						return type(
							e,
							sprout::breed::as_child<Domain>(args)...
							);
					}
				};
			}	// namespace detail
			//
			// funop
			//
			template<typename Sig, typename This, typename Domain>
			struct funop;
			template<typename Expr, typename... Args, typename This, typename Domain>
			struct funop<Expr(Args...), This, Domain>
				: public sprout::breed::result_of::detail::funop_impl<
					typename sprout::breed::detail::same_cv<Expr, This>::type,
					Domain,
					typename std::remove_reference<Args>::type...
				>
			{};
		}	// namespace result_of

		namespace exprns_ {
			//
			// basic_expr
			//
			template<typename Tag, typename Arg>
			struct basic_expr<Tag, term<Arg>, 0> {
			public:
				SPROUT_STATIC_CONSTEXPR long breed_arity_c = 0;
			public:
				typedef Tag breed_tag;
				typedef std::integral_constant<long, breed_arity_c> breed_arity;
				typedef basic_expr breed_base_expr;
				typedef sprout::breed::term<Arg> breed_args;
				typedef basic_expr breed_grammar;
				typedef sprout::breed::basic_default_domain breed_domain;
				typedef sprout::breed::default_generator breed_generator;
				typedef sprout::breed::tag::breed_expr fusion_tag;
				typedef basic_expr breed_derived_expr;
				typedef void breed_is_expr_;
				typedef sprout::breed::detail::not_a_valid_type address_of_hack_type_;
			public:
				template<long N>
				struct breed_child
					: public sprout::tppack_at<N, Arg>
				{};
			public:
				template<typename A>
				static SPROUT_CONSTEXPR basic_expr make(A const& arg) {
					return sprout::breed::detail::make_terminal(
						arg,
						static_cast<basic_expr const*>(0),
						static_cast<breed_args const*>(0)
						);
				}
			private:
				sprout::tuples::tuple<Arg> children_;
			public:
				explicit SPROUT_CONSTEXPR basic_expr(Arg const& arg)
					: children_(arg)
				{}
				template<long N>
				SPROUT_CONSTEXPR typename breed_child<N>::type const& child() const {
					return sprout::tuples::get<N>(children_);
				}
				template<long N>
				typename breed_child<N>::type const& child() {
					return sprout::tuples::get<N>(children_);
				}
				SPROUT_CONSTEXPR basic_expr const& breed_base() const {
					return *this;
				}
				basic_expr& breed_base() {
					return *this;
				}
			};
			template<typename Tag, typename... Args>
			struct basic_expr<Tag, sprout::breed::list<Args...>, sizeof...(Args)> {
			public:
				SPROUT_STATIC_CONSTEXPR long breed_arity_c = sizeof...(Args);
			public:
				typedef Tag breed_tag;
				typedef std::integral_constant<long, breed_arity_c> breed_arity;
				typedef basic_expr breed_base_expr;
				typedef sprout::breed::list<Args...> breed_args;
				typedef basic_expr breed_grammar;
				typedef sprout::breed::basic_default_domain breed_domain;
				typedef sprout::breed::default_generator breed_generator;
				typedef sprout::breed::tag::breed_expr fusion_tag;
				typedef basic_expr breed_derived_expr;
				typedef void breed_is_expr_;
				typedef sprout::breed::detail::not_a_valid_type address_of_hack_type_;
			public:
				template<long N>
				struct breed_child
					: public sprout::tppack_at<N, Args...>
				{};
			public:
				template<typename... As>
				static SPROUT_CONSTEXPR basic_expr make(As const&... args) {
					return basic_expr(args...);
				}
			private:
				sprout::tuples::tuple<Args...> children_;
			public:
				explicit SPROUT_CONSTEXPR basic_expr(Args const&... args)
					: children_(args...)
				{}
				template<long N>
				SPROUT_CONSTEXPR typename breed_child<N>::type const& child() const {
					return sprout::tuples::get<N>(children_);
				}
				template<long N>
				typename breed_child<N>::type const& child() {
					return sprout::tuples::get<N>(children_);
				}
				SPROUT_CONSTEXPR basic_expr const& breed_base() const {
					return *this;
				}
				basic_expr& breed_base() {
					return *this;
				}
			};

			//
			// expr
			//
			template<typename Tag, typename Arg>
			struct expr<Tag, sprout::breed::term<Arg>, 0> {
			public:
				SPROUT_STATIC_CONSTEXPR long breed_arity_c = 0;
			public:
				typedef Tag breed_tag;
				typedef std::integral_constant<long, breed_arity_c> breed_arity;
				typedef expr breed_base_expr;
				typedef sprout::breed::term<Arg> breed_args;
				typedef basic_expr<Tag, breed_args, 0> breed_grammar;
				typedef sprout::breed::basic_default_domain breed_domain;
				typedef sprout::breed::default_generator breed_generator;
				typedef sprout::breed::tag::breed_expr fusion_tag;
				typedef expr breed_derived_expr;
				typedef void proto_is_expr_;
				typedef sprout::breed::detail::not_a_valid_type address_of_hack_type_;
			public:
				template<long N>
				struct breed_child
					: public sprout::tppack_at<N, Arg>
				{};
				template<typename Sig>
				struct result {
				public:
					typedef typename sprout::breed::result_of::funop<
						Sig,
						expr,
						sprout::breed::default_domain
					>::type type;
				};
			public:
				template<typename A>
				static SPROUT_CONSTEXPR expr make(A const& arg) {
					return sprout::breed::detail::make_terminal(
						arg,
						static_cast<expr const*>(0),
						static_cast<breed_args const*>(0)
						);
				}
			private:
				sprout::tuples::tuple<Arg> children_;
			public:
				explicit SPROUT_CONSTEXPR expr(Arg const& arg)
					: children_(arg)
				{}
				template<long N>
				SPROUT_CONSTEXPR typename breed_child<N>::type const& child() const {
					return sprout::tuples::get<N>(children_);
				}
				template<long N>
				typename breed_child<N>::type const& child() {
					return sprout::tuples::get<N>(children_);
				}
				SPROUT_CONSTEXPR expr const& breed_base() const {
					return *this;
				}
				expr& breed_base() {
					return *this;
				}
				SPROUT_CONSTEXPR sprout::breed::expr<
					sprout::breed::tag::assign,
					sprout::breed::list<expr const&, expr const&>,
					2
				> operator=(expr const& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::assign,
						sprout::breed::list<expr const&, expr const&>,
						2
					>(*this, arg);
				}
				template<typename A>
				SPROUT_CONSTEXPR sprout::breed::expr<
					sprout::breed::tag::assign,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
					2
				> operator=(A const& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::assign,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename A>
				sprout::breed::expr<
					sprout::breed::tag::assign,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
					2
				> operator=(A& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::assign,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename A>
				SPROUT_CONSTEXPR sprout::breed::expr<
					sprout::breed::tag::subscript,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
					2
				> operator[](A const& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::subscript,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename A>
				sprout::breed::expr<
					sprout::breed::tag::subscript,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
					2
				> operator[](A& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::subscript,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename... As>
				SPROUT_CONSTEXPR typename sprout::breed::result_of::funop<
					expr(As const&...),
					expr,
					sprout::breed::default_domain
				>::type operator()(As const&... args) const {
					return sprout::breed::result_of::funop<
						expr(As const&...),
						expr,
						sprout::breed::default_domain
					>::call(*this, args...);
				}
			};
			template<typename Tag, typename... Args>
			struct expr<Tag, sprout::breed::list<Args...>, sizeof...(Args)> {
			public:
				SPROUT_STATIC_CONSTEXPR long breed_arity_c = sizeof...(Args);
			public:
				typedef Tag breed_tag;
				typedef std::integral_constant<long, breed_arity_c> breed_arity;
				typedef expr breed_base_expr;
				typedef sprout::breed::list<Args...> breed_args;
				typedef basic_expr<Tag, breed_args, 0> breed_grammar;
				typedef sprout::breed::basic_default_domain breed_domain;
				typedef sprout::breed::default_generator breed_generator;
				typedef sprout::breed::tag::breed_expr fusion_tag;
				typedef expr breed_derived_expr;
				typedef void proto_is_expr_;
				typedef sprout::breed::detail::not_a_valid_type address_of_hack_type_;
			public:
				template<long N>
				struct breed_child
					: public sprout::tppack_at<N, Args...>
				{};
				template<typename Sig>
				struct result {
				public:
					typedef typename sprout::breed::result_of::funop<
						Sig,
						expr,
						sprout::breed::default_domain
					>::type type;
				};
			public:
				template<typename... As>
				static SPROUT_CONSTEXPR basic_expr make(As const&... args) {
					return basic_expr(args...);
				}
			private:
				sprout::tuples::tuple<Arg> children_;
			public:
				explicit SPROUT_CONSTEXPR basic_expr(Args const&... args)
					: children_(args...)
				{}
				template<long N>
				SPROUT_CONSTEXPR typename breed_child<N>::type const& child() const {
					return sprout::tuples::get<N>(children_);
				}
				template<long N>
				typename breed_child<N>::type const& child() {
					return sprout::tuples::get<N>(children_);
				}
				SPROUT_CONSTEXPR basic_expr const& breed_base() const {
					return *this;
				}
				basic_expr& breed_base() {
					return *this;
				}
				SPROUT_CONSTEXPR sprout::breed::expr<
					sprout::breed::tag::assign,
					sprout::breed::list<expr const&, expr const&>,
					2
				> operator=(expr const& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::assign,
						sprout::breed::list<expr const&, expr const&>,
						2
					>(*this, arg);
				}
				template<typename A>
				SPROUT_CONSTEXPR sprout::breed::expr<
					sprout::breed::tag::assign,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
					2
				> operator=(A const& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::assign,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename A>
				sprout::breed::expr<
					sprout::breed::tag::assign,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
					2
				> operator=(A& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::assign,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename A>
				SPROUT_CONSTEXPR sprout::breed::expr<
					sprout::breed::tag::subscript,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
					2
				> operator[](A const& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::subscript,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A const>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename A>
				sprout::breed::expr<
					sprout::breed::tag::subscript,
					sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
					2
				> operator[](A& arg) const {
					return sprout::breed::expr<
						sprout::breed::tag::subscript,
						sprout::breed::list<expr const&, typename sprout::breed::result_of::as_child<A>::type>,
						2
					>(*this, sprout::breed::as_child(arg));
				}
				template<typename... As>
				SPROUT_CONSTEXPR typename sprout::breed::result_of::funop<
					expr(As const&...),
					expr,
					sprout::breed::default_domain
				>::type operator()(As const&... args) const {
					return sprout::breed::result_of::funop<
						expr(As const&...),
						expr,
						sprout::breed::default_domain
					>::call(*this, args...);
				}
			};
		}	// namespace exprns_

		//
		// unexpr
		//
		template<typename Expr>
		struct unexpr
			: public Expr
		{
		public:
			SPROUT_BREED_UNEXPR();
		public:
			explicit SPROUT_CONSTEXPR unexpr(Expr const& e)
				: Expr(e)
			{}
			using Expr::operator=;
		};
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_EXPR_HPP
