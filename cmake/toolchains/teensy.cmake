# This toolchain file is based on https://github.com/apmorton/teensy-template/blob/master/Makefile
# and https://github.com/queezythegreat/arduino-cmake
# and https://github.com/sudar/Arduino-Makefile
# and on the Teensy Makefile.

if(UNIX)
    include(Platform/UnixPaths)
    if(APPLE)
        list(APPEND CMAKE_SYSTEM_PREFIX_PATH ~/Applications
                                             /Applications
                                             /Developer/Applications
                                             /sw         # Fink
                                             /opt/local) # MacPorts
    endif()
elseif(WIN32)
    include(Platform/WindowsPaths)
endif()

if(NOT ARDUINO_SDK_PATH)
    set(ARDUINO_PATHS)

    foreach(DETECT_VERSION_MAJOR 1)
        foreach(DETECT_VERSION_MINOR RANGE 6 0)
            list(APPEND ARDUINO_PATHS arduino-${DETECT_VERSION_MAJOR}.${DETECT_VERSION_MINOR})
            foreach(DETECT_VERSION_PATCH  RANGE 5 0)
                list(APPEND ARDUINO_PATHS arduino-${DETECT_VERSION_MAJOR}.${DETECT_VERSION_MINOR}.${DETECT_VERSION_PATCH})
            endforeach()
        endforeach()
    endforeach()

    foreach(VERSION RANGE 23 19)
        list(APPEND ARDUINO_PATHS arduino-00${VERSION})
    endforeach()

    if(UNIX)
        file(GLOB SDK_PATH_HINTS /usr/share/arduino*
                                 /opt/local/arduino*
                                 /opt/arduino*
                                 /usr/local/share/arduino*)
    elseif(WIN32)
        set(SDK_PATH_HINTS "C:\\Program Files\\Arduino"
                           "C:\\Program Files (x86)\\Arduino")
    endif()
    list(SORT SDK_PATH_HINTS)
    list(REVERSE SDK_PATH_HINTS)
endif()

find_path(ARDUINO_SDK_PATH
          NAMES lib/version.txt
          PATH_SUFFIXES share/arduino
                        Arduino.app/Contents/Resources/Java/
                        ${ARDUINO_PATHS}
          HINTS ${SDK_PATH_HINTS}
          DOC "Arduino SDK path.")

if(ARDUINO_SDK_PATH)
    list(APPEND CMAKE_SYSTEM_PREFIX_PATH ${ARDUINO_SDK_PATH}/hardware/tools/arm)
else()
    message(FATAL_ERROR "Could not find Arduino SDK (set ARDUINO_SDK_PATH)!")
endif()



# User configurable variables
# (show up in cmake-gui)
#
set(TEENSY_VERSION 31 CACHE STRING "Set to the Teensy version corresponding to your board (30 or 31 allowed)" FORCE)
set(CPU_CORE_SPEED 96000000 CACHE STRING "Set to 24000000, 48000000, 72000000 or 96000000 to set CPU core speed" FORCE)
set(ARDUINOPATH "/Users/ron/Downloads/Arduino.app/Contents/Resources/Java/" CACHE STRING "Path to Arduino installation" FORCE)


# Derived variables
#
set(CPU cortex-m4)

set(TOOLSPATH "${ARDUINOPATH}hardware/tools/")
set(COMPILERPATH "${TOOLSPATH}arm/bin/")
set(COREPATH "${ARDUINOPATH}hardware/teensy/avr/cores/teensy3/")
set(LIBRARYPATH "${ARDUINOPATH}hardware/teensy/avr/libraries/")


# Normal toolchain configuration
#

# this one is important
set(CMAKE_SYSTEM_NAME Generic)

# where is the target environment 
#set(CMAKE_FIND_ROOT_PATH ${COMPILERPATH})

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


# Additional C and CPP files for Arduino support
#

