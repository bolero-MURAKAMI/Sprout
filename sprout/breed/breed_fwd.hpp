#ifndef SPROUT_BREED_BREED_FWD_HPP
#define SPROUT_BREED_BREED_FWD_HPP

#include <cstddef>
#include <climits>
#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace breed {
		namespace detail {
			typedef char yes_type;
			typedef char (&no_type)[2];

			template<long N>
			struct sized_type {
			public:
				typedef char (&type)[N];
			};

			struct dont_care;
			struct undefined;
			struct not_a_valid_type;

			struct private_type_ {
			public:
				SPROUT_CONSTEXPR private_type_ operator,(int) const;	// ???
			};

			template<typename T>
			struct uncvref {
			public:
				typedef T type;
			};
			template<typename T>
			struct uncvref<T const> {
			public:
				typedef T type;
			};
			template<typename T>
			struct uncvref<T&> {
			public:
				typedef T type;
			};
			template<typename T>
			struct uncvref<T const&> {
			public:
				typedef T type;
			};
			template<typename T, std::size_t N>
			struct uncvref<T const[N]> {
			public:
				typedef T type[N];
			};
			template<typename T, std::size_t N>
			struct uncvref<T (&)[N]> {
			public:
				typedef T type[N];
			};
			template<typename T, std::size_t N>
			struct uncvref<T const (&)[N]> {
			public:
				typedef T type[N];
			};

			struct ignore {
			public:
				ignore() = default;
				ignore(ignore const&) = default;
				ignore(ignore&&) = default;
				template<typename T>
				SPROUT_CONSTEXPR ignore(T const&) {}
			};

			struct _default;

			struct not_a_domain;
			struct not_a_grammar;
			struct not_a_generator;

			template<typename T, typename Void = void>
			struct is_transform_;

			template<typename T, typename Void = void>
			struct is_aggregate_;
		}	// namespace detail

		typedef sprout::breed::detail::ignore const ignore;

		namespace argsns_ {
			template<typename Arg>
			struct term;

			template<typename... Args>
			struct list;
		}	// namespace argsns_
		using namespace argsns_;

		namespace tagns_ {
			namespace tag {
				struct terminal;
				struct unary_plus;
				struct negate;
				struct dereference;
				struct complement;
				struct address_of;
				struct logical_not;
				struct pre_inc;
				struct pre_dec;
				struct post_inc;
				struct post_dec;

				struct shift_left;
				struct shift_right;
				struct multiplies;
				struct divides;
				struct modulus;
				struct plus;
				struct minus;
				struct less;
				struct greater;
				struct less_equal;
				struct greater_equal;
				struct equal_to;
				struct not_equal_to;
				struct logical_or;
				struct logical_and;
				struct bitwise_and;
				struct bitwise_or;
				struct bitwise_xor;
				struct comma;
				struct mem_ptr;

				struct assign;
				struct shift_left_assign;
				struct shift_right_assign;
				struct multiplies_assign;
				struct divides_assign;
				struct modulus_assign;
				struct plus_assign;
				struct minus_assign;
				struct bitwise_and_assign;
				struct bitwise_or_assign;
				struct bitwise_xor_assign;
				struct subscript;
				struct member;
				struct if_else_;
				struct function;

				// Fusion tags
				struct breed_expr;
				struct breed_expr_iterator;
				struct breed_flat_view;
			}	// namespace tag
		}	// namespace tagns_
		using namespace tagns_;

		template<typename Expr>
		struct tag_of;

		struct _;

		struct default_generator;

		struct basic_default_generator;

		template<template<typename> class Extends>
		struct generator;

		template<template<typename> class Extends>
		struct pod_generator;

		struct by_value_generator;

		template<typename First, typename Second>
		struct compose_generators;

		template<typename Generator, typename Void = void>
		struct wants_basic_expr;

		template<typename Generator>
		struct use_basic_expr;

		namespace domainns_ {
			typedef sprout::breed::detail::not_a_domain no_super_domain;

			template<
				typename Generator = sprout::breed::default_generator,
				typename Grammar = sprout::breed::_,
				typename Super = sprout::breed::domainns_::no_super_domain
			>
			struct domain;

			struct default_domain;

			struct basic_default_domain;

			struct deduce_domain;

			template<
				typename Domain,
				typename Tag,
				typename Args,
				bool WantsBasicExpr = sprout::breed::wants_basic_expr<typename Domain::breed_generator>::value
			>
			struct base_expr;
		}	// namespace domainns_
		using namespace domainns_;

		namespace exprns_ {
			template<typename Tag, typename Args, long Arity = Args::arity>
			struct basic_expr;

			template<typename Tag, typename Args, long Arity = Args::arity>
			struct expr;

			template<
				typename Expr,
				typename Derived,
				typename Domain = sprout::breed::default_domain,
				long Arity = Expr::breed_arity_c
			>
			struct extends;

			template<typename This, typename Fun, typename Domain>
			struct virtual_member;

			struct is_breed_expr;
		}
		using exprns_::expr;
		using exprns_::basic_expr;
		using exprns_::extends;
		using exprns_::is_breed_expr;

		template<typename... Args>
		struct or_;

		template<typename... Args>
		struct and_;

		template<typename Grammar>
		struct not_;

		template<
			typename Condition,
			typename Then = sprout::breed::_,
			typename Else = sprout::breed::not_<sprout::breed::_>
		>
		struct if_;

		template<typename Cases, typename Transform = sprout::breed::tag_of<sprout::breed::_>()>
		struct switch_;

		template<typename T>
		struct exact;

		template<typename T>
		struct convertible_to;

		template<typename Grammar>
		struct vararg;

		SPROUT_STATIC_CONSTEXPR int N = (INT_MAX >> 10);

		namespace context {
			struct null_context;

			template<typename Expr, typename Context, long Arity = Expr::breed_arity_c>
			struct null_eval;

			struct default_context;

			template<
				typename Expr,
				typename Context,
				typename Tag = typename Expr::breed_tag,
				long Arity = Expr::breed_arity_c
			>
			struct default_eval;

			template<typename Derived, typename DefaultCtx = sprout::breed::context::default_context>
			struct callable_context;

			template<typename Expr, typename Context, long Arity = Expr::breed_arity_c>
			struct callable_eval;
		}	// namespace context

		using context::null_context;
		using context::null_eval;
		using context::default_context;
		using context::default_eval;
		using context::callable_context;
		using context::callable_eval;

		namespace utility {
			template<typename T, typename Domain = sprout::breed::default_domain>
			struct literal;
		}	// namespace context

		using utility::literal;

		namespace result_of {
			template<typename T, typename Domain = sprout::breed::default_domain>
			struct as_expr;

			template<typename T, typename Domain = sprout::breed::default_domain>
			struct as_child;

			template<typename Expr, typename N = std::integral_constant<long, 0> >
			struct child;

			template<typename Expr, long N>
			struct child_c;

			template<typename Expr>
			struct left;

			template<typename Expr>
			struct right;

			template<typename Expr>
			struct deep_copy;

			template<typename Expr, typename Context>
			struct eval;

			template<
				typename Tag,
				typename DomainOrArg,
				typename... Args
			>
			struct make_expr;

			template<typename Tag, typename DomainOrSequence, typename SequenceOrVoid = void, typename Void = void>
			struct unpack_expr;
		}	// namespace result_of

		template<typename T, typename Void = void>
		struct is_expr;

		template<typename T, typename Void = void>
		struct is_domain;

		template<typename SubDomain, typename SuperDomain>
		struct is_sub_domain_of;

		template<typename Expr>
		struct arity_of;

		template<typename T, typename Void = void>
		struct domain_of;

		template<typename Expr, typename Grammar>
		struct matches;

		template<typename Tag, typename Arg>
		struct unary_expr;

		template<typename Tag, typename Left, typename Right>
		struct binary_expr;

		template<typename Tag, typename... Args>
		struct nary_expr;

		template<typename T>
		struct terminal;
		template<typename T>
		struct unary_plus;
		template<typename T>
		struct negate;
		template<typename T>
		struct dereference;
		template<typename T>
		struct complement;
		template<typename T>
		struct address_of;
		template<typename T>
		struct logical_not;
		template<typename T>
		struct pre_inc;
		template<typename T>
		struct pre_dec;
		template<typename T>
		struct post_inc;
		template<typename T>
		struct post_dec;

		template<typename T, typename U>
		struct shift_left;
		template<typename T, typename U>
		struct shift_right;
		template<typename T, typename U>
		struct multiplies;
		template<typename T, typename U>
		struct divides;
		template<typename T, typename U>
		struct modulus;
		template<typename T, typename U>
		struct plus;
		template<typename T, typename U>
		struct minus;
		template<typename T, typename U>
		struct less;
		template<typename T, typename U>
		struct greater;
		template<typename T, typename U>
		struct less_equal;
		template<typename T, typename U>
		struct greater_equal;
		template<typename T, typename U>
		struct equal_to;
		template<typename T, typename U>
		struct not_equal_to;
		template<typename T, typename U>
		struct logical_or;
		template<typename T, typename U>
		struct logical_and;
		template<typename T, typename U>
		struct bitwise_and;
		template<typename T, typename U>
		struct bitwise_or;
		template<typename T, typename U>
		struct bitwise_xor;
		template<typename T, typename U>
		struct comma;
		template<typename T, typename U>
		struct mem_ptr;

		template<typename T, typename U>
		struct assign;
		template<typename T, typename U>
		struct shift_left_assign;
		template<typename T, typename U>
		struct shift_right_assign;
		template<typename T, typename U>
		struct multiplies_assign;
		template<typename T, typename U>
		struct divides_assign;
		template<typename T, typename U>
		struct modulus_assign;
		template<typename T, typename U>
		struct plus_assign;
		template<typename T, typename U>
		struct minus_assign;
		template<typename T, typename U>
		struct bitwise_and_assign;
		template<typename T, typename U>
		struct bitwise_or_assign;
		template<typename T, typename U>
		struct bitwise_xor_assign;
		template<typename T, typename U>
		struct subscript;
		template<typename T, typename U>
		struct member;
		template<typename T, typename U, typename V>
		struct if_else_;

		template<typename... Args>
		struct function;

		namespace functional {
			struct left;
			struct right;
			struct eval;
			struct deep_copy;

			template<typename Domain = sprout::breed::default_domain>
			struct as_expr;

			template<typename Domain = sprout::breed::default_domain>
			struct as_child;

			template<typename N = std::integral_constant<long, 0> >
			struct child;

			template<long N>
			struct child_c;

			template<typename Tag, typename Domain = deduce_domain>
			struct make_expr;

			template<typename Tag, typename Domain = deduce_domain>
			struct unpack_expr;

			typedef sprout::breed::functional::make_expr<sprout::breed::tag::terminal> make_terminal;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::unary_plus> make_unary_plus;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::negate> make_negate;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::dereference> make_dereference;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::complement> make_complement;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::address_of> make_address_of;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::logical_not> make_logical_not;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::pre_inc> make_pre_inc;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::pre_dec> make_pre_dec;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::post_inc> make_post_inc;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::post_dec> make_post_dec;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_left> make_shift_left;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_right> make_shift_right;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::multiplies> make_multiplies;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::divides> make_divides;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::modulus> make_modulus;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::plus> make_plus;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::minus> make_minus;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::less> make_less;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::greater> make_greater;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::less_equal> make_less_equal;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::greater_equal> make_greater_equal;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::equal_to> make_equal_to;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::not_equal_to> make_not_equal_to;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::logical_or> make_logical_or;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::logical_and> make_logical_and;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_and> make_bitwise_and;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_or> make_bitwise_or;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_xor> make_bitwise_xor;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::comma> make_comma;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::mem_ptr> make_mem_ptr;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::assign> make_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_left_assign> make_shift_left_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_right_assign> make_shift_right_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::multiplies_assign> make_multiplies_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::divides_assign> make_divides_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::modulus_assign> make_modulus_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::plus_assign> make_plus_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::minus_assign> make_minus_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_and_assign> make_bitwise_and_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_or_assign> make_bitwise_or_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_xor_assign> make_bitwise_xor_assign;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::subscript> make_subscript;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::if_else_> make_if_else;
			typedef sprout::breed::functional::make_expr<sprout::breed::tag::function> make_function;

			struct flatten;
			struct make_pair;
			struct first;
			struct second;
			struct at;
			struct pop_front;
			struct push_front;
			struct pop_back;
			struct push_back;
			struct reverse;
		}	// namespace functional

		typedef functional::flatten _flatten;
		typedef functional::make_pair _make_pair;
		typedef functional::first _first;
		typedef functional::second _second;
		typedef functional::pop_front _at;
		typedef functional::pop_front _pop_front;
		typedef functional::push_front _push_front;
		typedef functional::pop_back _pop_back;
		typedef functional::push_back _push_back;
		typedef functional::reverse _reverse;
		typedef functional::eval _eval;
		struct _deep_copy;

		typedef sprout::breed::functional::make_expr<sprout::breed::tag::terminal> _make_terminal;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::unary_plus> _make_unary_plus;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::negate> _make_negate;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::dereference> _make_dereference;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::complement> _make_complement;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::address_of> _make_address_of;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::logical_not> _make_logical_not;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::pre_inc> _make_pre_inc;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::pre_dec> _make_pre_dec;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::post_inc> _make_post_inc;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::post_dec> _make_post_dec;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_left> _make_shift_left;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_right> _make_shift_right;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::multiplies> _make_multiplies;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::divides> _make_divides;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::modulus> _make_modulus;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::plus> _make_plus;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::minus> _make_minus;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::less> _make_less;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::greater> _make_greater;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::less_equal> _make_less_equal;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::greater_equal> _make_greater_equal;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::equal_to> _make_equal_to;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::not_equal_to> _make_not_equal_to;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::logical_or> _make_logical_or;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::logical_and> _make_logical_and;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_and> _make_bitwise_and;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_or> _make_bitwise_or;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_xor> _make_bitwise_xor;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::comma> _make_comma;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::mem_ptr> _make_mem_ptr;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::assign> _make_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_left_assign> _make_shift_left_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::shift_right_assign> _make_shift_right_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::multiplies_assign> _make_multiplies_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::divides_assign> _make_divides_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::modulus_assign> _make_modulus_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::plus_assign> _make_plus_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::minus_assign> _make_minus_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_and_assign> _make_bitwise_and_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_or_assign> _make_bitwise_or_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::bitwise_xor_assign> _make_bitwise_xor_assign;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::subscript> _make_subscript;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::if_else_> _make_if_else;
		typedef sprout::breed::functional::make_expr<sprout::breed::tag::function> _make_function;

		template<typename T>
		struct is_callable;

		template<typename T>
		struct is_transform;

		template<typename T>
		struct is_aggregate;

