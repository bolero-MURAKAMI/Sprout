/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_COMPARISON_HPP
#define SPROUT_UTILITY_COMPARISON_HPP

#include <sprout/config.hpp>
#include <sprout/utility/value_holder.hpp>

namespace sprout {
	//
	// comparison_forwarder
	//
	template<typename Compare = void>
	class comparison_forwarder {
	public:
		typedef Compare compare_type;
	private:
		sprout::value_holder<compare_type const&> comp_;
	public:
		explicit SPROUT_CONSTEXPR comparison_forwarder(compare_type const& comp)
			: comp_(comp)
		{}
		SPROUT_CONSTEXPR compare_type const& comp() const {
			return comp_;
		}
	};
	template<>
	class comparison_forwarder<void> {};
	//
	// operator->*
	//
	template<typename Compare>
	inline SPROUT_CONSTEXPR sprout::comparison_forwarder<Compare>
	operator->*(sprout::comparison_forwarder<>, Compare const& comp) {
		return sprout::comparison_forwarder<Compare>(comp);
	}

	//
	// comp
	//
	namespace {
		SPROUT_STATIC_CONSTEXPR sprout::comparison_forwarder<> comp = {};
	}	// anonymous-namespace

	//
	// comparison_holder
	//
	template<typename T, typename Compare = void>
	class comparison_holder {
	public:
		typedef T value_type;
		typedef Compare compare_type;
	private:
		sprout::value_holder<value_type const&> value_;
		sprout::value_holder<compare_type const&> comp_;
	public:
		SPROUT_CONSTEXPR comparison_holder(value_type const& value, compare_type const& comp)
			: value_(value), comp_(comp)
		{}
		SPROUT_CONSTEXPR value_type const& get() const {
			return value_;
		}
		SPROUT_CONSTEXPR compare_type const& comp() const {
			return comp_;
		}
	};
	template<typename T>
	class comparison_holder<T, void> {
	public:
		typedef T value_type;
	private:
		sprout::value_holder<value_type const&> value_;
	public:
		explicit SPROUT_CONSTEXPR comparison_holder(value_type const& value)
			: value_(value)
		{}
		SPROUT_CONSTEXPR value_type const& get() const {
			return value_;
		}
	};

