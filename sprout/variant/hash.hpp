#ifndef SPROUT_VARIANT_HASH_HPP
#define SPROUT_VARIANT_HASH_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash.hpp>
#include <sprout/variant/variant.hpp>
#include <sprout/variant/static_visitor.hpp>
#include <sprout/variant/apply_visitor.hpp>

namespace sprout {
	namespace detail {
		class variant_hash_visitor
			: public sprout::static_visitor<std::size_t>
		{
		public:
			template<typename T>
			SPROUT_CONSTEXPR std::size_t operator()(T const& t) const {
				return sprout::to_hash(t);
			}
		};
	}	// namespace detail
	//
	// hash_value
	//
	template<typename... Types>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::variant<Types...> const& v) {
		return sprout::hash_combine(
			sprout::apply_visitor(sprout::detail::variant_hash_visitor(), v),
			v.which()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_HASH_HPP
