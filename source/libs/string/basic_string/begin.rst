.. _sprout-string-basic_string-begin:
###############################################################################
begin
###############################################################################

Interface
========================================
.. sourcecode:: c++

  iterator begin() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_iterator begin() const SPROUT_NOEXCEPT;

Returns
========================================

| iterator for the first element.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(*input.begin() == 'h', "input first element is h.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

