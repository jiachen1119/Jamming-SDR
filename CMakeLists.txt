cmake_minimum_required(VERSION 3.27)
project(Jamming_SDR)

# must set the module path for cmake file, because it is null by default
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/src/cmake)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# finding package config is necessary
include(FindPkgConfig)

include_directories(src/sink)
include_directories(src/lib)
include_directories(src/source)
include_directories(src/process)

##########################################
# gr-osmosdr - OPTIONAL
##########################################
# osmosdr for HackRF
list(APPEND GR_REQUIRED_COMPONENTS RUNTIME PMT BLOCKS FFT FILTER ANALOG)
find_package(GROSMOSDR)

# determine whether found
if(GROSMOSDR_FOUND)
    # set properties
    set_package_properties(GROSMOSDR PROPERTIES
            PURPOSE "Used for communication with OsmoSDR and other front-ends (HackRF, bladeRF, Realtek's RTL2832U-based dongles, etc.)."
            TYPE OPTIONAL
    )
    message(STATUS "The driver for OsmoSDR and other front-ends (HackRF, bladeRF, Realtek's RTL2832U-based dongles, etc.) will be compiled.")
else()
    message(FATAL_ERROR "gr-osmosdr required to build gnss-sdr with the optional OSMOSDR driver")
endif()

################################################################################
# GNU Radio - https://www.gnuradio.org
################################################################################
list(APPEND GR_REQUIRED_COMPONENTS RUNTIME PMT BLOCKS FFT FILTER ANALOG)

find_package(GNURADIO)
set_package_properties(GNURADIO PROPERTIES
        PURPOSE "Implements flowgraph scheduler, provides some processing blocks and classes to create new ones."
        TYPE REQUIRED
)

add_subdirectory(src/sink)
add_subdirectory(src/lib)
add_subdirectory(src/source)
add_subdirectory(src/process)

set(UI_SOURCE MainWindow.ui)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(Jamming_SDR main.cpp MainWindow.cpp ${UI_SOURCE})

target_link_libraries(Jamming_SDR
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        sink
        lib
        source
        process
)

