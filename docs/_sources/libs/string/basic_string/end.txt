.. _sprout-string-basic_string-end:

###############################################################################
end
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR iterator end() SPROUT_NOEXCEPT;
  
  SPROUT_CONSTEXPR const_iterator end() const SPROUT_NOEXCEPT;

Returns
========================================

| iterator for position after the last element.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("homuhomu");
  static_assert(*(input.end() - 1) == 'u', "input last element is u.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

