AUX_SOURCE_DIRECTORY(. TESTSTL_SRC)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message(STATUS "in testSTL CXXFLAG :" ${CMAKE_CXX_FLAGS})

INCLUDE_DIRECTORIES(BEFORE /usr/local/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/utils)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/libout/utils)


ADD_EXECUTABLE(testSTL ${TESTSTL_SRC})
TARGET_LINK_LIBRARIES(testSTL libgtest.a libgmock.a libutils.a)
TARGET_LINK_LIBRARIES(testSTL folly z ssl crypto event glog gflags iberty pthread double-conversion boost_system boost_thread boost_filesystem boost_regex boost_program_options dl m)

INSTALL(TARGETS testSTL RUNTIME DESTINATION bin)

