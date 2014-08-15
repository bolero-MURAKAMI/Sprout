.. _sprout-string-basic_string-operator-subscript:

###############################################################################
operator[]
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR reference operator[](size_type n);
  
  SPROUT_CONSTEXPR const_reference operator[](size_type n) const;

Returns
========================================

| The element at the specified position in the string.

Remarks
========================================

| It causes undefined behavior if n is out of bounds.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(input[4] == 'h', "an element at position 4 is h.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

