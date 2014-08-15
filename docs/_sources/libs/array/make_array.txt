.. _sprout-array-make_array:

###############################################################################
make_array
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, typename... Types>
  inline SPROUT_CONSTEXPR sprout::array<typename std::remove_cv<T>::type, sizeof...(Types)>
  make_array(Types&&... args);

  template</*implementation-defined*/, typename... Types>
  inline SPROUT_CONSTEXPR sprout::array<typename sprout::common_decay<Types...>::type, sizeof...(Types)>
  make_array(Types&&... args);

Returns
========================================

| Returns an array object initialized with the argument all elements.

Remarks
========================================

| A first version needs to be specified in the template parameters explicitly type T of the elements in the array.
| And, the type of the elements in the array is a decayed common type of all arguments in the second version.
|
| Narrowing conversion is **not** prohibited in this make_array function. (It behaves like a static_cast)
| If you want to prohibit narrowing conversion, use :doc:`make_array_without_narrowing <./make_array_without_narrowing>` function.

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

