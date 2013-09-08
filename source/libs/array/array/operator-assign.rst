.. _sprout-array-array-operator-assign:
###############################################################################
operator=
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T2>
  array& operator=(array<T2, N> const& rhs);
  
  template<typename T2>
  array& operator=(array<T2, N>&& rhs);

Effects
========================================

| ``std::copy(rhs.begin(), rhs.end(), begin())``.
| or
| ``std::move(rhs.begin(), rhs.end(), begin())``.

Returns
========================================

| ``*this``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  SPROUT_STATIC_CONSTEXPR auto y = array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}};
  x = y;
  SPROUT_ASSERT_MSG(x == y, "y is assigned to x.");

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

