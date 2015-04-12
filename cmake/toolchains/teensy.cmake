# This toolchain file is based on https://github.com/apmorton/teensy-template/blob/master/Makefile
# and on the Teensy Makefile.

include(CMakeForceCompiler)


# User configurable variables
# (show up in cmake-gui)
#
set(TEENSY_VERSION 31 CACHE STRING "Set to the Teensy version corresponding to your board (30 or 31 allowed)" FORCE)
set(CPU_CORE_SPEED 96000000 CACHE STRING "Set to 24000000, 48000000, 72000000 or 96000000 to set CPU core speed" FORCE)
set(ARDUINOPATH "/Applications/Arduino.app/Contents/Resources/Java/" CACHE STRING "Path to Arduino installation" FORCE)


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

# specify the cross compiler
cmake_force_c_compiler(${COMPILERPATH}arm-none-eabi-gcc GNU)
cmake_force_cxx_compiler(${COMPILERPATH}arm-none-eabi-g++ GNU)

# where is the target environment 
set(CMAKE_FIND_ROOT_PATH ${COMPILERPATH})

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


# Additional C and CPP files for Arduino support
#

file(GLOB TEENSY_C_FILES ${COREPATH}*.c)
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
set(ARDUINO_INCLUDES ${ARDUINO_LIBRARY_INCLUDES};${COREPATH};${LIBRARYPATH}Ethernet/utility;${LIBRARYPATH}SD/utility;${LIBRARYPATH}Wire/utility)


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
	set_target_properties(${TARGET} PROPERTIES LINK_FLAGS "-Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs -mcpu=${CPU} -mthumb -T${LINKER_FILE}")
	set_target_properties(${TARGET} PROPERTIES OUTPUT_NAME ${ELFTARGET})

	add_custom_command(OUTPUT ${TARGET}.hex
	                   COMMAND ${COMPILERPATH}arm-none-eabi-size ${ELFTARGET}
	                   COMMAND ${COMPILERPATH}arm-none-eabi-objcopy -O ihex -R .eeprom ${ELFTARGET} ${TARGET}.hex
	                   COMMAND ${TOOLSPATH}teensy_post_compile -file=${TARGET} -path=${CMAKE_CURRENT_BINARY_DIR} -tools=${TOOLSPATH}
	                   DEPENDS ${TARGET}
	                   COMMENT "Creating HEX file for ${TARGET}")

	add_custom_target(hex ALL DEPENDS ${TARGET}.hex)
endfunction()

function(teensy_add_library TARGET)
	add_library(${TARGET} ${ARGN})

    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-Wall -g -Os -mcpu=${CPU} -mthumb -nostdlib -MMD -felide-constructors -fno-exceptions -fno-rtti -std=gnu++11")
	set_target_properties(${TARGET} PROPERTIES COMPILE_DEFINITIONS "${TEENSY_DEFINITIONS}")
	set_target_properties(${TARGET} PROPERTIES INCLUDE_DIRECTORIES "${ARDUINO_INCLUDES}")
endfunction()
