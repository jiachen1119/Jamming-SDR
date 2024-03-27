set(SOURCE_BLOCKS_SOURCES
        Chirp.cpp
)

set(SOURCE_BLOCKS_HEADERS
        Chirp.h
)

list(SORT SOURCE_BLOCKS_SOURCES)
list(SORT SOURCE_BLOCKS_HEADERS)

add_library(source_blocks ${SOURCE_BLOCKS_SOURCES} ${SOURCE_BLOCKS_HEADERS})
target_link_libraries(source_blocks
        Gnuradio::runtime
)
