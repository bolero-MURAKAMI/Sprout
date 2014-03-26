add_executable( libs_net_test_endian endian.cpp )
set_target_properties( libs_net_test_endian PROPERTIES OUTPUT_NAME "endian" )
add_test( libs_net_test_endian endian )
