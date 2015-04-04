/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_STD_TYPE_TRAITS_HPP
#define SPROUT_TYPE_TRAITS_STD_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
// 20.10.3, helper class:
#include <sprout/type_traits/integral_constant.hpp>
// 20.10.4.1, primary type categories:
#include <sprout/type_traits/is_void.hpp>
#include <sprout/type_traits/is_null_pointer.hpp>
#include <sprout/type_traits/is_integral.hpp>
#include <sprout/type_traits/is_floating_point.hpp>
#include <sprout/type_traits/is_array.hpp>
#include <sprout/type_traits/is_pointer.hpp>
#include <sprout/type_traits/is_lvalue_reference.hpp>
#include <sprout/type_traits/is_rvalue_reference.hpp>
#include <sprout/type_traits/is_member_object_pointer.hpp>
#include <sprout/type_traits/is_member_function_pointer.hpp>
#include <sprout/type_traits/is_enum.hpp>
#include <sprout/type_traits/is_union.hpp>
#include <sprout/type_traits/is_class.hpp>
#include <sprout/type_traits/is_function.hpp>
// 20.10.4.2 Composite type traits
#include <sprout/type_traits/is_reference.hpp>
#include <sprout/type_traits/is_arithmetic.hpp>
#include <sprout/type_traits/is_fundamental.hpp>
#include <sprout/type_traits/is_object.hpp>
#include <sprout/type_traits/is_scalar.hpp>
#include <sprout/type_traits/is_compound.hpp>
#include <sprout/type_traits/is_member_pointer.hpp>
// 20.10.4.3 Type properties
#include <sprout/type_traits/is_const.hpp>
#include <sprout/type_traits/is_volatile.hpp>
#include <sprout/type_traits/is_trivial.hpp>
#include <sprout/type_traits/is_trivially_copyable.hpp>
#include <sprout/type_traits/is_standard_layout.hpp>
#include <sprout/type_traits/is_pod.hpp>
#include <sprout/type_traits/is_literal_type.hpp>
#include <sprout/type_traits/is_empty.hpp>
#include <sprout/type_traits/is_polymorphic.hpp>
#include <sprout/type_traits/is_abstract.hpp>
#include <sprout/type_traits/is_final.hpp>
#include <sprout/type_traits/is_signed.hpp>
#include <sprout/type_traits/is_unsigned.hpp>
#include <sprout/type_traits/is_constructible.hpp>
#include <sprout/type_traits/is_default_constructible.hpp>
#include <sprout/type_traits/is_copy_constructible.hpp>
#include <sprout/type_traits/is_move_constructible.hpp>
#include <sprout/type_traits/is_assignable.hpp>
#include <sprout/type_traits/is_copy_assignable.hpp>
#include <sprout/type_traits/is_move_assignable.hpp>
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
#include <sprout/type_traits/is_nothrow_destructible.hpp>
#include <sprout/type_traits/has_virtual_destructor.hpp>
// 20.10.5 Type property queries
#include <sprout/type_traits/alignment_of.hpp>
#include <sprout/type_traits/rank.hpp>
#include <sprout/type_traits/extent.hpp>
// 20.10.6 Relationships between types
#include <sprout/type_traits/is_same.hpp>
#include <sprout/type_traits/is_base_of.hpp>
#include <sprout/type_traits/is_convertible.hpp>
// 20.10.7.1 Const-volatile modifications
#include <sprout/type_traits/remove_const.hpp>
#include <sprout/type_traits/remove_volatile.hpp>
#include <sprout/type_traits/remove_cv.hpp>
#include <sprout/type_traits/add_const.hpp>
#include <sprout/type_traits/add_volatile.hpp>
#include <sprout/type_traits/add_cv.hpp>
// 20.10.7.2 Reference modifications
#include <sprout/type_traits/remove_reference.hpp>
#include <sprout/type_traits/add_lvalue_reference.hpp>
#include <sprout/type_traits/add_rvalue_reference.hpp>
// 20.10.7.3 Sign modifications
#include <sprout/type_traits/make_signed.hpp>
#include <sprout/type_traits/make_unsigned.hpp>
// 20.10.7.4 Array modifications
#include <sprout/type_traits/remove_extent.hpp>
#include <sprout/type_traits/remove_all_extents.hpp>
// 20.10.7.5 Pointer modifications
#include <sprout/type_traits/remove_pointer.hpp>
#include <sprout/type_traits/add_pointer.hpp>
// 20.10.7.6 Other transformations
#include <sprout/type_traits/aligned_storage.hpp>
#include <sprout/type_traits/aligned_union.hpp>
#include <sprout/type_traits/decay.hpp>
#include <sprout/type_traits/enable_if.hpp>
#include <sprout/type_traits/conditional.hpp>
#include <sprout/type_traits/common_type.hpp>
#include <sprout/type_traits/underlying_type.hpp>
#include <sprout/type_traits/result_of.hpp>

#endif	// #ifndef SPROUT_TYPE_TRAITS_STD_TYPE_TRAITS_HPP
