/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_PROPERTY_HPP
#define SPROUT_TYPE_TRAITS_PROPERTY_HPP

#include <sprout/config.hpp>
// 20.10.4.3 Type properties
#include <sprout/type_traits/is_const.hpp>
#include <sprout/type_traits/is_volatile.hpp>
#include <sprout/type_traits/is_trivial.hpp>
#include <sprout/type_traits/is_trivially_copyable.hpp>
#include <sprout/type_traits/is_standard_layout.hpp>
#include <sprout/type_traits/is_pod.hpp>
#include <sprout/type_traits/is_literal_type.hpp>
#include <sprout/type_traits/has_unique_object_representations.hpp>
#include <sprout/type_traits/is_empty.hpp>
#include <sprout/type_traits/is_polymorphic.hpp>
#include <sprout/type_traits/is_abstract.hpp>
#include <sprout/type_traits/is_final.hpp>
#include <sprout/type_traits/is_aggregate.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>
#include <sprout/type_traits/is_constructible.hpp>
#include <sprout/type_traits/is_default_constructible.hpp>
#include <sprout/type_traits/is_copy_constructible.hpp>
#include <sprout/type_traits/is_move_constructible.hpp>
#include <sprout/type_traits/is_assignable.hpp>
#include <sprout/type_traits/is_copy_assignable.hpp>
#include <sprout/type_traits/is_move_assignable.hpp>
#include <sprout/type_traits/is_swappable_with.hpp>
#include <sprout/type_traits/is_swappable.hpp>
#include <sprout/type_traits/is_destructible.hpp>
#include <sprout/type_traits/is_trivially_constructible.hpp>
#include <sprout/type_traits/is_trivially_default_constructible.hpp>
#include <sprout/type_traits/is_trivially_copy_constructible.hpp>
#include <sprout/type_traits/is_trivially_move_constructible.hpp>
#include <sprout/type_traits/is_trivially_assignable.hpp>
#include <sprout/type_traits/is_trivially_copy_assignable.hpp>
#include <sprout/type_traits/is_trivially_move_assignable.hpp>
#include <sprout/type_traits/is_trivially_destructible.hpp>
#include <sprout/type_traits/is_nothrow_constructible.hpp>
#include <sprout/type_traits/is_nothrow_default_constructible.hpp>
#include <sprout/type_traits/is_nothrow_copy_constructible.hpp>
#include <sprout/type_traits/is_nothrow_move_constructible.hpp>
#include <sprout/type_traits/is_nothrow_assignable.hpp>
#include <sprout/type_traits/is_nothrow_copy_assignable.hpp>
#include <sprout/type_traits/is_nothrow_move_assignable.hpp>
#include <sprout/type_traits/is_nothrow_swappable_with.hpp>
#include <sprout/type_traits/is_nothrow_swappable.hpp>
#include <sprout/type_traits/is_nothrow_destructible.hpp>
#include <sprout/type_traits/has_virtual_destructor.hpp>

#include <sprout/type_traits/is_const_unqualified.hpp>
#include <sprout/type_traits/is_volatile_unqualified.hpp>
#include <sprout/type_traits/is_cv_unqualified.hpp>
#include <sprout/type_traits/is_sint.hpp>
#include <sprout/type_traits/is_uint.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/type_traits/is_c_str.hpp>
#include <sprout/type_traits/has_type.hpp>
#include <sprout/type_traits/has_value.hpp>

#endif	// #ifndef SPROUT_TYPE_TRAITS_PROPERTY_HPP
