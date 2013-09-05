.. _sprout-string-char_traits:
###############################################################################
char_traits
###############################################################################

.. toctree::
    :hidden:

    assign
    rq
    lt
    compare
    length
    find

Interface
========================================
.. sourcecode:: c++

  template<typename Char>
  struct char_traits {
    // types:
    typedef typename std::char_traits<Char>::char_type char_type;
    typedef typename std::char_traits<Char>::int_type int_type;
    typedef typename std::char_traits<Char>::off_type off_type;
    typedef typename std::char_traits<Char>::pos_type pos_type;
    typedef typename std::char_traits<Char>::state_type state_type;

    // character operations:
    static void assign(char_type& c1, char_type const& c2) SPROUT_NOEXCEPT;
    static SPROUT_CONSTEXPR bool eq(char_type c1, char_type c2) SPROUT_NOEXCEPT;
    static SPROUT_CONSTEXPR bool lt(char_type c1, char_type c2) SPROUT_NOEXCEPT;

    // string operations:
    static SPROUT_CONSTEXPR int compare(char_type const* s1, char_type const* s2, std::size_t n);
    static SPROUT_CONSTEXPR std::size_t length(char_type const* s);
    static SPROUT_CONSTEXPR char_type const* find(char_type const* s, std::size_t n, char_type const& a);
    static char_type* move(char_type* s1, char_type const* s2, std::size_t n);
    static char_type* copy(char_type* s1, char_type const* s2, std::size_t n);
    static char_type* assign(char_type* s, std::size_t n, char_type a);

    // integer type operations:
    static SPROUT_CONSTEXPR int_type not_eof(int_type c) SPROUT_NOEXCEPT;
    static SPROUT_CONSTEXPR char_type to_char_type(int_type c) SPROUT_NOEXCEPT;
    static SPROUT_CONSTEXPR int_type to_int_type(char_type c) SPROUT_NOEXCEPT;
    static SPROUT_CONSTEXPR bool eq_int_type(int_type c1, int_type c2) SPROUT_NOEXCEPT;
    static SPROUT_CONSTEXPR int_type eof() SPROUT_NOEXCEPT;

    // string operations (for iterator):
    template<typename ConstInputIterator>
    static SPROUT_CONSTEXPR int compare(char_type const* s1, ConstInputIterator s2, std::size_t n);
    template<typename ConstInputIterator>
    static SPROUT_CONSTEXPR int compare(ConstInputIterator s1, char_type const* s2, std::size_t n);
    template<typename ConstIterator1, typename ConstIterator2>
    static SPROUT_CONSTEXPR int compare(ConstIterator1 s1, ConstIterator2 s2, std::size_t n);
    template<typename ConstInputIterator>
    static SPROUT_CONSTEXPR std::size_t length(ConstInputIterator s);
    template<typename ConstInputIterator>
    static SPROUT_CONSTEXPR ConstInputIterator find(ConstInputIterator s, std::size_t n, char_type const& a);
    template<typename OutputIterator, typename ConstInputIterator>
    static OutputIterator move(OutputIterator s1, ConstInputIterator s2, std::size_t n);
    template<typename OutputIterator, typename ConstInputIterator>
    static OutputIterator copy(OutputIterator s1, ConstInputIterator s2, std::size_t n);
    template<typename OutputIterator>
    static OutputIterator assign(OutputIterator s, std::size_t n, char_type a);
  };

Description
========================================

Member types
----------------------------------------

======================================== =============================================================================== =======================================
type                                     definition                                                                      
======================================== =============================================================================== =======================================
char_type                                std::char_traits<Char>::char_type
int_type                                 std::char_traits<Char>::int_type
off_type                                 std::char_traits<Char>::off_type
pos_type                                 std::char_traits<Char>::pos_type
state_type                               std::char_traits<Char>::state_type
======================================== =============================================================================== =======================================

Static member functions
----------------------------------------

character operations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`assign <./assign>`
:doc:`eq <./eq>`
:doc:`lt <./lt>`
======================================== ===============================================================================

string operations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`compare <./compare>`
:doc:`length<./length>`
:doc:`find <./find>`
:doc:`move <./move>`
:doc:`copy <./copy>`
:doc:`assign <./assign-string>`
======================================== ===============================================================================

integer type operations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`not_eof <./not_eof>`
:doc:`to_char_type <./to_char_type>`
:doc:`to_int_type <./to_int_type>`
:doc:`eq_int_type <./eq_int_type>`
:doc:`eof <./eof>`
======================================== ===============================================================================

string operations (for iterator)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

======================================== ===============================================================================
function
======================================== ===============================================================================
:doc:`compare <./compare-iterator>`
:doc:`eqlength<./length-iterator>`
:doc:`find <./find-iterator>`
:doc:`move <./move-iterator>`
:doc:`copy <./copy-iterator>`
:doc:`assign <./assign-iterator>`
======================================== ===============================================================================

Header
========================================

``sprout/string/char_traits.hpp``

Convenience header: ``sprout/string.hpp``