file(GLOB TEENSY_C_FILES ${COREPATH}*.c ${LIBRARYPATH}*/utility/*.c)
file(GLOB TEENSY_CPP_FILES ${COREPATH}*.cpp)
file(GLOB LIBRARY_CPP_FILES ${LIBRARYPATH}*/*.cpp ${LIBRARYPATH}*/utility/*.cpp)
set(TEENSY_SOURCES ${TEENSY_C_FILES} ${TEENSY_CPP_FILES} ${LIBRARY_CPP_FILES})
list(REMOVE_ITEM TEENSY_SOURCES ${COREPATH}main.cpp)


# Add all libraries as include paths
#

macro(get_directorylist RESULT DIR)
  file(GLOB children RELATIVE ${DIR} ${DIR}*)
  set(DIRLIST "")
  foreach(child ${children})
    if(IS_DIRECTORY ${DIR}${child})
        list(APPEND DIRLIST ${DIR}${child})
    endif()
  endforeach()
  set(${RESULT} ${DIRLIST})
endmacro()

get_directorylist(ARDUINO_LIBRARY_INCLUDES ${LIBRARYPATH})
set(ARDUINO_INCLUDES ${ARDUINO_LIBRARY_INCLUDES};${COREPATH};${LIBRARYPATH}Adafruit_nRF8001/utility;${LIBRARYPATH}Audio/utility;${LIBRARYPATH}Ethernet/utility;${LIBRARYPATH}Keypad/utility;${LIBRARYPATH}SD/utility;${LIBRARYPATH}Snooze/utility;${LIBRARYPATH}VirtualWire/utility;${LIBRARYPATH}Wire/utility)


# Teensy 3.0 and 3.1 differentiation
#

if (TEENSY_VERSION EQUAL 30)
    set(CPU_DEFINE __MK20DX128__)
    set(LINKER_FILE ${COREPATH}mk20dx128.ld)
else()
    set(CPU_DEFINE __MK20DX256__)
    set(LINKER_FILE ${COREPATH}mk20dx256.ld)
endif()

set(TEENSY_DEFINITIONS USB_SERIAL
                       LAYOUT_US_ENGLISH
                       F_CPU=${CPU_CORE_SPEED}
                       ${CPU_DEFINE}
                       ARDUINO=10600
                       TEENSYDUINO=121)


# Macros to wrap add_[executable|library] for seamless Teensy integration
#
function(teensy_add_executable TARGET)
    set(ELFTARGET ${TARGET}.elf)

    add_executable(${TARGET} ${ARGN} ${TEENSY_SOURCES})

    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-Wall -g -Os -mcpu=${CPU} -mthumb -nostdlib -MMD -felide-constructors -fno-exceptions -fno-rtti -std=gnu++11")
    set_target_properties(${TARGET} PROPERTIES COMPILE_DEFINITIONS "${TEENSY_DEFINITIONS}")
    set_target_properties(${TARGET} PROPERTIES INCLUDE_DIRECTORIES "${ARDUINO_INCLUDES}")
    set_target_properties(${TARGET} PROPERTIES LINK_FLAGS "-Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs -mcpu=${CPU} -mthumb -T\"${LINKER_FILE}\"")
    set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${ELFTARGET})

    add_custom_command(OUTPUT ${TARGET}.hex
                       COMMAND ${COMPILERPATH}arm-none-eabi-size ${ELFTARGET}
                       COMMAND ${COMPILERPATH}arm-none-eabi-objcopy -O ihex -R .eeprom ${ELFTARGET} ${TARGET}.hex
                       COMMAND ${TOOLSPATH}teensy_post_compile -file=${TARGET} -path=${CMAKE_CURRENT_BINARY_DIR} -tools=${TOOLSPATH}
                       DEPENDS ${TARGET}
                       COMMENT "Creating HEX file for ${TARGET}")

    add_custom_target(${TARGET}-hex ALL DEPENDS ${TARGET}.hex)
endfunction()

function(teensy_add_library TARGET)
	add_library(${TARGET} ${ARGN})

    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-Wall -g -Os -mcpu=${CPU} -mthumb -nostdlib -MMD -felide-constructors -fno-exceptions -fno-rtti -std=gnu++11")
    set_target_properties(${TARGET} PROPERTIES COMPILE_DEFINITIONS "${TEENSY_DEFINITIONS}")
    set_target_properties(${TARGET} PROPERTIES INCLUDE_DIRECTORIES "${ARDUINO_INCLUDES}")
endfunction()
