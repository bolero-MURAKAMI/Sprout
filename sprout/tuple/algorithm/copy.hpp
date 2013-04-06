#ifndef SPROUT_TUPLE_ALGORITHM_COPY_HPP
#define SPROUT_TUPLE_ALGORITHM_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/tuple/indexes.hpp>

namespace sprout {
	namespace tuples {
		namespace result_of {
			//
			// copy
			//
			template<typename Tuple, typename InputTuple>
			struct copy {
			public:
				typedef typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type type;
			};
		}	// namespace result_of

		namespace detail {
			template<typename Result, typename Tuple, typename InputTuple, sprout::index_t... Indexes1, sprout::index_t... Indexes2>
			inline SPROUT_CONSTEXPR Result
			copy_impl(
				Tuple const& t, InputTuple const& input,
				sprout::index_tuple<Indexes1...>, sprout::index_tuple<Indexes2...>
				)
			{
				return sprout::tuples::remake<Result>(
					t,
					sprout::tuples::get<Indexes2>(input)...,
					sprout::tuples::get<Indexes1>(t)...
					);
			}
			template<typename Tuple, typename InputTuple>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				(sprout::tuples::tuple_size<Tuple>::value > sprout::tuples::tuple_size<InputTuple>::value),
				typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type
			>::type
			copy(Tuple const& t, InputTuple const& input) {
				return sprout::tuples::detail::copy_impl<typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type>(
					t, input,
					sprout::index_range<sprout::tuples::tuple_size<InputTuple>::value, sprout::tuples::tuple_size<Tuple>::value>::make(),
					sprout::tuple_indexes<InputTuple>::make()
					);
			}
			template<typename Tuple, typename InputTuple>
			inline SPROUT_CONSTEXPR typename std::enable_if<
				!(sprout::tuples::tuple_size<Tuple>::value > sprout::tuples::tuple_size<InputTuple>::value),
				typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type
			>::type
			copy(Tuple const& t, InputTuple const& input) {
				return sprout::tuples::detail::copy_impl<typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type>(
					t, input,
					sprout::index_tuple<>(),
					sprout::tuple_indexes<Tuple>::make()
					);
			}
		}	// namespace detail
		//
		// copy
		//
		template<typename Tuple, typename InputTuple>
		inline SPROUT_CONSTEXPR typename sprout::tuples::result_of::copy<Tuple, InputTuple>::type
		copy(Tuple const& t, InputTuple const& input) {
			return sprout::tuples::detail::copy(t, input);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_ALGORITHM_COPY_HPP
