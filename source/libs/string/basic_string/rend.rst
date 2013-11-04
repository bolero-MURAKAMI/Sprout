.. _sprout-string-basic_string-rend:
###############################################################################
rend
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR reverse_iterator rend() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_reverse_iterator rend() const SPROUT_NOEXCEPT;

Returns
========================================

| reverse iterator for position after the last element in reverse iteration.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(*(input.rend() - 1) == 'h', "input last element of reverse iteration is h.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

