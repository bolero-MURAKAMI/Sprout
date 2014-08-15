.. _sprout-string-basic_string-back:

###############################################################################
back
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR reference back();
  
  SPROUT_CONSTEXPR const_reference back() const;

Returns
========================================

| A reference to the last element in the string.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(input.back() == 'u', "a last element is u.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

