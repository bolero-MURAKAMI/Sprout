/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FORWARD_CLIST_HPP
#define SPROUT_FORWARD_CLIST_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/utility/move.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/utility/value_holder/value_holder.hpp>
#include <sprout/utility/value_holder/get.hpp>

namespace sprout {
	//
	// forward_clist
	//
	template<typename T>
	class forward_clist;

	namespace detail {
		template<typename List>
		class forward_item_iterator
			: public std::iterator<
				std::forward_iterator_tag,
				typename List::value_type,
				typename List::difference_type,
				typename std::conditional<
					std::is_const<typename std::remove_reference<List>::type>::value,
					typename List::const_pointer,
					typename List::pointer
				>::type,
				typename std::conditional<
					std::is_const<typename std::remove_reference<List>::type>::value,
					typename List::const_reference,
					typename List::reference
				>::type
			>
		{
			template<typename T>
			friend class sprout::forward_clist;
			template<typename L>
			friend class sprout::detail::forward_item_iterator;
		public:
			typedef List list_type;
			typedef typename std::conditional<
				std::is_reference<list_type>::value,
				typename std::remove_reference<list_type>::type const&,
				typename std::remove_reference<list_type>::type const
			>::type const_list_type;
		private:
			typedef std::iterator<
				std::forward_iterator_tag,
				typename List::value_type,
				typename List::difference_type,
				typename std::conditional<
					std::is_const<typename std::remove_reference<List>::type>::value,
					typename List::const_pointer,
					typename List::pointer
				>::type,
				typename std::conditional<
					std::is_const<typename std::remove_reference<List>::type>::value,
					typename List::const_reference,
					typename List::reference
				>::type
			> base_type;
			typedef typename std::remove_reference<list_type>::type::item_holder_type item_holder_type;
		public:
			typedef typename base_type::iterator_category iterator_category;
			typedef typename base_type::value_type value_type;
			typedef typename base_type::difference_type difference_type;
			typedef typename base_type::pointer pointer;
			typedef typename base_type::reference reference;
		private:
			item_holder_type item;
		private:
			explicit SPROUT_CONSTEXPR forward_item_iterator(item_holder_type const& p)
				: item(p)
			{}
		public:
			SPROUT_CONSTEXPR forward_item_iterator()
				: item()
			{}
			forward_item_iterator(forward_item_iterator const&) = default;
			SPROUT_CONSTEXPR operator forward_item_iterator<const_list_type>() const {
				return forward_item_iterator<const_list_type>(item);
			}
			SPROUT_CONSTEXPR forward_item_iterator next() const {
				return forward_item_iterator(item->next);
			}
			SPROUT_CXX14_CONSTEXPR void swap(forward_item_iterator& other)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(item, other.item)))
			{
				sprout::swap(item, other.item);
			}
			SPROUT_CONSTEXPR reference operator*() const {
				return item->get();
			}
			SPROUT_CONSTEXPR pointer operator->() const {
				return item->get_pointer();
			}
			SPROUT_CXX14_CONSTEXPR forward_item_iterator& operator++() {
				forward_item_iterator temp(next());
				temp.swap(*this);
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR forward_item_iterator operator++(int) {
				forward_item_iterator result(*this);
				++*this;
				return result;
			}
		};

		template<typename List1, typename List2>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_same<typename std::decay<List1>::type, typename std::decay<List2>::type>::value,
			bool
		>::type
		operator==(sprout::detail::forward_item_iterator<List1> const& lhs, sprout::detail::forward_item_iterator<List2> const& rhs) {
			return &*lhs == &*rhs;
		}
		template<typename List1, typename List2>
		inline SPROUT_CONSTEXPR typename std::enable_if<
			std::is_same<typename std::decay<List1>::type, typename std::decay<List2>::type>::value,
			bool
		>::type
		operator!=(sprout::detail::forward_item_iterator<List1> const& lhs, sprout::detail::forward_item_iterator<List2> const& rhs) {
			return !(lhs == rhs);
		}

