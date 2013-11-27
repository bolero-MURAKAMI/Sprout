add_executable( libs_variant_test_variant variant.cpp )
set_target_properties( libs_variant_test_variant PROPERTIES OUTPUT_NAME "variant" )
add_test( libs_variant_test_variant variant )