#		define SPROUT_BREED_UNEXPR() typedef int breed_is_expr_;
#		define SPROUT_BREED_CALLABLE() typedef void breed_is_callable_;
#		define SPROUT_BREED_AGGREGATE() typedef void breed_is_aggregate_;
#		define SPROUT_BREED_USE_BASIC_EXPR() typedef void breed_use_basic_expr_;

		struct callable {
		public:
			SPROUT_BREED_CALLABLE();
		};

		struct external_transform;

		template<typename PrimitiveTransform = void, typename X = void>
		struct transform;

		template<typename Grammar, typename Fun = Grammar>
		struct when;

		template<typename Fun>
		struct otherwise;

		template<typename Fun>
		struct call;

		template<typename Fun>
		struct make;

		template<typename PrimitiveTransform>
		struct protect;

		template<typename T>
		struct noinvoke;

		template<typename Fun>
		struct lazy;

		template<typename Sequence, typename State, typename Fun>
		struct fold;

		template<typename Sequence, typename State, typename Fun>
		struct reverse_fold;

		template<typename Sequence, typename State, typename Fun>
		struct fold_tree;

		template<typename Sequence, typename State, typename Fun>
		struct reverse_fold_tree;

		template<typename Grammar>
		struct pass_through;

		template<typename Grammar = sprout::breed::detail::_default>
		struct _default;

		struct _expr;
		struct _state;
		struct _data;

		struct _value;

		struct _void;

		template<typename T, T I>
		struct integral_c;

		template<char I>
		struct char_;

		template<int I>
		struct int_;

		template<long I>
		struct long_;

		template<std::size_t I>
		struct size_t;

		template<int I>
		struct _child_c;

		typedef _child_c<0> _child0;
		typedef _child_c<1> _child1;
		typedef _child0 _child;
		typedef _child0 _left;
		typedef _child1 _right;

		typedef _child_c<2> _child2;

		struct _byref;
		struct _byval;

		template<typename T>
		struct is_extension;
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_BREED_FWD_HPP
