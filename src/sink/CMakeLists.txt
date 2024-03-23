# set osmosdr variable
if(GROSMOSDR_FOUND)
    list(APPEND SINK_OPT_SOURCES OsmosdrSink.cpp)
    list(APPEND SINK_OPT_HEADERS OsmosdrSink.h)
endif()

set(SINK_SOURCES
        ${SINK_OPT_SOURCES}
)

set(SINK_HEADERS
        ${SINK_OPT_HEADERS}
)

if(USE_CMAKE_TARGET_SOURCES)
    add_library(sink STATIC)
    target_sources(sink
            PRIVATE
            ${SINK_SOURCES}
            PUBLIC
            ${SINK_HEADERS}
    )
else()
    source_group(Headers FILES ${SINK_HEADERS})
    add_library(sink
            ${SINK_SOURCES}
            ${SINK_HEADERS}
    )
endif()

if(GROSMOSDR_FOUND)
    target_link_libraries(sink
    PUBLIC
            Gnuradio::osmosdr
    )
endif ()

if (GNURADIO_FOUND)
    target_link_libraries(sink
    PUBLIC
            Gnuradio::blocks
            Gnuradio::iio
            Gnuradio::runtime
    )
    target_include_directories(sink
            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
            PUBLIC gnuradio::gnuradio-runtime ${CMAKE_CURRENT_SOURCE_DIR}/../lib
            PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
            PUBLIC $<INSTALL_INTERFACE:include>
    )
endif ()
