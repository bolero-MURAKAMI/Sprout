#ifndef SPROUT_WEED_PARSER_CHAR_CHAR_HPP
#define SPROUT_WEED_PARSER_CHAR_CHAR_HPP

#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/parser/lit.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>

namespace sprout {
	namespace weed {
		//
		// lit_char_p
		//
		template<typename T>
		struct lit_char_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute {
			public:
				typedef sprout::weed::unused type;
			};
			template<typename Context, typename Iterator>
			struct result {
			public:
				typedef sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> type;
			};
		private:
			T t_;
		public:
			lit_char_p() = default;
			SPROUT_CONSTEXPR explicit lit_char_p(T const& t)
				: t_(t)
			{}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first,
				Iterator last,
				Context const&
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				typedef typename std::iterator_traits<Iterator>::value_type elem_type;
				return first != last && *first == elem_type(t_)
					? result_type(true, sprout::next(first), attribute_type())
					: result_type(false, first, typename attribute<Context, Iterator>::type())
					;
			}
		};
		//
		// lit_g
		//
		template<typename T>
		struct lit_g::eval<
			T,
			typename std::enable_if<
				sprout::weed::traits::is_char_type<T>::value
			>::type
		> {
		public:
			typedef sprout::weed::lit_char_p<T> result_type;
		public:
			SPROUT_CONSTEXPR result_type operator()(T const& t) const {
				return result_type(t);
			}
		};

		//
		// char_p
		//
		template<typename T>
		struct char_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute {
			public:
				typedef typename std::iterator_traits<Iterator>::value_type type;
			};
			template<typename Context, typename Iterator>
			struct result {
			public:
				typedef sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> type;
			};
		private:
			T t_;
		public:
			char_p() = default;
			SPROUT_CONSTEXPR explicit char_p(T const& t)
				: t_(t)
			{}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first,
				Iterator last,
				Context const&
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				typedef typename std::iterator_traits<Iterator>::value_type elem_type;
				return first != last && *first == elem_type(t_)
					? result_type(true, sprout::next(first), *first)
					: result_type(false, first, attribute_type())
					;
			}
		};

		//
		// any_char_p
		//
		struct any_char_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute {
			public:
				typedef typename std::iterator_traits<Iterator>::value_type type;
			};
			template<typename Context, typename Iterator>
			struct result {
			public:
				typedef sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> type;
			};
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
					? result_type(true, sprout::next(first), *first)
					: result_type(false, first, attribute_type())
					;
			}
			template<typename T>
			SPROUT_CONSTEXPR sprout::weed::char_p<T> operator()(T const& t) const {
				return sprout::weed::char_p<T>(t);
			}
		};
		//
		// char_
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::any_char_p char_ = sprout::weed::any_char_p();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_CHAR_CHAR_HPP
