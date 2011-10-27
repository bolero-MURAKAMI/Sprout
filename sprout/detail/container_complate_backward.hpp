#ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_BACKWARD_HPP
#define SPROUT_DETAIL_CONTAINER_COMPLATE_BACKWARD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/fixed_container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace detail {
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate_backward_2(
			Result const& result,
			Args const&... args
			)
		{
			return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate_backward_2(
			Result const& result,
			Args const&... args
			)
		{
			return container_complate_backward_2(result, *sprout::prev(sprout::fixed_end(result), sizeof...(Args) + 1), args...);
		}
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate_backward_1(
			Result const& result,
			typename sprout::fixed_container_traits<Result>::difference_type remain,
			Args const&... args
			)
		{
			return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate_backward_1(
			Result const& result,
			typename sprout::fixed_container_traits<Result>::difference_type remain,
			Args const&... args
			)
		{
			return remain != 0
				? container_complate_backward_1(result, remain - 1, args..., *sprout::prev(sprout::fixed_end(result), remain))
				: container_complate_backward_2(result, args...)
				;
		}
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate_backward(
			Result const& result,
			Args const&... args
			)
		{
			return sprout::remake_clone<Result, Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size != sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate_backward(
			Result const& result,
			Args const&... args
			)
		{
			return container_complate_backward_1(result, sprout::fixed_end_offset_backward(result), args...);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_BACKWARD_HPP
