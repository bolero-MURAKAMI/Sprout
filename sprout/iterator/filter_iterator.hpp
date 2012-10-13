#ifndef SPROUT_ITERATOR_FILTER_ITERATOR_HPP
#define SPROUT_ITERATOR_FILTER_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/algorithm/find_if.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// filter_iterator
	//
	template<typename Predicate, typename Iterator>
	class filter_iterator
		: public std::iterator<
			typename std::conditional<
				std::is_convertible<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value,
				std::bidirectional_iterator_tag,
				typename std::iterator_traits<Iterator>::iterator_category
			>::type,
			typename std::iterator_traits<Iterator>::value_type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::iterator_traits<Iterator>::pointer,
			typename std::iterator_traits<Iterator>::reference
		>
	{
	public:
		typedef Predicate predicate_type;
		typedef Iterator iterator_type;
		typedef typename std::conditional<
			std::is_convertible<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value,
			std::bidirectional_iterator_tag,
			typename std::iterator_traits<Iterator>::iterator_category
		>::type iterator_category;
		typedef typename std::iterator_traits<Iterator>::value_type value_type;
		typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename std::iterator_traits<Iterator>::pointer pointer;
		typedef typename std::iterator_traits<Iterator>::reference reference;
	private:
		struct private_constructor_tag {};
	private:
		static SPROUT_CONSTEXPR iterator_type find_next(iterator_type first, iterator_type last, predicate_type pred) {
			return sprout::find_if(first, last, pred);
		}
		static SPROUT_CONSTEXPR iterator_type find_prev(iterator_type first, predicate_type pred) {
			return pred(*first) ? first
				: find_prev(sprout::prev(first), pred)
				;
		}
	protected:
		iterator_type current;
		iterator_type last;
		predicate_type pred;
	private:
		void satisfy_predicate() {
			while (current != last && !pred(*current)) {
				++current;
			}
		}
		void satisfy_predicate_backward() {
			while (!pred(*current)) {
				--current;
			}
		}
		SPROUT_CONSTEXPR filter_iterator(predicate_type pred, iterator_type it, iterator_type last, private_constructor_tag)
			: current(it)
			, last(last)
			, pred(pred)
		{}
		public:
		filter_iterator() = default;
		filter_iterator(filter_iterator const&) = default;
		SPROUT_CONSTEXPR filter_iterator(predicate_type pred, iterator_type it, iterator_type last = iterator_type())
			: current(find_next(it, last, pred))
			, last(last)
			, pred(pred)
		{}
		template<typename U>
		SPROUT_CONSTEXPR filter_iterator(filter_iterator<Predicate, U> const& it)
			: current(it.current)
			, last(it.last)
			, pred(it.pred)
		{}
		template<typename U>
		filter_iterator& operator=(filter_iterator<Predicate, U> const& it) {
			filter_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR iterator_type end() const {
			return last;
		}
		SPROUT_CONSTEXPR predicate_type predicate() const {
			return pred;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return *current;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*current;
		}

		filter_iterator& operator++() {
			++current;
			satisfy_predicate();
			return *this;
		}
		filter_iterator operator++(int) {
			filter_iterator result(*this);
			++current;
			satisfy_predicate();
			return result;
		}
		filter_iterator& operator--() {
			--current;
			satisfy_predicate_backward();
			return *this;
		}
		filter_iterator operator--(int) {
			filter_iterator temp(*this);
			--current;
			satisfy_predicate_backward();
			return temp;
		}
		SPROUT_CONSTEXPR filter_iterator next() const {
			return filter_iterator(pred, find_next(sprout::next(current), last, pred), last, private_constructor_tag());
		}
		SPROUT_CONSTEXPR filter_iterator prev() const {
			return filter_iterator(pred, find_prev(sprout::prev(current), pred), last, private_constructor_tag());
		}
		void swap(filter_iterator& other)
		SPROUT_NOEXCEPT_EXPR(
			SPROUT_NOEXCEPT_EXPR(sprout::swap(current, other.current))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(last, other.last))
			&& SPROUT_NOEXCEPT_EXPR(sprout::swap(pred, other.pred))
			)
		{
			sprout::swap(current, other.current);
			sprout::swap(last, other.last);
			sprout::swap(pred, other.pred);
		}
	};

	template<typename Predicate, typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::filter_iterator<Predicate, Iterator1> const& lhs,
		sprout::filter_iterator<Predicate, Iterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base();
	}
	template<typename Predicate, typename Iterator1, typename Iterator2>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::filter_iterator<Predicate, Iterator1> const& lhs,
		sprout::filter_iterator<Predicate, Iterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}

	//
	// make_filter_iterator
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::filter_iterator<Predicate, Iterator>
	make_filter_iterator(Predicate pred, Iterator it, Iterator last = Iterator()) {
		return sprout::filter_iterator<Predicate, Iterator>(pred, it, last);
	}

	//
	// swap
	//
	template<typename Predicate, typename Iterator>
	inline void
	swap(sprout::filter_iterator<Predicate, Iterator>& lhs, sprout::filter_iterator<Predicate, Iterator>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::filter_iterator<Predicate, Iterator>
	iterator_next(sprout::filter_iterator<Predicate, Iterator> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Predicate, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::filter_iterator<Predicate, Iterator>
	iterator_prev(sprout::filter_iterator<Predicate, Iterator> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// SPROUT_ITERATOR_FILTER_ITERATOR_HPP
