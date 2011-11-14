#ifndef SPROUT_WEED_TRAITS_PARSER_ATTRIBUTE_OF_HPP
#define SPROUT_WEED_TRAITS_PARSER_ATTRIBUTE_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/expr/expr.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>
#include <sprout/weed/traits/type/is_c_str.hpp>
#include <sprout/weed/traits/type/is_string.hpp>
#include <sprout/weed/traits/expr/is_expr.hpp>
#include <sprout/weed/traits/parser/is_parser.hpp>
#include <sprout/weed/traits/parser/limit_of.hpp>
#include <sprout/weed/attr_cnv/result_of/times.hpp>
#include <sprout/weed/attr_cnv/result_of/shift_left.hpp>
#include <sprout/weed/attr_cnv/result_of/modulus.hpp>
#include <sprout/weed/attr_cnv/result_of/bitwise_or.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// attribute_of
			//
			template<typename T, typename Iterator, typename Context, typename = void>
			struct attribute_of;
			template<typename T, typename Iterator, typename Context>
			struct attribute_of<T const, Iterator, Context>
				: public sprout::weed::traits::attribute_of<T, Iterator, Context>
			{};
			template<typename T, typename Iterator, typename Context>
			struct attribute_of<
				T,
				Iterator,
				Context,
				typename std::enable_if<
					sprout::weed::traits::is_parser<T>::value
					&& !sprout::weed::traits::is_expr<T>::value
					&& !sprout::weed::traits::is_char_type<T>::value
					&& !sprout::weed::traits::is_c_str<T>::value
					&& !sprout::weed::traits::is_string<T>::value
				>::type
			> {
			public:
				typedef typename T::template attribute<Context, Iterator>::type type;
			};
			template<typename T, typename Iterator, typename Context>
			struct attribute_of<
				T,
				Iterator,
				Context,
				typename std::enable_if<
					sprout::weed::traits::is_char_type<T>::value
					|| sprout::weed::traits::is_c_str<T>::value
					|| sprout::weed::traits::is_string<T>::value
				>::type
			> {
			public:
				typedef sprout::weed::unused type;
			};
			template<typename Arg, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::terminal, Arg>, Iterator, Context>
				: public sprout::weed::traits::attribute_of<Arg, Iterator, Context>
			{};
			template<typename Arg, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::unary_plus, Arg>, Iterator, Context>
				: public sprout::weed::attr_cnv::result_of::times<
					sprout::weed::traits::limit_of<Arg, Iterator, Context>::value,
					typename sprout::weed::traits::attribute_of<Arg, Iterator, Context>::type
				>
			{};
			template<typename Arg, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::negate, Arg>, Iterator, Context>
				: public sprout::weed::attr_cnv::result_of::negate<
					typename sprout::weed::traits::attribute_of<Arg, Iterator, Context>::type
				>
			{};
			template<typename Arg, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::dereference, Arg>, Iterator, Context>
				: public sprout::weed::attr_cnv::result_of::times<
					sprout::weed::traits::limit_of<Arg, Iterator, Context>::value,
					typename sprout::weed::traits::attribute_of<Arg, Iterator, Context>::type
				>
			{};
			template<typename Arg, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::address_of, Arg>, Iterator, Context> {
			public:
				typedef sprout::weed::unused type;
			};
			template<typename Arg, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::logical_not, Arg>, Iterator, Context> {
			public:
				typedef sprout::weed::unused type;
			};
			template<typename Arg1, typename Arg2, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::shift_left, Arg1, Arg2>, Iterator, Context>
				: public sprout::weed::attr_cnv::result_of::shift_left<
					typename sprout::weed::traits::attribute_of<Arg1, Iterator, Context>::type,
					typename sprout::weed::traits::attribute_of<Arg2, Iterator, Context>::type
				>
			{};
			template<typename Arg1, typename Arg2, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::modulus, Arg1, Arg2>, Iterator, Context>
				: public sprout::weed::attr_cnv::result_of::modulus<
					sprout::weed::traits::limit_of<Arg1, Iterator, Context>::value,
					typename sprout::weed::traits::attribute_of<Arg1, Iterator, Context>::type
				>
			{};
			template<typename Arg1, typename Arg2, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::minus, Arg1, Arg2>, Iterator, Context> {
			public:
				typedef typename sprout::weed::traits::attribute_of<Arg1, Iterator, Context>::type type;
			};
			template<typename Arg1, typename Arg2, typename Iterator, typename Context>
			struct attribute_of<sprout::weed::expr<sprout::weed::tag::bitwise_or, Arg1, Arg2>, Iterator, Context>
				: public sprout::weed::attr_cnv::result_of::bitwise_or<
					typename sprout::weed::traits::attribute_of<Arg1, Iterator, Context>::type,
					typename sprout::weed::traits::attribute_of<Arg2, Iterator, Context>::type
				>
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_PARSER_ATTRIBUTE_OF_HPP
