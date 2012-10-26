#ifndef SPROUT_OPTIONAL_OPTIONAL_HPP
#define SPROUT_OPTIONAL_OPTIONAL_HPP

#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/utility/value_holder.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/none.hpp>
#include <sprout/optional/nullopt.hpp>

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
			, val(v.val)
		{}
		template<class U>
		explicit SPROUT_CONSTEXPR optional(optional<U> const& v)
			: init(v.init)
			, val(v.val.get())
		{}

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
		template<class U>
		optional& operator=(optional<U> const& v) {
			assign(v);
			return *this;
		}

		void assign(sprout::nullopt_t) SPROUT_NOEXCEPT {
			destroy();
		}
		void assign(argument_type v) {
			optional temp(v);
			temp.swap(v);
		}
		void assign(optional const& v) {
			optional temp(v);
			temp.swap(v);
		}
		template<class U>
		void assign(optional<U> const& v) {
			optional temp(v);
			temp.swap(v);
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

		void swap(optional& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(val, other.val)))
		{
			sprout::swap(init, other.init);
			sprout::swap(val, other.val);
		}

		SPROUT_CONSTEXPR reference_const_type get() const {
			return is_initialized() ? val.get()
				: throw std::domain_error("optional: value not initialized")
				;
		}
		reference_type get() {
			return is_initialized() ? val.get()
				: throw std::domain_error("optional: value not initialized")
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

		SPROUT_CONSTEXPR pointer_const_type operator->() const {
			return is_initialized() ? val.get_pointer()
				: throw std::domain_error("optional: value not initialized")
				;
		}
		pointer_type operator->() {
			return is_initialized() ? val.get_pointer()
				: throw std::domain_error("optional: value not initialized")
				;
		}
		SPROUT_CONSTEXPR pointer_const_type get_pointer() const {
			return is_initialized() ? val.get_pointer()
				: throw std::domain_error("optional: value not initialized")
				;
		}
		pointer_type get_pointer() {
			return is_initialized() ? val.get_pointer()
				: throw std::domain_error("optional: value not initialized")
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
