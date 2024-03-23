//
// Created by tang on 24-3-21.
//

#ifndef JAMMING_SDR_VALVEBLOCK_H
#define JAMMING_SDR_VALVEBLOCK_H

#include "concurrent_queue.h"
#include <gnuradio/sync_block.h>  // for sync_block
#include <gnuradio/types.h>       // for gr_vector_const_void_star
#include <pmt/pmt.h>
#include <cstddef>  // for size_t
#include <cstdint>

/** \addtogroup Signal_Source
 * \{ */
/** \addtogroup Signal_Source_libs
 * \{ */


class ValveBlock;

std::shared_ptr<ValveBlock> make_valve(
        size_t sizeof_stream_item,
        uint64_t nitems,
        Concurrent_Queue<pmt::pmt_t>* queue);

std::shared_ptr<ValveBlock> make_valve(
        size_t sizeof_stream_item,
        uint64_t nitems,
        Concurrent_Queue<pmt::pmt_t>* queue,
        bool stop_flowgraph);

/*!
 * \brief Implementation of a GNU Radio block that sends a STOP message to the
 * control queue right after a specific number of samples have passed through it.
 */
class ValveBlock : public gr::sync_block
{
public:
    void open_valve();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

private:
    friend std::shared_ptr<ValveBlock> make_valve(
            size_t sizeof_stream_item,
            uint64_t nitems,
            Concurrent_Queue<pmt::pmt_t>* queue);

    friend std::shared_ptr<ValveBlock> make_valve(
            size_t sizeof_stream_item,
            uint64_t nitems,
            Concurrent_Queue<pmt::pmt_t>* queue,
            bool stop_flowgraph);

    ValveBlock(size_t sizeof_stream_item,
                   uint64_t nitems,
                   Concurrent_Queue<pmt::pmt_t>* queue, bool stop_flowgraph);

    uint64_t d_nitems;
    uint64_t d_ncopied_items;
    Concurrent_Queue<pmt::pmt_t>* d_queue;
    bool d_stop_flowgraph;
    bool d_open_valve;
};

#endif //JAMMING_SDR_VALVEBLOCK_H
