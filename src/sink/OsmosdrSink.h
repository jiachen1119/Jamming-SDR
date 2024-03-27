//
// Created by tang on 24-3-20.
//

#ifndef JAMMING_SDR_OSMOSDRSINK_H
#define JAMMING_SDR_OSMOSDRSINK_H

#include <osmosdr/sink.h>
#include <gnuradio/blocks/file_sink.h>
#include <gnuradio/runtime_types.h>
#include <pmt/pmt.h>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <gnuradio/top_block.h>
#include <osmosdr/source.h>
#include "ValveBlock.h"

typedef struct FrontEnd{
    double sample_rate_ = 4e6;
    double freq_ = 1575.42e6;
    double gain_ = 10;
    double if_gain_ = 10;
    double rf_gain_ = 10;
    double if_bw_ = 0;
    bool AGC_enabled_ = false;

    std::string item_type_ = "gr_complex";
    size_t item_size_ = sizeof(gr_complex);

    std::string antenna_;
    std::string osmosdr_args_ = "hackrf=0";
}FrontEnd;


class OsmosdrSink {
public:
    OsmosdrSink(unsigned int instream, unsigned int outstream, Concurrent_Queue<pmt::pmt_t>* queue);
    OsmosdrSink(unsigned int instream, unsigned int outstream, FrontEnd in, Concurrent_Queue<pmt::pmt_t>* queue);
    ~OsmosdrSink() = default;

    void connect(const gr::top_block_sptr& top_block);
    void disconnect(gr::top_block_sptr top_block);
    gr::basic_block_sptr get_left_block();
    gr::basic_block_sptr get_right_block();

    void driver_instance();

private:
    osmosdr::sink::sptr osmosdr_sink_;
    std::shared_ptr<gr::block> valve_;

    FrontEnd struct_;
    int64_t samples_ = 0;

    unsigned int in_stream_;
    unsigned int out_stream_;

};


#endif //JAMMING_SDR_OSMOSDRSINK_H
