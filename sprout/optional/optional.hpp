/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_OPTIONAL_HPP
#define SPROUT_OPTIONAL_OPTIONAL_HPP

#include <type_traits>
#include <initializer_list>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/value_holder/get.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/type_traits/std_type_traits.hpp>
#include <sprout/type_traits/is_convert_constructible.hpp>
#include <sprout/none.hpp>
#include <sprout/optional/nullopt.hpp>
#include <sprout/optional/in_place.hpp>
#include <sprout/optional/exceptions.hpp>
#include <sprout/assert.hpp>

namespace sprout {
	//
	// optional
	//
	template<typename T>
	class optional {
	public:
		typedef T type;
	private:
		typedef sprout::value_holder<type> holder_type;
	public:
		typedef typename holder_type::value_type value_type;
		typedef typename holder_type::lvalue_reference lvalue_reference;
		typedef typename holder_type::rvalue_reference rvalue_reference;
		typedef typename holder_type::reference reference;
		typedef typename holder_type::const_lvalue_reference const_lvalue_reference;
		typedef typename holder_type::const_rvalue_reference const_rvalue_reference;
		typedef typename holder_type::const_reference const_reference;
		typedef typename holder_type::pointer pointer;
		typedef typename holder_type::const_pointer const_pointer;
		typedef typename holder_type::lvalue_reference_type lvalue_reference_type;
		typedef typename holder_type::rvalue_reference_type rvalue_reference_type;
		typedef typename holder_type::reference_type reference_type;
		typedef typename holder_type::reference_const_type reference_const_type;
		typedef typename holder_type::pointer_type pointer_type;
		typedef typename holder_type::pointer_const_type pointer_const_type;
	public:
		template<typename... Args>
		struct is_constructible_args
			: public sprout::is_constructible<T, Args&&...>
		{};
	public:
		static SPROUT_CONSTEXPR reference_type get(optional& t) SPROUT_NOEXCEPT {
			return sprout::get(t.val);
		}
		static SPROUT_CONSTEXPR rvalue_reference_type get(optional&& t) SPROUT_NOEXCEPT {
			return static_cast<rvalue_reference_type>(get(t));
		}
		static SPROUT_CONSTEXPR reference_const_type get(optional const& t) SPROUT_NOEXCEPT {
			return sprout::get(t.val);
		}
		static SPROUT_CONSTEXPR pointer_type get_pointer(optional& t) SPROUT_NOEXCEPT {
			return sprout::get_pointer(t.val);
		}
		static SPROUT_CONSTEXPR pointer_type get_pointer(optional&& t) SPROUT_NOEXCEPT {
			return get_pointer(t);
		}
		static SPROUT_CONSTEXPR pointer_const_type get_pointer(optional const& t) SPROUT_NOEXCEPT {
			return sprout::get_pointer(t.val);
		}
		static SPROUT_CONSTEXPR reference_type get_value_or(optional& t, reference_type v) SPROUT_NOEXCEPT {
			return t.is_initialized() ? sprout::get(t.val)
				: v
				;
		}
		static SPROUT_CONSTEXPR rvalue_reference_type get_value_or(optional&& t, rvalue_reference_type v) SPROUT_NOEXCEPT {
			return static_cast<rvalue_reference_type>(get_value_or(t, v));
		}
		static SPROUT_CONSTEXPR reference_const_type get_value_or(optional const& t, reference_const_type v) SPROUT_NOEXCEPT {
			return t.is_initialized() ? sprout::get(t.val)
				: v
				;
		}
	private:
		bool init;
		holder_type val;
	private:
		SPROUT_CXX14_CONSTEXPR void destroy() SPROUT_NOEXCEPT {
			init = false;
		}
	public:
		// 20.6.4.1, constructors
		SPROUT_CONSTEXPR optional() SPROUT_NOEXCEPT
			: init(false)
		{}
		SPROUT_CONSTEXPR optional(sprout::nullopt_t) SPROUT_NOEXCEPT
			: init(false)
		{}
		SPROUT_CONSTEXPR optional(optional const& v)
			: init(v.init)
			, val(v.is_initialized() ? holder_type(*v) : holder_type())
		{}
#if SPROUT_GCC_IN_RANGE((4, 8, 0), (4, 8, 2))
		optional(optional&&) = default;
#else
		SPROUT_CONSTEXPR optional(optional&& v)
		SPROUT_NOEXCEPT_EXPR(std::is_nothrow_move_constructible<T>::value)
			: init(v.init)
			, val(v.is_initialized() ? holder_type(sprout::move(get(v))) : holder_type())
		{}
#endif
		SPROUT_CONSTEXPR optional(T const& v)
			: init(true)
			, val(v)
		{}
		// !!! TEMP: for T const&
//		SPROUT_CONSTEXPR optional(T&& v)
//			: init(true)
//			, val(sprout::move(v))
//		{}
		template<
			typename... Args,
			typename = typename std::enable_if<is_constructible_args<Args...>::value>::type
		>
		explicit SPROUT_CONSTEXPR optional(sprout::in_place_t, Args&&... args)
			: init(true)
			, val(sprout::in_place, sprout::forward<Args>(args)...)
		{}
		template<
			typename U, typename... Args,
			typename = typename std::enable_if<is_constructible_args<std::initializer_list<U>&, Args...>::value>::type
		>
		explicit SPROUT_CONSTEXPR optional(sprout::in_place_t, std::initializer_list<U> il, Args&&... args)
			: init(true)
			, val(sprout::in_place, il, sprout::forward<Args>(args)...)
		{}
		SPROUT_CONSTEXPR optional(bool cond, T const& v)
			: init(cond)
			, val(cond ? holder_type(v) : holder_type())
		{}
		// !!! TEMP: for T const&
//		SPROUT_CONSTEXPR optional(bool cond, T&& v)
//			: init(cond)
//			, val(cond ? holder_type(sprout::move(v)) : holder_type())
//		{}
		template<typename U>
		explicit SPROUT_CONSTEXPR optional(optional<U> const& v)
			: init(v.is_initialized())
			, val(v.is_initialized() ? holder_type(*v) : holder_type())
		{}
		template<typename U>
		explicit SPROUT_CONSTEXPR optional(optional<U>&& v)
			: init(v.is_initialized())
			, val(v.is_initialized() ? holder_type(sprout::move(optional<U>::get(v))) : holder_type())
		{}
		// 20.6.4.3, assignment
		SPROUT_CXX14_CONSTEXPR optional& operator=(sprout::nullopt_t v) SPROUT_NOEXCEPT {
			assign(v);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR optional& operator=(optional const& v) {
			assign(v);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR optional& operator=(optional&& v)
		SPROUT_NOEXCEPT_EXPR(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value)
		{
			assign(sprout::forward<optional>(v));
			return *this;
		}
		template<
			typename U,
//			typename = typename std::enable_if<std::is_constructible<T, U>::value && std::is_assignable<U, T>::value>::type
			typename = typename std::enable_if<std::is_constructible<T, U&&>::value>::type
		>
		SPROUT_CXX14_CONSTEXPR optional& operator=(U&& v) {
			assign(sprout::forward<U>(v));
			return *this;
		}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR optional& operator=(optional<U> const& v) {
			assign(v);
			return *this;
		}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR optional& operator=(optional<U>&& v) {
			assign(sprout::forward<optional<U> >(v));
			return *this;
		}

		template<
			typename... Args,
			typename = typename std::enable_if<is_constructible_args<Args...>::value>::type
		>
		SPROUT_CXX14_CONSTEXPR void emplace(Args&&... args) {
			optional temp(sprout::in_place, sprout::forward<Args>(args)...);
			temp.swap(*this);
		}
		template<
			typename U, typename... Args,
			typename = typename std::enable_if<is_constructible_args<std::initializer_list<U>&, Args...>::value>::type
		>
		SPROUT_CXX14_CONSTEXPR void emplace(std::initializer_list<U> il, Args&&... args) {
			optional temp(sprout::in_place, il, sprout::forward<Args>(args)...);
			temp.swap(*this);
		}

		SPROUT_CXX14_CONSTEXPR void assign(sprout::nullopt_t) SPROUT_NOEXCEPT {
			destroy();
		}
		SPROUT_CXX14_CONSTEXPR void assign(optional const& v) {
			optional temp(v);
			temp.swap(*this);
		}
		SPROUT_CXX14_CONSTEXPR void assign(optional&& v)
		SPROUT_NOEXCEPT_EXPR(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value)
		{
			optional temp(sprout::forward<optional>(v));
			temp.swap(*this);
		}
		template<
			typename U,
//			typename = typename std::enable_if<std::is_constructible<T, U>::value && std::is_assignable<U, T>::value>::type
			typename = typename std::enable_if<std::is_constructible<T, U&&>::value>::type
		>
		SPROUT_CXX14_CONSTEXPR void assign(U&& v) {
			optional temp(sprout::forward<U>(v));
			temp.swap(*this);
		}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR void assign(optional<U> const& v) {
			optional temp(v);
			temp.swap(*this);
		}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR void assign(optional<U>&& v) {
			optional temp(sprout::forward<optional<U> >(v));
			temp.swap(*this);
		}

		SPROUT_CXX14_CONSTEXPR void reset() SPROUT_NOEXCEPT {
			destroy();
		}
		SPROUT_CXX14_CONSTEXPR void reset(sprout::nullopt_t v) SPROUT_NOEXCEPT {
			assign(v);
		}
		template<
			typename U,
//			typename = typename std::enable_if<std::is_constructible<T, U>::value && std::is_assignable<U, T>::value>::type
			typename = typename std::enable_if<std::is_constructible<T, U&&>::value>::type
		>
		SPROUT_CXX14_CONSTEXPR void reset(U&& v) {
			assign(sprout::forward<U>(v));
		}
		// 20.6.4.4, swap
		SPROUT_CXX14_CONSTEXPR void swap(optional& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(val, other.val)))
		{
			sprout::swap(init, other.init);
			sprout::swap(val, other.val);
		}
		// 20.6.4.5, observers
		SPROUT_CONSTEXPR pointer_const_type operator->() const {
			return SPROUT_ASSERT(is_initialized()),
				val.get_pointer()
				;
		}
		SPROUT_CXX14_CONSTEXPR pointer_type operator->() {
			return SPROUT_ASSERT(is_initialized()),
				val.get_pointer()
				;
		}
		SPROUT_CONSTEXPR pointer_const_type get_pointer() const {
			return is_initialized() ? val.get_pointer()
				: 0
				;
		}
		SPROUT_CXX14_CONSTEXPR pointer_type get_pointer() {
			return is_initialized() ? val.get_pointer()
				: 0
				;
		}
		SPROUT_CONSTEXPR pointer_const_type get_ptr() const {
			return get_pointer();
		}
		SPROUT_CXX14_CONSTEXPR pointer_type get_ptr() {
			return get_pointer();
		}

		SPROUT_CONSTEXPR reference_const_type operator*() const {
			return (SPROUT_ASSERT(is_initialized()), true) ? val.get()
				: val.get()
				;
		}
		SPROUT_CXX14_CONSTEXPR reference_type operator*() {
			return (SPROUT_ASSERT(is_initialized()), true) ? val.get()
				: val.get()
				;
		}
		SPROUT_CONSTEXPR reference_const_type value() const {
			return get();
		}
		SPROUT_CXX14_CONSTEXPR reference_type value() {
			return get();
		}
		SPROUT_CONSTEXPR reference_const_type get() const {
			return is_initialized() ? val.get()
				: (throw sprout::bad_optional_access("optional<>: bad optional access"), val.get())
				;
		}
		SPROUT_CXX14_CONSTEXPR reference_type get() {
			return is_initialized() ? val.get()
				: (throw sprout::bad_optional_access("optional<>: bad optional access"), val.get())
				;
		}

		SPROUT_CONSTEXPR reference_const_type value_or(reference_const_type& v) const {
			return get_value_or(v);
		}
		SPROUT_CXX14_CONSTEXPR reference_type value_or(reference_type& v) {
			return get_value_or(v);
		}
		SPROUT_CONSTEXPR reference_const_type get_value_or(reference_const_type& v) const {
			return is_initialized() ? val.get()
				: v
				;
		}
		SPROUT_CXX14_CONSTEXPR reference_type get_value_or(reference_type& v) {
			return is_initialized() ? val.get()
				: v
				;
		}

		SPROUT_EXPLICIT_CONVERSION SPROUT_CONSTEXPR operator bool() const SPROUT_NOEXCEPT {
			return is_initialized();
		}
		SPROUT_CONSTEXPR bool operator!() const SPROUT_NOEXCEPT {
			return !is_initialized();
		}
		SPROUT_CONSTEXPR bool is_initialized() const SPROUT_NOEXCEPT {
			return init;
		}
	};

	//
	// swap
	//
	template<typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::optional<T>& lhs, sprout::optional<T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_OPTIONAL_HPP
