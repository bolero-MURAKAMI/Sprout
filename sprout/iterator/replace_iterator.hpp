#ifndef SPROUT_ITERATOR_REPLACE_ITERATOR_HPP
#define SPROUT_ITERATOR_REPLACE_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/transform_iterator.hpp>

namespace sprout {
	//
	// replace_value
	//
	template<typename T>
	class replace_value {
	public:
		typedef T result_type;
		typedef T const& argument_type;
	private:
		T old_;
		T new_;
	public:
		SPROUT_CONSTEXPR replace_value(T const& old_value, T const& new_value)
			: old_(old_value)
			, new_(new_value)
		{}
		SPROUT_CONSTEXPR T operator()(T const& value) const {
			return (value == old_) ? new_ : value;
		}
	};

	//
	// make_replace_iterator
	//
	template<typename T, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<sprout::replace_value<T>, Iterator>
	make_replace_iterator(Iterator it, T const& old_value, T const& new_value) {
		return sprout::transform_iterator<sprout::replace_value<T>, Iterator>(
			it, sprout::replace_value<T>(old_value, new_value)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_REPLACE_ITERATOR_HPP
