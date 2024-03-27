# set osmosdr variable
list(APPEND SOURCE_ADAPTERS_SOURCES SignalSource.cpp)
list(APPEND SOURCE_ADAPTERS_HEADERS SignalSource.h)

add_library(source_adapters
        ${SOURCE_ADAPTERS_SOURCES}
        ${SOURCE_ADAPTERS_HEADERS}
)

target_link_libraries(source_adapters
        PUBLIC
        Gnuradio::blocks
        Gnuradio::iio
        Gnuradio::runtime
        Gnuradio::analog
        source_blocks
        lib
)

target_include_directories(source_adapters
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC gnuradio::gnuradio-runtime ${CMAKE_CURRENT_SOURCE_DIR}/../lib gnuradio::gnuradio-analog
        PUBLIC ${PROJECT_SOURCE_DIR}/src/lib
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        PUBLIC $<INSTALL_INTERFACE:include>
)