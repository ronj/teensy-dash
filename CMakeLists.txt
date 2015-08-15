cmake_minimum_required(VERSION 2.8)

project(dash)

## Options section.
#
# Add user configurable options here.
# These will show up in the cmake-gui.

option(BUILD_FOR_EMULATOR "Build for SDL emulator" OFF)
option(BUILD_SHARED_LIBS  "Build shared libraries" OFF)


## Set our own module path.
#
# If you define additional FindXXX.cmake files,
# put them in this directory.

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(CheckCXXCompilerFlag)


## Generate version file
#
# Construct a semantic version number according to http://semver.org/
# and write that to Version.h in the binary dir.

FIND_PACKAGE(Git)

set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 1)
set(${CMAKE_PROJECT_NAME}_VERSION_PATCH 1)

execute_process(COMMAND ${GIT_EXECUTABLE} -C ${PROJECT_SOURCE_DIR} rev-parse --short HEAD
                OUTPUT_VARIABLE ${CMAKE_PROJECT_NAME}_VERSION_METADATA
                OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file("${PROJECT_SOURCE_DIR}/source/Version.h.in"
               "${PROJECT_BINARY_DIR}/Version.h")


## Derived settings.
#
# Based upon the options defined above
# derive some helper methods and enable
# required functionality.

set(EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/external)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${BUILD_FOR_EMULATOR})
  function(internal_add_executable)
    add_executable(${ARGN})
  endfunction()

  function(internal_add_library)
    add_library(${ARGN})
  endfunction()
else()
  function(internal_add_executable)
    teensy_add_executable(${ARGN})
  endfunction()

  function(internal_add_library)
    teensy_add_library(${ARGN})
  endfunction()
endif()


## Set up testing from CMake with CTest
#
# This will also set the option BUILD_TESTING
# when "On" the testing tree is built.

include(CTest)
enable_testing()

## Add unit tests.
#
# This macro requires two arguments.
# The first argument is the executable that needs to be called for running unit tests.
# This executable is expected to output zero in case of no failed test and non-zero in
# case one or more of the tests failed.
# The second argument is a list of source files that contain "TEST" or "TEST_F" macros.
#
# The source files are scanned for the macros and added to CTest with the following form:
# suitename::testname.
#
# Compatibility: Yaffut and Google Test (GTest).
# TODO: Proper support for FUNC test definition of Yaffut.
macro(add_unit_tests _executable)
  foreach(TEST_SOURCE ${ARGN})
    file(READ "${TEST_SOURCE}" CONTENTS)
    string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,]+)\\)" FOUND_TESTS ${CONTENTS})

    foreach(FOUND_TEST ${FOUND_TESTS})
      string(REGEX REPLACE ".*\\(([A-Za-z_0-9]+)[, ]*([A-Za-z_0-9]+)\\).*" "\\1::\\2" TEST_NAME ${FOUND_TEST})

      add_test(${TEST_NAME} ${_executable} ${TEST_NAME})
    endforeach()
  endforeach()
endmacro()


if (CMAKE_SIZEOF_VOID_P MATCHES 4)
    set(PROJECT_SIZE_TYPE x86 CACHE INTERNAL "" FORCE)
else()
    set(PROJECT_SIZE_TYPE x64 CACHE INTERNAL "" FORCE)
endif()


## Compiler options section.
#
# Based upon the options set by the user and the detected compiler
# the compilation flags are determined.

## Clang/GCC config section.

