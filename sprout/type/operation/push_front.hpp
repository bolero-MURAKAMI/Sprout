#ifndef SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP
#define SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		//
		// push_front
		//
		template<typename Tuple, typename T>
		struct push_front {
		private:
			template<typename IndexTuple>
			struct apply_impl;
			template<std::ptrdiff_t... Indexes>
			struct apply_impl<sprout::index_tuple<Indexes...> >
				: public sprout::types::rebind_types<
					Tuple
				>::template apply<
					T,
					typename sprout::types::tuple_element<Indexes, Tuple>::type...
				>
			{};
		public:
			typedef typename apply_impl<
				typename sprout::index_range<0, sprout::types::tuple_size<Tuple>::value>::type
			>::type type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_PUSH_FRONT_HPP
