/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_HOLDER_HPP
#define SPROUT_CONTAINER_CONTAINER_HOLDER_HPP

#include <utility>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>

namespace sprout {
	//
	// container_holder
	//
	template<typename Container>
	class container_holder
		: public sprout::container_traits_facade<Container>
	{
	private:
		typedef sprout::container_traits_facade<Container> facade_type;
	public:
		typedef Container container_type;
		typedef container_type internal_type;
		typedef typename facade_type::iterator iterator;
		typedef typename facade_type::const_iterator const_iterator;
		typedef typename facade_type::reference reference;
		typedef typename facade_type::const_reference const_reference;
		typedef typename facade_type::size_type size_type;
		typedef typename facade_type::difference_type difference_type;
		typedef typename facade_type::pointer pointer;
		typedef typename facade_type::const_pointer const_pointer;
		typedef internal_type& param_type;
		typedef internal_type const& const_param_type;
		typedef sprout::value_holder<param_type> holder_type;
	protected:
		holder_type container;
	public:
		SPROUT_CONSTEXPR container_holder()
			: container()
		{}
		explicit SPROUT_CONSTEXPR container_holder(param_type x)
			: container(x)
		{}
		SPROUT_CONSTEXPR container_holder(container_holder const&) = default;

		void swap(container_holder& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(other.container, container)))
		{
			sprout::swap(other.container, container);
		}
		// iterators:
		iterator begin() {
			return sprout::begin(*container);
		}
		SPROUT_CONSTEXPR const_iterator begin() const {
			return sprout::begin(*container);
		}
		iterator end() {
			return sprout::end(*container);
		}
		SPROUT_CONSTEXPR const_iterator end() const {
			return sprout::end(*container);
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const {
			return sprout::begin(*container);
		}
		SPROUT_CONSTEXPR const_iterator cend() const {
			return sprout::end(*container);
		}
		// capacity:
		SPROUT_CONSTEXPR size_type size() const SPROUT_NOEXCEPT {
			return sprout::size(*container);
		}
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return sprout::empty(*container);
		}

		param_type get_internal() {
			return *container;
		}
		SPROUT_CONSTEXPR const_param_type get_internal() const {
			return *container;
		}
		// element access:
		reference operator[](size_type i) {
			return *sprout::next(begin(), i);
		}
		SPROUT_CONSTEXPR const_reference operator[](size_type i) const {
			return *sprout::next(begin(), i);
		}
		reference at(size_type i) {
			return i < size() ? (*this)[i]
				: (throw std::out_of_range("container_holder<>: index out of range"), (*this)[i])
				;
		}
		SPROUT_CONSTEXPR const_reference at(size_type i) const {
			return i < size() ? (*this)[i]
				: (throw std::out_of_range("container_holder<>: index out of range"), (*this)[i])
				;
		}
		reference front() {
			return *begin();
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return *begin();
		}
		reference back() {
			return *sprout::next(begin(), size() - 1);
		}
		SPROUT_CONSTEXPR const_reference back() const {
			return *sprout::next(begin(), size() - 1);
		}
	};

	//
	// swap
	//
	template<typename Container>
	inline void
	swap(sprout::container_holder<Container>& lhs, sprout::container_holder<Container>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// container_construct_traits
	//
	template<typename Container>
	struct container_construct_traits<sprout::container_holder<Container> > {
	public:
		typedef typename sprout::container_construct_traits<Container>::copied_type copied_type;
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR copied_type
		deep_copy(Cont&& cont) {
			return sprout::deep_copy(sprout::get_internal(sprout::forward<Cont>(cont)));
		}
		template<typename... Args>
		static SPROUT_CONSTEXPR copied_type
		make(Args&&... args) {
			return sprout::make<copied_type>(sprout::forward<Args>(args)...);
		}
		template<typename Cont, typename... Args>
		static SPROUT_CONSTEXPR copied_type
		remake(Cont&& cont, typename sprout::container_traits<Container>::difference_type size, Args&&... args) {
			return sprout::remake<copied_type>(sprout::get_internal(sprout::forward<Cont>(cont)), size, sprout::forward<Args>(args)...);
		}
	};

	//
	// sub_container_traits
	//
	template<typename Container>
	struct sub_container_traits<sprout::container_holder<Container> > {
	private:
		static typename sprout::container_holder<Container>::param_type
		call(sprout::container_holder<Container>& cont) {
			return cont.get_internal();
		}
		static SPROUT_CONSTEXPR typename sprout::container_holder<Container>::const_param_type
		call(sprout::container_holder<Container> const& cont) {
			return cont.get_internal();
		}
	public:
		template<typename Cont>
		struct internal {
		public:
			typedef decltype(call(std::declval<Cont&&>())) type;
		};
	public:
		template<typename Cont>
		static SPROUT_CONSTEXPR typename internal<Cont>::type
		get_internal(Cont&& cont) {
			return call(sprout::forward<Cont>(cont));
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_HOLDER_HPP
