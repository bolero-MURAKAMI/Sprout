#ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_TIMES_HPP
#define SPROUT_WEED_ATTR_CNV_RESULT_OF_TIMES_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/string.hpp>
#include <sprout/array/array.hpp>
#include <sprout/algorithm/string/join.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_char_type.hpp>
#include <sprout/weed/traits/type/is_container.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			namespace result_of {
				//
				// times
				//
				template<std::size_t Limit, typename T, typename = void>
				struct times;
				// times<N>(container<V, K>) -> container<V, N * K>
				template<std::size_t Limit, typename T>
				struct times<
					Limit,
					T,
					typename std::enable_if<
						Limit != std::size_t(-1)
						&& sprout::weed::traits::is_container<T>::value
					>::type
				>
					: public sprout::algorithm::result_of::join<
						sprout::array<T, Limit>
					>
				{};
				// times<N>(V) -> container<V, N>
				template<std::size_t Limit, typename T>
				struct times<
					Limit,
					T,
					typename std::enable_if<
						Limit != std::size_t(-1)
						&& !sprout::weed::traits::is_container<T>::value
						&& !sprout::weed::traits::is_unused<T>::value
					>::type
				>
					: public std::conditional<
						sprout::weed::traits::is_char_type<T>::value,
						sprout::basic_string<T, Limit>,
						sprout::array<T, Limit>
					>
				{};
				// times<N>(unused) -> unused
				template<std::size_t Limit, typename T>
				struct times<
					Limit,
					T,
					typename std::enable_if<
						sprout::weed::traits::is_unused<T>::value
					>::type
				>
					: public sprout::identity<sprout::weed::unused>
				{};
			}	// namespace result_of
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_RESULT_OF_TIMES_HPP
