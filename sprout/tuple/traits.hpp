#ifndef SPROUT_TUPLE_TRAITS_HPP
#define SPROUT_TUPLE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace types {
		//
		// rebind_types
		//
		template<typename... Ts>
		struct rebind_types<sprout::tuples::tuple<Ts...> > {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef sprout::tuples::tuple<Types...> type;
			};
		};
	}	// namespace types

	using sprout::types::rebind_types;
}	// namespace sprout

namespace sprout {
	namespace tuples {
		//
		// rebind_types
		//
		template<typename Tuple>
		struct rebind_types
			: public sprout::types::rebind_types<Tuple>
		{};

		//
		// tuple_construct_traits
		//
		template<typename Tuple>
		struct tuple_construct_traits;

		namespace detail {
			template<typename Tuple, typename IndexTuple>
			struct default_copied;
			template<typename Tuple, sprout::index_t... Indexes>
			struct default_copied<Tuple, sprout::index_tuple<Indexes...> > {
			public:
				typedef typename sprout::tuples::rebind_types<Tuple>::template apply<
					typename std::decay<
						typename sprout::tuples::tuple_element<Indexes, Tuple>::type
					>::type...
				>::type type;
			};

			template<typename Tuple, typename... Args>
			SPROUT_CONSTEXPR typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type
			default_make_tuple(Args&&... args) {
				typedef typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type copied_type;
				return copied_type(sprout::forward<Args>(args)...);
			}
		}	// namespace detail

		template<typename Tuple>
		struct tuple_construct_traits {
		public:
			typedef typename sprout::tuples::detail::default_copied<
				Tuple,
				typename sprout::index_range<0, sprout::tuples::tuple_size<Tuple>::value>::type
			>::type copied_type;
		public:
			template<typename Tup>
			static SPROUT_CONSTEXPR copied_type deep_copy(Tup&& tup) {
				return sprout::forward<Tup>(tup);
			}
			template<typename... Args>
			static SPROUT_CONSTEXPR copied_type make(Args&&... args) {
				return sprout::tuples::detail::default_make_tuple<Tuple>(sprout::forward<Args>(args)...);
			}
			template<typename Tup, typename... Args>
			static SPROUT_CONSTEXPR copied_type remake(
				Tup&& tup,
				Args&&... args
				)
			{
				return make(sprout::forward<Args>(args)...);
			}
		};
		template<typename Tuple>
		struct tuple_construct_traits<Tuple const>
			: public sprout::tuples::tuple_construct_traits<Tuple>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_construct_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TRAITS_HPP
