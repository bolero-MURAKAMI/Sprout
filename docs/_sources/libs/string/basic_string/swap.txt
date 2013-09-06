.. _sprout-string-basic_string-swap:
###############################################################################
swap
###############################################################################

Interface
========================================
.. sourcecode:: c++

  void swap(basic_string& s) SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(std::swap(std::declval<T&>(), std::declval<T&>())));

Postcondition
========================================

| ``*this`` contains the same sequence of characters that was in s, s contains the same sequence of characters that was in ``*this``.

Throws
========================================

| Nothing unless one of the element-wise swap calls throws an exception.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");
  auto y = string<8>("madocchi");
  swap(x, y);
  SPROUT_ASSERT_MSG(x == "madocchi" && y == "homuhomu", "each element are swapped.");

Complexity
========================================

| linear.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

