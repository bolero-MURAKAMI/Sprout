/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_EXEMPT_PTR_HPP
#define SPROUT_EXEMPT_PTR_HPP

#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/functional/hash.hpp>

namespace sprout {
	//
	// exempt_ptr
	//
	template<typename T>
	class exempt_ptr {
	public:
		typedef T value_type;
		typedef T element_type;
		typedef T* pointer;
		typedef T const* const_pointer;
		typedef T& reference;
		typedef T const& const_reference;
		typedef std::ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	private:
		pointer p_;
	private:
		template<typename P>
		static SPROUT_CONSTEXPR bool is_compat() {
			return std::is_convertible<P*, pointer>::value;
		}
	public:
		SPROUT_CONSTEXPR exempt_ptr() SPROUT_NOEXCEPT
			: p_()
		{}
		SPROUT_CONSTEXPR exempt_ptr(std::nullptr_t) SPROUT_NOEXCEPT
			: exempt_ptr()
		{}
		explicit SPROUT_CONSTEXPR exempt_ptr(pointer other) SPROUT_NOEXCEPT
			: p_(other)
		{}
		template<
			typename U,
			typename sprout::enabler_if<std::is_convertible<U*, pointer>::value>::type = sprout::enabler
		>
		explicit SPROUT_CONSTEXPR exempt_ptr(U* other) SPROUT_NOEXCEPT
			: p_(other)
		{}
		template<
			typename U,
			typename sprout::enabler_if<std::is_convertible<U*, pointer>::value>::type = sprout::enabler
		>
		SPROUT_CONSTEXPR exempt_ptr(sprout::exempt_ptr<U> const& other) SPROUT_NOEXCEPT
			: p_(other.get())
		{}
		SPROUT_CXX14_CONSTEXPR exempt_ptr&
		operator=(std::nullptr_t) SPROUT_NOEXCEPT {
			reset();
			return *this;
		}
		template<
			typename U,
			typename sprout::enabler_if<std::is_convertible<U*, pointer>::value>::type = sprout::enabler
		>
		SPROUT_CXX14_CONSTEXPR exempt_ptr&
		operator=(U* other) SPROUT_NOEXCEPT {
			reset(other);
			return *this;
		}
		template<
			typename U,
			typename sprout::enabler_if<std::is_convertible<U*, pointer>::value>::type = sprout::enabler
		>
		SPROUT_CXX14_CONSTEXPR exempt_ptr&
		operator=(exempt_ptr<U> const& other) SPROUT_NOEXCEPT {
			reset(other.get());
			return *this;
		}
		SPROUT_CONSTEXPR pointer
		get() const SPROUT_NOEXCEPT {
			return p_;
		}
		SPROUT_CONSTEXPR reference
		operator*() const SPROUT_NOEXCEPT {
			return *get();
		}
		SPROUT_CONSTEXPR pointer
		operator->() const SPROUT_NOEXCEPT {
			return get();
		}
		SPROUT_EXPLICIT_CONVERSION SPROUT_CONSTEXPR operator bool() const SPROUT_NOEXCEPT {
			return get();
		}
		SPROUT_CONSTEXPR operator pointer() SPROUT_NOEXCEPT {
			return get();
		}
		SPROUT_CONSTEXPR operator const_pointer() const SPROUT_NOEXCEPT {
			return get();
		}
		SPROUT_CXX14_CONSTEXPR pointer
		release() SPROUT_NOEXCEPT {
			pointer old = get();
			reset();
			return old;
		}
		SPROUT_CXX14_CONSTEXPR void
		reset(pointer t = 0) SPROUT_NOEXCEPT {
			p_ = t;
		}
		SPROUT_CXX14_CONSTEXPR void
		swap(exempt_ptr& other) SPROUT_NOEXCEPT {
			swap(p_, other.p_);
		}
		SPROUT_CXX14_CONSTEXPR exempt_ptr&
		operator++() {
			++p_;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR exempt_ptr&
		operator--() {
			--p_;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR exempt_ptr operator++(int) {
			pointer tmp = p_; ++p_; return exempt_ptr{tmp};
		}
		SPROUT_CXX14_CONSTEXPR exempt_ptr operator--(int) {
			pointer tmp = p_; --p_; return exempt_ptr{tmp};
		}
		SPROUT_CXX14_CONSTEXPR exempt_ptr
		operator+() const {
			return *this; }
		SPROUT_CXX14_CONSTEXPR exempt_ptr
		operator+(std::ptrdiff_t d) const {
			return exempt_ptr{p_+d};
		}
		SPROUT_CXX14_CONSTEXPR exempt_ptr
		operator-(std::ptrdiff_t d) const {
			return exempt_ptr{p_-d};
		}
		SPROUT_CXX14_CONSTEXPR value_type&
		operator[](std::ptrdiff_t k) {
			return p_[k];
		}
		SPROUT_CXX14_CONSTEXPR value_type const&
		operator[](std::ptrdiff_t k) const {
			return p_[k];
		}
	};
	//
	// swap
	//
	template<typename T>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::exempt_ptr<T>& x, sprout::exempt_ptr<T>& y) SPROUT_NOEXCEPT {
		x.swap(y);
	}
	//
	// make_exempt
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::exempt_ptr<T>
	make_exempt(T* p) SPROUT_NOEXCEPT {
		return sprout::exempt_ptr<T>(p);
	}
	//
	// operator==
	// operator!=
	//
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::exempt_ptr<T> const& x, sprout::exempt_ptr<U> const& y) SPROUT_NOEXCEPT {
		return x.get() == y.get();
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::exempt_ptr<T> const& x, sprout::exempt_ptr<U> const& y) SPROUT_NOEXCEPT {
		return !(x == y);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::exempt_ptr<T> const& x, std::nullptr_t y) SPROUT_NOEXCEPT {
		return x.get() == y;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::exempt_ptr<T> const& x, std::nullptr_t y) SPROUT_NOEXCEPT {
		return !(x == y);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator==(std::nullptr_t x, sprout::exempt_ptr<T> const& y) SPROUT_NOEXCEPT {
		return x == y.get();
	}
	template<typename T>
	inline SPROUT_CONSTEXPR bool
	operator!=(std::nullptr_t x, sprout::exempt_ptr<T> const& y) SPROUT_NOEXCEPT {
		return !(x == y);
	}
	//
	// operator<
	// operator>
	// operator=<
	// operator=>
	//
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::exempt_ptr<T> const& x, sprout::exempt_ptr<U> const& y) {
		return x.get() < y.get();
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::exempt_ptr<T> const& x, sprout::exempt_ptr<U> const& y) {
		return y < x;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::exempt_ptr<T> const& x, sprout::exempt_ptr<U> const& y) {
		return !(y < x);
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::exempt_ptr<T> const& x, sprout::exempt_ptr<U> const& y) {
		return !(x < y);
	}
	//
	// operator+
	// operator-
	//
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::exempt_ptr<T>
	operator+(std::ptrdiff_t d, sprout::exempt_ptr<T> const& p) {
		return p + d;
	}
	template<typename T>
	inline SPROUT_CONSTEXPR std::ptrdiff_t
	operator-(sprout::exempt_ptr<T> const& x, sprout::exempt_ptr<T> const& y) {
		return x.get() - y.get();
	}
}	// namespace sprout

namespace sprout {
	//
	// hash_value
	//
	template<typename T>
	inline SPROUT_CONSTEXPR std::size_t
	hash_value(sprout::exempt_ptr<T> const& v) {
		return sprout::hash_value(v.get());
	}
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// hash
	//
	template<typename T>
	struct hash<sprout::exempt_ptr<T> >
		: public sprout::hash<sprout::exempt_ptr<T> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_EXEMPT_PTR_HPP
