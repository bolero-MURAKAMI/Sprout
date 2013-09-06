.. _sprout-string-basic_string-empty:
###############################################################################
empty
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CONSTEXPR bool empty() const SPROUT_NOEXCEPT;

Returns
========================================

| true if the array size is 0, false otherwise.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto input = string<8>("");
  static_assert(input.empty(), "input is empty.");

Complexity
========================================

| Recursive function invocations in *O(1)* (constant) depth.

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

