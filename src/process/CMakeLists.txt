set(PROCESS_SOURCES ProcessThread.cpp)
set(PROCESS_HEADERS ProcessThread.h)

add_library(process ${PROCESS_HEADER} ${PROCESS_SOURCES})

set(QT5_LIBRARIES
        Qt5::Core
)
target_link_libraries(process PUBLIC ${QT5_LIBRARIES} sink lib source_blocks source_adapters Gnuradio::blocks
        Gnuradio::iio
        Gnuradio::runtime
        Gnuradio::analog
        lib
)
target_include_directories(process
        PUBLIC ${PROJECT_SOURCE_DIR}/src/source/adapters
        ${PROJECT_SOURCE_DIR}/src/source/gnuradio_blocks
        ${PROJECT_SOURCE_DIR}/src/sink
)
