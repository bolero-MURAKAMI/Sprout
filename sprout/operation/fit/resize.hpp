#ifndef SPROUT_OPERATION_FIT_RESIZE_HPP
#define SPROUT_OPERATION_FIT_RESIZE_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/resize.hpp>
#include <sprout/sub_array/sub_array.hpp>
#include <sprout/sub_array/sub.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// resize
			//
			template<std::size_t N, typename Container>
			struct resize {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::resize<N, Container>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// resize
		//
		template<std::size_t N, typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::resize<N, Container>::type
		resize(Container const& cont, T const& v) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::resize<N>(cont, v)),
				0,
				sprout::container_traits<typename sprout::fit::result_of::resize<N, Container>::type>::static_size
				);
		}
		template<std::size_t N, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::resize<N, Container>::type
		resize(Container const& cont) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::resize<N>(cont)),
				0,
				sprout::container_traits<typename sprout::fit::result_of::resize<N, Container>::type>::static_size
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_RESIZE_HPP
