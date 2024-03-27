# set osmosdr variable
list(APPEND SOURCE_SOURCES SignalSource.cpp)
list(APPEND SOURCE_HEADERS SignalSource.h)

add_library(source
        ${SOURCE_SOURCES}
        ${SOURCE_HEADERS}
)

add_subdirectory(gnuradio_blocks)

target_link_libraries(source
        PUBLIC
        Gnuradio::blocks
        Gnuradio::iio
        Gnuradio::runtime
        Gnuradio::analog
        source_blocks
)

target_include_directories(source
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC gnuradio::gnuradio-runtime ${CMAKE_CURRENT_SOURCE_DIR}/../lib gnuradio::gnuradio-analog
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        PUBLIC $<INSTALL_INTERFACE:include>
)

target_include_directories(source PUBLIC gnuradio_blocks)