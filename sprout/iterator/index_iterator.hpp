#ifndef SPROUT_ITERATOR_INDEX_ITERATOR_HPP
#define SPROUT_ITERATOR_INDEX_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/fixed_container/traits.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/utility/value_holder.hpp>

namespace sprout {
	//
	// index_iterator
	//
	template<typename Container>
	class index_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			typename sprout::fixed_container_traits<typename std::decay<Container>::type>::value_type,
			typename sprout::fixed_container_traits<typename std::decay<Container>::type>::difference_type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<Container>::type>::value,
				typename sprout::fixed_container_traits<typename std::decay<Container>::type>::const_pointer,
				typename sprout::fixed_container_traits<typename std::decay<Container>::type>::pointer
			>::type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<Container>::type>::value,
				typename sprout::fixed_container_traits<typename std::decay<Container>::type>::const_reference,
				typename sprout::fixed_container_traits<typename std::decay<Container>::type>::reference
			>::type
		>
	{
	public:
		typedef Container container_type;
		typedef typename sprout::fixed_container_traits<typename std::decay<container_type>::type> traits_type;
		typedef typename std::conditional<
			std::is_reference<container_type>::value,
			typename std::decay<container_type>::type const&,
			typename std::decay<container_type>::type const
		>::type const_container_type;
	private:
		typedef std::iterator<
			std::random_access_iterator_tag,
			typename traits_type::value_type,
			typename traits_type::difference_type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<container_type>::type>::value,
				typename traits_type::const_pointer,
				typename traits_type::pointer
			>::type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<container_type>::type>::value,
				typename traits_type::const_reference,
				typename traits_type::reference
			>::type
		> base_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
		typedef typename traits_type::size_type size_type;
	private:
		sprout::value_holder<container_type> holder_;
		size_type index_;
	private:
		SPROUT_CONSTEXPR index_iterator(sprout::value_holder<container_type> const& r, size_type index)
			: holder_(r)
			, index_(index)
		{}
	public:
		SPROUT_CONSTEXPR index_iterator()
			: holder_()
			, index_()
		{}
		index_iterator(index_iterator const&) = default;
		SPROUT_CONSTEXPR index_iterator(typename sprout::value_holder<container_type>::param_type p, size_type index)
			: holder_(p)
			, index_(index)
		{}
		operator index_iterator<const_container_type>() const {
			return index_iterator<const_container_type>(holder_.get(), index_);
		}
		SPROUT_CONSTEXPR index_iterator next() const {
			return index_iterator(holder_, index_ + 1);
		}
		SPROUT_CONSTEXPR index_iterator prev() const {
			return index_iterator(holder_, index_ - 1);
		}
		void swap(index_iterator& other) {
			using std::swap;
			swap(holder_, other.holder_);
			swap(index_, other.index_);
		}
		friend SPROUT_CONSTEXPR bool operator==(index_iterator const& lhs, index_iterator const& rhs) {
			return lhs.index_ == rhs.index_;
		}
		friend SPROUT_CONSTEXPR bool operator!=(index_iterator const& lhs, index_iterator const& rhs) {
			return !(lhs == rhs);
		}
		friend SPROUT_CONSTEXPR bool operator<(index_iterator const& lhs, index_iterator const& rhs) {
			return lhs.index_ < rhs.index_;
		}
		friend SPROUT_CONSTEXPR bool operator>(index_iterator const& lhs, index_iterator const& rhs) {
			return rhs < lhs;
		}
		friend SPROUT_CONSTEXPR bool operator<=(index_iterator const& lhs, index_iterator const& rhs) {
			return !(rhs < lhs);
		}
		friend SPROUT_CONSTEXPR bool operator>=(index_iterator const& lhs, index_iterator const& rhs) {
			return !(lhs < rhs);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return holder_.get()[index_];
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &holder_.get()[index_];
		}
		index_iterator& operator++() {
			index_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		index_iterator operator++(int) {
			index_iterator result(*this);
			++*this;
			return result;
		}
		index_iterator& operator--() {
			index_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		index_iterator operator--(int) {
			index_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR index_iterator operator+(difference_type n) const {
			return index_iterator(holder_, index_ + n);
		}
		SPROUT_CONSTEXPR index_iterator operator-(difference_type n) const {
			return index_iterator(holder_, index_ - n);
		}
		index_iterator& operator+=(difference_type n) {
			index_iterator temp(holder_, index_ + n);
			temp.swap(this);
			return this;
		}
		index_iterator& operator-=(difference_type n) {
			index_iterator temp(holder_, index_ - n);
			temp.swap(this);
			return this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return holder_.get()[index_ + n];
		}
		friend SPROUT_CONSTEXPR difference_type operator-(index_iterator const& lhs, index_iterator const& rhs) {
			return static_cast<difference_type>(lhs.index_) - static_cast<difference_type>(rhs.index_);
		}
		friend SPROUT_CONSTEXPR index_iterator operator+(difference_type n, index_iterator const& it) {
			return it + n;
		}
	};

	//
	// swap
	//
	template<typename Container>
	void swap(sprout::index_iterator<Container>& lhs, sprout::index_iterator<Container>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// next
	//
	template<typename Container>
	SPROUT_CONSTEXPR sprout::index_iterator<Container> next(
		sprout::index_iterator<Container> const& it
		)
	{
		return it.next();
	}
	template<typename Container>
	SPROUT_CONSTEXPR sprout::index_iterator<Container> next(
		sprout::index_iterator<Container> const& it,
		typename sprout::index_iterator<Container>::difference_type n
		)
	{
		return it + n;
	}

	//
	// prev
	//
	template<typename Container>
	SPROUT_CONSTEXPR sprout::index_iterator<Container> prev(
		sprout::index_iterator<Container> const& it
		)
	{
		return it.prev();
	}
	template<typename Container>
	SPROUT_CONSTEXPR sprout::index_iterator<Container> prev(
		sprout::index_iterator<Container> const& it,
		typename sprout::index_iterator<Container>::difference_type n
		)
	{
		return it - n;
	}
}	// namespace sprout



#include <sprout/detail/iterator.hpp>

namespace sprout {
	//
	// distance
	//
	template<typename Container>
	SPROUT_CONSTEXPR typename std::iterator_traits<sprout::index_iterator<Container> >::difference_type distance(
		sprout::index_iterator<Container> first,
		sprout::index_iterator<Container> last
		)
	{
		return last - first;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_INDEX_ITERATOR_HPP
