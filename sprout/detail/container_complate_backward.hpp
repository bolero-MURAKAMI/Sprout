/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_BACKWARD_HPP
#define SPROUT_DETAIL_CONTAINER_COMPLATE_BACKWARD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/iterator/operation.hpp>
#include <sprout/algorithm/fixed/results.hpp>

namespace sprout {
	namespace detail {
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size == sizeof...(Args),
			typename sprout::fixed::results::algorithm<Result>::type
		>::type
		container_complate_backward_2(Result const& result, Args const&... args) {
			return sprout::remake<Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size != sizeof...(Args),
			typename sprout::fixed::results::algorithm<Result>::type
		>::type
		container_complate_backward_2(Result const& result, Args const&... args) {
			return sprout::detail::container_complate_backward_2(result, *sprout::prev(sprout::internal_end(result), sizeof...(Args) + 1), args...);
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size == sizeof...(Args),
			typename sprout::fixed::results::algorithm<Result>::type
		>::type
		container_complate_backward_1(
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
			typename sprout::fixed::results::algorithm<Result>::type
		>::type
		container_complate_backward_1(
			Result const& result,
			typename sprout::container_traits<Result>::difference_type remain,
			Args const&... args
			)
		{
			return remain != 0
				? sprout::detail::container_complate_backward_1(result, remain - 1, args..., *sprout::prev(sprout::internal_end(result), remain))
				: sprout::detail::container_complate_backward_2(result, args...)
				;
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size == sizeof...(Args),
			typename sprout::fixed::results::algorithm<Result>::type
		>::type
		container_complate_backward(Result const& result, Args const&... args) {
			return sprout::remake<Result>(result, sprout::size(result), args...);
		}
		template<typename Result, typename... Args>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			sprout::container_traits<Result>::static_size != sizeof...(Args),
			typename sprout::fixed::results::algorithm<Result>::type
		>::type
		container_complate_backward(Result const& result, Args const&... args) {
			return sprout::detail::container_complate_backward_1(result, sprout::internal_end_offset_backward(result), args...);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_CONTAINER_COMPLATE_BACKWARD_HPP
