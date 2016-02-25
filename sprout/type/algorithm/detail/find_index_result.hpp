/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_DETAIL_FIND_INDEX_RESULT_HPP
#define SPROUT_TYPE_ALGORITHM_DETAIL_FIND_INDEX_RESULT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple, std::size_t Found>
			struct find_index_result
				: public sprout::integral_constant<std::size_t, Found>
			{
			public:
				typedef sprout::bool_constant<Found != sprout::types::tuple_size<Tuple>::value> is_found;
			};
		}	// namespace detail
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_DETAIL_FIND_INDEX_RESULT_HPP
