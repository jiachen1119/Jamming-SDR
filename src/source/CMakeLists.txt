# set osmosdr variable
if(GROSMOSDR_FOUND)
    list(APPEND SOURCE_SOURCES SignalSource.cpp)
    list(APPEND SOURCE_HEADERS SignalSource.h)
endif()

if(USE_CMAKE_TARGET_SOURCES)
    add_library(source STATIC)
    target_sources(source
            PRIVATE
            ${SOURCE_SOURCES}
            PUBLIC
            ${SOURCE_HEADERS}
    )
else()
    source_group(Headers FILES ${SOURCE_HEADERS})
    add_library(source
            ${SOURCE_SOURCES}
            ${SOURCE_HEADERS}
    )
endif()

if (GNURADIO_FOUND)
    target_link_libraries(sink
            PUBLIC
            Gnuradio::blocks
            Gnuradio::iio
            Gnuradio::runtime
            Gnuradio::analog
    )
    target_include_directories(sink
            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            PUBLIC gnuradio::gnuradio-runtime ${CMAKE_CURRENT_SOURCE_DIR}/../lib gnuradio::gnuradio-analog
            PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
            PUBLIC $<INSTALL_INTERFACE:include>
    )
endif ()
