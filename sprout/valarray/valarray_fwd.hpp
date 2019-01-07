/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VALARRAY_VALARRAY_FWD_HPP
#define SPROUT_VALARRAY_VALARRAY_FWD_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>

namespace sprout {
	//
	// valarray
	//
	template<typename T, std::size_t N>
	class valarray;

	//
	// slice
	//
	class slice;
	//
	// slice_array
	//
	template<typename T, std::size_t N>
	class slice_array;

	//
	// gslice
	//
	template<std::size_t N>
	class gslice;
	//
	// gslice_array
	//
	template<typename T, std::size_t N, std::size_t M>
	class gslice_array;

	//
	// mask_array
	//
	template<typename T, std::size_t N, std::size_t M>
	class mask_array;

	//
	// indirect_array
	//
	template<typename T, std::size_t N, std::size_t M>
	class indirect_array;

}	// namespace sprout

#endif	// #ifndef SPROUT_VALARRAY_VALARRAY_FWD_HPP
