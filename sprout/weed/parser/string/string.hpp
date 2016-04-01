/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_STRING_STRING_HPP
#define SPROUT_WEED_PARSER_STRING_STRING_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/container/begin.hpp>
#include <sprout/container/end.hpp>
#include <sprout/container/size.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/equal.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>
#include <sprout/weed/parser/lit.hpp>
#include <sprout/weed/traits/type/is_c_str.hpp>
#include <sprout/weed/traits/type/is_string.hpp>
#include <sprout/weed/detail/c_str_as_string.hpp>

namespace sprout {
	namespace weed {
		//
		// lit_str_p
		//
		template<typename T>
		struct lit_str_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute
				: public sprout::identity<sprout::weed::unused>
			{};
			template<typename Context, typename Iterator>
			struct result
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> >
			{};
		private:
			T t_;
		public:
			SPROUT_CONSTEXPR lit_str_p() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			explicit SPROUT_CONSTEXPR lit_str_p(T const& t)
				: t_(t)
			{}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first, Iterator last,
				Context const&
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::distance(first, last) >= sprout::size(t_)
					&& sprout::equal(sprout::begin(t_), sprout::end(t_), first)
					? result_type(true, sprout::next(first, sprout::size(t_)), attribute_type())
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
				sprout::weed::traits::is_c_str<T>::value
			>::type
		> {
		public:
			typedef sprout::weed::lit_str_p<
				typename sprout::weed::detail::c_str_as_string<T const>::type
			> result_type;
		public:
			SPROUT_CONSTEXPR result_type operator()(T const& t) const {
				return result_type(sprout::to_string(t));
			}
		};
		template<typename T>
		struct lit_g::eval<
			T,
			typename std::enable_if<
				sprout::weed::traits::is_string<T>::value
			>::type
		> {
		public:
			typedef sprout::weed::lit_str_p<T> result_type;
		public:
			SPROUT_CONSTEXPR result_type operator()(T const& t) const {
				return result_type(t);
			}
		};

		//
		// str_p
		//
		template<typename T>
		struct str_p
			: public sprout::weed::parser_base
		{
		public:
			template<typename Context, typename Iterator>
			struct attribute
				: public sprout::identity<T>
			{};
			template<typename Context, typename Iterator>
			struct result
				: public sprout::identity<sprout::weed::parser_result<Iterator, typename attribute<Context, Iterator>::type> >
			{};
		private:
			T t_;
		public:
			SPROUT_CONSTEXPR str_p() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
			explicit SPROUT_CONSTEXPR str_p(T const& t)
				: t_(t)
			{}
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first, Iterator last,
				Context const&
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return sprout::distance(first, last) >= sprout::size(t_)
					&& sprout::equal(sprout::begin(t_), sprout::end(t_), first)
					? result_type(true, sprout::next(first, sprout::size(t_)), attribute_type())
					: result_type(false, first, typename attribute<Context, Iterator>::type())
					;
			}
		};
		//
		// string
		//
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::weed::traits::is_c_str<T const>::value,
			sprout::weed::str_p<
				typename sprout::weed::detail::c_str_as_string<T const>::type
			>
		>::type string(T const& t) {
			return sprout::weed::str_p<
				typename sprout::weed::detail::c_str_as_string<T const>::type
				>(sprout::to_string(t));
		}
		template<typename T>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::weed::traits::is_string<T>::value,
			sprout::weed::str_p<T>
		>::type string(T const& t) {
			return sprout::weed::str_p<T>(t);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_STRING_STRING_HPP
