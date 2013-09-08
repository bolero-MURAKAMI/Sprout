.. _sprout-string-basic_string-u16string:
###############################################################################
u16string
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<std::size_t N>
  using u16string = sprout::basic_string<char16_t, N>;

Examples
========================================
.. sourcecode:: c++

  #include <type_traits>
  #include <sprout/string.hpp>
  using namespace sprout;
  
  using type = u16string<8>;
  static_assert(std::is_same<type::value_type, char16_t>::value, "element type of u16string is char16_t.");

Header
========================================

| ``sprout/string/alias.hpp``
| Convenience header: ``sprout/string.hpp``

