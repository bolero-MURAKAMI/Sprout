/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_TRACE_HPP
#define TESTSPR_TRACE_HPP

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <vector>
#include <utility>
#include <string>
#include <typeinfo>
#include <iostream>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/preprocessor/stringize.hpp>
#include <sprout/current_function.hpp>
#include <sprout/assert.hpp>
#include <testspr/singleton.hpp>
#include <testspr/typeinfo.hpp>
#include <testspr/print.hpp>

namespace testspr {
	//
	// trace_info
	//
	class trace_info {
	private:
		std::string file_;
		long line_;
		std::string tag_;
		std::string what_;
	public:
		SPROUT_NON_CONSTEXPR trace_info(std::string const& file, long line)
			: file_(file), line_(line), tag_("(unknown)"), what_("(unknown)")
		{}
		SPROUT_NON_CONSTEXPR trace_info(std::string const& file, long line, std::string const& tag)
			: file_(file), line_(line), tag_(tag), what_("(unknown)")
		SPROUT_NON_CONSTEXPR {}
		trace_info(std::string const& file, long line, std::string const& tag, std::string const& what)
			: file_(file), line_(line), tag_(tag), what_(what)
		{}
		SPROUT_NON_CONSTEXPR std::string const& file() const {
			return file_;
		}
		SPROUT_NON_CONSTEXPR long line() const {
			return line_;
		}
		SPROUT_NON_CONSTEXPR std::string const& tag() const {
			return tag_;
		}
		SPROUT_NON_CONSTEXPR std::string const& what() const {
			return what_;
		}
	};

	//
	// trace_record
	//
	class trace_record
		: public testspr::singleton<testspr::trace_record>
	{
	private:
		typedef testspr::singleton<testspr::trace_record> self_type;
	public:
		typedef std::vector<std::pair<std::string, testspr::trace_info> > container_type;
		typedef container_type::size_type size_type;
		typedef container_type::value_type value_type;
		typedef container_type::reference reference;
		typedef container_type::const_reference const_reference;
		typedef container_type::iterator iterator;
		typedef container_type::const_iterator const_iterator;
	public:
		static inline SPROUT_NON_CONSTEXPR trace_record& instance() {
			return get_mutable_instance();
		}
	private:
		container_type info_;
	public:
		SPROUT_NON_CONSTEXPR void push(std::string const& command, testspr::trace_info const& info) {
			info_.emplace_back(command, info);
		}
		SPROUT_NON_CONSTEXPR void pop() {
			info_.pop_back();
		}
		SPROUT_NON_CONSTEXPR reference top() {
			return info_.back();
		}
		SPROUT_NON_CONSTEXPR const_reference top() const {
			return info_.back();
		}
		SPROUT_NON_CONSTEXPR size_type size() const {
			return info_.size();
		}
		SPROUT_NON_CONSTEXPR iterator begin() {
			return info_.begin();
		}
		SPROUT_NON_CONSTEXPR iterator end() {
			return info_.end();
		}
		SPROUT_NON_CONSTEXPR const_iterator begin() const {
			return info_.begin();
		}
		SPROUT_NON_CONSTEXPR const_iterator end() const {
			return info_.end();
		}
		SPROUT_NON_CONSTEXPR const_iterator cbegin() const {
			return info_.cbegin();
		}
		SPROUT_NON_CONSTEXPR const_iterator cend() const {
			return info_.cend();
		}
		SPROUT_NON_CONSTEXPR void clear() {
			info_.clear();
		}
		template<typename OutputIterator>
		SPROUT_NON_CONSTEXPR void copy(OutputIterator out) const {
			std::copy(begin(), end(), out);
		}
		SPROUT_NON_CONSTEXPR void print() const {
			testspr::print_ln("trace-record current: size:", size(), ":");
			for (const_iterator it = cbegin(), last = cend(); it != last; ++it) {
				testspr::print_ln("  ", it->first, " - ", it->second.file(), ":", it->second.line(), ": ", it->second.tag(), ": ", it->second.what());
			}
		}
	};

