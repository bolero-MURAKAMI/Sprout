.. _sprout-array-array-begin:
###############################################################################
begin
###############################################################################

Interface
========================================
.. sourcecode:: c++

  iterator begin() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT;

Returns
========================================

| iterator for the first element.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(*input.begin() == 1, "input first element is 1.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

