.. _sprout-array-make_array:
###############################################################################
make_array
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, typename... Types>
  inline SPROUT_CONSTEXPR sprout::array<T, sizeof...(Types)>
  make_array(Types&&... args);

Returns
========================================

| Returns an array object initialized with the argument all elements.

Remarks
========================================

| This function needs to be specified in the template parameters explicitly type T of the elements in the array.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  
  SPROUT_STATIC_CONSTEXPR auto x = sprout::make_array<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  static_assert(x.size() == 10, "array x initialized with 10 elements.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/make_array.hpp``
| Convenience header: ``sprout/array.hpp``

