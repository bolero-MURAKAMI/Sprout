.. _sprout-array-array-front:
###############################################################################
front
###############################################################################

Interface
========================================
.. sourcecode:: c++

  reference front();
  
  SPROUT_CONSTEXPR const_reference front() const;

Returns
========================================

| A reference to the first element in the array.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(input.front() == 1, "a first element is 1.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

