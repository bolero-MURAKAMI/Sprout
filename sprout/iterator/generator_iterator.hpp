/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_GENERATOR_ITERATOR_HPP
#define SPROUT_ITERATOR_GENERATOR_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>
#include <sprout/generator/functions.hpp>
#include <sprout/utility/swap.hpp>

namespace sprout {
	//
	// generator_iterator
	//
	template<typename Generator>
	class generator_iterator
		: public std::iterator<
			std::forward_iterator_tag,
			typename std::remove_reference<decltype(sprout::generators::generated_value(std::declval<Generator const>()))>::type,
			std::ptrdiff_t,
			typename std::remove_reference<decltype(sprout::generators::generated_value(std::declval<Generator const>()))>::type*,
			decltype(sprout::generators::generated_value(std::declval<Generator const>()))
		>
	{
	public:
		typedef Generator generator_type;
		typedef std::forward_iterator_tag iterator_category;
		typedef decltype(sprout::generators::generated_value(std::declval<Generator const>())) reference;
		typedef typename std::remove_reference<reference>::type value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type* pointer;
	private:
		generator_type gen_;
		difference_type index_;
	public:
		SPROUT_CONSTEXPR generator_iterator()
			: gen_(), index_()
		{}
		explicit SPROUT_CONSTEXPR generator_iterator(
			generator_type const& gen,
			difference_type index = sprout::numeric_limits<difference_type>::max()
			)
			: gen_(gen), index_(index)
		{}
		SPROUT_CXX14_CONSTEXPR generator_type& generator() {
			return gen_;
		}
		SPROUT_CONSTEXPR generator_type const& generator() const {
			return gen_;
		}
		SPROUT_CONSTEXPR difference_type index() const {
			return index_;
		}
		SPROUT_CONSTEXPR generator_iterator operator()() const {
			return generator_iterator(sprout::generators::next_generator(gen_)(), index_ - 1);
		}
		SPROUT_CONSTEXPR generator_iterator next() const {
			return (*this)();
		}
		SPROUT_CONSTEXPR reference generated_value() const {
			return sprout::generators::generated_value(gen_);
		}
		SPROUT_CONSTEXPR generator_iterator next_generator() const {
			return (*this)();
		}
		SPROUT_CONSTEXPR operator reference() const {
			return generated_value();
		}
		SPROUT_CXX14_CONSTEXPR void swap(generator_iterator& other)
		SPROUT_NOEXCEPT_IF_EXPR(sprout::swap(gen_, other.gen_))
		{
			sprout::swap(gen_, other.gen_);
			sprout::swap(index_, other.index_);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return sprout::generators::generated_value(gen_);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		SPROUT_CXX14_CONSTEXPR generator_iterator& operator++() {
			generator_iterator temp((*this)());
			temp.swap(*this);
			return *this;
		}
		SPROUT_CXX14_CONSTEXPR generator_iterator operator++(int) {
			generator_iterator result(*this);
			++*this;
			return result;
		}
	};

	template<typename Generator>
	inline SPROUT_CONSTEXPR bool
	operator==(sprout::generator_iterator<Generator> const& lhs, sprout::generator_iterator<Generator> const& rhs) {
		return lhs.index() == rhs.index();
	}
	template<typename Generator>
	inline SPROUT_CONSTEXPR bool
	operator!=(sprout::generator_iterator<Generator> const& lhs, sprout::generator_iterator<Generator> const& rhs) {
		return !(lhs == rhs);
	}
	template<typename Generator>
	inline SPROUT_CONSTEXPR bool
	operator<(sprout::generator_iterator<Generator> const& lhs, sprout::generator_iterator<Generator> const& rhs) {
		return rhs.index() < lhs.index();
	}
	template<typename Generator>
	inline SPROUT_CONSTEXPR bool
	operator>(sprout::generator_iterator<Generator> const& lhs, sprout::generator_iterator<Generator> const& rhs) {
		return rhs < lhs;
	}
	template<typename Generator>
	inline SPROUT_CONSTEXPR bool
	operator<=(sprout::generator_iterator<Generator> const& lhs, sprout::generator_iterator<Generator> const& rhs) {
		return !(rhs < lhs);
	}
	template<typename Generator>
	inline SPROUT_CONSTEXPR bool
	operator>=(sprout::generator_iterator<Generator> const& lhs, sprout::generator_iterator<Generator> const& rhs) {
		return !(lhs < rhs);
	}
	template<typename Generator>
	inline SPROUT_CONSTEXPR typename sprout::generator_iterator<Generator>::difference_type
	operator-(sprout::generator_iterator<Generator> const& lhs, sprout::generator_iterator<Generator> const& rhs) {
		return rhs.index() - lhs.index();
	}

	//
	// swap
	//
	template<typename Generator>
	inline SPROUT_CXX14_CONSTEXPR void
	swap(sprout::generator_iterator<Generator>& lhs, sprout::generator_iterator<Generator>& rhs)
	SPROUT_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_next
	//
	template<typename Generator>
	inline SPROUT_CONSTEXPR sprout::generator_iterator<Generator>
	iterator_next(sprout::generator_iterator<Generator> const& it) {
		return it.next();
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_GENERATOR_ITERATOR_HPP