	//
	// trace_stack
	//
	class trace_stack
		: public testspr::singleton<testspr::trace_stack>
	{
	private:
		typedef testspr::singleton<testspr::trace_stack> self_type;
	public:
		typedef std::vector<testspr::trace_info> container_type;
		typedef container_type::size_type size_type;
		typedef container_type::value_type value_type;
		typedef container_type::reference reference;
		typedef container_type::const_reference const_reference;
		typedef container_type::iterator iterator;
		typedef container_type::const_iterator const_iterator;
		typedef std::function<bool (testspr::trace_stack const&)> function_type;
	private:
		class comparable_function {
		private:
			function_type func_;
		public:
			SPROUT_NON_CONSTEXPR comparable_function(function_type const& f)
				: func_(f)
			{}
			SPROUT_NON_CONSTEXPR bool operator()(trace_stack const& t) const {
				return func_(t);
			}
			SPROUT_NON_CONSTEXPR bool operator==(function_type const& rhs) const {
				return func_ == nullptr ? rhs == nullptr
					: rhs == nullptr ? false
					: func_.target_type() == rhs.target_type()
						&& func_.target<bool (*)(testspr::trace_stack const&)>() == rhs.target<bool (*)(testspr::trace_stack const&)>()
					;
			}
			SPROUT_NON_CONSTEXPR bool operator!=(function_type const& rhs) const {
				return !(*this == rhs);
			}
		};
	private:
		typedef std::vector<comparable_function> function_container_type;
	private:
		class print_on_push {
		public:
			SPROUT_NON_CONSTEXPR bool operator()(testspr::trace_stack const& stack) const {
				testspr::trace_info const& info = stack.top();
				testspr::print_ln("trace-stack push: ", info.file(), ":", info.line(), ": ", info.tag(), ": ", info.what());
				return false;
			}
		};
		class print_on_pop {
		public:
			SPROUT_NON_CONSTEXPR bool operator()(testspr::trace_stack const& stack) const {
				testspr::trace_info const& info = stack.top();
				testspr::print_ln("trace-stack pop: ", info.file(), ":", info.line(), ": ", info.tag(), ": ", info.what());
				return false;
			}
		};
		class record_on_push {
		public:
			SPROUT_NON_CONSTEXPR bool operator()(testspr::trace_stack const& stack) const {
				testspr::trace_record::instance().push("push", stack.top());
				return false;
			}
		};
		class record_on_pop {
		public:
			SPROUT_NON_CONSTEXPR bool operator()(testspr::trace_stack const& stack) const {
				testspr::trace_record::instance().push("pop", stack.top());
				return false;
			}
		};
		class print_on_notify {
		public:
			SPROUT_NON_CONSTEXPR bool operator()(testspr::trace_stack const& stack) const {
				testspr::trace_info const& info = stack.top();
				testspr::print_ln("trace-stack notify: ", info.file(), ":", info.line(), ": ", info.tag(), ": ", info.what());
				if (info.tag() == "assertion-failed") {
					testspr::trace_stack::instance().print();
					testspr::trace_record::instance().print();
				}
				return false;
			}
		};
		class record_on_notify {
		public:
			SPROUT_NON_CONSTEXPR bool operator()(testspr::trace_stack const& stack) const {
				testspr::trace_record::instance().push("notify", stack.top());
				return false;
			}
		};
	public:
		static inline SPROUT_NON_CONSTEXPR trace_stack& instance() {
			return get_mutable_instance();
		}
	private:
		container_type info_;
		function_container_type callback_on_push_;
		function_container_type callback_on_pop_;
		function_container_type callback_on_notify_;
	private:
		SPROUT_NON_CONSTEXPR bool callback_on_push() {
			for (function_container_type::iterator it = callback_on_push_.begin(), last = callback_on_push_.end(); it != last; ++it) {
				if ((*it)(*this)) {
					return true;
				}
			}
			return false;
		}
		SPROUT_NON_CONSTEXPR bool callback_on_pop() {
			for (function_container_type::reverse_iterator it = callback_on_pop_.rbegin(), last = callback_on_pop_.rend(); it != last; ++it) {
				if ((*it)(*this)) {
					return true;
				}
			}
			return false;
		}
		SPROUT_NON_CONSTEXPR bool callback_on_notify() {
			for (function_container_type::iterator it = callback_on_notify_.begin(), last = callback_on_notify_.end(); it != last; ++it) {
				if ((*it)(*this)) {
					return true;
				}
			}
			return false;
		}
	public:
		SPROUT_NON_CONSTEXPR void push(std::string const& file, long line) {
			info_.emplace_back(file, line);
			callback_on_push();
		}
		SPROUT_NON_CONSTEXPR void push(std::string const& file, long line, std::string const& tag) {
			info_.emplace_back(file, line, tag);
			callback_on_push();
		}
		SPROUT_NON_CONSTEXPR void push(std::string const& file, long line, std::string const& tag, std::string const& what) {
			info_.emplace_back(file, line, tag, what);
			callback_on_push();
		}
		SPROUT_NON_CONSTEXPR void pop() {
			callback_on_pop();
			info_.pop_back();
		}
		SPROUT_NON_CONSTEXPR reference top() {
			return info_.back();
		}
		SPROUT_NON_CONSTEXPR const_reference top() const {
			return info_.back();
		}
		SPROUT_NON_CONSTEXPR size_type size() const {
			return info_.size();
		}
		SPROUT_NON_CONSTEXPR iterator begin() {
			return info_.begin();
		}
		SPROUT_NON_CONSTEXPR iterator end() {
			return info_.end();
		}
		SPROUT_NON_CONSTEXPR const_iterator begin() const {
			return info_.begin();
		}
		SPROUT_NON_CONSTEXPR const_iterator end() const {
			return info_.end();
		}
		SPROUT_NON_CONSTEXPR const_iterator cbegin() const {
			return info_.cbegin();
		}
		SPROUT_NON_CONSTEXPR const_iterator cend() const {
			return info_.cend();
		}
		template<typename OutputIterator>
		SPROUT_NON_CONSTEXPR void copy(OutputIterator out) const {
			std::copy(begin(), end(), out);
		}
		SPROUT_NON_CONSTEXPR void print() const {
			testspr::print_ln("trace-stack current: size:", size(), ":");
			for (const_iterator it = cbegin(), last = cend(); it != last; ++it) {
				testspr::print_ln("  ", it->file(), ":", it->line(), ": ", it->tag(), ": ", it->what());
			}
		}

		SPROUT_NON_CONSTEXPR void notify_assertion_failed(std::string const& expr, std::string const& file, long line) {
			info_.emplace_back(file, line, "assertion-failed", expr);
			callback_on_notify();
			info_.pop_back();
		}
		template<typename E>
		SPROUT_NON_CONSTEXPR void notify_throw_exception(E const& exception, std::string const& file, long line) {
			info_.emplace_back(file, line, "throw-exception", testspr::typename_of(exception));
			callback_on_notify();
			info_.pop_back();
		}
		template<typename E>
		SPROUT_NON_CONSTEXPR void notify_caught_exception(E const& exception, std::string const& file, long line) {
			info_.emplace_back(file, line, "caught-exception", testspr::typename_of(exception));
			callback_on_notify();
			info_.pop_back();
		}
		SPROUT_NON_CONSTEXPR void notify_mark(std::string const& name, std::string const& file, long line) {
			info_.emplace_back(file, line, "mark", name);
			callback_on_notify();
			info_.pop_back();
		}

		SPROUT_NON_CONSTEXPR void push_callback_on_push(function_type const& callback) {
			callback_on_push_.push_back(callback);
		}
		SPROUT_NON_CONSTEXPR void pop_callback_on_push(function_type const& callback) {
			function_container_type::reverse_iterator rfound
				= std::find(callback_on_push_.rbegin(), callback_on_push_.rend(), callback);
			if (rfound != callback_on_push_.rend()) {
				callback_on_push_.erase(rfound.base() - 1);
			}
		}
		SPROUT_NON_CONSTEXPR void push_callback_on_pop(function_type const& callback) {
			callback_on_pop_.push_back(callback);
		}
		SPROUT_NON_CONSTEXPR void pop_callback_on_pop(function_type const& callback) {
			function_container_type::reverse_iterator rfound
				= std::find(callback_on_pop_.rbegin(), callback_on_pop_.rend(), callback);
			if (rfound != callback_on_pop_.rend()) {
				callback_on_pop_.erase(rfound.base() - 1);
			}
		}
		SPROUT_NON_CONSTEXPR void push_callback_on_notify(function_type const& callback) {
			callback_on_notify_.push_back(callback);
		}
		SPROUT_NON_CONSTEXPR void pop_callback_on_notify(function_type const& callback) {
			function_container_type::reverse_iterator rfound
				= std::find(callback_on_notify_.rbegin(), callback_on_notify_.rend(), callback);
			if (rfound != callback_on_notify_.rend()) {
				callback_on_notify_.erase(rfound.base() - 1);
			}
		}

		SPROUT_NON_CONSTEXPR void enable_print_on_entry() {
			{
				function_type callback = print_on_push();
				function_container_type::iterator found
					= std::find(callback_on_push_.begin(), callback_on_push_.end(), callback);
				if (found == callback_on_push_.end()) {
					push_callback_on_push(callback);
				}
			}
			{
				function_type callback = print_on_pop();
				function_container_type::iterator found
					= std::find(callback_on_pop_.begin(), callback_on_pop_.end(), callback);
				if (found == callback_on_pop_.end()) {
					push_callback_on_pop(callback);
				}
			}
			{
				function_type callback = print_on_notify();
				function_container_type::iterator found
					= std::find(callback_on_notify_.begin(), callback_on_notify_.end(), callback);
				if (found == callback_on_notify_.end()) {
					push_callback_on_notify(callback);
				}
			}
		}
		SPROUT_NON_CONSTEXPR void disable_print_on_entry() {
			{
				function_type callback = print_on_push();
				pop_callback_on_push(callback);
			}
			{
				function_type callback = print_on_pop();
				pop_callback_on_pop(callback);
			}
			{
				function_type callback = print_on_notify();
				pop_callback_on_notify(callback);
			}
		}

		SPROUT_NON_CONSTEXPR void enable_record_on_entry() {
			{
				function_type callback = record_on_push();
				function_container_type::iterator found
					= std::find(callback_on_push_.begin(), callback_on_push_.end(), callback);
				if (found == callback_on_push_.end()) {
					push_callback_on_push(callback);
				}
			}
			{
				function_type callback = record_on_pop();
				function_container_type::iterator found
					= std::find(callback_on_pop_.begin(), callback_on_pop_.end(), callback);
				if (found == callback_on_pop_.end()) {
					push_callback_on_pop(callback);
				}
			}
			{
				function_type callback = record_on_notify();
				function_container_type::iterator found
					= std::find(callback_on_notify_.begin(), callback_on_notify_.end(), callback);
				if (found == callback_on_notify_.end()) {
					push_callback_on_notify(callback);
				}
			}
		}
		SPROUT_NON_CONSTEXPR void disable_record_on_entry() {
			{
				function_type callback = record_on_push();
				pop_callback_on_push(callback);
			}
			{
				function_type callback = record_on_pop();
				pop_callback_on_pop(callback);
			}
			{
				function_type callback = record_on_notify();
				pop_callback_on_notify(callback);
			}
		}
	};

