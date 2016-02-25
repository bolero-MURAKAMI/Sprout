/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_NUMERIC_INT_P_HPP
#define SPROUT_WEED_PARSER_NUMERIC_INT_P_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/detail/ndigits.hpp>
#include <sprout/detail/char_literal.hpp>

namespace sprout {
	namespace weed {
		//
		// int_p
		//
		template<
			typename IntType,
			std::size_t Radix = 10,
			std::size_t MinDigits = 1,
			std::size_t MaxDigits = sprout::integer_digits<IntType, Radix>::value
		>
		struct int_p
			: public sprout::weed::parser_base
		{
		private:
			SPROUT_STATIC_CONSTEXPR std::size_t limit_digits = MaxDigits <= sprout::integer_digits<IntType, Radix>::value
				? MaxDigits
				: sprout::integer_digits<IntType, Radix>::value
				;
		public:
			template<typename Context, typename Iterator>
			struct attribute
				: public sprout::identity<IntType>
			{};
			template<typename Context, typename Iterator>
			struct result
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> >
			{};
		private:
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type make_result(
				typename result<Context, Iterator>::type const& res,
				int sign = 0
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				return res.success() && sign < 0
					? result_type(true, res.current(), -res.attr())
					: res
					;
			}
			template<std::size_t N, typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename std::enable_if<
				N == limit_digits,
				typename result<Context, Iterator>::type
			>::type call_1(
				Iterator first,
				Iterator last,
				Iterator temp_first,
				IntType t,
				std::size_t n,
				PResult const& res
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? n < MaxDigits
						? call_0<N - 1, Context>(
							sprout::next(first),
							last,
							temp_first,
							static_cast<IntType>(t * Radix + sprout::tuples::get<0>(res)),
							n
							)
						: result_type(
							true,
							sprout::next(first),
							static_cast<IntType>(t * Radix + sprout::tuples::get<0>(res))
							)
					: N < MinDigits
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<std::size_t N, typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename std::enable_if<
				N != limit_digits,
				typename result<Context, Iterator>::type
			>::type call_1(
				Iterator first,
				Iterator last,
				Iterator temp_first,
				IntType t,
				std::size_t n,
				PResult const& res
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? call_0<N, Context>(
						sprout::next(first),
						last,
						temp_first,
						static_cast<IntType>(t * Radix + sprout::tuples::get<0>(res)),
						n
						)
					: N < MinDigits
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<std::size_t N, typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call_0(
				Iterator first,
				Iterator last,
				Iterator temp_first,
				IntType t,
				std::size_t n
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return first != last
					? call_1<N + 1, Context>(
						first,
						last,
						temp_first,
						t,
						n + 1,
						sprout::weed::detail::from_ndigit<Radix, IntType>(*first)
						)
					: N < MinDigits
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call_i(
				Iterator first,
				Iterator last,
				Iterator temp_first,
				PResult const& res
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? call_0<1, Context>(
						sprout::next(first),
						last,
						temp_first,
						sprout::tuples::get<0>(res),
						1
						)
					: result_type(false, temp_first, attribute_type())
					;
			}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call(
				Iterator first,
				Iterator last,
				Iterator temp_first,
				int sign = 0
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return first != last
					? make_result<Context, Iterator>(
						call_i<Context>(
							first,
							last,
							temp_first,
							sprout::weed::detail::from_ndigit<Radix, IntType>(*first)
							),
						sign
						)
					: result_type(false, temp_first, attribute_type())
					;
			}
		public:
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first,
				Iterator last,
				Context const&
				) const
			{
				typedef typename std::iterator_traits<Iterator>::value_type elem_type;
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return first != last
					? *first == SPROUT_CHAR_LITERAL('+', elem_type)
						? call<Context>(
							sprout::next(first),
							last,
							first,
							1
							)
						: *first == SPROUT_CHAR_LITERAL('-', elem_type)
							? call<Context>(
								sprout::next(first),
								last,
								first,
								-1
								)
							: call<Context>(
								first,
								last,
								first
								)
					: result_type(false, first, attribute_type())
					;
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_INT_P_HPP
