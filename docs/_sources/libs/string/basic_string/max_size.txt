.. _sprout-string-basic_string-max_size:

###############################################################################
max_size
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR size_type max_size() const SPROUT_NOEXCEPT;

Returns
========================================

| The number of elements contained in the string.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(input.max_size() == 8, "input max size is 8.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

