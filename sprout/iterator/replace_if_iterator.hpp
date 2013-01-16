#ifndef SPROUT_ITERATOR_REPLACE_ITERATOR_HPP
#define SPROUT_ITERATOR_REPLACE_ITERATOR_HPP

#include <sprout/config.hpp>
#include <sprout/iterator/transform_iterator.hpp>

namespace sprout {
	//
	// replace_value_if
	//
	template<typename Predicate, typename T>
	class replace_value_if {
	public:
		typedef Predicate predicate_type;
		typedef T const& result_type;
		typedef T const& argument_type;
	private:
		Predicate pred_;
		T new_;
	public:
		SPROUT_CONSTEXPR replace_value_if(Predicate pred, T const& new_value)
			: pred_(pred)
			, new_(new_value)
		{}
		SPROUT_CONSTEXPR T operator()(T const& value) const {
			return pred_(value) ? new_ : value;
		}
	};

	//
	// make_replace_if_iterator
	//
	template<typename Predicate, typename T, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<sprout::replace_value_if<Predicate, T>, Iterator>
	make_replace_if_iterator(Iterator it, Predicate pred, T const& new_value) {
		return sprout::transform_iterator<sprout::replace_value_if<Predicate, T>, Iterator>(
			it, sprout::replace_value_if<Predicate, T>(pred, new_value)
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_REPLACE_ITERATOR_HPP
