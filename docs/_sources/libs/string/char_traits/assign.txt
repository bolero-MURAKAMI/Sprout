.. _sprout-string-char_traits-assign:
###############################################################################
assign
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static SPROUT_CXX14_CONSTEXPR void assign(char_type& c1, char_type const& c2);

Effects
========================================

| Equivalent to ``std::char_traits<Char>::assign(c1, c2)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  char x = 'H';
  SPROUT_STATIC_CONSTEXPR char y = 'M';
  int main() {
    char_traits<char>::assign(x, y);
    SPROUT_ASSERT_MSG(x == y, "y is assigned to x.");
  }

Complexity
========================================

| constant.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

