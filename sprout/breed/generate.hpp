#ifndef SPROUT_BREED_GENERATE_HPP
#define SPROUT_BREED_GENERATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/args.hpp>
#include <sprout/breed/detail/std_result_of.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename Expr>
			struct by_value_generator_;
			template<typename Tag, typename Arg>
			struct by_value_generator_<sprout::breed::expr<Tag, sprout::breed::term<Arg>, 0> > {
			public:
				typedef breed::expr<
					Tag,
					sprout::breed::term<typename sprout::breed::detail::term_traits<Arg>::value_type>,
					0
				> type;
			public:
				static SPROUT_CONSTEXPR type call(breed::expr<Tag, term<Arg>, 0> const& e) {
					return type(e.template child<0>());
				}
			};
			template<typename Tag, typename Arg>
			struct by_value_generator_<sprout::breed::basic_expr<Tag, sprout::breed::term<Arg>, 0> > {
			public:
				typedef breed::expr<
					Tag,
					sprout::breed::term<typename sprout::breed::detail::term_traits<Arg>::value_type>,
					0
				> type;
			public:
				static SPROUT_CONSTEXPR type call(breed::expr<Tag, term<Arg>, 0> const& e) {
					return type(e.template child<0>());
				}
			};
			template<typename Tag, typename... Args>
			struct by_value_generator_<
				sprout::breed::expr<Tag, sprout::breed::list<Args...>, sizeof...(Args)>
			> {
			public:
				typedef sprout::breed::list<Args...> src_args;
				typedef sprout::breed::list<typename sprout::breed::detail::uncvref<Args>::type...> dst_args;
				typedef sprout::breed::expr<Tag, src_args, N> src_type;
				typedef sprout::breed::expr<Tag, dst_args, N> type;
			private:
				template<std::ptrdiff_t... Indexes>
				static SPROUT_CONSTEXPR type call_impl(src_type const& e, sprout::index_tuple<Indexes...>) {
					return type(e.template child<Indexes>()...);
				}
			public:
				static SPROUT_CONSTEXPR type call(src_type const& e) {
					return call_impl(typename sprout::index_range<0, sizeof...(Args)>::type());
				}
			};
			template<typename Tag, typename... Args>
			struct by_value_generator_<
				sprout::breed::basic_expr<Tag, sprout::breed::list<Args...>, sizeof...(Args)>
			> {
			public:
				typedef sprout::breed::list<Args...> src_args;
				typedef sprout::breed::list<typename sprout::breed::detail::uncvref<Args>::type...> dst_args;
				typedef sprout::breed::basic_expr<Tag, src_args, N> src_type;
				typedef sprout::breed::basic_expr<Tag, dst_args, N> type;
			private:
				template<std::ptrdiff_t... Indexes>
				static SPROUT_CONSTEXPR type call_impl(src_type const& e, sprout::index_tuple<Indexes...>) {
					return type(e.template child<Indexes>()...);
				}
			public:
				static SPROUT_CONSTEXPR type call(src_type const& e) {
					return call_impl(typename sprout::index_range<0, sizeof...(Args)>::type());
				}
			};
		}	// namespace detail

		//
		// use_basic_expr
		//
		template<typename Generator>
		struct use_basic_expr
			: public Generator
		{
		public:
			SPROUT_BREED_USE_BASIC_EXPR();
		};

		//
		// default_generator
		//
		struct default_generator {
		public:
			SPROUT_BREED_CALLABLE()
		public:
			template<typename Sig>
			struct result;
			template<typename This, typename Expr>
			struct result<This(Expr)> {
			public:
				typedef Expr type;
			};
		public:
			template<typename Expr>
#ifdef SPROUT_BREED_STRICT_RESULT_OF
			SPROUT_CONSTEXPR Expr
#else
			SPROUT_CONSTEXPR Expr const&
#endif
			operator()(Expr const& e) const {
				return e;
			}
		};

		//
		// basic_default_generator
		//
		struct basic_default_generator
			: public sprout::breed::use_basic_expr<sprout::breed::default_generator>
		{};
		
		//
		// generator
		//
		template<template<typename> class Extends>
		struct generator {
			SPROUT_BREED_CALLABLE()
			SPROUT_BREED_USE_BASIC_EXPR()
		public:
			template<typename Sig>
			struct result;
			template<typename This, typename Expr>
			struct result<This(Expr)> {
			public:
				typedef Extends<Expr> type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr&)> {
			public:
				typedef Extends<Expr> type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr const&)>
			{
 			public:
				typedef Extends<Expr> type;
			};
		public:
			template<typename Expr>
			SPROUT_CONSTEXPR Extends<Expr> operator()(Expr const& e) const {
				return Extends<Expr>(e);
			}
		};

		//
		// pod_generator
		//
		template<template<typename> class Extends>
		struct pod_generator {
		public:
			SPROUT_BREED_CALLABLE()
			SPROUT_BREED_USE_BASIC_EXPR()
		public:
			template<typename Sig>
			struct result;
			template<typename This, typename Expr>
			struct result<This(Expr)> {
			public:
				typedef Extends<Expr> type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr&)> {
			public:
				typedef Extends<Expr> type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr const&)> {
			public:
				typedef Extends<Expr> type;
			};
		public:
			template<typename Expr>
			SPROUT_CONSTEXPR Extends<Expr> operator()(Expr const& e) const {
				return Extends<Expr>(e);
			}
		};

		//
		// by_value_generator
		//
		struct by_value_generator {
		public:
			SPROUT_BREED_CALLABLE()
		public:
			template<typename Sig>
			struct result;
			template<typename This, typename Expr>
			struct result<This(Expr)> {
			public:
				typedef typename sprout::breed::detail::by_value_generator_<Expr>::type type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr&)> {
			public:
				typedef typename sprout::breed::detail::by_value_generator_<Expr>::type type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr const&)> {
			public:
				typedef typename sprout::breed::detail::by_value_generator_<Expr>::type type;
			};
		public:
			template<typename Expr>
			SPROUT_CONSTEXPR typename result<by_value_generator(Expr)>::type operator()(Expr const& e) const {
				return sprout::breed::detail::by_value_generator_<Expr>::call(e);
			}
		};

		//
		// compose_generators
		//
		template<typename First, typename Second>
		struct compose_generators {
		public:
			SPROUT_BREED_CALLABLE()
		public:
			template<typename Sig>
			struct result;
			template<typename This, typename Expr>
			struct result<This(Expr)> {
			public:
				typedef typename Second::template result<
					Second(typename First::template result<First(Expr)>::type)
				>::type type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr&)> {
			public:
				typedef typename Second::template result<
					Second(typename First::template result<First(Expr)>::type)
				>::type type;
			};
			template<typename This, typename Expr>
			struct result<This(Expr const&)> {
			public:
				typedef typename Second::template result<
					Second(typename First::template result<First(Expr)>::type)
				>::type type;
			};
		public:
			template<typename Expr>
			SPROUT_CONSTEXPR typename result<compose_generators(Expr)>::type operator()(Expr const& e) const {
				return Second()(First()(e));
			}
		};

		//
		// wants_basic_expr
		//
		template<typename Generator, typename Void>
		struct wants_basic_expr
			: public std::false_type
		{};
		template<typename Generator>
		struct wants_basic_expr<Generator, typename Generator::breed_use_basic_expr_>
			: public std::true_type
		{};

		//
		// is_callable
		//
		template<>
		struct is_callable<default_generator>
			: public std::true_type
		{};
		template<template<typename> class Extends>
		struct is_callable<sprout::breed::generator<Extends> >
			: public std::true_type
		{};
		template<template<typename> class Extends>
		struct is_callable<sprout::breed::pod_generator<Extends> >
			: public std::true_type
		{};
		template<>
		struct is_callable<sprout::breed::by_value_generator>
			: public std::true_type
		{};
		template<typename First, typename Second>
		struct is_callable<sprout::breed::compose_generators<First, Second> >
			: public std::true_type
		{};

		namespace detail {
			template<typename Expr>
			struct std_result_of<sprout::breed::default_domain(Expr)> {
			public:
				typedef Expr type;
			};
			template<typename Expr>
			struct std_result_of<sprout::breed::basic_default_domain(Expr)> {
			public:
				typedef Expr type;
			};
			template<typename Expr>
			struct std_result_of<sprout::breed::default_generator(Expr)> {
			public:
				typedef Expr type;
			};
			template<typename Expr>
			struct std_result_of<sprout::breed::basic_default_generator(Expr)> {
			public:
				typedef Expr type;
			};
		}	// namespace detail
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_GENERATE_HPP
