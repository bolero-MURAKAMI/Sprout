#ifndef SPROUT_FUNCTIONAL_HASH_TO_HASH_HPP
#define SPROUT_FUNCTIONAL_HASH_TO_HASH_HPP

#include <cstddef>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/functional/hash/hash_fwd.hpp>
#include <sprout/functional/hash/hash_value.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl hash_value(...);
}	// namespace sprout_adl

namespace sprout_hash_detail {
	using sprout::hash_value;
	using sprout_adl::hash_value;

	template<typename T>
	struct has_adl_hash_value_test {
	public:
		template<
			typename U = T,
			typename sprout::enabler_if<
				sprout::is_found_via_adl<decltype(hash_value(std::declval<U>()))>::value
			>::type = sprout::enabler
		>
		static std::true_type test(int);
		static std::false_type test(...);
	};
#if defined(_MSC_VER)
	template<typename T, typename Base_ = decltype(sprout_hash_detail::has_adl_hash_value_test<T>::test(0))>
	struct has_adl_hash_value
		: public Base_
	{};
#else
	template<typename T>
	struct has_adl_hash_value
		: public decltype(sprout_hash_detail::has_adl_hash_value_test<T>::test(0))
	{};
#endif

	template<typename T, typename Enable = void>
	struct select_adl_hash_value;
	template<typename T>
	struct select_adl_hash_value<
		T,
		typename std::enable_if<
			sprout_hash_detail::has_adl_hash_value<T>::value
		>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_adl_hash_value<
		T,
		typename std::enable_if<!(
			sprout_hash_detail::has_adl_hash_value<T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<typename T, typename Enable = void>
	struct select_std_hash;
	template<typename T>
	struct select_std_hash<
		T,
		typename std::enable_if<
			!sprout_hash_detail::has_adl_hash_value<T>::value
		>::type
	>
		: public std::true_type
	{};
	template<typename T>
	struct select_std_hash<
		T,
		typename std::enable_if<!(
			!sprout_hash_detail::has_adl_hash_value<T>::value
		)>::type
	>
		: public std::false_type
	{};

	template<typename T, typename = void>
	struct noexcept_to_hash;
	template<typename T>
	struct noexcept_to_hash<T, typename std::enable_if<sprout_hash_detail::select_adl_hash_value<T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(hash_value(std::declval<T>()), false)>
	{};
	template<typename T>
	struct noexcept_to_hash<T, typename std::enable_if<sprout_hash_detail::select_std_hash<T>::value>::type>
		: public std::integral_constant<bool, SPROUT_NOEXCEPT_EXPR_OR_DEFAULT(std::hash<typename std::decay<T>::type>()(std::declval<T>()), false)>
	{};

	template<typename T, typename = void>
	struct to_hash_result;
	template<typename T>
	struct to_hash_result<T, typename std::enable_if<sprout_hash_detail::select_adl_hash_value<T>::value>::type> {
	public:
		typedef decltype(hash_value(std::declval<T>())) type;
	};
	template<typename T>
	struct to_hash_result<T, typename std::enable_if<sprout_hash_detail::select_std_hash<T>::value>::type> {
	public:
		typedef decltype(std::hash<typename std::decay<T>::type>()(std::declval<T>())) type;
	};

	template<
		typename T,
		typename sprout::enabler_if<sprout_hash_detail::select_adl_hash_value<T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_hash_detail::to_hash_result<T>::type
	to_hash_impl(T&& t)
	SPROUT_NOEXCEPT_EXPR((sprout_hash_detail::noexcept_to_hash<T>::value))
	{
		return hash_value(sprout::forward<T>(t));
	}
	template<
		typename T,
		typename sprout::enabler_if<sprout_hash_detail::select_std_hash<T>::value>::type = sprout::enabler
	>
	inline SPROUT_CONSTEXPR typename sprout_hash_detail::to_hash_result<T>::type
	to_hash_impl(T&& t)
	SPROUT_NOEXCEPT_EXPR((sprout_hash_detail::noexcept_to_hash<T>::value))
	{
		return std::hash<typename std::decay<T>::type>()(sprout::forward<T>(t));
	}
}	// namespace sprout_hash_detail

namespace sprout {
	//
	// to_hash
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	to_hash(T const& v) {
		return sprout_hash_detail::to_hash_impl(v);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_HASH_TO_HASH_HPP
