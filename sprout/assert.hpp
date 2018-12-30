/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ASEERT_HPP
#define SPROUT_ASEERT_HPP

#if defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG)
#	include <sprout/config.hpp>
#	include <sprout/preprocessor/config.hpp>
#	include <sprout/preprocessor/cat.hpp>
#	include <sprout/preprocessor/variadic/size.hpp>
#elif defined(SPROUT_ENABLE_ASSERT_HANDLER)
#	include <sprout/config.hpp>
#	include <sprout/preprocessor/config.hpp>
#	include <sprout/preprocessor/cat.hpp>
#	include <sprout/preprocessor/variadic/size.hpp>
#else
#	include <cstdlib>
#	include <iostream>
#	include <sprout/config.hpp>
#	include <sprout/preprocessor/config.hpp>
#	include <sprout/preprocessor/cat.hpp>
#	include <sprout/preprocessor/variadic/size.hpp>
#endif
#include <sprout/preprocessor/stringize.hpp>

//
// SPROUT_ASSERTION_FAILED_FORMAT
//
#ifndef SPROUT_ASSERTION_FAILED_FORMAT
#	define SPROUT_ASSERTION_FAILED_FORMAT(expr, file, line) \
		"***** Internal Program Error - assertion (" #expr ") failed: " file "(" SPROUT_PP_STRINGIZE(line) ")"
#endif

//
// SPROUT_ASSERT_MSG
//

#if defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG)

#	define SPROUT_ASSERT_MSG(expr, msg) \
		((void)0)

#elif defined(SPROUT_ENABLE_ASSERT_HANDLER)

namespace sprout {
	//
	// assertion_info_msg
	//
	class assertion_info_msg {
	private:
		char const* expr_;
		char const* msg_;
		char const* function_;
		char const* file_;
		long line_;
	public:
		SPROUT_CONSTEXPR assertion_info_msg(char const* expr, char const* msg, char const* function, char const* file, long line)
			: expr_(expr), msg_(msg), function_(function), file_(file), line_(line)
		{}
		SPROUT_CONSTEXPR char const* expr() const SPROUT_NOEXCEPT {
			return expr_;
		}
		SPROUT_CONSTEXPR char const* msg() const SPROUT_NOEXCEPT {
			return msg_;
		}
		SPROUT_CONSTEXPR char const* function() const SPROUT_NOEXCEPT {
			return function_;
		}
		SPROUT_CONSTEXPR char const* file() const SPROUT_NOEXCEPT {
			return file_;
		}
		SPROUT_CONSTEXPR long line() const SPROUT_NOEXCEPT {
			return line_;
		}
	};

	//
	// assertion_failed_msg_default
	//
	inline SPROUT_NON_CONSTEXPR bool
	assertion_failed_default(sprout::assertion_info_msg const& info) {
		return (std::cerr << "***** Internal Program Error - assertion (" << info.expr() << ") failed: " << info.file() << "(" << info.line() << ")" << ": " << msg << std::endl),
			std::abort(), false
			;
	}

	//
	// assertion_failed_msg
	//	* user defined
	//
	void
	assertion_failed_msg(sprout::assertion_info_msg const&);
}	// namespace sprout

