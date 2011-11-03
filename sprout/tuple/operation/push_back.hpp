#ifndef SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP
#define SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/tuple/functions.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// push_back
			//
			template<typename Tuple, typename T>
			struct push_back {
			private:
				template<typename IndexTuple>
				struct apply_impl;
				template<std::ptrdiff_t... Indexes>
				struct apply_impl<sprout::index_tuple<Indexes...>>
					: public sprout::tuples::rebind_types<
						Tuple
					>::template apply<
						typename sprout::tuples::tuple_element<Indexes, Tuple>::type...,
						T
					>
				{};
			public:
				typedef typename apply_impl<
					typename sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::type
				>::type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename T, std::ptrdiff_t... Indexes>
			SPROUT_CONSTEXPR inline Result push_back_impl(
				Tuple const& t,
				T const& v,
				sprout::index_tuple<Indexes...>
				)
			{
				return sprout::tuples::remake_clone<Result>(
					t,
					sprout::tuples::get<Indexes>(t)...,
					v
					);
			}
		}	// namespace detail
		//
		// push_back
		//
		template<typename Tuple, typename T>
		SPROUT_CONSTEXPR inline typename sprout::tuples::result_of::push_back<Tuple, T>::type push_back(
			Tuple const& t,
			T const& v
			)
		{
			return sprout::tuples::detail::push_back_impl<typename sprout::tuples::result_of::push_back<Tuple, T>::type>(
				t,
				v,
				typename sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::type()
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_OPERATION_PUSH_BACK_HPP