if (CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  set(PROJECT_COMMON_FLAGS "${PROJECT_COMMON_FLAGS} -Wall -Wextra -Wno-missing-braces")

  if (MINGW)
    set(PROJECT_COMMON_FLAGS "${PROJECT_COMMON_FLAGS} -static-libstdc++ -static-libgcc -static")
  endif()

  foreach (flag "-std=c++11" "-std=c++0x")
    CHECK_CXX_COMPILER_FLAG(${flag} CXX_COMPILER_SUPPORTS_NEW_ISO_STD)

    if (CXX_COMPILER_SUPPORTS_NEW_ISO_STD)
      set(CXX_NEW_ISO_STD_FLAG ${flag})
      break()
    endif()
  endforeach()

  if (NOT CXX_COMPILER_SUPPORTS_NEW_ISO_STD)
    #message(FATAL_ERROR "The project requires C++11 features.\n"
    #                    "You need at least one of the following compilers:\n"
    #                    "- gcc 4.7 (see: http://gcc.gnu.org/projects/cxx0x.html).\n"
    #                    "- clang 3.1 (see: http://clang.llvm.org/cxx_status.html).")
  endif()

  if (CMAKE_COMPILER_IS_CLANGXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_NEW_ISO_STD_FLAG} -stdlib=libc++")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_NEW_ISO_STD_FLAG}")
    # Workaround for usage of thread::sleep (see: http://stackoverflow.com/questions/12523122/what-is-glibcxx-use-nanosleep-all-about).
    add_definitions("-D_GLIBCXX_USE_NANOSLEEP")
  endif()

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PROJECT_COMMON_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_COMMON_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${PROJECT_COMMON_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${PROJECT_COMMON_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${PROJECT_COMMON_FLAGS}")
endif()


## Build Common
#
set(COMMON_SOURCES source/Common/ArduinoWrapper.h
                   source/Common/DisableInterruptContext.h
                   source/Common/Interpolation.h
                   source/Common/List.h
                   source/Common/Logger.h
                   source/Common/Math.cpp
                   source/Common/Math.h
                   source/Common/NonCopyable.h
                   source/Common/Task.h
                   source/Common/TaskScheduler.cpp
                   source/Common/TaskScheduler.h
                   source/Common/TimedTask.cpp
                   source/Common/TimedTask.h)

internal_add_library(${CMAKE_PROJECT_NAME}.Common ${COMMON_SOURCES})


## Build HardwareLayer
#

set(HARDWARE_LAYER_SOURCES source/HardwareLayer/AccelerometerDriver.h
                           source/HardwareLayer/AnalogPin.h
                           source/HardwareLayer/Common/ADXL335Driver.cpp
                           source/HardwareLayer/Common/ADXL335Driver.h
                           source/HardwareLayer/DigitalPin.h
                           source/HardwareLayer/DisplayDriver.h
						   source/HardwareLayer/FrequencyCounter.h
                           source/HardwareLayer/Hardware.h
                           source/HardwareLayer/Platform.h
                           source/HardwareLayer/RotaryEncoder.h
                           source/HardwareLayer/Timer.h)

if (${BUILD_FOR_EMULATOR})
  list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_DIR}/sdl2-2.0.3)
  list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_DIR}/sdl2-2.0.3/lib/${PROJECT_SIZE_TYPE})

  add_definitions("-DBUILD_FOR_EMULATOR")

  find_package(SDL2 REQUIRED)

  list(APPEND EXTERNAL_INCLUDES ${SDL2_INCLUDE_DIR})
  list(APPEND EXTERNAL_LIBRARIES ${SDL2_LIBRARY})

  list(APPEND HARDWARE_LAYER_SOURCES
              source/HardwareLayer/SDL/SDLAnalogPin.cpp
              source/HardwareLayer/SDL/SDLAnalogPin.h
              source/HardwareLayer/SDL/SDLDigitalPin.cpp
              source/HardwareLayer/SDL/SDLDigitalPin.h
              source/HardwareLayer/SDL/SDLDisplayDriver.cpp
              source/HardwareLayer/SDL/SDLDisplayDriver.h
			  source/HardwareLayer/SDL/SDLFrequencyCounter.cpp
			  source/HardwareLayer/SDL/SDLFrequencyCounter.h
              source/HardwareLayer/SDL/SDLHardware.cpp
              source/HardwareLayer/SDL/SDLHardware.h
              source/HardwareLayer/SDL/SDLPlatform.cpp
              source/HardwareLayer/SDL/SDLPlatform.h
              source/HardwareLayer/SDL/SDLRotaryEncoder.cpp
              source/HardwareLayer/SDL/SDLRotaryEncoder.h
              source/HardwareLayer/SDL/SDLTimer.cpp
              source/HardwareLayer/SDL/SDLTimer.h)
else()
  list(APPEND HARDWARE_LAYER_SOURCES
              source/HardwareLayer/Teensy/NeoPixelLedDriver.cpp
              source/HardwareLayer/Teensy/NeoPixelLedDriver.h
              source/HardwareLayer/Teensy/ST7735DisplayDriver.cpp
              source/HardwareLayer/Teensy/ST7735DisplayDriver.h
              source/HardwareLayer/Teensy/TeensyAnalogPin.cpp
              source/HardwareLayer/Teensy/TeensyAnalogPin.h
              source/HardwareLayer/Teensy/TeensyDigitalPin.cpp
              source/HardwareLayer/Teensy/TeensyDigitalPin.h
			  source/HardwareLayer/Teensy/TeensyFrequencyCounter.cpp
			  source/HardwareLayer/Teensy/TeensyFrequencyCounter.h
              source/HardwareLayer/Teensy/TeensyHardware.cpp
              source/HardwareLayer/Teensy/TeensyHardware.h
              source/HardwareLayer/Teensy/TeensyPlatform.cpp
              source/HardwareLayer/Teensy/TeensyPlatform.h
              source/HardwareLayer/Teensy/TeensyRotaryEncoder.cpp
              source/HardwareLayer/Teensy/TeensyRotaryEncoder.h
              source/HardwareLayer/Teensy/TeensyTimer.cpp
              source/HardwareLayer/Teensy/TeensyTimer.h)
