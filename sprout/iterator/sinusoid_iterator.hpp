#ifndef SPROUT_ITERATOR_SINUSOID_ITERATOR_HPP
#define SPROUT_ITERATOR_SINUSOID_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>

namespace sprout {
	//
	// sinusoid_iterator
	//
	template<typename Value>
	class sinusoid_iterator
		: public std::iterator<
			std::random_access_iterator_tag,
			Value,
			std::ptrdiff_t,
			Value*,
			Value
		>
	{
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef Value value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type reference;
	private:
		difference_type index_;
		value_type frequency_;
		value_type amplitude_;
		value_type phase_;
		value_type d_;
	private:
		explicit SPROUT_CONSTEXPR sinusoid_iterator(sinusoid_iterator const& other, difference_type index)
			: index_(index)
			, frequency_(other.frequency_)
			, amplitude_(other.amplitude_)
			, phase_(other.phase_)
			, d_(other.d_)
		{}
	public:
		SPROUT_CONSTEXPR sinusoid_iterator()
			: index_()
			, frequency_(1)
			, amplitude_(1)
			, phase_(0)
			, d_(value_type(2) * sprout::math::pi<value_type>())
		{}
		sinusoid_iterator(sinusoid_iterator const&) = default;
		explicit SPROUT_CONSTEXPR sinusoid_iterator(
			difference_type index,
			value_type const& frequency = 1,
			value_type const& amplitude = 1,
			value_type const& phase = 0
			)
			: index_(index)
			, frequency_(frequency)
			, amplitude_(amplitude)
			, phase_(phase)
			, d_(value_type(2) * sprout::math::pi<value_type>() * frequency)
		{}
		template<typename U>
		SPROUT_CONSTEXPR sinusoid_iterator(sinusoid_iterator<U> const& it)
			: index_(it.index_)
			, frequency_(it.frequency_)
			, amplitude_(it.amplitude_)
			, phase_(it.phase_)
			, d_(it.d_)
		{}
		template<typename U>
		sinusoid_iterator& operator=(sinusoid_iterator<U> const& it) {
			sinusoid_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR value_type const& frequency() const {
			return frequency_;
		}
		SPROUT_CONSTEXPR value_type const& amplitude() const {
			return amplitude_;
		}
		SPROUT_CONSTEXPR value_type const& phase() const {
			return phase_;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			using sprout::sin;
			return amplitude_ * sin(d_ * value_type(index_) + phase_);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &operator*()();
		}
		sinusoid_iterator& operator++() {
			++index_;
			return *this;
		}
		sinusoid_iterator operator++(int) {
			sinusoid_iterator result(*this);
			++index_;
			return result;
		}
		sinusoid_iterator& operator--() {
			--index_;
			return *this;
		}
		sinusoid_iterator operator--(int) {
			sinusoid_iterator temp(*this);
			--index_;
			return temp;
		}
		SPROUT_CONSTEXPR sinusoid_iterator operator+(difference_type n) const {
			return sinusoid_iterator(*this, index_ + n);
		}
		SPROUT_CONSTEXPR sinusoid_iterator operator-(difference_type n) const {
			return sinusoid_iterator(*this, index_ - n);
		}
		sinusoid_iterator& operator+=(difference_type n) {
			sinusoid_iterator temp(*this, index_ + n);
			temp.swap(*this);
			return *this;
		}
		sinusoid_iterator& operator-=(difference_type n) {
			sinusoid_iterator temp(*this, index_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			using sprout::sin;
			return amplitude_ * sin(d_ * value_type(index_ + n) + phase_);
		}
		SPROUT_CONSTEXPR sinusoid_iterator next() const {
			return sinusoid_iterator(*this, index_ + 1);
		}
		SPROUT_CONSTEXPR sinusoid_iterator prev() const {
			return sinusoid_iterator(*this, index_ - 1);
		}
		void swap(sinusoid_iterator& other) {
			using std::swap;
			swap(index_, other.index_);
			swap(frequency_, other.frequency_);
			swap(amplitude_, other.amplitude_);
			swap(phase_, other.phase_);
			swap(d_, other.d_);
		}
	};

	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator==(
		sprout::sinusoid_iterator<Value1> const& lhs,
		sprout::sinusoid_iterator<Value2> const& rhs
		)
	{
		return lhs.index() == rhs.index();
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator!=(
		sprout::sinusoid_iterator<Value1> const& lhs,
		sprout::sinusoid_iterator<Value2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator<(
		sprout::sinusoid_iterator<Value1> const& lhs,
		sprout::sinusoid_iterator<Value2> const& rhs
		)
	{
		return lhs.index() < rhs.index();
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator>(
		sprout::sinusoid_iterator<Value1> const& lhs,
		sprout::sinusoid_iterator<Value2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator<=(
		sprout::sinusoid_iterator<Value1> const& lhs,
		sprout::sinusoid_iterator<Value2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR bool operator>=(
		sprout::sinusoid_iterator<Value1> const& lhs,
		sprout::sinusoid_iterator<Value2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<typename Value1, typename Value2>
	SPROUT_CONSTEXPR typename sprout::sinusoid_iterator<Value1>::difference_type operator-(
		sprout::sinusoid_iterator<Value1> const& lhs,
		sprout::sinusoid_iterator<Value2> const& rhs
		)
	{
		return lhs.index() - rhs.index();
	}
	template<typename Value>
	SPROUT_CONSTEXPR sprout::sinusoid_iterator<Value> operator+(
		typename sprout::sinusoid_iterator<Value>::difference_type n,
		sprout::sinusoid_iterator<Value> const& it
		)
	{
		return it + n;
	}

	//
	// swap
	//
	template<typename Value>
	void swap(sprout::sinusoid_iterator<Value>& lhs, sprout::sinusoid_iterator<Value>& rhs) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}

	//
	// next
	//
	template<typename Value>
	SPROUT_CONSTEXPR sprout::sinusoid_iterator<Value> next(
		sprout::sinusoid_iterator<Value> const& it
		)
	{
		return it.next();
	}
	template<typename Value>
	SPROUT_CONSTEXPR sprout::sinusoid_iterator<Value> next(
		sprout::sinusoid_iterator<Value> const& it,
		typename sprout::sinusoid_iterator<Value>::difference_type n
		)
	{
		return it + n;
	}

	//
	// prev
	//
	template<typename Value>
	SPROUT_CONSTEXPR sprout::sinusoid_iterator<Value> prev(
		sprout::sinusoid_iterator<Value> const& it
		)
	{
		return it.prev();
	}
	template<typename Value>
	SPROUT_CONSTEXPR sprout::sinusoid_iterator<Value> prev(
		sprout::sinusoid_iterator<Value> const& it,
		typename sprout::sinusoid_iterator<Value>::difference_type n
		)
	{
		return it - n;
	}

	//
	// distance
	//
	template<typename Value>
	SPROUT_CONSTEXPR typename std::iterator_traits<sprout::sinusoid_iterator<Value> >::difference_type
	distance(
		sprout::sinusoid_iterator<Value> first,
		sprout::sinusoid_iterator<Value> last
		)
	{
		return last - first;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_SINUSOID_ITERATOR_HPP
