.. _sprout-array-array-end:
###############################################################################
end
###############################################################################

Interface
========================================
.. sourcecode:: c++

  iterator end() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT;

Returns
========================================

| iterator for position after the last element.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(*(input.end() - 1) == 10, "input last element is 10.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

