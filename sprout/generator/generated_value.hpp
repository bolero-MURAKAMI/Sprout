#ifndef SPROUT_GENERATOR_GENERATED_VALUE_HPP
#define SPROUT_GENERATOR_GENERATED_VALUE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/generator/generator_access_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl generated_value(...);
}	// namespace sprout_adl

namespace sprout_generator_detail {
	using sprout_adl::generated_value;

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen>::generated_value(std::declval<Gen&>()))
	generated_value(Gen& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen>::generated_value(std::declval<Gen&>())))
	{
		return sprout::generators::generator_access_traits<Gen>::generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::generated_value(std::declval<Gen&&>()))
	>::type
	generated_value(Gen&& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<typename std::remove_reference<Gen>::type>::generated_value(std::declval<Gen&&>())))
	{
		return sprout::generators::generator_access_traits<Gen>::generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(sprout::generators::generator_access_traits<Gen const>::generated_value(std::declval<Gen const&>()))
	generated_value(Gen const& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::generators::generator_access_traits<Gen const>::generated_value(std::declval<Gen const&>())))
	{
		return sprout::generators::generator_access_traits<Gen const>::generated_value(gen);
	}

	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(generated_value(std::declval<Gen&>()))
	call_generated_value(Gen& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(generated_value(std::declval<Gen&>())))
	{
		return generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		!std::is_const<Gen>::value && !std::is_volatile<Gen>::value && !std::is_reference<Gen>::value,
		decltype(generated_value(std::declval<Gen&&>()))
	>::type
	call_generated_value(Gen&& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(generated_value(std::declval<Gen&&>())))
	{
		return generated_value(gen);
	}
	template<typename Gen>
	inline SPROUT_CONSTEXPR decltype(generated_value(std::declval<Gen const&>()))
	call_generated_value(Gen const& gen)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(generated_value(std::declval<Gen const&>())))
	{
		return generated_value(gen);
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		//
		// generated_value
		//
		template<typename T>
		inline SPROUT_CONSTEXPR decltype(sprout_generator_detail::call_generated_value(std::declval<T>()))
		generated_value(T&& t)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout_generator_detail::call_generated_value(std::declval<T>())))
		{
			return sprout_generator_detail::call_generated_value(sprout::forward<T>(t));
		}
	}	// namespace generators

	using sprout::generators::generated_value;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_GENERATED_VALUE_HPP
