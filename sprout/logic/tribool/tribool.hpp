/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_LOGIC_TRIBOOL_TRIBOOL_HPP
#define SPROUT_LOGIC_TRIBOOL_TRIBOOL_HPP

#include <sprout/config.hpp>
#include <sprout/logic/tribool/tribool_fwd.hpp>

namespace sprout {
	namespace logic {
		namespace detail {
			struct indeterminate_t {};
		}	// namespace detail

		//
		// indeterminate_keyword_t
		//
		typedef bool (*indeterminate_keyword_t)(sprout::logic::tribool, sprout::logic::detail::indeterminate_t);

		//
		// tribool
		//
		class tribool {
		private:
			struct dummy {
			public:
				SPROUT_CXX14_CONSTEXPR void nonnull() {}
			};
			typedef void (dummy::*safe_bool)();
		public:
			enum value_t {
				false_value,
				true_value,
				indeterminate_value
			};
		public:
			value_t value;
		public:
			SPROUT_CONSTEXPR tribool()
				: value(false_value)
			{}
			SPROUT_CONSTEXPR tribool(bool initial_value)
				: value(initial_value? true_value : false_value)
			{}
			SPROUT_CONSTEXPR tribool(sprout::logic::indeterminate_keyword_t)
				: value(indeterminate_value)
			{}
			SPROUT_CONSTEXPR operator safe_bool() const {
				return value == true_value ? &dummy::nonnull : 0;
			}
		};

		//
		// indeterminate
		//
		inline SPROUT_CONSTEXPR bool
		indeterminate(sprout::logic::tribool x, sprout::logic::detail::indeterminate_t = sprout::logic::detail::indeterminate_t()) {
			return x.value == sprout::logic::tribool::indeterminate_value;
		}

		//
		// operator!
		//
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator!(sprout::logic::tribool x) {
			return x.value == sprout::logic::tribool::false_value ? sprout::logic::tribool(true)
				: x.value == sprout::logic::tribool::true_value ? sprout::logic::tribool(false)
				: sprout::logic::tribool(sprout::logic::indeterminate)
				;
		}

		//
		// operator&&
		//
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator&&(sprout::logic::tribool lhs, sprout::logic::tribool rhs) {
			return static_cast<bool>(!lhs) || static_cast<bool>(!rhs) ? sprout::logic::tribool(false)
				: static_cast<bool>(lhs) && static_cast<bool>(rhs) ? sprout::logic::tribool(true)
				: sprout::logic::tribool(sprout::logic::indeterminate)
				;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator&&(tribool lhs, bool rhs) {
			return rhs ? lhs : sprout::logic::tribool(false);
		}

		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator&&(bool lhs, sprout::logic::tribool rhs) {
			return lhs ? rhs : sprout::logic::tribool(false);
		}

		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator&&(sprout::logic::indeterminate_keyword_t, sprout::logic::tribool lhs) {
			return !lhs ? sprout::logic::tribool(false) : sprout::logic::tribool(sprout::logic::indeterminate);
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator&&(sprout::logic::tribool lhs, sprout::logic::indeterminate_keyword_t) {
			return !lhs ? sprout::logic::tribool(false) : sprout::logic::tribool(indeterminate);
		}

		//
		// operator||
		//
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator||(sprout::logic::tribool lhs, sprout::logic::tribool rhs) {
			return static_cast<bool>(!lhs) && static_cast<bool>(!rhs) ? sprout::logic::tribool(false)
				: static_cast<bool>(lhs) || static_cast<bool>(rhs) ? sprout::logic::tribool(true)
				: sprout::logic::tribool(sprout::logic::indeterminate)
				;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator||(sprout::logic::tribool lhs, bool rhs) {
			return rhs ? sprout::logic::tribool(true) : lhs;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator||(bool lhs, sprout::logic::tribool rhs) {
			return lhs ? sprout::logic::tribool(true) : rhs;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator||(sprout::logic::indeterminate_keyword_t, sprout::logic::tribool lhs) {
			return lhs ? sprout::logic::tribool(true) : sprout::logic::tribool(sprout::logic::indeterminate);
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator||(sprout::logic::tribool lhs, sprout::logic::indeterminate_keyword_t) {
			return lhs ? sprout::logic::tribool(true) : sprout::logic::tribool(sprout::logic::indeterminate);
		}

		//
		// operator==
		//
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator==(sprout::logic::tribool lhs, sprout::logic::tribool rhs) {
			return sprout::logic::indeterminate(lhs) || sprout::logic::indeterminate(rhs)
				? sprout::logic::tribool(sprout::logic::indeterminate)
				: (lhs && rhs) || (!lhs && !rhs)
				;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator==(sprout::logic::tribool lhs, bool rhs) {
			return lhs == sprout::logic::tribool(rhs);
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator==(bool lhs, sprout::logic::tribool rhs) {
			return sprout::logic::tribool(lhs) == rhs;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator==(sprout::logic::indeterminate_keyword_t, sprout::logic::tribool lhs) {
			return sprout::logic::tribool(sprout::logic::indeterminate) == lhs;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator==(sprout::logic::tribool lhs, sprout::logic::indeterminate_keyword_t) {
			return sprout::logic::tribool(sprout::logic::indeterminate) == lhs;
		}

		//
		// operator!=
		//
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator!=(sprout::logic::tribool lhs, sprout::logic::tribool rhs) {
			return sprout::logic::indeterminate(lhs) || sprout::logic::indeterminate(rhs)
				? sprout::logic::tribool(sprout::logic::indeterminate)
				: !((lhs && rhs) || (!lhs && !rhs))
				;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator!=(sprout::logic::tribool lhs, bool rhs) {
			return lhs != sprout::logic::tribool(rhs);
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator!=(bool lhs, sprout::logic::tribool rhs) {
			return sprout::logic::tribool(lhs) != rhs;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator!=(sprout::logic::indeterminate_keyword_t, sprout::logic::tribool lhs) {
			return sprout::logic::tribool(sprout::logic::indeterminate) != lhs;
		}
		inline SPROUT_CONSTEXPR sprout::logic::tribool
		operator!=(sprout::logic::tribool lhs, sprout::logic::indeterminate_keyword_t) {
			return sprout::logic::tribool(sprout::logic::indeterminate) != lhs;
		}
	}	// namespace logic

	using sprout::logic::tribool;
	using sprout::logic::indeterminate;
}	// namespace sprout

#define SPROUT_TRIBOOL_THIRD_STATE(NAME) \
	inline SPROUT_CONSTEXPR bool \
	NAME(sprout::logic::tribool lhs, sprout::logic::detail::indeterminate_t = sprout::logic::detail::indeterminate_t()) { \
		return lhs.value == sprout::logic::tribool::indeterminate_value; \
	}

#endif	// #ifndef SPROUT_LOGIC_TRIBOOL_TRIBOOL_HPP
