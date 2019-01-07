/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_AUXILIARY_EOI_HPP
#define SPROUT_WEED_PARSER_AUXILIARY_EOI_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>

namespace sprout {
	namespace weed {
		//
		// eoi_p
		//
		struct eoi_p
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
		public:
			template<typename Context, typename Iterator>
			SPROUT_CONSTEXPR typename result<Context, Iterator>::type operator()(
				Iterator first, Iterator last,
				Context const&
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				return result_type(first == last, first, attribute_type());
			}
		};
		//
		// eoi
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::eoi_p eoi = sprout::weed::eoi_p();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_AUXILIARY_EOI_HPP
