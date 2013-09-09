.. _sprout-array-array-empty:
###############################################################################
empty
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT;

Returns
========================================

| true if the array size is 0, false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 0>{{}};
  static_assert(input.empty(), "input is empty.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

