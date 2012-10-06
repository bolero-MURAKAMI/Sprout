#ifndef SPROUT_OPERATION_FIT_SET_HPP
#define SPROUT_OPERATION_FIT_SET_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/operation/fixed/set.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace fit {
		namespace result_of {
			//
			// set
			//
			template<typename Container, typename T>
			struct set {
			public:
				typedef sprout::sub_array<
					typename sprout::container_traits<
						typename sprout::fixed::result_of::set<Container, T>::type
					>::internal_type
				> type;
			};
		}	// namespace result_of

		//
		// set
		//
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::set<Container, T>::type
		set(Container const& cont, typename sprout::container_traits<Container>::const_iterator pos, T const& v) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::set(cont, pos, v)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont)
				);
		}
		template<typename Container, typename T>
		inline SPROUT_CONSTEXPR typename sprout::fit::result_of::set<Container, T>::type
		set(Container const& cont, typename sprout::container_traits<Container>::difference_type pos, T const& v) {
			return sprout::sub_copy(
				sprout::get_internal(sprout::fixed::set(cont, pos, v)),
				sprout::internal_begin_offset(cont),
				sprout::internal_end_offset(cont)
				);
		}
	}	// namespace fit
}	// namespace sprout

#endif	// #ifndef SPROUT_OPERATION_FIT_SET_HPP
