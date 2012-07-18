#ifndef SPROUT_TYPE_REBIND_TYPES_HPP
#define SPROUT_TYPE_REBIND_TYPES_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// rebind_types
		//
		template<typename Tuple>
		struct rebind_types;

		template<typename Tuple>
		struct rebind_types<Tuple const> {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef typename sprout::types::rebind_types<
					Tuple
				>::template apply<
					Types...
				>::type const type;
			};
		};

		template<typename Tuple>
		struct rebind_types<Tuple volatile> {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef typename sprout::types::rebind_types<
					Tuple
				>::template apply<
					Types...
				>::type volatile type;
			};
		};

		template<typename Tuple>
		struct rebind_types<Tuple const volatile> {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef typename sprout::types::rebind_types<
					Tuple
				>::template apply<
					Types...
				>::type const volatile type;
			};
		};
	}	// namespace types

	using sprout::types::rebind_types;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_REBIND_TYPES_HPP
