aux_source_directory(. LIB_SOURCES)
list(APPEND LIB_HEADERS ValveBlock.h concurrent_queue.h command_event.h BlockInterface.h Variable.h)

if(USE_CMAKE_TARGET_SOURCES)
    add_library(lib STATIC)
    target_sources(lib
            PRIVATE
            ${LIB_SOURCES}
            PUBLIC
            ${LIB_HEADERS}
    )
else()
    source_group(Headers FILES ${LIB_HEADERS})
    add_library(lib
            ${LIB_SOURCES}
            ${LIB_HEADERS}
    )
endif()

target_link_libraries(lib source_blocks)