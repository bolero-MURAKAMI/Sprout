#ifndef SPROUT_ITERATOR_PHASE_SPECTRUM_ITERATOR_HPP
#define SPROUT_ITERATOR_PHASE_SPECTRUM_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/numeric/dft/phase_spectrum_value.hpp>

namespace sprout {
	//
	// phase_value
	//
	template<typename T>
	class phase_value {
	public:
		typedef typename T::value_type result_type;
		typedef T argument_type;
	public:
		SPROUT_CONSTEXPR phase_value() {}
		SPROUT_CONSTEXPR typename T::value_type operator()(T const& value) const {
			return sprout::phase_spectrum_value(value);
		}
	};

	//
	// make_phase_spectrum_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<sprout::phase_value<typename std::iterator_traits<Iterator>::value_type>, Iterator>
	make_phase_spectrum_iterator(Iterator it) {
		return sprout::transform_iterator<sprout::phase_value<typename std::iterator_traits<Iterator>::value_type>, Iterator>(
			it, sprout::phase_value<typename std::iterator_traits<Iterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_PHASE_SPECTRUM_ITERATOR_HPP
