#ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_HPP
#define SPROUT_DETAIL_CONTAINER_COMPLATE_HPP

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
		>::type container_complate_2(
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
		>::type container_complate_2(
			Result const& result,
			Args const&... args
			)
		{
			return container_complate_2(result, args..., *sprout::next(sprout::fixed_begin(result), sizeof...(Args)));
		}
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate_1(
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
		>::type container_complate_1(
			Result const& result,
			typename sprout::fixed_container_traits<Result>::difference_type remain,
			Args const&... args
			)
		{
			return remain != 0
				? container_complate_1(result, remain - 1, *sprout::next(sprout::fixed_begin(result), remain - 1), args...)
				: container_complate_2(result, args...)
				;
		}
		template<typename Result, typename... Args>
		SPROUT_CONSTEXPR inline typename std::enable_if<
			sprout::fixed_container_traits<Result>::fixed_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type container_complate(
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
		>::type container_complate(
			Result const& result,
			Args const&... args
			)
		{
			return container_complate_1(result, sprout::fixed_begin_offset(result), args...);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_HPP
