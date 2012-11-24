#ifndef SPROUT_ITERATOR_GENERATOR_ITERATOR_HPP
#define SPROUT_ITERATOR_GENERATOR_ITERATOR_HPP

#include <cstddef>
#include <limits>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include <sprout/config.hpp>
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
		difference_type count_;
	public:
		SPROUT_CONSTEXPR generator_iterator()
			: gen_(), count_()
		{}
		explicit SPROUT_CONSTEXPR generator_iterator(
			generator_type const& gen,
			difference_type count = std::numeric_limits<difference_type>::max()
			)
			: gen_(gen), count_(count)
		{}
		generator_type& generator() {
			return gen_;
		}
		SPROUT_CONSTEXPR generator_type const& generator() const {
			return gen_;
		}
		SPROUT_CONSTEXPR difference_type count() const {
			return count_;
		}
		SPROUT_CONSTEXPR generator_iterator operator()() const {
			return count_ != 0
				? generator_iterator(sprout::generators::next_generator(gen_)(), count_ > 0 ? count_ - 1 : count_)
				: throw std::out_of_range("generator_iterator<>: increment at out of range")
				;
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
		void swap(generator_iterator& other)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(sprout::swap(gen_, other.gen_)))
		{
			sprout::swap(gen_, other.gen_);
			sprout::swap(count_, other.count_);
		}
		friend SPROUT_CONSTEXPR bool operator==(generator_iterator const& lhs, generator_iterator const& rhs) {
			return lhs.count_ == rhs.count_;
		}
		friend SPROUT_CONSTEXPR bool operator!=(generator_iterator const& lhs, generator_iterator const& rhs) {
			return !(lhs == rhs);
		}
		friend SPROUT_CONSTEXPR bool operator<(generator_iterator const& lhs, generator_iterator const& rhs) {
			typedef typename std::make_unsigned<difference_type>::type unsigned_type;
			return static_cast<unsigned_type>(lhs.count_) > static_cast<unsigned_type>(rhs.count_);
		}
		friend SPROUT_CONSTEXPR bool operator>(generator_iterator const& lhs, generator_iterator const& rhs) {
			return rhs < lhs;
		}
		friend SPROUT_CONSTEXPR bool operator<=(generator_iterator const& lhs, generator_iterator const& rhs) {
			return !(rhs < lhs);
		}
		friend SPROUT_CONSTEXPR bool operator>=(generator_iterator const& lhs, generator_iterator const& rhs) {
			return !(lhs < rhs);
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return count_ != 0
				? sprout::generators::generated_value(gen_)
				: (
					throw std::out_of_range("generator_iterator<>: dereference at out of range"),
					sprout::generators::generated_value(gen_)
					)
				;
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &*(*this);
		}
		generator_iterator& operator++() {
			generator_iterator temp((*this)());
			temp.swap(*this);
			return *this;
		}
		generator_iterator operator++(int) {
			generator_iterator result(*this);
			++*this;
			return result;
		}
		friend SPROUT_CONSTEXPR difference_type operator-(generator_iterator const& lhs, generator_iterator const& rhs) {
			return rhs.count_ - lhs.count_;
		}
	};

	//
	// swap
	//
	template<typename Generator>
	inline void
	swap(sprout::generator_iterator<Generator>& lhs, sprout::generator_iterator<Generator>& rhs)
	SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// iterator_distance
	//
	template<typename Generator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<sprout::generator_iterator<Generator> >::difference_type
	iterator_distance(sprout::generator_iterator<Generator> first, sprout::generator_iterator<Generator> last) {
		return last - first;
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

#endif // #ifndef SPROUT_ITERATOR_GENERATOR_ITERATOR_HPP
