#ifndef SPROUT_ITERATOR_SET_UNION_ITERATOR_HPP
#define SPROUT_ITERATOR_SET_UNION_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/type_traits/common.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// set_union_iterator
	//
	template<
		typename LIterator, typename RIterator,
		typename Compare = sprout::less<>
	>
	class set_union_iterator
		: public std::iterator<
			typename sprout::min_iterator_category<
				typename sprout::common_iterator_category<LIterator, RIterator>::type,
				std::forward_iterator_tag
			>::type,
			typename sprout::common_iterator_value_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_difference_type<LIterator, RIterator>::type,
			typename sprout::common_iterator_pointer<LIterator, RIterator>::type,
			typename sprout::common_iterator_reference<LIterator, RIterator>::type
		>
	{
	public:
		typedef LIterator iterator_type;
		typedef RIterator iterator2_type;
		typedef Compare compare_type;
		typedef typename sprout::min_iterator_category<
			typename sprout::common_iterator_category<LIterator, RIterator>::type,
			std::forward_iterator_tag
		>::type iterator_category;
		typedef typename sprout::common_iterator_value_type<LIterator, RIterator>::type value_type;
		typedef typename sprout::common_iterator_difference_type<LIterator, RIterator>::type difference_type;
		typedef typename sprout::common_iterator_pointer<LIterator, RIterator>::type pointer;
		typedef typename sprout::common_iterator_reference<LIterator, RIterator>::type reference;
	private:
		static SPROUT_CONSTEXPR bool check_in_left(
			iterator_type it1, iterator_type lst1,
			iterator2_type it2, iterator2_type lst2,
			Compare comp
			)
		{
			return it1 != lst1 ? (it2 != lst2 ? comp(*it1, *it2) || !comp(*it2, *it1) : true)
				: !(it2 != lst2)
				;
		}
	protected:
		iterator_type current1;
		iterator_type lst1;
		iterator2_type current2;
		iterator2_type lst2;
		Compare comp;
		bool in_left;
	public:
		set_union_iterator()
			: current1(), lst1(), current2(), lst2(), comp(), in_left(true)
		{}
		set_union_iterator(set_union_iterator const&) = default;
		SPROUT_CONSTEXPR set_union_iterator(
			iterator_type it1, iterator_type lst1,
			iterator2_type it2, iterator2_type lst2,
			Compare comp = Compare()
			)
			: current1(it1), lst1(lst1)
			, current2(it2), lst2(lst2)
			, comp(comp)
			, in_left(check_in_left(it1, lst1, it2, lst2, comp))
		{}
		template<typename U, typename V, typename W>
		SPROUT_CONSTEXPR set_union_iterator(set_union_iterator<U, V, W> const& it)
			: current1(it.base()), lst1(it.last1())
			, current2(it.base2()), lst2(it.last2())
			, comp(it.compare())
			, in_left(it.is_in_left())
		{}
		template<typename U, typename V, typename W>
		set_union_iterator& operator=(set_union_iterator<U, V, W> const& it) {
			set_union_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current1;
		}
		SPROUT_CONSTEXPR iterator_type last1() const {
			return lst1;
		}
		SPROUT_CONSTEXPR iterator2_type base2() const {
			return current2;
		}
		SPROUT_CONSTEXPR iterator2_type last2() const {
			return lst2;
		}
		SPROUT_CONSTEXPR Compare compare() const {
			return comp;
		}
		SPROUT_CONSTEXPR bool is_in_left() const {
			return in_left;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return is_in_left() ? *current1 : *current2;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		set_union_iterator& operator++() {
			if (current1 != lst1) {
				if (current2 != lst2) {
					if (comp(*current1, *current2)) {
						++current1;
					} else if (comp(*current2, *current1)) {
						++current2;
					} else {
						++current1;
						++current2;
					}
				} else {
					++current1;
				}
			} else if (current2 != lst2) {
				++current2;
			}
			in_left = check_in_left(current1, lst1, current2, lst2, comp);
			return *this;
		}
		set_union_iterator operator++(int) {
			set_union_iterator result(*this);
			if (current1 != lst1) {
				if (current2 != lst2) {
					if (comp(*current1, *current2)) {
						++current1;
					} else if (comp(*current2, *current1)) {
						++current2;
					} else {
						++current1;
						++current2;
					}
				} else {
					++current1;
				}
			} else if (current2 != lst2) {
				++current2;
			}
			in_left = check_in_left(current1, lst1, current2, lst2, comp);
			return result;
		}
		SPROUT_CONSTEXPR set_union_iterator next() const {
			return current1 != lst1
				? current2 != lst2
					? comp(*current1, *current2)
						? set_union_iterator(sprout::next(current1), lst1, current2, lst2, comp)
						: comp(*current2, *current1)
							? set_union_iterator(current1, lst1, sprout::next(current2), lst2, comp)
							: set_union_iterator(sprout::next(current1), lst1, sprout::next(current2), lst2, comp)
					: set_union_iterator(sprout::next(current1), lst1, current2, lst2, comp)
				: current2 != lst2
					? set_union_iterator(current1, lst1, sprout::next(current2), lst2, comp)
				: *this
				;
		}
		void swap(set_union_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current1, other.current1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(lst1, other.lst1))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(current2, other.current2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(lst2, other.lst2))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(comp, other.comp))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(in_left, other.in_left))
			)
		{
			sprout::swap(current1, other.current1);
			sprout::swap(lst1, other.lst1);
			sprout::swap(current2, other.current2);
			sprout::swap(lst2, other.lst2);
			sprout::swap(comp, other.comp);
			sprout::swap(in_left, other.in_left);
		}
	};

	template<
		typename LIterator1, typename RIterator1, typename Compare1,
		typename LIterator2, typename RIterator2, typename Compare2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::set_union_iterator<LIterator1, RIterator1, Compare1> const& lhs,
		sprout::set_union_iterator<LIterator2, RIterator2, Compare2> const& rhs
		)
	{
		return lhs.base() == rhs.base() && lhs.base2() == rhs.base2();
	}
	template<
		typename LIterator1, typename RIterator1, typename Compare1,
		typename LIterator2, typename RIterator2, typename Compare2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::set_union_iterator<LIterator1, RIterator1, Compare1> const& lhs,
		sprout::set_union_iterator<LIterator2, RIterator2, Compare2> const& rhs
		)
	{
		return !(lhs == rhs);
	}

	//
	// make_set_union_iterator
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::set_union_iterator<LIterator, RIterator, Compare>
	make_set_union_iterator(LIterator it1, LIterator lst1, RIterator it2, RIterator lst2, Compare comp) {
		return sprout::set_union_iterator<LIterator, RIterator, Compare>(it1, lst1, it2, lst2, comp);
	}
	template<typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::set_union_iterator<LIterator, RIterator>
	make_set_union_iterator(LIterator it1, LIterator lst1, RIterator it2, RIterator lst2) {
		return sprout::set_union_iterator<LIterator, RIterator>(it1, lst1, it2, lst2);
	}

	//
	// swap
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline void
	swap(
		sprout::set_union_iterator<LIterator, RIterator, Compare>& lhs,
		sprout::set_union_iterator<LIterator, RIterator, Compare>& rhs
		)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename LIterator, typename RIterator, typename Compare>
	inline SPROUT_CONSTEXPR sprout::set_union_iterator<LIterator, RIterator, Compare>
	iterator_next(sprout::set_union_iterator<LIterator, RIterator, Compare> const& it) {
		return it.next();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_SET_UNION_ITERATOR_HPP
