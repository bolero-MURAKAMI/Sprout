.. _sprout-array-array-swap-global:
###############################################################################
swap
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N>
  inline SPROUT_CXX14_CONSTEXPR void
  swap(sprout::array<T, N>& lhs, sprout::array<T, N>& rhs)
  SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)));

Effects
========================================

| ``lhs.swap(rhs)``.

Throws
========================================

| Nothing unless ``lhs.swap(rhs)`` throws an exception.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/array.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = array<int, 10>{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
  auto y = array<int, 10>{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}};
  int main() {
    swap(x, y);
    SPROUT_ASSERT_MSG(x[0] == 10 && y[0] == 1, "each element are swapped.");
  }

Complexity
========================================

| linear in N.

Header
========================================

| ``sprout/array/array.hpp``
| Convenience header: ``sprout/array.hpp``

