/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_SEQ_ALGORITHM_FIND_HPP
#define SPROUT_TYPE_SEQ_ALGORITHM_FIND_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		namespace seq {
			namespace detail {
				template<typename First, typename Last, typename T, typename = void>
				struct find_impl;
				template<typename First, typename Last, typename T>
				struct find_impl<
					First, Last, T,
					typename std::enable_if<
						std::is_same<First, Last>::value
					>::type
				> {
				public:
					typedef Last type;
				};
				template<typename First, typename Last, typename T>
				struct find_impl<
					First, Last, T,
					typename std::enable_if<
						!std::is_same<First, Last>::value
						&& std::is_same<typename sprout::types::deref<First>::type, T>::value
					>::type
				> {
				public:
					typedef First type;
				};
				template<typename First, typename Last, typename T>
				struct find_impl<
					First, Last, T,
					typename std::enable_if<
						!std::is_same<First, Last>::value
						&& !std::is_same<typename sprout::types::deref<First>::type, T>::value
					>::type
				>
					: public sprout::types::seq::detail::find_impl<
						typename sprout::types::next<First>::type,
						Last,
						T
					>
				{};
			}	// namespace detail
			//
			// find
			//
			template<typename ForwardSequence, typename T>
			struct find
				: public sprout::types::seq::detail::find_impl<
					typename sprout::types::begin<ForwardSequence>::type,
					typename sprout::types::end<ForwardSequence>::type,
					T
				>
			{};
		}	// namespace seq
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_SEQ_ALGORITHM_FIND_HPP
