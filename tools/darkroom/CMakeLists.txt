if( OpenCV_FOUND )
  include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )
  add_executable( tools_darkroom_texconv texconv.cpp )
  target_link_libraries( tools_darkroom_texconv ${OpenCV_LDFLAGS} )
  set_target_properties( tools_darkroom_texconv PROPERTIES OUTPUT_NAME "texconv" )
  install( TARGETS tools_darkroom_texconv
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
  )
endif( OpenCV_FOUND )