namespace sprout {
	namespace detail {
		inline bool
		assertion_failed_msg(bool cond, char const* formatted, char const* expr, char const* msg, char const* function, char const* file, long line) {
			return cond ? true
				: ((void)sprout::assertion_failed_msg(sprout::assertion_info_msg(expr, msg, function, file, line)), false)
				;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check_msg(bool cond, char const* formatted, char const* expr, char const* msg, char const* function, char const* file, long line) {
			return cond ? true
				: sprout::detail::assertion_failed_msg(cond, formatted, expr, msg, function, file, line)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT_MSG(expr, msg) ( \
		(void)sprout::detail::assertion_check_msg( \
			(expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__), \
			#expr, msg, "(unknown)"/*SPROUT_CURRENT_FUNCTION*/, __FILE__, __LINE__ \
			) \
		)

#else

namespace sprout {
	namespace detail {
		inline SPROUT_NON_CONSTEXPR bool
		assertion_failed_msg(char const* formatted, char const* msg) {
			return (std::cerr << formatted << ": " << msg << std::endl), std::abort(), false;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check_msg(bool cond, char const* formatted, char const* msg) {
			return cond ? true
				: sprout::detail::assertion_failed_msg(formatted, msg)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT_MSG(expr, msg) \
		((void)sprout::detail::assertion_check_msg((expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__), msg))

#endif

//
// SPROUT_ASSERT
//

#if defined(SPROUT_DISABLE_ASSERTS) || defined(NDEBUG)

#	define SPROUT_ASSERT_1(expr) \
		((void)0)

#elif defined(SPROUT_ENABLE_ASSERT_HANDLER)

namespace sprout {
	//
	// assertion_info
	//
	class assertion_info {
	private:
		char const* expr_;
		char const* function_;
		char const* file_;
		long line_;
	public:
		SPROUT_CONSTEXPR assertion_info(char const* expr, char const* function, char const* file, long line)
			: expr_(expr), function_(function), file_(file), line_(line)
		{}
		SPROUT_CONSTEXPR char const* expr() const SPROUT_NOEXCEPT {
			return expr_;
		}
		SPROUT_CONSTEXPR char const* function() const SPROUT_NOEXCEPT {
			return function_;
		}
		SPROUT_CONSTEXPR char const* file() const SPROUT_NOEXCEPT {
			return file_;
		}
		SPROUT_CONSTEXPR long line() const SPROUT_NOEXCEPT {
			return line_;
		}
	};

	//
	// assertion_failed_default
	//
	inline SPROUT_NON_CONSTEXPR bool
	assertion_failed_default(sprout::assertion_info const& info) {
		return (std::cerr << "***** Internal Program Error - assertion (" << info.expr() << ") failed: " << info.file() << "(" << info.line() << ")" << std::endl),
			std::abort(), false
			;
	}

	//
	// assertion_failed
	//	* user defined
	//
	void
	assertion_failed(sprout::assertion_info const&);
}	// namespace sprout

namespace sprout {
	namespace detail {
		inline SPROUT_NON_CONSTEXPR bool
		assertion_failed(bool cond, char const* formatted, char const* expr, char const* function, char const* file, long line) {
			return cond ? true
				: ((void)sprout::assertion_failed(sprout::assertion_info(expr, function, file, line)), false)
				;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check(bool cond, char const* formatted, char const* expr, char const* function, char const* file, long line) {
			return cond ? true
				: sprout::detail::assertion_failed(cond, formatted, expr, function, file, line)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT_1(expr) \
		(void)sprout::detail::assertion_check( \
			(expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__), \
			#expr, "(unknown)"/*SPROUT_CURRENT_FUNCTION*/, __FILE__, __LINE__ \
			) \
		)

#else

namespace sprout {
	namespace detail {
		inline SPROUT_NON_CONSTEXPR bool
		assertion_failed(char const* formatted) {
			return (std::cerr << formatted << std::endl), std::abort(), false;
		}
		inline SPROUT_CONSTEXPR bool
		assertion_check(bool cond, char const* formatted) {
			return cond ? true
				: sprout::detail::assertion_failed(formatted)
				;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_ASSERT_1(expr) \
		((void)sprout::detail::assertion_check((expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__)))

#endif

#if SPROUT_PP_VARIADICS
#	define SPROUT_ASSERT_2(expr, msg) \
		SPROUT_ASSERT_MSG(expr, msg)
#	define SPROUT_ASSERT(...) \
		SPROUT_PP_CAT(SPROUT_ASSERT_, SPROUT_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)
#else
#	define SPROUT_ASSERT(expr) \
		SPROUT_ASSERT_1(expr)
#endif

//
// SPROUT_VERIFY
//

#if defined(SPROUT_DISABLE_ASSERTS) || (!defined(SPROUT_ENABLE_ASSERT_HANDLER) && defined(NDEBUG))

namespace sprout {
	namespace detail {
		inline SPROUT_CONSTEXPR bool
		verification_disabled(bool) SPROUT_NOEXCEPT {
			return true;
		}
	}	// namespace detail
}	// namespace sprout

#	define SPROUT_VERIFY(expr) \
		((void)(sprout::detail::verification_disabled((expr))))

#else

#	define SPROUT_VERIFY(expr) \
		SPROUT_ASSERT(expr)

#endif

#endif	// #ifndef SPROUT_ASEERT_HPP
