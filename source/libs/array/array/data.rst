.. _sprout-array-array-data:
###############################################################################
data
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR pointer data() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_pointer data() const SPROUT_NOEXCEPT;

Returns
========================================

| Pointer to the data contained by the array.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(input.data()[0] == 1, "a first element is 1.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