		template<typename List>
		inline SPROUT_CXX14_CONSTEXPR void
		swap(sprout::detail::forward_item_iterator<List>& lhs, sprout::detail::forward_item_iterator<List>& rhs)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
		{
			lhs.swap(rhs);
		}

		template<typename List>
		inline SPROUT_CONSTEXPR sprout::detail::forward_item_iterator<List>
		iterator_next(sprout::detail::forward_item_iterator<List> const& it) {
			return it.next();
		}
	}	// namespace detail

	//
	// forward_clist
	//
	template<typename T>
	class forward_clist {
		template<typename List>
		friend class sprout::detail::forward_item_iterator;
	public:
		// types:
		typedef T value_type;
		typedef value_type& reference;
		typedef value_type const& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type const* const_pointer;
		typedef sprout::detail::forward_item_iterator<forward_clist> iterator;
		typedef sprout::detail::forward_item_iterator<forward_clist const> const_iterator;
	public:
		class item;
	private:
		typedef sprout::value_holder<item&> item_holder_type;
	public:
		//
		// item
		//
		class item {
			friend class forward_clist;
			template<typename List>
			friend class sprout::detail::forward_item_iterator;
		private:
			typedef sprout::value_holder<typename forward_clist::value_type> holder_type;
			typedef sprout::value_holder<item&> item_holder_type;
		public:
			typedef typename holder_type::value_type value_type;
			typedef typename holder_type::lvalue_reference lvalue_reference;
			typedef typename holder_type::rvalue_reference rvalue_reference;
			typedef typename holder_type::reference reference;
			typedef typename holder_type::const_lvalue_reference const_lvalue_reference;
			typedef typename holder_type::const_rvalue_reference const_rvalue_reference;
			typedef typename holder_type::const_reference const_reference;
			typedef typename holder_type::pointer pointer;
			typedef typename holder_type::const_pointer const_pointer;
			typedef typename holder_type::lvalue_reference_type lvalue_reference_type;
			typedef typename holder_type::rvalue_reference_type rvalue_reference_type;
			typedef typename holder_type::reference_type reference_type;
			typedef typename holder_type::reference_const_type reference_const_type;
			typedef typename holder_type::pointer_type pointer_type;
			typedef typename holder_type::pointer_const_type pointer_const_type;
		public:
			static SPROUT_CONSTEXPR reference_type get(item& t) SPROUT_NOEXCEPT {
				return sprout::get(t.val);
			}
			static SPROUT_CONSTEXPR rvalue_reference_type get(item&& t) SPROUT_NOEXCEPT {
				return static_cast<rvalue_reference_type>(get(t));
			}
			static SPROUT_CONSTEXPR reference_const_type get(item const& t) SPROUT_NOEXCEPT {
				return sprout::get(t.val);
			}
			static SPROUT_CONSTEXPR pointer_type get_pointer(item& t) SPROUT_NOEXCEPT {
				return sprout::get_pointer(t.val);
			}
			static SPROUT_CONSTEXPR pointer_type get_pointer(item&& t) SPROUT_NOEXCEPT {
				return get_pointer(t);
			}
			static SPROUT_CONSTEXPR pointer_const_type get_pointer(item const& t) SPROUT_NOEXCEPT {
				return sprout::get_pointer(t.val);
			}
		private:
			holder_type val;
			item_holder_type next;
		private:
			item& operator=(item const&) SPROUT_DELETED_FUNCTION_DECL
			item& operator=(item&&) SPROUT_DELETED_FUNCTION_DECL
		private:
			SPROUT_CONSTEXPR item(typename holder_type::argument_type p, item_holder_type const& n)
				: val(p)
				, next(n)
			{}
			SPROUT_CONSTEXPR item(typename holder_type::movable_argument_type p, item_holder_type const& n)
				: val(sprout::move(p))
				, next(n)
			{}

			SPROUT_CXX14_CONSTEXPR void swap(item& other)
			SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(val, other.val)) && SPROUT_NOEXCEPT_EXPR(sprout::swap(next, other.next)))
			{
				sprout::swap(val, other.val);
				sprout::swap(next, other.next);
			}

			SPROUT_CXX14_CONSTEXPR void unlink_all() {
				if (next.is_initialized()) {
					next->unlink_all();
					{
						item_holder_type temp = item_holder_type();
						temp.swap(next);
					}
				}
			}
			SPROUT_CXX14_CONSTEXPR void unlink() {
				item_holder_type temp = item_holder_type();
				temp.swap(next);
			}
		public:
			SPROUT_CONSTEXPR item() SPROUT_NOEXCEPT
				: val(), next()
			{}
			item(item const&) = default;
			SPROUT_CONSTEXPR item(typename holder_type::argument_type p)
				: val(p), next()
			{}
			SPROUT_CONSTEXPR item(typename holder_type::movable_argument_type p)
				: val(sprout::move(p)), next()
			{}

			SPROUT_CXX14_CONSTEXPR item& operator=(typename holder_type::argument_type p) {
				item temp(p, next);
				temp.swap(p);
				return *this;
			}
			SPROUT_CXX14_CONSTEXPR item& operator=(typename holder_type::movable_argument_type p) {
				item temp(sprout::move(p), next);
				temp.swap(p);
				return *this;
			}

			SPROUT_CXX14_CONSTEXPR pointer_type operator->() {
				return get_pointer();
			}
			SPROUT_CONSTEXPR pointer_const_type operator->() const {
				return get_pointer();
			}
			SPROUT_CXX14_CONSTEXPR pointer_type get_pointer() {
				return val.get_pointer();
			}
			SPROUT_CONSTEXPR pointer_const_type get_pointer() const {
				return val.get_pointer();
			}
			SPROUT_CXX14_CONSTEXPR reference_type operator*() {
				return get();
			}
			SPROUT_CONSTEXPR reference_const_type operator*() const {
				return get();
			}
			SPROUT_CXX14_CONSTEXPR reference_type get() {
				return val.get();
			}
			SPROUT_CONSTEXPR reference_const_type get() const {
				return val.get();
			}
			SPROUT_CONSTEXPR bool is_linked() const {
				return next.is_initialized();
			}
		};
	private:
		item fst;
	public:
		// construct/copy/destroy:
		SPROUT_CONSTEXPR forward_clist()
			: fst()
		{}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR forward_clist(InputIterator first, InputIterator last)
			: fst()
		{
			item_holder_type* p = &fst.next;
			for (; first != last; ++first) {
				*p = *first;
				p = &(*p)->next;
			}
		}
		SPROUT_CXX14_CONSTEXPR forward_clist(forward_clist&& x)
			: fst(sprout::move(x.fst))
		{}
		SPROUT_CXX14_CONSTEXPR forward_clist& operator=(forward_clist&& x) {
			fst = sprout::move(x.fst);
			return *this;
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR void assign(InputIterator first, InputIterator last) {
			forward_clist temp(first, last);
			temp.swap(*this);
			temp.clear();
		}
		// iterators:
		SPROUT_CXX14_CONSTEXPR iterator before_begin() SPROUT_NOEXCEPT {
			return iterator(item_holder_type(fst));
		}
		SPROUT_CONSTEXPR const_iterator before_begin() const SPROUT_NOEXCEPT {
			return const_iterator(item_holder_type(fst));
		}
		SPROUT_CXX14_CONSTEXPR iterator begin() SPROUT_NOEXCEPT {
			return iterator(fst.next);
		}
		SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT {
			return const_iterator(fst.next);
		}
		SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT {
			return iterator();
		}
		SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT {
			return const_iterator();
		}
		SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT {
			return const_iterator(fst.next);
		}
		SPROUT_CONSTEXPR const_iterator cbefore_begin() const SPROUT_NOEXCEPT{
			return const_iterator(fst.next);
		}
		SPROUT_CONSTEXPR const_iterator cend() const SPROUT_NOEXCEPT {
			return const_iterator();
		}
		// capacity:
		SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT {
			return !!fst.next;
		}
		SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT {
			return sprout::numeric_limits<size_type>::max();
		}
		// element access:
		SPROUT_CXX14_CONSTEXPR reference front() {
			return fst.next->get();
		}
		SPROUT_CONSTEXPR const_reference front() const {
			return fst.next->get();
		}
		// modifiers:
		SPROUT_CXX14_CONSTEXPR void push_front(item& x) {
			item_holder_type nxt(x);
			nxt->next = fst.next;
			fst.next = nxt;
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR void push_front(InputIterator first, InputIterator last) {
			item_holder_type nxt(fst.next);
			item_holder_type* p = &fst.next;
			for (; first != last; ++first) {
				*p = *first;
				p = &(*p)->next;
			}
			*p = nxt;
		}
		SPROUT_CXX14_CONSTEXPR void pop_front() {
			item_holder_type nxt(fst.next);
			fst.next = fst.next->next;
			nxt->unlink();
		}

		SPROUT_CXX14_CONSTEXPR iterator insert_after(const_iterator position, item& x) {
			item_holder_type nxt(x);
			nxt->next = position.item->next;
			position.item->next = nxt;
			return iterator(nxt);
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR iterator insert_after(const_iterator position, InputIterator first, InputIterator last) {
			item_holder_type nxt(position.item->next);
			item_holder_type pos(position.item);
			item_holder_type* p = &pos;
			for (; first != last; ++first) {
				(*p)->next = *first;
				p = &(*p)->next;
			}
			(*p)->next = nxt;
			return iterator(*p);
		}

		SPROUT_CXX14_CONSTEXPR iterator erase_after(const_iterator position) {
			const_iterator first(position.next());
			position.item->next = first.item->next;
			first.item->unlink();
			return iterator(position.item->next);
		}
		SPROUT_CXX14_CONSTEXPR iterator erase_after(const_iterator position, const_iterator last) {
			const_iterator first(position.next());
			position.item->next = last.item;
			while (first != last) {
				const_iterator nxt(first.next());
				first.item->unlink();
				first = nxt;
			}
			return iterator(last.item);
		}

		SPROUT_CXX14_CONSTEXPR void swap(forward_clist& other) {
			sprout::swap(fst, other.fst);
		}
		SPROUT_CXX14_CONSTEXPR void clear() SPROUT_NOEXCEPT {
			fst.unlink_all();
		}

		SPROUT_CXX14_CONSTEXPR void unlink(item& x) {
			for (iterator first = before_begin(), last = end(); first != last; ++first) {
				iterator nxt = first.next();
				if (nxt.item.get_pointer() == &x) {
					first.item->next = sprout::move(nxt.item->next);
					nxt.item->unlink();
					break;
				}
			}
		}
		template<typename InputIterator>
		SPROUT_CXX14_CONSTEXPR void unlink(InputIterator first, InputIterator last) {
			for (; first != last; ++first) {
				unlink(*first);
			}
		}
	};

	//
	// get
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::reference_type
	get(typename sprout::forward_clist<T>::item& x) {
		return sprout::forward_clist<T>::item::get(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::rvalue_reference
	get(typename sprout::forward_clist<T>::item&& x) {
		return sprout::forward_clist<T>::item::get(sprout::move(x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::reference_const_type
	get(typename sprout::forward_clist<T>::item const& x) {
		return sprout::forward_clist<T>::item::get(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::pointer_type
	get(typename sprout::forward_clist<T>::item* x) {
		return sprout::forward_clist<T>::item::get_pointer(*x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::pointer_const_type
	get(typename sprout::forward_clist<T>::item const* x) {
		return sprout::forward_clist<T>::item::get_pointer(*x);
	}

	//
	// get_pointer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::pointer_type
	get_pointer(typename sprout::forward_clist<T>::item& x) {
		return sprout::forward_clist<T>::item::get_pointer(x);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::pointer_type
	get_pointer(typename sprout::forward_clist<T>::item&& x) {
		return sprout::forward_clist<T>::item::get_pointer(sprout::move(x));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::forward_clist<T>::item::pointer_const_type
	get_pointer(typename sprout::forward_clist<T>::item const& x) {
		return sprout::forward_clist<T>::item::get_pointer(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_FORWARD_CLIST_HPP
