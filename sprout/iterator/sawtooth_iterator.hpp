/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_SAWTOOTH_ITERATOR_HPP
#define SPROUT_ITERATOR_SAWTOOTH_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/iterator/iterator.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>
#include <sprout/utility/swap.hpp>
#include <sprout/numeric/dft/detail/sawtooth.hpp>

namespace sprout {
	//
	// sawtooth_iterator
	//
	template<typename Value>
	class sawtooth_iterator
		: public sprout::iterator<
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
	private:
		explicit SPROUT_CONSTEXPR sawtooth_iterator(sawtooth_iterator const& other, difference_type index)
			: index_(index)
			, frequency_(other.frequency_)
			, amplitude_(other.amplitude_)
			, phase_(other.phase_)
		{}
	public:
		SPROUT_CONSTEXPR sawtooth_iterator()
			: index_()
			, frequency_(1)
			, amplitude_(1)
			, phase_(0)
		{}
		sawtooth_iterator(sawtooth_iterator const&) = default;
		explicit SPROUT_CONSTEXPR sawtooth_iterator(
			difference_type index,
			value_type const& frequency = 1,
			value_type const& amplitude = 1,
			value_type const& phase = 0
			)
			: index_(index)
			, frequency_(frequency)
			, amplitude_(amplitude)
			, phase_(phase)
		{}
		template<typename U>
		SPROUT_CONSTEXPR sawtooth_iterator(sawtooth_iterator<U> const& it)
			: index_(it.index_)
			, frequency_(it.frequency_)
			, amplitude_(it.amplitude_)
			, phase_(it.phase_)
		{}
		template<typename U>
		SPROUT_CXX14_CONSTEXPR sawtooth_iterator& operator=(sawtooth_iterator<U> const& it) {
			sawtooth_iterator temp(it);
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
			return amplitude_ == 0 ? 0
				: sprout::detail::sawtooth_value(frequency_, amplitude_, phase_, index_)
				;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &operator*()();
		}
		SPROUT_CXX14_CONSTEXPR sawtooth_iterator& operator++() {
			++index_;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR sawtooth_iterator operator++(int) {
			sawtooth_iterator result(*this);
			++index_;
			return result;
		}
		SPROUT_CXX14_CONSTEXPR sawtooth_iterator& operator--() {
			--index_;
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR sawtooth_iterator operator--(int) {
			sawtooth_iterator temp(*this);
			--index_;
			return temp;
		}
		SPROUT_CONSTEXPR sawtooth_iterator operator+(difference_type n) const {
			return sawtooth_iterator(*this, index_ + n);
		}
		SPROUT_CONSTEXPR sawtooth_iterator operator-(difference_type n) const {
			return sawtooth_iterator(*this, index_ - n);
		}
		SPROUT_CXX14_CONSTEXPR sawtooth_iterator& operator+=(difference_type n) {
			sawtooth_iterator temp(*this, index_ + n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR sawtooth_iterator& operator-=(difference_type n) {
			sawtooth_iterator temp(*this, index_ - n);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return amplitude_ == 0 ? 0
				: sprout::detail::sawtooth_value(frequency_, amplitude_, phase_, index_ + n)
				;
		}
		SPROUT_CONSTEXPR sawtooth_iterator next() const {
			return sawtooth_iterator(*this, index_ + 1);
		}
		SPROUT_CONSTEXPR sawtooth_iterator prev() const {
			return sawtooth_iterator(*this, index_ - 1);
		}
		SPROUT_CXX14_CONSTEXPR void swap(sawtooth_iterator& other) SPROUT_NOEXCEPT {
			sprout::swap(index_, other.index_);
			sprout::swap(frequency_, other.frequency_);
			sprout::swap(amplitude_, other.amplitude_);
			sprout::swap(phase_, other.phase_);
		}
	};

	template<typename Value1, typename Value2>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::sawtooth_iterator<Value1> const& lhs, sprout::sawtooth_iterator<Value2> const& rhs) {
		return lhs.index() == rhs.index();
	}
	template<typename Value1, typename Value2>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::sawtooth_iterator<Value1> const& lhs, sprout::sawtooth_iterator<Value2> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Value1, typename Value2>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::sawtooth_iterator<Value1> const& lhs, sprout::sawtooth_iterator<Value2> const& rhs) {
		return lhs.index() < rhs.index();
	}
	template<typename Value1, typename Value2>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::sawtooth_iterator<Value1> const& lhs, sprout::sawtooth_iterator<Value2> const& rhs) {
		return rhs < lhs;
	}
	template<typename Value1, typename Value2>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::sawtooth_iterator<Value1> const& lhs, sprout::sawtooth_iterator<Value2> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Value1, typename Value2>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::sawtooth_iterator<Value1> const& lhs, sprout::sawtooth_iterator<Value2> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Value1, typename Value2>
	inline SPROUT_CONSTEXPR typename sprout::sawtooth_iterator<Value1>::difference_type
	operator-(sprout::sawtooth_iterator<Value1> const& lhs, sprout::sawtooth_iterator<Value2> const& rhs) {
		return lhs.index() - rhs.index();
	}
	template<typename Value>
	inline SPROUT_CONSTEXPR sprout::sawtooth_iterator<Value>
	operator+(typename sprout::sawtooth_iterator<Value>::difference_type n, sprout::sawtooth_iterator<Value> const& it) {
		return it + n;
	}

	//
	// swap
	//
	template<typename Value>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::sawtooth_iterator<Value>& lhs, sprout::sawtooth_iterator<Value>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Value>
	inline SPROUT_CONSTEXPR sprout::sawtooth_iterator<Value>
	iterator_next(sprout::sawtooth_iterator<Value> const& it) {
		return it.next();
	}

	//
	// iterator_prev
	//
	template<typename Value>
	inline SPROUT_CONSTEXPR sprout::sawtooth_iterator<Value>
	iterator_prev(sprout::sawtooth_iterator<Value> const& it) {
		return it.prev();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_SAWTOOTH_ITERATOR_HPP
