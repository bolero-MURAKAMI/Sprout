.. _sprout-string-basic_string-resize:

###############################################################################
resize
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR void resize(size_type n, value_type c);
  
  SPROUT_CXX14_CONSTEXPR void resize(size_type n);

Requires
========================================

| ``n <= max_size()``.

Effects
========================================

| Alters the length of the string designated by ``*this`` as follows:
  * If ``n <= size()``, the function replaces the string designated by ``*this`` with a string of length n whose elements are a copy of the initial elements of the original string designated by ``*this``.
  * If ``n > size()``, the function replaces the string designated by ``*this`` with a string of length n whose first size() elements are a copy of the original string designated by ``*this``, and whose remaining elements are all initialized to c.

| Equivalent to ``resize(n, value_type())`` when there is no parameter c.

Throws
========================================

| std::length_error if ``n > max_size()``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");
  int main() {
    x.resize(4);
    SPROUT_ASSERT_MSG(x.size() == 4 && x == "homu", "string is resized to 4.");
  }

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

