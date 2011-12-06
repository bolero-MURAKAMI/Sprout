#ifndef SPROUT_TUPLE_TRAITS_HPP
#define SPROUT_TUPLE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/type/rebind_types.hpp>

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
		// tuple_traits
		//
		template<typename Tuple>
		struct tuple_traits {
		public:
			typedef Tuple internal_type;
			typedef Tuple clone_type;
		};
		template<typename Tuple>
		struct tuple_traits<Tuple const>
			: public sprout::tuples::tuple_traits<Tuple>
		{};

		//
		// rebind_types
		//
		template<typename Tuple>
		struct rebind_types
			: public sprout::types::rebind_types<Tuple>
		{};

		//
		// clone_functor
		//
		template<typename Tuple>
		struct clone_functor {
		public:
			template<typename Other>
			SPROUT_CONSTEXPR typename sprout::tuples::tuple_traits<Tuple>::clone_type operator()(Other&& t) const {
				return typename sprout::tuples::tuple_traits<Tuple>::clone_type(sprout::forward<Other>(t));
			}
		};
		template<typename Tuple>
		struct clone_functor<Tuple const>
			: public sprout::tuples::clone_functor<Tuple>
		{};

		//
		// make_clone_functor
		//
		template<typename Tuple>
		struct make_clone_functor {
		public:
			template<typename... Args>
			SPROUT_CONSTEXPR typename sprout::tuples::tuple_traits<Tuple>::clone_type operator()(Args&&... args) const {
				return typename sprout::tuples::tuple_traits<Tuple>::clone_type(sprout::forward<Args>(args)...);
			}
		};
		template<typename Tuple>
		struct make_clone_functor<Tuple const>
			: public sprout::tuples::make_clone_functor<Tuple>
		{};

		//
		// remake_clone_functor
		//
		template<typename Tuple>
		struct remake_clone_functor {
		public:
			template<typename Other, typename... Args>
			SPROUT_CONSTEXPR typename sprout::tuples::tuple_traits<Tuple>::clone_type operator()(
				Other&& other,
				Args&&... args
				) const
			{
				return sprout::tuples::make_clone_functor<Tuple>().template operator()(sprout::forward<Args>(args)...);
			}
		};
		template<typename Tuple>
		struct remake_clone_functor<Tuple const>
			: public sprout::tuples::remake_clone_functor<Tuple>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TRAITS_HPP
