/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_FLEX_HPP
#define SPROUT_TUPLE_FLEX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/tuple/tuple/tuple.hpp>
#include <sprout/tuple/tuple/get.hpp>
#include <sprout/tuple/tuple/tuple_size.hpp>
#include <sprout/tuple/tuple/tuple_element.hpp>
#include <sprout/tuple/tuple/type_traits.hpp>
#include <sprout/tuple/flexibly_construct.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type_traits/common_decay.hpp>

namespace sprout {
	namespace tuples {
		//
		// flex_tuple
		//
		template<typename... Types>
		class flex_tuple {
		public:
			typedef sprout::tuples::tuple<Types...> tuple_type;
		private:
			typedef sprout::value_holder<tuple_type const&> holder_type;
		private:
			holder_type holder_;
		public:
			flex_tuple(flex_tuple const&) = default;
			flex_tuple(flex_tuple&&) = default;
			SPROUT_CONSTEXPR flex_tuple(tuple_type const& t)
				: holder_(t)
			{}
			SPROUT_CONSTEXPR operator tuple_type const&() const {
				return holder_.get();
			}
			template<typename... UTypes>
			SPROUT_CONSTEXPR operator sprout::tuples::tuple<UTypes...>() const {
				return sprout::tuples::tuple<UTypes...>(sprout::tuples::flexibly_construct, holder_.get());
			}
		};
		//
		// flex
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T const&
		flex(T const& t) {
			return t;
		}
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::flex_tuple<Types...>
		flex(sprout::tuples::tuple<Types...> const& t) {
			return sprout::tuples::flex_tuple<Types...>(t);
		}
		template<typename To, typename... Types>
		inline SPROUT_CONSTEXPR To
		flex(sprout::tuples::tuple<Types...> const& t) {
			return sprout::tuples::flex(t);
		}

		//
		// recursive_flex_tuple
		//
		template<typename... Types>
		class recursive_flex_tuple
			: public sprout::tuples::flex_tuple<Types...>
		{
		private:
			typedef sprout::tuples::flex_tuple<Types...> base_type;
		private:
			template<typename... UTypes, sprout::index_t... Indexes>
			static SPROUT_CONSTEXPR sprout::tuples::tuple<UTypes...>
			implicit_conversion_impl(typename base_type::tuple_type const& t, sprout::index_tuple<Indexes...>) {
				return sprout::tuples::tuple<UTypes...>(
					sprout::tuples::flexibly_construct,
					sprout::tuples::flex(sprout::tuples::get<Indexes>(t))...
					);
			}
		public:
			recursive_flex_tuple(recursive_flex_tuple const&) = default;
			recursive_flex_tuple(recursive_flex_tuple&&) = default;
			SPROUT_CONSTEXPR recursive_flex_tuple(typename base_type::tuple_type const& t)
				: base_type(t)
			{}
			template<typename... UTypes>
			SPROUT_CONSTEXPR operator sprout::tuples::tuple<UTypes...>() const {
				return implicit_conversion_impl<UTypes...>(*this, sprout::make_index_tuple<sizeof...(Types)>::make());
			}
		};
		//
		// recursive_flex
		//
		template<typename T>
		inline SPROUT_CONSTEXPR T const&
		recursive_flex(T const& t) {
			return t;
		}
		template<typename... Types>
		inline SPROUT_CONSTEXPR sprout::tuples::recursive_flex_tuple<Types...>
		recursive_flex(sprout::tuples::tuple<Types...> const& t) {
			return sprout::tuples::recursive_flex_tuple<Types...>(t);
		}
		template<typename To, typename... Types>
		inline SPROUT_CONSTEXPR To
		recursive_flex(sprout::tuples::tuple<Types...> const& t) {
			return sprout::tuples::recursive_flex(t);
		}

		//
		// common_flex_type
		//
		template<typename... Types>
		struct common_flex_type;
		template<typename T>
		struct common_flex_type<T>
			: public sprout::common_decay<T>
		{};
		namespace detail {
			template<typename T, typename U, typename IndexTuple>
			struct common_flex_type_impl_2;
			template<typename T, typename U, sprout::index_t... Indexes>
			struct common_flex_type_impl_2<T, U, sprout::index_tuple<Indexes...> >
				: public sprout::identity<
					sprout::tuples::tuple<
						typename sprout::tuples::common_flex_type<
							typename sprout::tuples::tuple_element<Indexes, T>::type,
							typename sprout::tuples::tuple_element<Indexes, U>::type
						>::type...
					>
				>
			{};