	//
	// function_tracer
	//
	class function_tracer {
	public:
		SPROUT_NON_CONSTEXPR function_tracer(std::string const& file, long line) {
			testspr::trace_stack::instance().push(file, line, "function");
		}
		SPROUT_NON_CONSTEXPR function_tracer(std::string const& file, long line, std::string const& function) {
			testspr::trace_stack::instance().push(file, line, "function", function);
		}
		~function_tracer() SPROUT_NOEXCEPT {
			testspr::trace_stack::instance().pop();
		}
	};
	//
	// TESTSPR_TRACE_FUNCTION
	//
#	define TESTSPR_TRACE_FUNCTION() \
		testspr::function_tracer SPROUT_PP_CAT(testspr_function_tracer_, __LINE__)(__FILE__, __LINE__, SPROUT_CURRENT_FUNCTION)
	//
	// TESTSPR_TRACE_FUNCTION_EXPR
	//
#	define TESTSPR_TRACE_FUNCTION_EXPR() \
		((void)testspr::function_tracer(__FILE__, __LINE__, SPROUT_CURRENT_FUNCTION))

	//
	// block_tracer
	//
	class block_tracer {
	public:
		SPROUT_NON_CONSTEXPR block_tracer(std::string const& file, long line) {
			testspr::trace_stack::instance().push(file, line, "block");
		}
		SPROUT_NON_CONSTEXPR block_tracer(std::string const& file, long line, std::string const& name) {
			testspr::trace_stack::instance().push(file, line, "block", name);
		}
		~block_tracer() SPROUT_NOEXCEPT {
			testspr::trace_stack::instance().pop();
		}
	};
	//
	// TESTSPR_TRACE_BLOCK
	//
#	define TESTSPR_TRACE_BLOCK(name) \
		testspr::block_tracer SPROUT_PP_CAT(testspr_block_tracer_, __LINE__)(__FILE__, __LINE__, testspr::to_string(name))
	//
	// TESTSPR_TRACE_BLOCK_EXPR
	//
#	define TESTSPR_TRACE_BLOCK_EXPR(name) \
		((void)testspr::block_tracer(__FILE__, __LINE__, testspr::to_string(name)))

