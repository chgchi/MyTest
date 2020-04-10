AUX_SOURCE_DIRECTORY(. TESTFOLLY_SRC)

INCLUDE_DIRECTORIES(BEFORE /usr/local/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/utils)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/libout/utils)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message(STATUS "in testFolly CXXFLAG :" ${CMAKE_CXX_FLAGS})

ADD_EXECUTABLE(testFolly ${TESTFOLLY_SRC})
TARGET_LINK_LIBRARIES(testFolly libutils.a)
TARGET_LINK_LIBRARIES(testFolly folly z ssl crypto event glog gflags iberty pthread double-conversion boost_system boost_thread boost_filesystem boost_regex boost_program_options dl m)

INSTALL(TARGETS testFolly RUNTIME DESTINATION bin)

