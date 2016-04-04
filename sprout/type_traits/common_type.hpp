/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_COMMON_TYPE_HPP
#define SPROUT_TYPE_TRAITS_COMMON_TYPE_HPP

#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/has_type.hpp>
#include <sprout/utility/pack.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	//
	// undecayed_common_type
	//
	namespace detail {
		template<typename T1, typename T2>
		struct undecayed_common_type2
			: public sprout::identity<decltype(std::declval<bool>() ? std::declval<T1>() : std::declval<T2>())>
		{};
		template<typename Void, typename... Types>
		struct undecayed_common_type_impl
			: public sprout::detail::nil_base
		{};
		template<typename T>
		struct undecayed_common_type_impl<void, T>
			: public sprout::identity<T>
		{};
		template<typename T1, typename T2, typename... Tail>
		struct undecayed_common_type_impl<typename sprout::head_element<void, typename sprout::detail::undecayed_common_type2<T1, T2>::type>::type, T1, T2, Tail...>
			: public sprout::detail::undecayed_common_type_impl<void, typename sprout::detail::undecayed_common_type2<T1, T2>::type, Tail...>
		{};
	}	// namespace detail
	template<typename... Types>
	struct undecayed_common_type
		: public sprout::detail::undecayed_common_type_impl<void, Types...>
	{};

	//
	// common_type
	//
	namespace detail {
		template<typename CommonType, bool = sprout::has_type<CommonType>::value>
		struct common_type_impl;
		template<typename CommonType>
		struct common_type_impl<CommonType, false>
			: public CommonType
		{};
		template<typename CommonType>
		struct common_type_impl<CommonType, true>
			: public std::decay<typename CommonType::type>
		{};
	}	// namespace detail
	template<typename... Types>
	struct common_type
		: public sprout::detail::common_type_impl<sprout::undecayed_common_type<Types...> >
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename... Types>
	using undecayed_common_type_t = typename sprout::undecayed_common_type<Types...>::type;

	template<typename... Types>
	using common_type_t = typename sprout::common_type<Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_COMMON_TYPE_HPP
