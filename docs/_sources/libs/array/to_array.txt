.. _sprout-array-to_array:
###############################################################################
to_array
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N>
  inline SPROUT_CONSTEXPR sprout::array<T, N>
  to_array(T const (& arr)[N]);

Returns
========================================

| Returns the array object copied all elements from the built-in array.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  
  SPROUT_STATIC_CONSTEXPR int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  SPROUT_STATIC_CONSTEXPR auto y = sprout::to_array(x);
  static_assert(y[0] == x[0], "array y is same as built-in array x.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

