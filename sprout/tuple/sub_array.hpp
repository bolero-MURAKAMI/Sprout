#ifndef SPROUT_TUPLE_SUB_ARRAY_HPP
#define SPROUT_TUPLE_SUB_ARRAY_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/sub_array.hpp>

namespace sprout {
	namespace tuples {
		//
		// get
		//
		template<std::size_t I, typename Container>
		typename sprout::container_traits<sprout::sub_array<Container> >::value_type& get(
			sprout::sub_array<Container>& t
			) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(*sprout::next(sprout::internal_begin(t), I)))
		{
			static_assert(I < sprout::container_traits<sprout::sub_array<Container> >::static_size, "get: index out of range");
			return *sprout::next(sprout::internal_begin(t), I);
		}
		template<std::size_t I, typename Container>
		SPROUT_CONSTEXPR typename sprout::container_traits<sprout::sub_array<Container> >::value_type const& get(
			sprout::sub_array<Container> const& t
			) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(*sprout::next(sprout::internal_begin(t), I)))
		{
			static_assert(I < sprout::container_traits<sprout::sub_array<Container> >::static_size, "get: index out of range");
			return *sprout::next(sprout::internal_begin(t), I);
		}
		template<std::size_t I, typename Container>
		typename sprout::container_traits<sprout::sub_array<Container> >::value_type&& get(
			sprout::sub_array<Container>&& t
			) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::move(sprout::tuples::get<I>(t))))
		{
			return std::move(sprout::tuples::get<I>(t));
		}
	}	// namespace tuples

	using sprout::tuples::get;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_SUB_ARRAY_HPP
