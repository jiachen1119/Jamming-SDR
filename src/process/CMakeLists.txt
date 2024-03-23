set(PROCESS_SOURCES ProcessThread.cpp)
set(PROCESS_HEADERS ProcessThread.h)

add_library(process ${PROCESS_HEADER} ${PROCESS_SOURCES})

set(QT5_LIBRARIES
        Qt5::Core
)
target_link_libraries(process PUBLIC ${QT5_LIBRARIES} sink lib source Gnuradio::blocks
        Gnuradio::iio
        Gnuradio::runtime
        Gnuradio::analog)
