#ifndef SPROUT_WEED_OPERATOR_DEREFERENCE_HPP
#define SPROUT_WEED_OPERATOR_DEREFERENCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/weed/expr/tag.hpp>
#include <sprout/weed/expr/make_expr.hpp>
#include <sprout/weed/traits/expr/expr_of.hpp>
#include <sprout/weed/traits/parser/is_parser.hpp>
#include <sprout/weed/detail/uncvref.hpp>

namespace sprout {
	namespace weed {
		//
		// operator*
		//
		template<
			typename Arg,
			typename = typename std::enable_if<
				sprout::weed::traits::is_parser<
					typename sprout::weed::detail::uncvref<Arg>::type
				>::value
			>::type
		>
		inline SPROUT_CONSTEXPR typename sprout::weed::traits::expr_of<
			sprout::weed::tag::dereference,
			Arg
		>::type operator*(Arg&& arg) {
			return sprout::weed::make_expr<sprout::weed::tag::dereference>(
				sprout::forward<Arg>(arg)
				);
		}
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_OPERATOR_DEREFERENCE_HPP
