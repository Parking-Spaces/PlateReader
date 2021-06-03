cmake_minimum_required(VERSION 3.19)
project(PlateReader)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
# Another way is to use CMake's FetchContent module to clone gRPC at
# configure time. This makes gRPC's source code available to your project,
# similar to a git submodule.
message(STATUS "Using gRPC via add_subdirectory (FetchContent).")
FetchContent_Declare(
        grpc
        GIT_REPOSITORY https://github.com/grpc/grpc.git
        # when using gRPC, you will actually set this to an existing tag, such as
        # v1.25.0, v1.26.0 etc..
        # For the purpose of testing, we override the tag used to the commit
        # that's currently under test.
        GIT_TAG v1.38.0)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(grpc)

# Since FetchContent uses add_subdirectory under the hood, we can use
# the grpc targets directly from this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)
if (CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else ()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif ()

# Proto file
get_filename_component(hw_proto "../CentralProto/parkingspaces.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/parkingspaces.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/parkingspaces.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/parkingspaces.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/parkingspaces.grpc.pb.h")

add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
        DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(hw_grpc_proto
        ${hw_grpc_srcs}
        ${hw_grpc_hdrs}
        ${hw_proto_srcs}
        ${hw_proto_hdrs})

add_executable(PlateReader main.cpp platereader.cpp server_conn.cpp
         ${hw_proto_srcs}  ${hw_grpc_srcs})

target_link_libraries(PlateReader openalpr ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})