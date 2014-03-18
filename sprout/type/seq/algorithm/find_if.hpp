/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_SEQ_ALGORITHM_FIND_IF_HPP
#define SPROUT_TYPE_SEQ_ALGORITHM_FIND_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		namespace seq {
			namespace detail {
				template<typename First, typename Last, typename Predicate, typename = void>
				struct find_if_impl;

				template<typename First, typename Last, typename Predicate, typename = void>
				struct find_if_impl_1;
				template<typename First, typename Last, typename Predicate>
				struct find_if_impl_1<
					First, Last, Predicate,
					typename std::enable_if<
						Predicate::template apply<typename sprout::types::deref<First>::type>::type::value
					>::type
				> {
				public:
					typedef First type;
				};
				template<typename First, typename Last, typename Predicate>
				struct find_if_impl_1<
					First, Last, Predicate,
					typename std::enable_if<
						!Predicate::template apply<typename sprout::types::deref<First>::type>::type::value
					>::type
				>
					: public sprout::types::seq::detail::find_if_impl<
						typename sprout::types::next<First>::type,
						Last,
						Predicate
					>
				{};

				template<typename First, typename Last, typename Predicate>
				struct find_if_impl<
					First, Last, Predicate,
					typename std::enable_if<
						std::is_same<First, Last>::value
					>::type
				> {
				public:
					typedef Last type;
				};
				template<typename First, typename Last, typename Predicate>
				struct find_if_impl<
					First, Last, Predicate,
					typename std::enable_if<
						!std::is_same<First, Last>::value
					>::type
				>
					: public sprout::types::seq::detail::find_if_impl_1<First, Last, Predicate>
				{};
			}	// namespace detail
			//
			// find_if
			//
			template<typename ForwardSequence, typename Predicate>
			struct find_if
				: public sprout::types::seq::detail::find_if_impl<
					typename sprout::types::begin<ForwardSequence>::type,
					typename sprout::types::end<ForwardSequence>::type,
					Predicate
				>
			{};
		}	// namespace seq
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_SEQ_ALGORITHM_FIND_IF_HPP
