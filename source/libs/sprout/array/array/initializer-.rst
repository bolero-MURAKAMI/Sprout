.. _sprout-array-array-initializer-:
###############################################################################
(initializer)
###############################################################################

Remarks
========================================

| An array is an aggregate that can be initialized with the syntax

.. sourcecode:: c++

  array<T, N> a = { initializer-list };

| where initializer-list is a comma-separated list of up to N elements whose types are convertible to T.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

