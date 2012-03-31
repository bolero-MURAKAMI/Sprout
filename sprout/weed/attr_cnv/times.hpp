#ifndef SPROUT_WEED_ATTR_CNV_TIMES_HPP
#define SPROUT_WEED_ATTR_CNV_TIMES_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/array.hpp>
#include <sprout/container/make.hpp>
#include <sprout/algorithm/string/join.hpp>
#include <sprout/weed/unused.hpp>
#include <sprout/weed/traits/type/is_container.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>
#include <sprout/weed/attr_cnv/result_of/times.hpp>

namespace sprout {
	namespace weed {
		namespace attr_cnv {
			//
			// times
			//
			// times<N>(container<V, K>) -> container<V, N * K>
			template<std::size_t Limit, typename T, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::traits::is_container<T>::value,
				typename sprout::weed::attr_cnv::result_of::times<Limit, T>::type
			>::type times(Args const&... args) {
				return sprout::algorithm::join(
					sprout::make<sprout::array<T, Limit> >(args...)
					);
			}
			// times<N>(V) -> container<V, N>
			template<std::size_t Limit, typename T, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				!sprout::weed::traits::is_container<T>::value
				&& !sprout::weed::traits::is_unused<T>::value,
				typename sprout::weed::attr_cnv::result_of::times<Limit, T>::type
			>::type times(Args const&... args) {
				typedef typename sprout::weed::attr_cnv::result_of::times<Limit, T>::type type;
				return sprout::make<type>(args...);
			}
			// times<N>(unused) -> unused
			template<std::size_t Limit, typename T, typename... Args>
			static SPROUT_CONSTEXPR typename std::enable_if<
				sprout::weed::traits::is_unused<T>::value,
				typename sprout::weed::attr_cnv::result_of::times<Limit, T>::type
			>::type times(Args const&... args) {
				return sprout::weed::unused();
			}
		}	// namespace attr_cnv
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_ATTR_CNV_TIMES_HPP
