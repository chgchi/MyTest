AUX_SOURCE_DIRECTORY(. TESTAlgorithm_SRC)

INCLUDE_DIRECTORIES(BEFORE /usr/local/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/utils)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/libout/utils)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
message(STATUS "in TESTAlgorithm CXXFLAG :" ${CMAKE_CXX_FLAGS})

ADD_EXECUTABLE(testAlgorithms ${TESTAlgorithm_SRC})
TARGET_LINK_LIBRARIES(testAlgorithms libgtest.a libgmock.a libutils.a)
TARGET_LINK_LIBRARIES(testAlgorithms boost_system boost_thread boost_filesystem boost_regex boost_program_options pthread dl m)

INSTALL(TARGETS testAlgorithms RUNTIME DESTINATION bin)

