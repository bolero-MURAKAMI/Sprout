.. _sprout-array-make_common_array:
###############################################################################
make_common_array
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename... Types>
  inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
  make_common_array(Types&&... args);

Returns
========================================

| Returns an array object initialized with the argument all elements.

Remarks
========================================

| The type of the elements in the array is a decayed common type of all arguments.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  
  SPROUT_STATIC_CONSTEXPR auto x = sprout::make_common_array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  static_assert(x.size() == 10, "array x initialized with 10 elements.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/array/make_array.hpp``
| Convenience header: ``sprout/array.hpp``

