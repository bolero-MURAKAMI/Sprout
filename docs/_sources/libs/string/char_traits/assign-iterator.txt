.. _sprout-string-char_traits-assign-iterator:
###############################################################################
assign
###############################################################################

Interface
========================================
.. sourcecode:: c++

  template<typename OutputIterator>
  static SPROUT_CXX14_CONSTEXPR OutputIterator assign(OutputIterator s, std::size_t n, char_type a);

Effects
========================================

| For each i in [0,n) performs ``assign(s[i], c)``.

Examples
========================================
.. sourcecode:: c++

  #include <sprout/string.hpp>
  #include <sprout/assert.hpp>
  using namespace sprout;
  
  auto x = string<8>("homuhomu");;
  int main() {
    char_traits<char>::assign(x.begin(), 8, 'M');
    SPROUT_ASSERT_MSG(x[0] == 'M', "x is filled by M.");
  }

Complexity
========================================

| linear.

Header
========================================

| ``sprout/string/char_traits.hpp``
| Convenience header: ``sprout/string.hpp``

