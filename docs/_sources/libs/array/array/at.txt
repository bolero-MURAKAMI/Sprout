.. _sprout-array-array-at:
###############################################################################
at
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR reference at(size_type n);
  
  SPROUT_CONSTEXPR const_reference at(size_type n) const;

Returns
========================================

| The element at the specified position in the array.

Throws
========================================

| It throws std::out_of_range if n is out of bounds.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(input.at(5) == 6, "an element at position 5 is 6.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

