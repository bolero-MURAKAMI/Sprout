.. _sprout-string-char_traits-assign-string:
###############################################################################
assign
###############################################################################

Interface
========================================
.. sourcecode:: c++

  static char_type* assign(char_type* s, std::size_t n, char_type a);

Effects
========================================

| Equivalent to ``std::char_traits<Char>::assign(s, n, a)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  char x[] = "homuhomu";
  int main() {
    char_traits<char>::assign(x, 8, 'M');
    SPROUT_ASSERT_MSG(x[0] == 'M', "x is filled by M.");
  }

Complexity
========================================

| linear.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

