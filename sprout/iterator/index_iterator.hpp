#ifndef SPROUT_ITERATOR_INDEX_ITERATOR_HPP
#define SPROUT_ITERATOR_INDEX_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/value_holder.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// index_iterator
	//
	template<typename Container>
	class index_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			typename sprout::container_traits<typename std::remove_reference<Container>::type>::value_type,
			typename sprout::container_traits<typename std::remove_reference<Container>::type>::difference_type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<Container>::type>::value,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::const_pointer,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::pointer
			>::type,
			typename std::conditional<
				std::is_const<typename std::remove_reference<Container>::type>::value,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::const_reference,
				typename sprout::container_traits<typename std::remove_reference<Container>::type>::reference
			>::type
		>
	{
	public:
		typedef Container container_type;
		typedef typename sprout::container_traits<typename std::remove_reference<container_type>::type> traits_type;
		typedef typename std::conditional<
			std::is_reference<container_type>::value,
			typename std::remove_reference<container_type>::type const&,
			typename std::remove_reference<container_type>::type const
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
		typedef sprout::value_holder<container_type> holder_type;
	public:
		typedef typename base_type::iterator_category iterator_category;
		typedef typename base_type::value_type value_type;
		typedef typename base_type::difference_type difference_type;
		typedef typename base_type::pointer pointer;
		typedef typename base_type::reference reference;
		typedef typename traits_type::size_type size_type;
	private:
		holder_type holder_;
		size_type index_;
	private:
		SPROUT_CONSTEXPR index_iterator(holder_type const& r, size_type index)
			: holder_(r)
			, index_(index)
		{}
	public:
		SPROUT_CONSTEXPR index_iterator()
			: holder_()
			, index_()
		{}
		index_iterator(index_iterator const&) = default;
		explicit SPROUT_CONSTEXPR index_iterator(typename holder_type::param_type p)
			: holder_(p)
			, index_(0)
		{}
		SPROUT_CONSTEXPR index_iterator(typename holder_type::param_type p, size_type index)
			: holder_(p)
			, index_(index)
		{}
		operator index_iterator<const_container_type>() const {
			return index_iterator<const_container_type>(holder_.get(), index_);
		}
		SPROUT_CONSTEXPR typename holder_type::mutable_or_const_reference base() const {
			return holder_.get();
		}
		SPROUT_CONSTEXPR size_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR index_iterator next() const {
			return index_iterator(holder_, index_ + 1);
		}
		SPROUT_CONSTEXPR index_iterator prev() const {
			return index_iterator(holder_, index_ - 1);
		}
		void swap(index_iterator& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(holder_, other.holder_)))
		{
			sprout::swap(holder_, other.holder_);
			sprout::swap(index_, other.index_);
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
			temp.swap(*this);
			return *this;
		}
		index_iterator& operator-=(difference_type n) {
			index_iterator temp(holder_, index_ - n);
			temp.swap(*this);
			return *this;
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
	inline void
	swap(sprout::index_iterator<Container>& lhs, sprout::index_iterator<Container>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// is_index_iterator
	//
	template<typename T>
	struct is_index_iterator
		: public std::false_type
	{};
	template<typename T>
	struct is_index_iterator<T const>
		: public sprout::is_index_iterator<T>
	{};
	template<typename T>
	struct is_index_iterator<T const volatile>
		: public sprout::is_index_iterator<T>
	{};
	template<typename Container>
	struct is_index_iterator<sprout::index_iterator<Container> >
		: public std::true_type
	{};

	//
	// iterator_distance
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<sprout::index_iterator<Container> >::difference_type
	iterator_distance(sprout::index_iterator<Container> first, sprout::index_iterator<Container> last) {
		return last - first;
	}

	//
	// iterator_next
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR sprout::index_iterator<Container>
	iterator_next(sprout::index_iterator<Container> const& it) {
		return it.next();
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR sprout::index_iterator<Container>
	iterator_next(
		sprout::index_iterator<Container> const& it,
		typename sprout::index_iterator<Container>::difference_type n
		)
	{
		return it + n;
	}

	//
	// iterator_prev
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR sprout::index_iterator<Container>
	iterator_prev(sprout::index_iterator<Container> const& it) {
		return it.prev();
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR sprout::index_iterator<Container>
	iterator_prev(
		sprout::index_iterator<Container> const& it,
		typename sprout::index_iterator<Container>::difference_type n
		)
	{
		return it - n;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_INDEX_ITERATOR_HPP
