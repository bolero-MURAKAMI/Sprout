#ifndef SPROUT_BREED_DETAIL_AS_EXPR_HPP
#define SPROUT_BREED_DETAIL_AS_EXPR_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/breed/breed_fwd.hpp>
#include <sprout/breed/args.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			template<typename Generator>
			struct base_generator {
			public:
				typedef Generator type;
			};
			template<typename Generator>
			struct base_generator<sprout::breed::use_basic_expr<Generator> > {
			public:
				typedef Generator type;
			};

			template<typename T, typename Generator, bool WantsBasicExpr>
			struct as_expr;
			template<typename T, typename Generator>
			struct as_expr<T, Generator, false> {
			public:
				typedef typename sprout::breed::detail::term_traits<T const&>::value_type value_type;
				typedef sprout::breed::expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<value_type>,
					0
				> expr_type;
				typedef typename Generator::template result<Generator(expr_type)>::type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return Generator()(expr_type::make(t));
				}
			};
			template<typename T, typename Generator>
			struct as_expr<T, Generator, true> {
			public:
				typedef typename sprout::breed::detail::term_traits<T const&>::value_type value_type;
				typedef sprout::breed::basic_expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<value_type>,
					0
				> expr_type;
				typedef typename Generator::template result<Generator(expr_type)>::type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return Generator()(expr_type::make(t));
				}
			};
			template<typename T>
			struct as_expr<T, sprout::breed::default_generator, false> {
			public:
				typedef typename sprout::breed::detail::term_traits<T const&>::value_type value_type;
				typedef sprout::breed::expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<value_type>,
					0
				> result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return result_type::make(t);
				}
			};
			template<typename T>
			struct as_expr<T, sprout::breed::default_generator, true> {
			public:
				typedef typename sprout::breed::detail::term_traits<T const&>::value_type value_type;
				typedef sprout::breed::basic_expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<value_type>,
					0
				> result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return result_type::make(t);
				}
			};

			template<typename T, typename Generator, bool WantsBasicExpr>
			struct as_child;
			template<typename T, typename Generator>
			struct as_child<T, Generator, false> {
			public:
				typedef T const& reference;
				typedef sprout::breed::expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<reference>,
					0
				> expr_type;
				typedef typename Generator::template result<Generator(expr_type)>::type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return Generator()(expr_type::make(t));
				}
			};
			template<typename T, typename Generator>
			struct as_child<T, Generator, true> {
			public:
				typedef T const& reference;
				typedef sprout::breed::basic_expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<reference>,
					0
				> expr_type;
				typedef typename Generator::template result<Generator(expr_type)>::type result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return Generator()(expr_type::make(t));
				}
			};
			template<typename T>
			struct as_child<T, sprout::breed::default_generator, false> {
			public:
				typedef T const& reference;
				typedef sprout::breed::expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<reference>,
					0
				> result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return result_type::make(t);
				}
			};
			template<typename T>
			struct as_child<T, sprout::breed::default_generator, true> {
			public:
				typedef T const& reference;
				typedef sprout::breed::basic_expr<
					sprout::breed::tag::terminal,
					sprout::breed::term<reference>,
					0
				> result_type;
			public:
				SPROUT_CONSTEXPR result_type operator()(T const& t) const {
					return result_type::make(t);
				}
			};
		}	// namespace detail
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_DETAIL_AS_EXPR_HPP
