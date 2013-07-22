#ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_HPP
#define SPROUT_DETAIL_CONTAINER_COMPLATE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/result_of.hpp>

namespace sprout {
	namespace detail {
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type
		container_complate_2(Result const& result, Args const&... args) {
			return sprout::remake<Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size != sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type
		container_complate_2(Result const& result, Args const&... args) {
			return container_complate_2(result, args..., *sprout::next(sprout::internal_begin(result), sizeof...(Args)));
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type
		container_complate_1(
			Result const& result,
			typename sprout::container_traits<Result>::difference_type,
			Args const&... args
			)
		{
			return sprout::remake<Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size != sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type
		container_complate_1(
			Result const& result,
			typename sprout::container_traits<Result>::difference_type remain,
			Args const&... args
			)
		{
			return remain != 0
				? container_complate_1(result, remain - 1, *sprout::next(sprout::internal_begin(result), remain - 1), args...)
				: container_complate_2(result, args...)
				;
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size == sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type
		container_complate(Result const& result, Args const&... args) {
			return sprout::remake<Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size != sizeof...(Args),
			typename sprout::fixed::result_of::algorithm<Result>::type
		>::type
		container_complate(Result const& result, Args const&... args) {
			return container_complate_1(result, sprout::internal_begin_offset(result), args...);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_HPP
