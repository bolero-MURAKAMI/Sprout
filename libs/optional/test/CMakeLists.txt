add_executable( libs_optional_test_optional optional.cpp )
set_target_properties( libs_optional_test_optional PROPERTIES OUTPUT_NAME "optional" )
add_test( libs_optional_test_optional optional )
