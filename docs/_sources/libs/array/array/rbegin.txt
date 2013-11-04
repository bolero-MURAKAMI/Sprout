.. _sprout-array-array-rbegin:
###############################################################################
rbegin
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR reverse_iterator rbegin() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_reverse_iterator rbegin() const SPROUT_NOEXCEPT;

Returns
========================================

| reverse iterator for the first element of reverse iteration.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  static_assert(*input.rbegin() == 10, "input first element of reverse iteration is 10.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

