.. _sprout-string-basic_string-clear:

###############################################################################
clear
###############################################################################

Interface
========================================
.. sourcecode:: c++

  SPROUT_CXX14_CONSTEXPR void clear() SPROUT_NOEXCEPT;

Effects
========================================

| Fill [begin,end) with value_type(), and set the 0 to length.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");
  int main() {
    x.clear();
    SPROUT_ASSERT_MSG(x.size() == 0 && x == "", "string is cleared.");
  }

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

