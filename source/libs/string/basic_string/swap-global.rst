.. _sprout-string-basic_string-swap-global:
###############################################################################
swap
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename T, std::size_t N, typename Traits>
  inline SPROUT_CXX14_CONSTEXPR void
  swap(sprout::basic_string<T, N, Traits>& lhs, sprout::basic_string<T, N, Traits>& rhs)
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

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");
  auto y = string<8>("madocchi");
  int main() {
    swap(x, y);
    SPROUT_ASSERT_MSG(x == "madocchi" && y == "homuhomu", "each element are swapped.");
  }

Complexity
========================================

| linear in N.

Header
========================================

| ``sprout/string/array.hpp``
| Convenience header: ``sprout/string.hpp``

