#ifndef SPROUT_WEED_PARSER_NUMERIC_UINT_P_HPP
#define SPROUT_WEED_PARSER_NUMERIC_UINT_P_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/integer/integer_digits.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/detail/ndigits.hpp>

namespace sprout {
	namespace weed {
		//
		// uint_p
		//
		template<
			typename IntType,
			std::size_t Radix,
			std::size_t MinDigits = 1,
			std::size_t MaxDigits = sprout::integer_digits<IntType, Radix>::value
		>
		struct uint_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute {
			public:
				typedef IntType type;
			};
			template<typename Context, typename Iterator>
			struct result {
			public:
				typedef sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> type;
			};
		private:
			template<std::size_t N, typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename std::enable_if<
				N == MaxDigits,
				typename result<Context, Iterator>::type
			>::type call_1(
				Iterator first,
				Iterator last,
				Iterator temp_first,
				IntType t,
				PResult const& res
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? result_type(
						true,
						sprout::next(first),
						static_cast<IntType>(t * Radix | sprout::tuples::get<0>(res))
						)
					: N < MinDigits
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<std::size_t N, typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename std::enable_if<
				N != MaxDigits,
				typename result<Context, Iterator>::type
			>::type call_1(
				Iterator first,
				Iterator last,
				Iterator temp_first,
				IntType t,
				PResult const& res
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? call_0<N, Context>(
						sprout::next(first),
						last, temp_first,
						static_cast<IntType>(t * Radix | sprout::tuples::get<0>(res))
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
				IntType t
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
						sprout::weed::detail::from_ndigit<Radix, IntType>(*first)
						)
					: N < MinDigits
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call(
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
						sprout::tuples::get<0>(res)
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
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return first != last
					? call<Context>(
						first,
						last,
						first,
						sprout::weed::detail::from_ndigit<Radix, IntType>(*first)
						)
					: result_type(false, first, attribute_type())
					;
			}
		};
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_UINT_P_HPP