endif()

internal_add_library(${CMAKE_PROJECT_NAME}.HardwareLayer ${HARDWARE_LAYER_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME}.HardwareLayer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
                                                                      ${CMAKE_CURRENT_SOURCE_DIR}/source/HardwareLayer
                                                                      ${CMAKE_CURRENT_SOURCE_DIR}/source/HardwareLayer/Common
                                                                      ${EXTERNAL_INCLUDES})


## Build PeripheralLayer
#

list(APPEND PERIPHERAL_LAYER_SOURCES
            source/PeripheralLayer/AccelerationAxis.cpp
            source/PeripheralLayer/AccelerationAxis.h
			source/PeripheralLayer/Bitmap.h
			source/PeripheralLayer/Bitmaps.cpp
			source/PeripheralLayer/Bitmaps.h
            source/PeripheralLayer/Color.cpp
            source/PeripheralLayer/Color.h
            source/PeripheralLayer/Configuration.cpp
            source/PeripheralLayer/Configuration.h
            source/PeripheralLayer/EventSource.cpp
            source/PeripheralLayer/EventSource.h
            source/PeripheralLayer/EventTypes.h
			source/PeripheralLayer/Font.h
			source/PeripheralLayer/Fonts.cpp
			source/PeripheralLayer/Fonts.h
            source/PeripheralLayer/FrequencyCounter.cpp
            source/PeripheralLayer/FrequencyCounter.h
            source/PeripheralLayer/GraphicContext.cpp
            source/PeripheralLayer/GraphicContext.h
			source/PeripheralLayer/ParkDistanceDecoder.cpp
			source/PeripheralLayer/ParkDistanceDecoder.h
            source/PeripheralLayer/Peripherals.cpp
            source/PeripheralLayer/Peripherals.h
            source/PeripheralLayer/PowerManagement.cpp
            source/PeripheralLayer/PowerManagement.h
            source/PeripheralLayer/PulseCounter.cpp
            source/PeripheralLayer/PulseCounter.h
            source/PeripheralLayer/RotaryEventSource.cpp
            source/PeripheralLayer/RotaryEventSource.h
            source/PeripheralLayer/SerialEventSource.cpp
            source/PeripheralLayer/SerialEventSource.h
            source/PeripheralLayer/TextHelper.cpp
            source/PeripheralLayer/TextHelper.h
            source/PeripheralLayer/TimeProvider.cpp
            source/PeripheralLayer/TimeProvider.h
            source/PeripheralLayer/VoltageDivider.cpp
            source/PeripheralLayer/VoltageDivider.h
            source/PeripheralLayer/Voltmeter.cpp
            source/PeripheralLayer/Voltmeter.h)

