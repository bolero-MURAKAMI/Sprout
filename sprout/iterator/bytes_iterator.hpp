#ifndef SPROUT_ITERATOR_BYTES_ITERATOR_HPP
#define SPROUT_ITERATOR_BYTES_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/endian_traits.hpp>

namespace sprout {
	//
	// bytes_iterator
	//
	template<
		typename Iterator,
		typename Traits = sprout::endian_traits<typename std::iterator_traits<Iterator>::value_type>
	>
	class bytes_iterator
		: public std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			unsigned char,
			std::ptrdiff_t,
			void,
			unsigned char
		>
	{
	public:
		typedef Iterator base_type;
		typedef Traits traits_type;
	private:
		typedef std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			unsigned char,
			std::ptrdiff_t,
			void,
			unsigned char
		> iterator_type;
	public:
		typedef typename iterator_type::iterator_category iterator_category;
		typedef typename iterator_type::value_type value_type;
		typedef typename iterator_type::difference_type difference_type;
		typedef typename iterator_type::pointer pointer;
		typedef typename iterator_type::reference reference;
	private:
		struct next_tag {};
		struct prev_tag {};
		struct ra_tag {};
	private:
		base_type it_;
		difference_type i_;
	private:
		SPROUT_CONSTEXPR bytes_iterator(base_type it, difference_type i)
			: it_(it)
			, i_(i)
		{}
		SPROUT_CONSTEXPR bytes_iterator(base_type it, difference_type i, next_tag)
			: it_(i / traits_type::size() == 0 ? it : sprout::next(it))
			, i_(i % traits_type::size())
		{}
		SPROUT_CONSTEXPR bytes_iterator(base_type it, difference_type i, prev_tag)
			: it_((i + 1 - traits_type::size()) / traits_type::size() == 0 ? it : sprout::prev(it))
			, i_(i % traits_type::size() + traits_type::size())
		{}
		SPROUT_CONSTEXPR bytes_iterator(base_type it, difference_type i, ra_tag)
			: it_(i >= 0
				? sprout::next(it, i / traits_type::size())
				: sprout::next(it, (i + 1 - traits_type::size()) / traits_type::size())
				)
			, i_(i >= 0
				? i % traits_type::size()
				: i % traits_type::size() + traits_type::size()
				)
		{}
	public:
		SPROUT_CONSTEXPR bytes_iterator()
			: it_()
			, i_()
		{}
		bytes_iterator(bytes_iterator const&) = default;
		explicit SPROUT_CONSTEXPR bytes_iterator(base_type it)
			: it_(it)
			, i_()
		{}
		SPROUT_CONSTEXPR bytes_iterator next() const {
			return bytes_iterator(it_, i_ + 1, next_tag());
		}
		SPROUT_CONSTEXPR bytes_iterator prev() const {
			return bytes_iterator(it_, i_ - 1, prev_tag());
		}
		void swap(bytes_iterator& other) {
			using std::swap;
			swap(it_, other.it_);
			swap(i_, other.i_);
		}
		friend SPROUT_CONSTEXPR bool operator==(bytes_iterator const& lhs, bytes_iterator const& rhs) {
			return lhs.it_ == rhs.it_ && lhs.i_ == rhs.i_;
		}
		friend SPROUT_CONSTEXPR bool operator!=(bytes_iterator const& lhs, bytes_iterator const& rhs) {
			return !(lhs == rhs);
		}
		friend SPROUT_CONSTEXPR bool operator<(bytes_iterator const& lhs, bytes_iterator const& rhs) {
			return lhs.it_ < rhs.it_ || (lhs.it_ == rhs.it_ && lhs.i_ < rhs.i_);
		}
		friend SPROUT_CONSTEXPR bool operator>(bytes_iterator const& lhs, bytes_iterator const& rhs) {
			return rhs < lhs;
		}
		friend SPROUT_CONSTEXPR bool operator<=(bytes_iterator const& lhs, bytes_iterator const& rhs) {
			return !(rhs < lhs);
		}
		friend SPROUT_CONSTEXPR bool operator>=(bytes_iterator const& lhs, bytes_iterator const& rhs) {
			return !(lhs < rhs);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return traits_type::get_byte(*it_, i_);
		}
		bytes_iterator& operator++() {
			bytes_iterator temp(next());
			temp.swap(*this);
			return *this;
		}
		bytes_iterator operator++(int) {
			bytes_iterator result(*this);
			++*this;
			return result;
		}
		bytes_iterator& operator--() {
			bytes_iterator temp(prev());
			temp.swap(*this);
			return *this;
		}
		bytes_iterator operator--(int) {
			bytes_iterator result(*this);
			--*this;
			return result;
		}
		SPROUT_CONSTEXPR bytes_iterator operator+(difference_type n) const {
			return bytes_iterator(it_, i_ + n, ra_tag());
		}
		SPROUT_CONSTEXPR bytes_iterator operator-(difference_type n) const {
			return bytes_iterator(it_, i_ - n, ra_tag());
		}
		bytes_iterator& operator+=(difference_type n) {
			bytes_iterator temp(it_, i_ + n, ra_tag());
			temp.swap(*this);
			return *this;
		}
		bytes_iterator& operator-=(difference_type n) {
			bytes_iterator temp(it_, i_ - n, ra_tag());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return *(*this + n);
		}
		friend SPROUT_CONSTEXPR difference_type operator-(bytes_iterator const& lhs, bytes_iterator const& rhs) {
			return (lhs.it_ - rhs.it_) * traits_type::size() + (lhs.i_ - rhs.i_);
		}
		friend SPROUT_CONSTEXPR bytes_iterator operator+(difference_type n, bytes_iterator const& it) {
			return it + n;
		}
	};

	//
	// make_bytes_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator> make_bytes_iterator(Iterator it) {
		return sprout::bytes_iterator<Iterator>(it);
	}
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits> make_bytes_iterator(Iterator it, Traits) {
		return sprout::bytes_iterator<Iterator, Traits>(it);
	}

	//
	// swap
	//
	template<typename Iterator, typename Traits>
	inline void swap(sprout::bytes_iterator<Iterator, Traits>& lhs, sprout::bytes_iterator<Iterator, Traits>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// distance
	//
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<sprout::bytes_iterator<Iterator, Traits> >::difference_type
	distance(
		sprout::bytes_iterator<Iterator, Traits> first,
		sprout::bytes_iterator<Iterator, Traits> last
		)
	{
		return last - first;
	}

	//
	// iterator_next
	//
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits> iterator_next(
		sprout::bytes_iterator<Iterator, Traits> const& it
		)
	{
		return it.next();
	}
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits> iterator_next(
		sprout::bytes_iterator<Iterator, Traits> const& it,
		typename sprout::bytes_iterator<Iterator, Traits>::difference_type n
		)
	{
		return it + n;
	}

	//
	// iterator_prev
	//
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits> iterator_prev(
		sprout::bytes_iterator<Iterator, Traits> const& it
		)
	{
		return it.prev();
	}
	template<typename Iterator, typename Traits>
	inline SPROUT_CONSTEXPR sprout::bytes_iterator<Iterator, Traits> iterator_prev(
		sprout::bytes_iterator<Iterator, Traits> const& it,
		typename sprout::bytes_iterator<Iterator, Traits>::difference_type n
		)
	{
		return it - n;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_BYTES_ITERATOR_HPP
