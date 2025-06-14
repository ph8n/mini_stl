file(GLOB TEST_SRCS CONFIGURE_DEPENDS "*.cpp")

foreach(src ${TEST_SRCS})
  get_filename_component(test_name ${src} NAME_WE)

  add_executable(${test_name} ${src})

  target_link_libraries(${test_name}
    PRIVATE
      DSA
      Catch2::Catch2
  )

  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
