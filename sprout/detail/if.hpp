#ifndef SPROUT_DETAIL_IF_HPP
#define SPROUT_DETAIL_IF_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		//
		// if_c
		//
		template<bool C, typename T1, typename T2>
		struct if_c {
			typedef T1 type;
		};
		template<typename T1, typename T2>
		struct if_c<false, T1, T2> {
			typedef T2 type;
		};

		//
		// if_
		//
		template<typename Cond, typename T1, typename T2>
		struct if_
			: public sprout::detail::if_c<Cond::value, T1, T2>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_IF_HPP
