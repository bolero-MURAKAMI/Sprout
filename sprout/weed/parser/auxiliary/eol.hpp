/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_PARSER_AUXILIARY_EOL_HPP
#define SPROUT_WEED_PARSER_AUXILIARY_EOL_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/parser_result.hpp>
#include <sprout/weed/parser/parser_base.hpp>

namespace sprout {
	namespace weed {
		//
		// eol_p
		//
		struct eol_p
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
				Iterator first,
				Iterator last,
				Context const&
				) const
			{
				typedef typename result<Context, Iterator>::type result_type;
				typedef typename attribute<Context, Iterator>::type attribute_type;
				typedef typename std::iterator_traits<Iterator>::value_type elem_type;
				return first != last
					? *first == elem_type('\r')
						? sprout::next(first) != last
							? *sprout::next(first) == elem_type('\n')
								? result_type(true, sprout::next(sprout::next(first)), attribute_type())
								: result_type(true, sprout::next(first), attribute_type())
							: result_type(true, sprout::next(first), attribute_type())
						: *first == elem_type('\n')
							? result_type(true, sprout::next(first), attribute_type())
							: result_type(false, first, attribute_type())
					: result_type(false, first, attribute_type())
					;
			}
		};
		//
		// eol
		//
		SPROUT_STATIC_CONSTEXPR sprout::weed::eol_p eol = sprout::weed::eol_p();
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_PARSER_AUXILIARY_EOL_HPP
