/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_AMPLITUDE_SPECTRUM_ITERATOR_HPP
#define SPROUT_ITERATOR_AMPLITUDE_SPECTRUM_ITERATOR_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/transform_iterator.hpp>
#include <sprout/numeric/dft/amplitude_spectrum_value.hpp>

namespace sprout {
	//
	// amplitude_value
	//
	template<typename T = void>
	class amplitude_value {
	public:
		typedef typename T::value_type result_type;
		typedef T argument_type;
	public:
		SPROUT_CONSTEXPR typename T::value_type
		operator()(T const& value) const {
			return sprout::amplitude_spectrum_value(value);
		}
	};
	template<>
	class amplitude_value<void> {
	public:
		template<typename T>
		SPROUT_CONSTEXPR typename T::value_type
		operator()(T const& value) const {
			return sprout::amplitude_spectrum_value(value);
		}
	};

	//
	// make_amplitude_spectrum_iterator
	//
	template<typename Iterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<sprout::amplitude_value<typename std::iterator_traits<Iterator>::value_type>, Iterator>
	make_amplitude_spectrum_iterator(Iterator it) {
		return sprout::transform_iterator<sprout::amplitude_value<typename std::iterator_traits<Iterator>::value_type>, Iterator>(
			it, sprout::amplitude_value<typename std::iterator_traits<Iterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_AMPLITUDE_SPECTRUM_ITERATOR_HPP
