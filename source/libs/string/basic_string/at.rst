.. _sprout-string-basic_string-at:
###############################################################################
at
###############################################################################

Interface
========================================
.. sourcecode:: c++

  reference at(size_type n);
  
  SPROUT_CONSTEXPR const_reference at(size_type n) const;

Returns
========================================

| The element at the specified position in the string.

Throws
========================================

| It throws std::out_of_range if n is out of bounds.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(input.at(4) == 'h', "an element at position 5 is h.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