			template<typename T, typename U, typename Enable = void>
			struct common_flex_type_impl_1;
			template<typename T, typename U>
			struct common_flex_type_impl_1<T, U, typename std::enable_if<(sprout::tuples::tuple_size<T>::value < sprout::tuples::tuple_size<U>::value)>::type>
				: public sprout::tuples::common_flex_type<U>
			{};
			template<typename T, typename U>
			struct common_flex_type_impl_1<T, U, typename std::enable_if<(sprout::tuples::tuple_size<T>::value > sprout::tuples::tuple_size<U>::value)>::type>
				: public sprout::tuples::common_flex_type<T>
			{};
			template<typename T, typename U>
			struct common_flex_type_impl_1<T, U, typename std::enable_if<(sprout::tuples::tuple_size<T>::value == sprout::tuples::tuple_size<U>::value)>::type>
				: public sprout::tuples::detail::common_flex_type_impl_2<T, U, typename sprout::tuples::tuple_indexes<T>::type>
			{};

			template<typename T, typename U, typename Enable = void>
			struct common_flex_type_impl;
			template<typename T, typename U>
			struct common_flex_type_impl<T, U, typename std::enable_if<(sprout::tuples::is_tuple<T>::value && sprout::tuples::is_tuple<U>::value)>::type>
				: public sprout::tuples::detail::common_flex_type_impl_1<T, U>
			{};
			template<typename T, typename U>
			struct common_flex_type_impl<T, U, typename std::enable_if<!(sprout::tuples::is_tuple<T>::value && sprout::tuples::is_tuple<U>::value)>::type>
				: public sprout::common_decay<T, U>
			{};
		}	// namespace detail
		template<typename T, typename U>
		struct common_flex_type<T, U>
			: public sprout::tuples::detail::common_flex_type_impl<T, U>
		{};
		template<typename T, typename U, typename... Tail>
		struct common_flex_type<T, U, Tail...>
			: public sprout::tuples::common_flex_type<typename sprout::tuples::common_flex_type<T, U>::type, Tail...>
		{};

		//
		// common_recursive_flex_type
		//
		template<typename... Types>
		struct common_recursive_flex_type;
		template<typename T>
		struct common_recursive_flex_type<T>
			: public sprout::tuples::common_flex_type<T>
		{};
		namespace detail {
			template<typename T, typename U, typename IndexTuple>
			struct common_recursive_flex_type_impl_2;
			template<typename T, typename U, sprout::index_t... Indexes>
			struct common_recursive_flex_type_impl_2<T, U, sprout::index_tuple<Indexes...> >
				: public sprout::identity<
					sprout::tuples::tuple<
						typename sprout::tuples::common_recursive_flex_type<
							typename sprout::tuples::tuple_element<Indexes, T>::type,
							typename sprout::tuples::tuple_element<Indexes, U>::type
						>::type...
					>
				>
			{};

			template<typename T, typename U, typename Enable = void>
			struct common_recursive_flex_type_impl_1;
			template<typename T, typename U>
			struct common_recursive_flex_type_impl_1<T, U, typename std::enable_if<(sprout::tuples::tuple_size<T>::value < sprout::tuples::tuple_size<U>::value)>::type>
				: public sprout::tuples::common_recursive_flex_type<U>
			{};
			template<typename T, typename U>
			struct common_recursive_flex_type_impl_1<T, U, typename std::enable_if<(sprout::tuples::tuple_size<T>::value > sprout::tuples::tuple_size<U>::value)>::type>
				: public sprout::tuples::common_recursive_flex_type<T>
			{};
			template<typename T, typename U>
			struct common_recursive_flex_type_impl_1<T, U, typename std::enable_if<(sprout::tuples::tuple_size<T>::value == sprout::tuples::tuple_size<U>::value)>::type>
				: public sprout::tuples::detail::common_recursive_flex_type_impl_2<T, U, typename sprout::tuples::tuple_indexes<T>::type>
			{};

			template<typename T, typename U, typename Enable = void>
			struct common_recursive_flex_type_impl;
			template<typename T, typename U>
			struct common_recursive_flex_type_impl<T, U, typename std::enable_if<(sprout::tuples::is_tuple<T>::value && sprout::tuples::is_tuple<U>::value)>::type>
				: public sprout::tuples::detail::common_recursive_flex_type_impl_1<T, U>
			{};
			template<typename T, typename U>
			struct common_recursive_flex_type_impl<T, U, typename std::enable_if<!(sprout::tuples::is_tuple<T>::value && sprout::tuples::is_tuple<U>::value)>::type>
				: public sprout::tuples::common_flex_type<T, U>
			{};
		}	// namespace detail
		template<typename T, typename U>
		struct common_recursive_flex_type<T, U>
			: public sprout::tuples::detail::common_recursive_flex_type_impl<T, U>
		{};
		template<typename T, typename U, typename... Tail>
		struct common_recursive_flex_type<T, U, Tail...>
			: public sprout::tuples::common_recursive_flex_type<typename sprout::tuples::common_recursive_flex_type<T, U>::type, Tail...>
		{};
	}	// namespace tuples

	using sprout::tuples::flex_tuple;
	using sprout::tuples::flex;

	using sprout::tuples::recursive_flex_tuple;
	using sprout::tuples::recursive_flex;

	using sprout::tuples::common_flex_type;
	using sprout::tuples::common_recursive_flex_type;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_FLEX_HPP
