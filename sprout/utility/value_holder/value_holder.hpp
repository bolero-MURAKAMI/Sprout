#ifndef SPROUT_UTILITY_VALUE_HOLDER_VALUE_HOLDER_HPP
#define SPROUT_UTILITY_VALUE_HOLDER_VALUE_HOLDER_HPP

#include <sprout/config.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		struct holder_helper {
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T const& const_reference;
			typedef T const& mutable_or_const_reference;
			typedef T* pointer;
			typedef T const* const_pointer;
			typedef T const* mutable_or_const_pointer;
			typedef T const& param_type;
			typedef T holder_type;
		public:
			static SPROUT_CONSTEXPR holder_type const& hold(param_type p) SPROUT_NOEXCEPT {
				return p;
			}
			static SPROUT_CONSTEXPR reference ref(holder_type& r) {
				return r;
			}
			static SPROUT_CONSTEXPR const_reference ref(holder_type const& r) {
				return r;
			}
			static SPROUT_CONSTEXPR pointer ptr(holder_type& r) SPROUT_NOEXCEPT {
				return &r;
			}
			static SPROUT_CONSTEXPR const_pointer ptr(holder_type const& r) SPROUT_NOEXCEPT {
				return &r;
			}
		};
		template<typename T>
		struct holder_helper<T const> {
		public:
			typedef T value_type;
			typedef T const& reference;
			typedef T const& const_reference;
			typedef T const& mutable_or_const_reference;
			typedef T const* pointer;
			typedef T const* const_pointer;
			typedef T const* mutable_or_const_pointer;
			typedef T const& param_type;
			typedef T holder_type;
		public:
			static SPROUT_CONSTEXPR holder_type const& hold(param_type p) SPROUT_NOEXCEPT {
				return &p;
			}
			static SPROUT_CONSTEXPR reference ref(holder_type& r) {
				return *r;
			}
			static SPROUT_CONSTEXPR const_reference ref(holder_type const& r) {
				return *r;
			}
			static SPROUT_CONSTEXPR pointer ptr(holder_type& r) SPROUT_NOEXCEPT {
				return &r;
			}
			static SPROUT_CONSTEXPR const_pointer ptr(holder_type const& r) SPROUT_NOEXCEPT {
				return &r;
			}
		};
		template<typename T>
		struct holder_helper<T&> {
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T const& const_reference;
			typedef T& mutable_or_const_reference;
			typedef T* pointer;
			typedef T const* const_pointer;
			typedef T* mutable_or_const_pointer;
			typedef T& param_type;
			typedef T* holder_type;
		public:
			static SPROUT_CONSTEXPR holder_type hold(param_type p) SPROUT_NOEXCEPT {
				return &p;
			}
			static SPROUT_CONSTEXPR reference ref(holder_type r) {
				return *r;
			}
			static SPROUT_CONSTEXPR pointer ptr(holder_type r) SPROUT_NOEXCEPT {
				return r;
			}
		};
		template<typename T>
		struct holder_helper<T const&> {
		public:
			typedef T value_type;
			typedef T const& reference;
			typedef T const& const_reference;
			typedef T const& mutable_or_const_reference;
			typedef T const* pointer;
			typedef T const* const_pointer;
			typedef T const* mutable_or_const_pointer;
			typedef T const& param_type;
			typedef T const* holder_type;
		public:
			static SPROUT_CONSTEXPR holder_type hold(param_type p) SPROUT_NOEXCEPT {
				return &p;
			}
			static SPROUT_CONSTEXPR reference ref(holder_type r) {
				return *r;
			}
			static SPROUT_CONSTEXPR pointer ptr(holder_type r) SPROUT_NOEXCEPT {
				return r;
			}
		};
	}	// namespace detail
	//
	// value_holder
	//
	template<typename T>
	class value_holder {
	public:
		typedef T type;
	private:
		typedef sprout::detail::holder_helper<type> helper_type;
		typedef typename helper_type::holder_type holder_type;
	public:
		typedef typename helper_type::value_type value_type;
		typedef typename helper_type::reference reference;
		typedef typename helper_type::const_reference const_reference;
		typedef typename helper_type::mutable_or_const_reference mutable_or_const_reference;
		typedef typename helper_type::pointer pointer;
		typedef typename helper_type::const_pointer const_pointer;
		typedef typename helper_type::mutable_or_const_pointer mutable_or_const_pointer;
		typedef typename helper_type::param_type param_type;
		typedef reference reference_type;
		typedef mutable_or_const_reference reference_const_type;
		typedef pointer pointer_type;
		typedef mutable_or_const_pointer pointer_const_type;
		typedef param_type argument_type;
	private:
		holder_type holder_;
	public:
		SPROUT_CONSTEXPR value_holder()
			: holder_()
		{}
		SPROUT_CONSTEXPR value_holder(value_holder const&) = default;
		explicit SPROUT_CONSTEXPR value_holder(param_type p)
			: holder_(helper_type::hold(p))
		{}

		value_holder& operator=(value_holder const&) = default;
		value_holder& operator=(param_type p) {
			value_holder temp(p);
			temp.swap(p);
			return *this;
		}

		void swap(value_holder& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(holder_, other.holder_)))
		{
			sprout::swap(holder_, other.holder_);
		}

		operator reference() {
			return helper_type::ref(holder_);
		}
		SPROUT_CONSTEXPR operator mutable_or_const_reference() const {
			return helper_type::ref(holder_);
		}
		reference operator*() {
			return helper_type::ref(holder_);
		}
		SPROUT_CONSTEXPR mutable_or_const_reference operator*() const {
			return helper_type::ref(holder_);
		}
		reference get() {
			return helper_type::ref(holder_);
		}
		SPROUT_CONSTEXPR mutable_or_const_reference get() const {
			return helper_type::ref(holder_);
		}

		pointer operator->() SPROUT_NOEXCEPT {
			return helper_type::ptr(holder_);
		}
		SPROUT_CONSTEXPR mutable_or_const_pointer operator->() const SPROUT_NOEXCEPT {
			return helper_type::ptr(holder_);
		}
		pointer get_pointer() SPROUT_NOEXCEPT {
			return helper_type::ptr(holder_);
		}
		SPROUT_CONSTEXPR mutable_or_const_pointer get_pointer() const SPROUT_NOEXCEPT {
			return helper_type::ptr(holder_);
		}
		pointer get_ptr() SPROUT_NOEXCEPT {
			return get_pointer();
		}
		SPROUT_CONSTEXPR mutable_or_const_pointer get_ptr() const SPROUT_NOEXCEPT {
			return get_pointer();
		}
		SPROUT_CONSTEXPR bool is_initialized() const SPROUT_NOEXCEPT {
			return !!get_pointer();
		}
	};

	//
	// swap
	//
	template<typename T>
	inline void
	swap(sprout::value_holder<T>& lhs, sprout::value_holder<T>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}
}	// namespace sprout

#endif // #ifndef SPROUT_UTILITY_VALUE_HOLDER_VALUE_HOLDER_HPP
