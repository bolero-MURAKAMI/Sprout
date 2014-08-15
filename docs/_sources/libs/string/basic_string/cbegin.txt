.. _sprout-string-basic_string-cbegin:

###############################################################################
cbegin
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR const_iterator cbegin() const SPROUT_NOEXCEPT;

Returns
========================================

| iterator for the first element always const.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(*input.cbegin() == 'h', "input first element is h.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

