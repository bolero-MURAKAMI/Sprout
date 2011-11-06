#ifndef SPROUT_VARIANT_GET_HPP
#define SPROUT_VARIANT_GET_HPP

#include <sprout/config.hpp>
#include <sprout/variant/variant.hpp>

namespace sprout {
	//
	// get
	//
	template<typename U, typename... Types>
	SPROUT_CONSTEXPR U const& get(sprout::variant<Types...> const& operand) {
		return operand.template get<U>();
	}
	template<typename U, typename... Types>
	U& get(sprout::variant<Types...>& operand) {
		return operand.template get<U>();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_GET_HPP
