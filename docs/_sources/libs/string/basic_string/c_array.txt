.. _sprout-string-basic_string-c_array:
###############################################################################
back
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR pointer c_array() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_pointer c_array() const SPROUT_NOEXCEPT;

Returns
========================================

| Pointer to the data contained by the string.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(input.c_array()[0] == 'h', "a first element is h.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

