.. _sprout-string-basic_string-operator-std-basic_string:
###############################################################################
operator std::basic_string
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename Allocator>
  SPROUT_EXPLICIT_CONVERSION operator std::basic_string<T, Traits, Allocator>() const;

Returns
========================================

| conversion to std::basic_string.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  SPROUT_STATIC_CONSTEXPR auto x = string<8>("homuhomu");
  auto y = static_cast<std::string>(x);
  SPROUT_ASSERT_MASG(x == y.c_str(), "y is converted from x.");

Header
========================================

| ``sprout/string/string.hpp``
| Convenience header: ``sprout/string.hpp``

