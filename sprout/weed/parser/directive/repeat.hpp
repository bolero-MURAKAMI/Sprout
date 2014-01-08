/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_DIRECTIVE_REPEAT_HPP
#define SPROUT_WEED_PARSER_DIRECTIVE_REPEAT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/expr/make_terminal_or_expr.hpp>
#include <sprout/weed/expr/eval.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/attr_cnv/results/times.hpp>
#include <sprout/weed/attr_cnv/times.hpp>
#include <sprout/weed/traits/expr/terminal_or_expr_of.hpp>
#include <sprout/weed/traits/parser/attribute_of.hpp>
#include <sprout/weed/traits/parser/limit_of.hpp>

namespace sprout {
	namespace weed {
		//
		// repeat_p
		//
		template<typename Parser>
		struct repeat_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute;
			template<typename Context, typename Iterator>
			struct result;
		private:
			template<typename Context, typename Iterator>
			struct eval {
			private:
				typedef typename sprout::weed::traits::limit_of<Parser, Iterator, Context>::type limit;
				typedef typename sprout::weed::traits::attribute_of<Parser, Iterator, Context>::type attr_type;
			public:
				typedef typename repeat_p::template attribute<Context, Iterator>::type attribute_type;
				typedef typename repeat_p::template result<Context, Iterator>::type result_type;
			private:
				template<typename Result, typename... Attrs>
				SPROUT_CONSTEXPR typename std::enable_if<
					sizeof...(Attrs) + 1 == limit::value,
					result_type
				>::type call(
					repeat_p const& p,
					Iterator first,
					Result const& res,
					Attrs const&... attrs
					) const
				{
					return res.success()
						? result_type(true, res.current(), sprout::weed::attr_cnv::times<limit::value, attr_type>(attrs..., res.attr()))
						: p.count_ <= sizeof...(Attrs)
							? result_type(true, first, sprout::weed::attr_cnv::times<limit::value, attr_type>(attrs...))
							: result_type(false, first, attribute_type())
						;
				}
				template<typename Result, typename... Attrs>
				SPROUT_CONSTEXPR typename std::enable_if<
					sizeof...(Attrs) + 1 != limit::value,
					result_type
				>::type call(
					repeat_p const& p,
					Iterator first,
					Result const& res,
					Attrs const&... attrs
					) const
				{
					return res.success()
						? call(p, p.count_ <= sizeof...(Attrs) ? res.current() : first, sprout::weed::eval(p.expr_, res.ctx()), attrs..., res.attr())
						: p.count_ <= sizeof...(Attrs)
							? result_type(true, first, sprout::weed::attr_cnv::times<limit::value, attr_type>(attrs...))
							: result_type(false, first, attribute_type())
						;
				}
				template<typename Result>
				SPROUT_CONSTEXPR result_type call_inf(
					repeat_p const& p,
					Iterator first,
					Result const& res,
					std::size_t n
					) const
				{
					return res.success()
						? call_inf(p, p.count_ <= n ? res.current() : first, sprout::weed::eval(p.expr_, res.ctx()), n + 1)
						: result_type(p.count_ <= n || p.count_ == std::size_t(-1), first, attribute_type())
						;
				}
				template<bool Infinity, typename Result>
				SPROUT_CONSTEXPR typename std::enable_if<
					Infinity,
					result_type
				>::type call(
					repeat_p const& p,
					Iterator first,
					Result const& res
					) const
				{
					return res.success()
						? call_inf(
							p,
							p.count_ <= 0 ? res.current() : first,
							sprout::weed::eval(p.expr_, res.ctx()),
							1
							)
						: result_type(p.count_ <= 0 || p.count_ == std::size_t(-1), first, attribute_type())
						;
				}
				template<bool Infinity, typename Result>
				SPROUT_CONSTEXPR typename std::enable_if<
					!Infinity,
					result_type
				>::type call(
					repeat_p const& p,
					Iterator first,
					Result const& res
					) const
				{
					return res.success()
						? call(
							p,
							p.count_ <= 0 ? res.current() : first,
							sprout::weed::eval(p.expr_, res.ctx()),
							res.attr()
							)
						: result_type(p.count_ <= 0, first, attribute_type())
						;
				}
			public:
				SPROUT_CONSTEXPR result_type operator()(
					repeat_p const& p,
					Iterator first,
					Context const& ctx
					) const
				{
					return call<limit::value == std::size_t(-1)>(
						p,
						first,
						sprout::weed::eval(p.expr_, ctx)
						);
				}
			};
		public:
			template<typename Context, typename Iterator>
			struct attribute
				: public sprout::weed::attr_cnv::results::times<
					sprout::weed::traits::limit_of<Parser, Iterator, Context>::value,
					typename sprout::weed::traits::attribute_of<Parser, Iterator, Context>::type
				>
			{};
			template<typename Context, typename Iterator>
			struct result
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> >
			{};
		private:
			typedef typename sprout::weed::traits::terminal_or_expr_of<Parser>::type expr_type;
		private:
			expr_type expr_;
			std::size_t count_;
		public:
			repeat_p() = default;
			explicit SPROUT_CONSTEXPR repeat_p(Parser const& p, std::size_t count = -1)
				: expr_(sprout::weed::make_terminal_or_expr(p))
				, count_(count)
			{}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first, Iterator,
				Context const& ctx
				) const
			{
				return eval<Context, Iterator>()(*this, first, ctx);
			}
		};

		//
		// repeat_g
		//
		struct repeat_g {
		private:
			std::size_t count_;
		public:
			explicit SPROUT_CONSTEXPR repeat_g(std::size_t count)
				: count_(count)
			{}
			template<typename Parser>
			SPROUT_CONSTEXPR sprout::weed::repeat_p<Parser> operator[](Parser const& p) const {
				return sprout::weed::repeat_p<Parser>(p, count_);
			}
		};

		//
		// repeat_d
		//
		struct repeat_d {
		public:
			template<typename Parser>
			SPROUT_CONSTEXPR sprout::weed::repeat_p<Parser> operator[](Parser const& p) const {
				return sprout::weed::repeat_p<Parser>(p);
			}
			SPROUT_CONSTEXPR sprout::weed::repeat_g operator()(std::size_t count) const {
				return sprout::weed::repeat_g(count);
			}
		};

		//
		// repeat
		//
		SPROUT_CONSTEXPR sprout::weed::repeat_d repeat = sprout::weed::repeat_d();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_DIRECTIVE_REPEAT_HPP
