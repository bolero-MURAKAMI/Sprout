#ifndef SPROUT_TUPLE_PIT_HPP
#define SPROUT_TUPLE_PIT_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/pit.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::pit<Container> >::value_type&
		get(sprout::pit<Container>& t) SPROUT_NOEXCEPT {
			static_assert(I < sprout::container_traits<sprout::pit<Container> >::static_size, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::pit<Container> >::value_type const&
		get(sprout::pit<Container> const& t) SPROUT_NOEXCEPT {
			static_assert(I < sprout::container_traits<sprout::pit<Container> >::static_size, "get: index out of range");
			return t[I];
		}
		template<std::size_t I, typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<sprout::pit<Container> >::value_type&&
		get(sprout::pit<Container>&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::move(sprout::tuples::get<I>(t))))
		{
			return sprout::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_PIT_HPP
