/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_STRING_TO_STRING_CONSTANT_HPP
#define SPROUT_TYPE_STRING_TO_STRING_CONSTANT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/string.hpp>
#include <sprout/type/string/string.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/seq/algorithm/find_if.hpp>
#include <sprout/type/iterator/distance.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		//
		// to_string_constant
		//
		namespace detail {
			struct is_nul {
			public:
				template<typename T, typename Enable = void>
				struct apply
					: public sprout::false_type
				{};
				template<typename T>
				struct apply<T, typename std::enable_if<T::value == 0>::type>
					: public sprout::true_type
				{};
			};
			template<typename Sequence>
			struct str_length
				: public sprout::types::distance<
					typename sprout::types::begin<Sequence>::type,
					typename sprout::types::seq::find_if<
						Sequence,
						sprout::types::detail::is_nul
					>::type
				>
			{};
			template<typename Sequence, sprout::index_t... Indexes>
			inline SPROUT_CONSTEXPR sprout::basic_string<
				typename Sequence::value_type,
				sprout::types::detail::str_length<Sequence>::value
			> to_string_constant_impl(sprout::index_tuple<Indexes...>) {
				return sprout::make_string<typename Sequence::value_type>(
					sprout::types::tuple_element<Indexes, Sequence>::type::value...
					);
			}
		}	// namespace detail
		template<typename Sequence>
		inline SPROUT_CONSTEXPR sprout::basic_string<
			typename Sequence::value_type,
			sprout::types::detail::str_length<Sequence>::value
		> to_string_constant() {
			return sprout::types::detail::to_string_constant_impl<Sequence>(
				sprout::make_index_tuple<sprout::types::detail::str_length<Sequence>::value>::make()
				);
		}
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_STRING_TO_STRING_CONSTANT_HPP