internal_add_library(${CMAKE_PROJECT_NAME}.PeripheralLayer ${PERIPHERAL_LAYER_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME}.PeripheralLayer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_link_libraries(${CMAKE_PROJECT_NAME}.PeripheralLayer ${CMAKE_PROJECT_NAME}.Common)


## Build ApplicationLayer
#

list(APPEND APPLICATION_LAYER_SOURCES
            source/ApplicationLayer/DashApplication.cpp
            source/ApplicationLayer/DashApplication.h
            source/ApplicationLayer/DrawEventArgs.h
            source/ApplicationLayer/ModelCollection.cpp
            source/ApplicationLayer/ModelCollection.h
            source/ApplicationLayer/ModelUpdateTask.cpp
            source/ApplicationLayer/ModelUpdateTask.h
            source/ApplicationLayer/Palette.h
            source/ApplicationLayer/UserEventsTask.cpp
            source/ApplicationLayer/UserEventsTask.h
            source/ApplicationLayer/UserInterfaceTask.cpp
            source/ApplicationLayer/UserInterfaceTask.h
            source/ApplicationLayer/ViewCollection.cpp
            source/ApplicationLayer/ViewCollection.h)

list(APPEND APPLICATION_LAYER_VIEW_SOURCES
            source/ApplicationLayer/Views/BaseView.h
            source/ApplicationLayer/Views/GraphView.cpp
            source/ApplicationLayer/Views/GraphView.h
            source/ApplicationLayer/Views/IconValueRow.cpp
            source/ApplicationLayer/Views/IconValueRow.h
            source/ApplicationLayer/Views/LargeValueView.cpp
            source/ApplicationLayer/Views/LargeValueView.h
			source/ApplicationLayer/Views/ParkDistanceView.cpp
			source/ApplicationLayer/Views/ParkDistanceView.h
            source/ApplicationLayer/Views/TripComputerView.cpp
            source/ApplicationLayer/Views/TripComputerView.h
            source/ApplicationLayer/Views/TwoRowView.cpp
            source/ApplicationLayer/Views/TwoRowView.h
            source/ApplicationLayer/Views/View.h
            source/ApplicationLayer/Views/XYScatterView.cpp
            source/ApplicationLayer/Views/XYScatterView.h)

list(APPEND APPLICATION_LAYER_MODEL_SOURCES
            source/ApplicationLayer/Models/AccelerationModel.cpp
            source/ApplicationLayer/Models/AccelerationModel.h
            source/ApplicationLayer/Models/CalculatedGearModel.cpp
            source/ApplicationLayer/Models/CalculatedGearModel.h
            source/ApplicationLayer/Models/ConversionHelper.cpp
            source/ApplicationLayer/Models/ConversionHelper.h
            source/ApplicationLayer/Models/Model.cpp
            source/ApplicationLayer/Models/Model.h
			source/ApplicationLayer/Models/ParkDistanceModel.cpp
			source/ApplicationLayer/Models/ParkDistanceModel.h
            source/ApplicationLayer/Models/PitchModel.cpp
            source/ApplicationLayer/Models/PitchModel.h
            source/ApplicationLayer/Models/RandomValueModel.cpp
            source/ApplicationLayer/Models/RandomValueModel.h
            source/ApplicationLayer/Models/RollModel.cpp
            source/ApplicationLayer/Models/RollModel.h
            source/ApplicationLayer/Models/RPMModel.cpp
            source/ApplicationLayer/Models/RPMModel.h
            source/ApplicationLayer/Models/SpeedModel.cpp
            source/ApplicationLayer/Models/SpeedModel.h
            source/ApplicationLayer/Models/TripComputerModel.cpp
            source/ApplicationLayer/Models/TripComputerModel.h
            source/ApplicationLayer/Models/TripData.cpp
            source/ApplicationLayer/Models/TripData.h
            source/ApplicationLayer/Models/VoltageModel.cpp
            source/ApplicationLayer/Models/VoltageModel.h
            source/ApplicationLayer/Models/WheelTickModel.cpp
            source/ApplicationLayer/Models/WheelTickModel.h)

internal_add_library(${CMAKE_PROJECT_NAME}.ApplicationLayer ${APPLICATION_LAYER_SOURCES} ${APPLICATION_LAYER_VIEW_SOURCES} ${APPLICATION_LAYER_MODEL_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME}.ApplicationLayer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_link_libraries(${CMAKE_PROJECT_NAME}.ApplicationLayer ${CMAKE_PROJECT_NAME}.PeripheralLayer)


## Build Application
#

list(APPEND APPLICATION_SOURCES source/Application.h source/main.cpp)

if (${BUILD_FOR_EMULATOR})
  list(APPEND APPLICATION_SOURCES source/EmulatorApplication.cpp)
else()
  list(APPEND APPLICATION_SOURCES source/EmbeddedApplication.cpp)
endif()

internal_add_executable(${CMAKE_PROJECT_NAME} ${APPLICATION_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source ${PROJECT_BINARY_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.Common ${CMAKE_PROJECT_NAME}.HardwareLayer ${CMAKE_PROJECT_NAME}.PeripheralLayer ${CMAKE_PROJECT_NAME}.ApplicationLayer ${EXTERNAL_LIBRARIES})

if (WIN32)
  if (MSVC)
    if (${BUILD_FOR_EMULATOR})
      set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

      add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
                         COMMAND ${CMAKE_COMMAND} -E copy_if_different
                         "${EXTERNAL_DIR}/sdl2-2.0.3/lib/${PROJECT_SIZE_TYPE}/SDL2.dll"
                         $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)
    endif()
  endif()
endif()


## Build unittests if required.
#

if(${BUILD_TESTING})
  if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
  endif()

  file(GLOB_RECURSE TEST_SOURCES "test_*.cpp")

  internal_add_executable(${CMAKE_PROJECT_NAME}.UnitTests ${TEST_SOURCES} "${EXTERNAL_DIR}/yaffut/testrunner.cpp")
  target_link_libraries(${CMAKE_PROJECT_NAME}.UnitTests ${CMAKE_PROJECT_NAME}.ApplicationLayer ${CMAKE_PROJECT_NAME}.Common)
  target_include_directories(${CMAKE_PROJECT_NAME}.UnitTests PUBLIC ${EXTERNAL_DIR}/yaffut ${EXTERNAL_DIR}/hippomocks ${CMAKE_CURRENT_SOURCE_DIR}/source)

  add_unit_tests("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.UnitTests" ${TEST_SOURCES})
endif()
