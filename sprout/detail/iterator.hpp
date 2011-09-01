#ifndef SPROUT_DETAIL_ITERATOR_HPP
#define SPROUT_DETAIL_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include HDR_ITERATOR_SSCRISK_CEL_OR_SPROUT_DETAIL

namespace sprout {
	namespace detail {
		//
		// distance
		//
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type distance(
			Iterator first,
			Iterator last
			)
		{
			return first == last ? 0 : 1 + sprout::detail::distance(first + 1, last);
		}

		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type bidirectional_distance_impl(
			Iterator first1,
			Iterator first2,
			Iterator last,
			typename std::iterator_traits<Iterator>::difference_type current = 1
			)
		{
			return first1 == last
				? current
				: first2 == last
				? -current
				: sprout::detail::bidirectional_distance_impl(first1 + 1, first2 - 1, last, current + 1)
				;
		}
		//
		// bidirectional_distance
		//
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type bidirectional_distance(
			Iterator first,
			Iterator last
			)
		{
			return first == last ? 0 : sprout::detail::bidirectional_distance_impl(first + 1, first - 1, last);
		}

		//
		// reverse_iterator
		//
		template<typename Iterator>
		class reverse_iterator
			: public std::iterator<
				typename std::iterator_traits<Iterator>::iterator_category,
				typename std::iterator_traits<Iterator>::value_type,
				typename std::iterator_traits<Iterator>::difference_type,
				typename std::iterator_traits<Iterator>::pointer,
				typename std::iterator_traits<Iterator>::reference
			>
		{
		public:
			typedef Iterator iterator_type;
			typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
			typedef typename std::iterator_traits<iterator_type>::value_type value_type;
			typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
			typedef typename std::iterator_traits<iterator_type>::pointer pointer;
			typedef typename std::iterator_traits<iterator_type>::reference reference;
		protected:
			iterator_type current;
		private:
			iterator_type deref_tmp;
		public:
			reverse_iterator() = default;
			reverse_iterator(reverse_iterator const&) = default;
			SPROUT_CONSTEXPR explicit reverse_iterator(iterator_type it)
				: current(it)
				, deref_tmp(current - 1)
			{}
			template<typename U>
			SPROUT_CONSTEXPR reverse_iterator(reverse_iterator<U> const& it)
				: current(it)
				, deref_tmp(current - 1)
			{}
			template<typename U>
			reverse_iterator& operator=(const reverse_iterator<U>& it) {
				reverse_iterator temp(it);
				temp.swap(this);
				return this;
			}
			SPROUT_CONSTEXPR iterator_type base() const {
				return current;
			}
			SPROUT_CONSTEXPR reference operator*() const {
				return *deref_tmp;
			}
			SPROUT_CONSTEXPR pointer operator->() const {
				return &*deref_tmp;
			}
			reverse_iterator& operator++() {
				--current;
				--deref_tmp;
				return this;
			}
			reverse_iterator operator++(int) {
				reverse_iterator result(this);
				--current;
				--deref_tmp;
				return result;
			}
			reverse_iterator& operator--() {
				++current;
				++deref_tmp;
				return this;
			}
			reverse_iterator operator--(int) {
				reverse_iterator temp(this);
				++current;
				++deref_tmp;
				return temp;
			}
			SPROUT_CONSTEXPR reverse_iterator operator+(difference_type n) const {
				return reverse_iterator(current - n);
			}
			SPROUT_CONSTEXPR reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(current + n);
			}
			reverse_iterator& operator+=(difference_type n) {
				reverse_iterator temp(current - n);
				temp.swap(this);
				return this;
			}
			reverse_iterator& operator-=(difference_type n) {
				reverse_iterator temp(current + n);
				temp.swap(this);
				return this;
			}
			SPROUT_CONSTEXPR reference operator[](difference_type n) const {
				return *(deref_tmp - n);
			}
			void swap(reverse_iterator& other) {
				using std::swap;
				swap(current, other.current);
				swap(deref_tmp, other.deref_tmp);
			}
		};
		template <typename Iterator1, typename Iterator2>
		SPROUT_CONSTEXPR bool operator==(
			sprout::detail::reverse_iterator<Iterator1> const& lhs,
			sprout::detail::reverse_iterator<Iterator2> const& rhs
			)
		{
			return lhs.base() == rhs.base();
		}
		template <typename Iterator1, typename Iterator2>
		SPROUT_CONSTEXPR bool operator!=(
			sprout::detail::reverse_iterator<Iterator1> const& lhs,
			sprout::detail::reverse_iterator<Iterator2> const& rhs
			)
		{
			return !(lhs == rhs);
		}
		template <typename Iterator>
		SPROUT_CONSTEXPR sprout::detail::reverse_iterator<Iterator> operator+(
			typename sprout::detail::reverse_iterator<Iterator>::difference_type n,
			sprout::detail::reverse_iterator<Iterator> const& it
			)
		{
			return it + n;
		}

		//
		// swap
		//
		template<typename Iterator>
		void swap(sprout::detail::reverse_iterator<Iterator>& lhs, sprout::detail::reverse_iterator<Iterator>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
			lhs.swap(rhs);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ITERATOR_HPP
