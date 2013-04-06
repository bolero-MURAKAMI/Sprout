#ifndef SPROUT_TYPE_OPERATION_PUSH_BACK_HPP
#define SPROUT_TYPE_OPERATION_PUSH_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/tuple/indexes.hpp>

namespace sprout {
	namespace types {
		//
		// push_back
		//
		template<typename Tuple, typename... Ts>
		struct push_back {
			static_assert(sizeof...(Ts) >= 1, "sizeof...(Ts) >= 1");
		private:
			template<typename IndexTuple>
			struct apply_impl;
			template<sprout::index_t... Indexes>
			struct apply_impl<sprout::index_tuple<Indexes...> >
				: public sprout::types::rebind_types<
					Tuple
				>::template apply<
					typename sprout::types::tuple_element<Indexes, Tuple>::type...,
					Ts...
				>
			{};
		public:
			typedef typename apply_impl<
				typename sprout::tuple_indexes<Tuple>::type
			>::type type;
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_PUSH_BACK_HPP
