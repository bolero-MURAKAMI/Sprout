add_executable( libs_bitset_test_bitset bitset.cpp )
set_target_properties( libs_bitset_test_bitset PROPERTIES OUTPUT_NAME "bitset" )
add_test( libs_bitset_test_bitset bitset )