	namespace detail {
		inline SPROUT_NON_CONSTEXPR bool
		trace_assertion_failed(char const* formatted, char const* expr, char const* file, long line) {
			testspr::trace_stack::instance().notify_assertion_failed(expr, file, line);
			return (std::cerr << formatted << std::endl), std::abort(), false;
		}
		inline SPROUT_NON_CONSTEXPR bool
		trace_assertion_check(bool cond, char const* formatted, char const* expr, char const* file, long line) {
			return cond ? true
				: testspr::detail::trace_assertion_failed(formatted, expr, file, line)
				;
		}
	}	// namespace detail
	//
	// TESTSPR_TRACE_ASSERT
	//
#	define TESTSPR_TRACE_ASSERT(expr) \
		((void)testspr::detail::trace_assertion_check((expr), SPROUT_ASSERTION_FAILED_FORMAT(expr, __FILE__, __LINE__), SPROUT_PP_STRINGIZE((expr)), __FILE__, __LINE__))

	namespace detail {
		template<typename E>
		inline SPROUT_NON_CONSTEXPR void
		trace_throw(E&& exception, char const* file, long line) {
			testspr::trace_stack::instance().notify_throw_exception(exception, file, line);
			throw sprout::forward<E>(exception);
		}
	}	// namespace detail
	//
	// TESTSPR_TRACE_THROW
	//
#	define TESTSPR_TRACE_THROW(e) \
		((void)testspr::detail::trace_throw(e, __FILE__, __LINE__))

