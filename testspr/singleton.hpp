/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_SINGLETON_HPP
#define TESTSPR_SINGLETON_HPP

#include <sprout/config.hpp>
#include <sprout/utility/noncopyable.hpp>
#include <sprout/assert.hpp>

namespace testspr {
	//
	// singleton_module
	//
	class singleton_module
		: public sprout::noncopyable
	{
	private:
		static inline SPROUT_NON_CONSTEXPR bool& get_lock() {
			static bool lock = false;
			return lock;
		}
	public:
		static inline SPROUT_NON_CONSTEXPR void lock() {
			get_lock() = true;
		}
		static inline SPROUT_NON_CONSTEXPR void unlock() {
			get_lock() = false;
		}
		static inline SPROUT_NON_CONSTEXPR bool is_locked() {
			return get_lock();
		}
	};

	namespace detail {
		template<typename T>
		class singleton_wrapper
			: public T
		{
		public:
			static bool m_is_destroyed;
		public:
			~singleton_wrapper() {
				m_is_destroyed = true;
			}
		};
		template<typename T>
		bool testspr::detail::singleton_wrapper<T>::m_is_destroyed = false;
	}	// namespace detail

	//
	// singleton
	//
	template<typename T>
	class singleton
		: public testspr::singleton_module
	{
	public:
		typedef T instance_type;
	private:
		static instance_type& instance;
	private:
		static inline SPROUT_NON_CONSTEXPR void use(const instance_type&) {}
		static inline SPROUT_NON_CONSTEXPR instance_type& get_instance() {
			static detail::singleton_wrapper<instance_type> t;
			SPROUT_ASSERT(!testspr::detail::singleton_wrapper<instance_type>::m_is_destroyed);
			use(instance);
			return static_cast<instance_type&>(t);
		}
	public:
		static inline SPROUT_NON_CONSTEXPR instance_type& get_mutable_instance() {
			SPROUT_ASSERT(!is_locked());
			return get_instance();
		}
		static inline SPROUT_NON_CONSTEXPR instance_type const& get_const_instance() {
			return get_instance();
		}
		static inline SPROUT_NON_CONSTEXPR bool is_destroyed() {
			return testspr::detail::singleton_wrapper<instance_type>::m_is_destroyed;
		}
	};
	template<typename T>
	T& singleton<T>::instance = testspr::singleton<T>::get_instance();
}	// namespace testspr

#endif	// #ifndef TESTSPR_SINGLETON_HPP
