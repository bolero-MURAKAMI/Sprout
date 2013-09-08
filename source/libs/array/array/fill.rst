.. _sprout-array-array-fill:
###############################################################################
fill
###############################################################################

Interface
========================================
.. sourcecode:: c++

  void fill(const_reference value);
  
  SPROUT_CONSTEXPR array fill(const_reference value) const;

Effects
========================================

| ``std::fill_n(begin(), N, value)``, or without effects in the case of const version.

Returns
========================================

| void, or array filled with value in the case of const version.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  x.fill(0);
  SPROUT_ASSERT_MSG(x[0] == 0, "filled with 0.");

.. sourcecode:: c++

  #include <sprout/array.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto y = x.fill(0);
  static_assert(y[0] == 0, "filled with 0.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

