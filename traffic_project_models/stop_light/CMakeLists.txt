CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(emissive_plugin)

SET(CMAKE_CXX_STANDARD 11)

# Set the path to the Gazebo CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/share/gazebo/cmake)

# Find the Gazebo libraries and include paths
FIND_PACKAGE(gazebo 11 REQUIRED)
INCLUDE_DIRECTORIES(${GAZEBO_INCLUDE_DIRS})
LINK_DIRECTORIES(${GAZEBO_LIBRARY_DIRS})

# Find the Boost libraries and include paths
FIND_PACKAGE(Boost REQUIRED COMPONENTS system)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})



# Build the plugin
ADD_LIBRARY(emissive_plugin SHARED plugins/emissive_plugin.cc)
TARGET_LINK_LIBRARIES(emissive_plugin ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${ros_LIBRARIES})

# Install the plugin
INSTALL(TARGETS emissive_plugin DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/gazebo_plugins/)