	namespace detail {
		template<typename E>
		inline SPROUT_NON_CONSTEXPR void
		trace_caught(E&& exception, char const* file, long line) {
			testspr::trace_stack::instance().notify_caught_exception(exception, file, line);
		}
	}	// namespace detail
	//
	// TESTSPR_TRACE_CAUGHT
	//
#	define TESTSPR_TRACE_CAUGHT(e) \
		((void)testspr::detail::trace_caught(e, __FILE__, __LINE__))

	//
	// TESTSPR_TRACE_MARK
	//
#	define TESTSPR_TRACE_MARK(name) \
		((void)testspr::trace_stack::instance().notify_mark(testspr::to_string(name), __FILE__, __LINE__))

	//
	// TESTSPR_PRINT_TRACE_STACK
	// TESTSPR_PRINT_TRACE_RECORD
	//
#	define TESTSPR_PRINT_TRACE_STACK() \
		((void)testspr::trace_stack::instance().print())
#	define TESTSPR_PRINT_TRACE_RECORD() \
		((void)testspr::trace_record::instance().print())


	//
	// TESTSPR_ENABLE_PRINT_ON_ENTRY
	// TESTSPR_DISABLE_PRINT_ON_ENTRY
	//
#	define TESTSPR_ENABLE_PRINT_ON_ENTRY() \
		((void)testspr::trace_stack::instance().enable_print_on_entry())
#	define TESTSPR_DISABLE_PRINT_ON_ENTRY() \
		((void)testspr::trace_stack::instance().disable_print_on_entry())

	//
	// TESTSPR_ENABLE_RECORD_ON_ENTRY
	// TESTSPR_DISABLE_RECORD_ON_ENTRY
	//
#	define TESTSPR_ENABLE_RECORD_ON_ENTRY() \
		((void)testspr::trace_stack::instance().enable_record_on_entry())
#	define TESTSPR_DISABLE_RECORD_ON_ENTRY() \
		((void)testspr::trace_stack::instance().disable_record_on_entry())
}	// namespace testspr

#endif	// #ifndef TESTSPR_TRACE_HPP
