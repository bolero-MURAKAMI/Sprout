#ifndef SPROUT_OPTIONAL_OPTIONAL_HPP
#define SPROUT_OPTIONAL_OPTIONAL_HPP

#include <sprout/config.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/none.hpp>
#include <sprout/optional/nullopt.hpp>
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
		typedef typename holder_type::reference reference;
		typedef typename holder_type::const_reference const_reference;
		typedef typename holder_type::pointer pointer;
		typedef typename holder_type::const_pointer const_pointer;
		typedef typename holder_type::reference_type reference_type;
		typedef typename holder_type::reference_const_type reference_const_type;
		typedef typename holder_type::pointer_type pointer_type;
		typedef typename holder_type::pointer_const_type pointer_const_type;
		typedef typename holder_type::argument_type argument_type;
	private:
		bool init;
		holder_type val;
	private:
		void destroy() SPROUT_NOEXCEPT {
			init = false;
		}
	public:
		// 20.5.4.1, constructors
		SPROUT_CONSTEXPR optional() SPROUT_NOEXCEPT
			: init(false)
		{}
		SPROUT_CONSTEXPR optional(sprout::nullopt_t) SPROUT_NOEXCEPT
			: init(false)
		{}
		SPROUT_CONSTEXPR optional(argument_type v)
			: init(true)
			, val(v)
		{}
		SPROUT_CONSTEXPR optional(bool cond, argument_type v)
			: init(cond)
			, val(cond ? holder_type(v) : holder_type())
		{}
		SPROUT_CONSTEXPR optional(optional const& v)
			: init(v.init)
			, val(v.is_initialized() ? holder_type(*v) : holder_type())
		{}
		template<typename U>
		explicit SPROUT_CONSTEXPR optional(optional<U> const& v)
			: init(v.is_initialized())
			, val(v.is_initialized() ? holder_type(*v) : holder_type())
		{}
		// 20.5.4.3, assignment
		optional& operator=(sprout::nullopt_t v) SPROUT_NOEXCEPT {
			assign(v);
			return *this;
		}
		optional& operator=(argument_type v) {
			assign(v);
			return *this;
		}
		optional& operator=(optional const& v) {
			assign(v);
			return *this;
		}
		template<typename U>
		optional& operator=(optional<U> const& v) {
			assign(v);
			return *this;
		}

		void assign(sprout::nullopt_t) SPROUT_NOEXCEPT {
			destroy();
		}
		void assign(argument_type v) {
			optional temp(v);
			temp.swap(*this);
		}
		void assign(optional const& v) {
			optional temp(v);
			temp.swap(*this);
		}
		template<typename U>
		void assign(optional<U> const& v) {
			optional temp(v);
			temp.swap(*this);
		}

		void reset() SPROUT_NOEXCEPT {
			destroy();
		}
		void reset(sprout::nullopt_t v) SPROUT_NOEXCEPT {
			assign(v);
		}
		void reset(argument_type v) {
			assign(v);
		}
		// 20.5.4.4, swap
		void swap(optional& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(val, other.val)))
		{
			sprout::swap(init, other.init);
			sprout::swap(val, other.val);
		}
		// 20.5.4.5, observers
		SPROUT_CONSTEXPR reference_const_type operator*() const {
			return (SPROUT_ASSERT(is_initialized()), true) ? val.get()
				: val.get()
				;
		}
		reference_type operator*() {
			return (SPROUT_ASSERT(is_initialized()), true) ? val.get()
				: val.get()
				;
		}
		SPROUT_CONSTEXPR reference_const_type get() const {
			return is_initialized() ? val.get()
				: (throw sprout::bad_optional_access("optional<>: bad optional access"), val.get())
				;
		}
		reference_type get() {
			return is_initialized() ? val.get()
				: (throw sprout::bad_optional_access("optional<>: bad optional access"), val.get())
				;
		}
		SPROUT_CONSTEXPR reference_const_type get_value_or(reference_const_type& v) const {
			return is_initialized() ? val.get()
				: v
				;
		}
		reference_type get_value_or(reference_type& v) {
			return is_initialized() ? val.get()
				: v
				;
		}

		SPROUT_CONSTEXPR reference_const_type value() const {
			return get();
		}
		reference_type value() {
			return get();
		}
		SPROUT_CONSTEXPR reference_const_type value_or(reference_const_type& v) const {
			return get_value_or(v);
		}
		reference_type value_or(reference_type& v) {
			return get_value_or(v);
		}

		SPROUT_CONSTEXPR pointer_const_type operator->() const {
			return SPROUT_ASSERT(is_initialized()),
				val.get_pointer()
				;
		}
		pointer_type operator->() {
			return SPROUT_ASSERT(is_initialized()),
				val.get_pointer()
				;
		}
		SPROUT_CONSTEXPR pointer_const_type get_pointer() const {
			return is_initialized() ? val.get_pointer()
				: 0
				;
		}
		pointer_type get_pointer() {
			return is_initialized() ? val.get_pointer()
				: 0
				;
		}
		SPROUT_CONSTEXPR pointer_const_type get_ptr() const {
			return get_pointer();
		}
		pointer_type get_ptr() {
			return get_pointer();
		}

		SPROUT_CONSTEXPR operator bool() const SPROUT_NOEXCEPT {
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
	inline void
	swap(sprout::optional<T>& lhs, sprout::optional<T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_OPTIONAL_HPP
