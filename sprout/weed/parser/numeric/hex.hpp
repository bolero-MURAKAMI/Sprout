#ifndef SPROUT_WEED_PARSER_NUMERIC_HEX_HPP
#define SPROUT_WEED_PARSER_NUMERIC_HEX_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/detail/xdigits.hpp>

namespace sprout {
	namespace weed {
		//
		// hex_p
		//
		template<typename IntType, std::size_t Min = sizeof(IntType) * 2, std::size_t Max = sizeof(IntType) * 2>
		struct hex_p
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
				N == Max,
				typename result<Context, Iterator>::type
			>::type call_1(Iterator first, Iterator last, Iterator temp_first, IntType t, PResult const& res) const {
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? result_type(true, sprout::next(first), static_cast<IntType>(t << 4 | sprout::tuples::get<0>(res)))
					: N < Min
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<std::size_t N, typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename std::enable_if<
				N != Max,
				typename result<Context, Iterator>::type
			>::type call_1(Iterator first, Iterator last, Iterator temp_first, IntType t, PResult const& res) const {
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? call_0<N, Context>(sprout::next(first), last, temp_first, static_cast<IntType>(t << 4 | sprout::tuples::get<0>(res)))
					: N < Min
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<std::size_t N, typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call_0(Iterator first, Iterator last, Iterator temp_first, IntType t) const {
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return first != last
					? call_1<N + 1, Context>(first, last, temp_first, t, sprout::weed::detail::from_xdigit<IntType>(*first))
					: N < Min
						? result_type(false, temp_first, attribute_type())
						: result_type(true, first, t)
					;
			}
			template<typename Context, typename Iterator, typename PResult>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type call(Iterator first, Iterator last, Iterator temp_first, PResult const& res) const {
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::tuples::get<1>(res)
					? call_0<1, Context>(sprout::next(first), last, temp_first, sprout::tuples::get<0>(res))
					: result_type(false, temp_first, attribute_type())
					;
			}
		public:
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(Iterator first, Iterator last, Context const&) const {
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return first != last
					? call<Context>(first, last, first, sprout::weed::detail::from_xdigit<IntType>(*first))
					: result_type(false, first, attribute_type())
					;
			}
		};
		//
		// hex8
		// hex16
		// hex32
		// hex64
		// uhex8
		// uhex16
		// uhex32
		// uhex64
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int8_t, 1> hex8 = sprout::weed::hex_p<std::int8_t, 1>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int16_t, 1> hex16 = sprout::weed::hex_p<std::int16_t, 1>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int32_t, 1> hex32 = sprout::weed::hex_p<std::int32_t, 1>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int64_t, 1> hex64 = sprout::weed::hex_p<std::int64_t, 1>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint8_t, 1> uhex8 = sprout::weed::hex_p<std::uint8_t, 1>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint16_t, 1> uhex16 = sprout::weed::hex_p<std::uint16_t, 1>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint32_t, 1> uhex32 = sprout::weed::hex_p<std::uint32_t, 1>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint64_t, 1> uhex64 = sprout::weed::hex_p<std::uint64_t, 1>();
		//
		// hex8f
		// hex16f
		// hex32f
		// hex64f
		// uhex8f
		// uhex16f
		// uhex32f
		// uhex64f
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int8_t> hex8f = sprout::weed::hex_p<std::int8_t>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int16_t> hex16f = sprout::weed::hex_p<std::int16_t>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int32_t> hex32f = sprout::weed::hex_p<std::int32_t>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::int64_t> hex64f = sprout::weed::hex_p<std::int64_t>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint8_t> uhex8f = sprout::weed::hex_p<std::uint8_t>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint16_t> uhex16f = sprout::weed::hex_p<std::uint16_t>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint32_t> uhex32f = sprout::weed::hex_p<std::uint32_t>();
		SPROUT_STATIC_CONSTEXPR sprout::weed::hex_p<std::uint64_t> uhex64f = sprout::weed::hex_p<std::uint64_t>();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_NUMERIC_HEX_HPP