	//
	// operator%
	//
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::comparison_holder<T, Compare>
	operator%(sprout::comparison_forwarder<Compare> const& lhs, T const& rhs) {
		return sprout::comparison_holder<T, Compare>(rhs, lhs.comp());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::comparison_holder<T>
	operator%(sprout::comparison_forwarder<>, T const& rhs) {
		return sprout::comparison_holder<T>(rhs);
	}

	//
	// comparison_base
	//
	template<typename T, typename Compare = void>
	class comparison_base {
	public:
		typedef T value_type;
		typedef Compare compare_type;
	private:
		sprout::value_holder<value_type const&> value_;
		sprout::value_holder<compare_type const&> comp_;
		bool cond_;
	public:
		SPROUT_CONSTEXPR comparison_base() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		comparison_base(comparison_base const&) = default;
		SPROUT_CONSTEXPR comparison_base(value_type const& value, compare_type const& comp)
			: value_(value), comp_(comp), cond_(true)
		{}
		SPROUT_CONSTEXPR value_type const& get() const {
			return value_;
		}
		SPROUT_CONSTEXPR compare_type const& comp() const {
			return comp_;
		}
		SPROUT_CONSTEXPR operator bool() const {
			return cond_;
		}
		SPROUT_CONSTEXPR bool operator!() const {
			return !cond_;
		}
	};
	template<typename T>
	class comparison_base<T, void> {
	public:
		typedef T value_type;
	private:
		sprout::value_holder<value_type const&> value_;
		bool cond_;
	public:
		SPROUT_CONSTEXPR comparison_base() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		comparison_base(comparison_base const&) = default;
		explicit SPROUT_CONSTEXPR comparison_base(value_type const& value)
			: value_(value), cond_(true)
		{}
		SPROUT_CONSTEXPR value_type const& get() const {
			return value_;
		}
		SPROUT_CONSTEXPR operator bool() const {
			return cond_;
		}
		SPROUT_CONSTEXPR bool operator!() const {
			return !cond_;
		}
	};

	//
	// less_comparison
	//
	template<typename T, typename Compare = void>
	class less_comparison
		: public sprout::comparison_base<T, Compare>
	{
	public:
		typedef sprout::comparison_base<T, Compare> base_type;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::compare_type compare_type;
	public:
		SPROUT_CONSTEXPR less_comparison() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		less_comparison(less_comparison const&) = default;
		SPROUT_CONSTEXPR less_comparison(value_type const& value, compare_type const& comp)
			: base_type(value, comp)
		{}
	};
	template<typename T>
	class less_comparison<T, void>
		: public sprout::comparison_base<T>
	{
	public:
		typedef sprout::comparison_base<T> base_type;
		typedef typename base_type::value_type value_type;
	public:
		SPROUT_CONSTEXPR less_comparison() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		less_comparison(less_comparison const&) = default;
		explicit SPROUT_CONSTEXPR less_comparison(value_type const& value)
			: base_type(value)
		{}
	};
	//
	// operator<
	// operator<=
	//
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::less_comparison<T, Compare>
	operator<(sprout::comparison_forwarder<Compare> const& lhs, T const& rhs) {
		return sprout::less_comparison<T, Compare>(rhs, lhs.comp());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::less_comparison<T>
	operator<(sprout::comparison_forwarder<>, T const& rhs) {
		return sprout::less_comparison<T>(rhs);
	}
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::less_comparison<T, Compare>
	operator<=(sprout::comparison_forwarder<Compare> const& lhs, T const& rhs) {
		return sprout::less_comparison<T, Compare>(rhs, lhs.comp());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::less_comparison<T>
	operator<=(sprout::comparison_forwarder<>, T const& rhs) {
		return sprout::less_comparison<T>(rhs);
	}
	//
	// operator<
	//
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U, Compare>
	operator<(sprout::comparison_holder<T, Compare> const& lhs, U const& rhs) {
		return lhs.comp()(lhs.get(), rhs) ? sprout::less_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::less_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U>
	operator<(sprout::comparison_holder<T> const& lhs, U const& rhs) {
		return lhs.get() < rhs ? sprout::less_comparison<U>(rhs)
			: sprout::less_comparison<U>()
			;
	}
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U, Compare>
	operator<(sprout::less_comparison<T, Compare> const& lhs, U const& rhs) {
		return lhs.comp()(lhs.get(), rhs) ? sprout::less_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::less_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U>
	operator<(sprout::less_comparison<T> const& lhs, U const& rhs) {
		return lhs && lhs.get() < rhs ? sprout::less_comparison<U>(rhs)
			: sprout::less_comparison<U>()
			;
	}
	//
	// operator<=
	//
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U, Compare>
	operator<=(sprout::comparison_holder<T, Compare> const& lhs, U const& rhs) {
		return !lhs.comp()(rhs, lhs.get()) ? sprout::less_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::less_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U>
	operator<=(sprout::comparison_holder<T> const& lhs, U const& rhs) {
		return lhs.get() <= rhs ? sprout::less_comparison<U>(rhs)
			: sprout::less_comparison<U>()
			;
	}
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U, Compare>
	operator<=(sprout::less_comparison<T, Compare> const& lhs, U const& rhs) {
		return !lhs.comp()(rhs, lhs.get()) ? sprout::less_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::less_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::less_comparison<U>
	operator<=(sprout::less_comparison<T> const& lhs, U const& rhs) {
		return lhs && lhs.get() <= rhs ? sprout::less_comparison<U>(rhs)
			: sprout::less_comparison<U>()
			;
	}
	//
	// operator>
	// operator>=
	// operator==
	// operator!=
	//
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator>(sprout::less_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator>=(sprout::less_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator==(sprout::less_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator!=(sprout::less_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL

	//
	// greater_comparison
	//
	template<typename T, typename Compare = void>
	class greater_comparison
		: public sprout::comparison_base<T, Compare>
	{
	public:
		typedef sprout::comparison_base<T, Compare> base_type;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::compare_type compare_type;
	public:
		SPROUT_CONSTEXPR greater_comparison() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		greater_comparison(greater_comparison const&) = default;
		SPROUT_CONSTEXPR greater_comparison(value_type const& value, compare_type const& comp)
			: base_type(value, comp)
		{}
	};
	template<typename T>
	class greater_comparison<T, void>
		: public sprout::comparison_base<T>
	{
	public:
		typedef sprout::comparison_base<T> base_type;
		typedef typename base_type::value_type value_type;
	public:
		SPROUT_CONSTEXPR greater_comparison() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		greater_comparison(greater_comparison const&) = default;
		explicit SPROUT_CONSTEXPR greater_comparison(value_type const& value)
			: base_type(value)
		{}
	};
	//
	// operator>
	// operator>=
	//
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<T, Compare>
	operator>(sprout::comparison_forwarder<Compare> const& lhs, T const& rhs) {
		return sprout::greater_comparison<T>(rhs, lhs.comp());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<T>
	operator>(sprout::comparison_forwarder<>, T const& rhs) {
		return sprout::greater_comparison<T>(rhs);
	}
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<T, Compare>
	operator>=(sprout::comparison_forwarder<Compare> const& lhs, T const& rhs) {
		return sprout::greater_comparison<T>(rhs, lhs.comp());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<T>
	operator>=(sprout::comparison_forwarder<>, T const& rhs) {
		return sprout::greater_comparison<T>(rhs);
	}
	//
	// operator>
	//
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U, Compare>
	operator>(sprout::comparison_holder<T, Compare> const& lhs, U const& rhs) {
		return lhs.comp()(rhs, lhs.get()) ? sprout::greater_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::greater_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U>
	operator>(sprout::comparison_holder<T> const& lhs, U const& rhs) {
		return rhs < lhs.get() ? sprout::greater_comparison<U>(rhs)
			: sprout::greater_comparison<U>()
			;
	}
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U, Compare>
	operator>(sprout::greater_comparison<T, Compare> const& lhs, U const& rhs) {
		return lhs.comp()(rhs, lhs.get()) ? sprout::greater_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::greater_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U>
	operator>(sprout::greater_comparison<T> const& lhs, U const& rhs) {
		return lhs && rhs < lhs.get() ? sprout::greater_comparison<U>(rhs)
			: sprout::greater_comparison<U>()
			;
	}
	//
	// operator>=
	//
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U, Compare>
	operator>=(sprout::comparison_holder<T, Compare> const& lhs, U const& rhs) {
		return !lhs.comp()(lhs.get(), rhs) ? sprout::greater_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::greater_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U>
	operator>=(sprout::comparison_holder<T> const& lhs, U const& rhs) {
		return !(lhs.get() < rhs) ? sprout::greater_comparison<U>(rhs)
			: sprout::greater_comparison<U>()
			;
	}
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U, Compare>
	operator>=(sprout::greater_comparison<T, Compare> const& lhs, U const& rhs) {
		return !lhs.comp()(lhs.get(), rhs) ? sprout::greater_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::greater_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::greater_comparison<U>
	operator>=(sprout::greater_comparison<T> const& lhs, U const& rhs) {
		return lhs && !(lhs.get() < rhs) ? sprout::greater_comparison<U>(rhs)
			: sprout::greater_comparison<U>()
			;
	}
	//
	// operator<
	// operator<=
	// operator==
	// operator!=
	//
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator<(sprout::greater_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator<=(sprout::greater_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator==(sprout::greater_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator!=(sprout::greater_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL

	//
	// equal_comparison
	//
	template<typename T, typename Compare = void>
	class equal_comparison
		: public sprout::comparison_base<T, Compare>
	{
	public:
		typedef sprout::comparison_base<T, Compare> base_type;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::compare_type compare_type;
	public:
		SPROUT_CONSTEXPR equal_comparison() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		equal_comparison(equal_comparison const&) = default;
		SPROUT_CONSTEXPR equal_comparison(value_type const& value, compare_type const& comp)
			: base_type(value, comp)
		{}
	};
	template<typename T>
	class equal_comparison<T, void>
		: public sprout::comparison_base<T>
	{
	public:
		typedef sprout::comparison_base<T> base_type;
		typedef typename base_type::value_type value_type;
	public:
		SPROUT_CONSTEXPR equal_comparison() SPROUT_DEFAULTED_DEFAULT_CONSTRUCTOR_DECL
		equal_comparison(equal_comparison const&) = default;
		explicit SPROUT_CONSTEXPR equal_comparison(value_type const& value)
			: base_type(value)
		{}
	};
	//
	// operator==
	//
	template<typename T, typename Compare>
	inline SPROUT_CONSTEXPR sprout::equal_comparison<T, Compare>
	operator==(sprout::comparison_forwarder<Compare> const& lhs, T const& rhs) {
		return sprout::equal_comparison<T>(rhs, lhs.comp());
	}
	template<typename T>
	inline SPROUT_CONSTEXPR sprout::equal_comparison<T>
	operator==(sprout::comparison_forwarder<>, T const& rhs) {
		return sprout::equal_comparison<T>(rhs);
	}
	//
	// operator==
	//
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::equal_comparison<U, Compare>
	operator==(sprout::comparison_holder<T, Compare> const& lhs, U const& rhs) {
		return !lhs.comp()(lhs.get(), rhs) && !lhs.comp()(rhs, lhs.get()) ? sprout::equal_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::equal_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::equal_comparison<U>
	operator==(sprout::comparison_holder<T> const& lhs, U const& rhs) {
		return !(lhs.get() < rhs) && !(rhs < lhs.get()) ? sprout::equal_comparison<U>(rhs)
			: sprout::equal_comparison<U>()
			;
	}
	template<typename T, typename Compare, typename U>
	inline SPROUT_CONSTEXPR sprout::equal_comparison<U, Compare>
	operator==(sprout::equal_comparison<T, Compare> const& lhs, U const& rhs) {
		return !lhs.comp()(lhs.get(), rhs) && !lhs.comp()(rhs, lhs.get()) ? sprout::equal_comparison<U, Compare>(rhs, lhs.comp())
			: sprout::equal_comparison<U, Compare>()
			;
	}
	template<typename T, typename U>
	inline SPROUT_CONSTEXPR sprout::equal_comparison<U>
	operator==(sprout::equal_comparison<T> const& lhs, U const& rhs) {
		return lhs && !(lhs.get() < rhs) && !(rhs < lhs.get()) ? sprout::equal_comparison<U>(rhs)
			: sprout::equal_comparison<U>()
			;
	}
	//
	// operator<
	// operator<=
	// operator>
	// operator>=
	// operator!=
	//
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator<(sprout::equal_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator<=(sprout::equal_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator>(sprout::equal_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator>=(sprout::equal_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
	template<typename T, typename Compare, typename U>
	SPROUT_NON_CONSTEXPR void
	operator!=(sprout::equal_comparison<T, Compare> const&, U const&) SPROUT_DELETED_FUNCTION_DECL
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_COMPARISON_HPP
