#ifndef SPROUT_GENERATOR_GENERATED_VALUE_HPP
#define SPROUT_GENERATOR_GENERATED_VALUE_HPP

#include <utility>
#include <type_traits>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl generated_value(...);
}	// namespace sprout_adl

namespace sprout_generator_detail {
	using sprout::tuples::get;
	using sprout_adl::generated_value;

	template<typename T>
	struct has_adl_generated_value_test {
	public:
		template<
			typename U = T,
			typename sprout::enabler_if<
				sprout::is_found_via_adl<decltype(generated_value(std::declval<U>()))>::value
			>::type = sprout::enabler
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<typename T>
	struct has_adl_generated_value
		: public decltype(sprout_generator_detail::has_adl_generated_value_test<T>::test(0))
	{};

	template<typename T>
	struct has_mem_generated_value_test {
	public:
		template<
			typename U = T,
			typename = decltype(std::declval<U>().generated_value())
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<typename T>
	struct has_mem_generated_value
		: public decltype(sprout_generator_detail::has_mem_generated_value_test<T>::test(0))
	{};

	template<typename T>
	struct has_get_generated_value_test {
	public:
		template<
			typename U = T,
			typename = decltype(get<0>(std::declval<U>()))
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
	template<typename T>
	struct has_get_generated_value
		: public decltype(sprout_generator_detail::has_get_generated_value_test<T>::test(0))
	{};

	template<typename T, typename Enable = void>
	struct select_adl_generated_value;
	template<typename T>
	struct select_adl_generated_value<
		T,
		typename std::enable_if<
			sprout_generator_detail::has_adl_generated_value<T>::value
		>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_adl_generated_value<
		T,
		typename std::enable_if<!(
			sprout_generator_detail::has_adl_generated_value<T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<typename T, typename Enable = void>
	struct select_mem_generated_value;
	template<typename T>
	struct select_mem_generated_value<
		T,
		typename std::enable_if<
			sprout_generator_detail::has_mem_generated_value<T>::value
			&& !sprout_generator_detail::has_adl_generated_value<T>::value
		>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_mem_generated_value<
		T,
		typename std::enable_if<!(
			sprout_generator_detail::has_mem_generated_value<T>::value
			&& !sprout_generator_detail::has_adl_generated_value<T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<typename T, typename Enable = void>
	struct select_get_generated_value;
	template<typename T>
	struct select_get_generated_value<
		T,
		typename std::enable_if<
			sprout_generator_detail::has_get_generated_value<T>::value
			&& !sprout_generator_detail::has_adl_generated_value<T>::value
			&& !sprout_generator_detail::has_mem_generated_value<T>::value
		>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_get_generated_value<
		T,
		typename std::enable_if<!(
			sprout_generator_detail::has_get_generated_value<T>::value
			&& !sprout_generator_detail::has_adl_generated_value<T>::value
			&& !sprout_generator_detail::has_mem_generated_value<T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<typename T, typename = void>
	struct noexcept_generated_value;
	template<typename T>
	struct noexcept_generated_value<T, typename std::enable_if<sprout_generator_detail::select_adl_generated_value<T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(generated_value(std::declval<T>()), false)>
	{};
	template<typename T>
	struct noexcept_generated_value<T, typename std::enable_if<sprout_generator_detail::select_mem_generated_value<T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(std::declval<T>().generated_value(), false)>
	{};
	template<typename T>
	struct noexcept_generated_value<T, typename std::enable_if<sprout_generator_detail::select_get_generated_value<T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(get<0>(std::declval<T>()), false)>
	{};

	template<typename T, typename = void>
	struct generated_value_result;
	template<typename T>
	struct generated_value_result<T, typename std::enable_if<sprout_generator_detail::select_adl_generated_value<T>::value>::type> {
	public:
		typedef decltype(generated_value(std::declval<T>())) type;
	};
	template<typename T>
	struct generated_value_result<T, typename std::enable_if<sprout_generator_detail::select_mem_generated_value<T>::value>::type> {
	public:
		typedef decltype(std::declval<T>().generated_value()) type;
	};
	template<typename T>
	struct generated_value_result<T, typename std::enable_if<sprout_generator_detail::select_get_generated_value<T>::value>::type> {
	public:
		typedef decltype(get<0>(std::declval<T>())) type;
	};

	template<
		typename T,
		typename sprout::enabler_if<sprout_generator_detail::select_adl_generated_value<T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_generator_detail::generated_value_result<T>::type
	generated_value_impl(T&& t)
		SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_generated_value<T>::value))
	{
		return generated_value(sprout::forward<T>(t));
	}
	template<
		typename T,
		typename sprout::enabler_if<sprout_generator_detail::select_mem_generated_value<T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_generator_detail::generated_value_result<T>::type
	generated_value_impl(T&& t)
		SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_generated_value<T>::value))
	{
		return sprout::forward<T>(t).generated_value();
	}
	template<
		typename T,
		typename sprout::enabler_if<sprout_generator_detail::select_get_generated_value<T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_generator_detail::generated_value_result<T>::type
	generated_value_impl(T&& t)
		SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_generated_value<T>::value))
	{
		return get<0>(sprout::forward<T>(t));
	}
}	// namespace sprout_generator_detail

namespace sprout {
	namespace generators {
		//
		// generated_value
		//
		template<typename T>
		inline SPROUT_CONSTEXPR typename sprout_generator_detail::generated_value_result<T>::type
		generated_value(T&& t)
			SPROUT_NOEXCEPT_EXPR((sprout_generator_detail::noexcept_generated_value<T>::value))
		{
			return sprout_generator_detail::generated_value_impl(sprout::forward<T>(t));
		}
	}	// namespace generators

	using sprout::generators::generated_value;
}	// namespace sprout

#endif	// #ifndef SPROUT_GENERATOR_GENERATED_VALUE_HPP
