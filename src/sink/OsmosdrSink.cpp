//
// Created by tang on 24-3-20.
//

#include "OsmosdrSink.h"

#include <utility>

OsmosdrSink::OsmosdrSink(unsigned int instream, unsigned int outstream, Concurrent_Queue<pmt::pmt_t>* queue) : in_stream_(instream), out_stream_(outstream)
{
    // 1. Make the driver instance
    driver_instance();

    // For LimeSDR: Set RX antenna
    if (!struct_.antenna_.empty())
    {
        osmosdr_sink_->set_antenna(struct_.antenna_, 0);
        std::cout << "Set TX Antenna: " << osmosdr_sink_->get_antenna(0) << '\n';
    }

    // 2 set sampling rate
    osmosdr_sink_->set_sample_rate(struct_.sample_rate_);
    std::cout << "Actual TX Rate: " << osmosdr_sink_->get_sample_rate() << " [SPS]...\n";

    // 3. set rx frequency
    osmosdr_sink_->set_center_freq(struct_.freq_);
    std::cout << "Actual TX Freq: " << osmosdr_sink_->get_center_freq() << " [Hz]...\n";

    // 4. set rx gain
    if (this->struct_.AGC_enabled_)
    {
        osmosdr_sink_->set_gain_mode(true);
        std::cout << "AGC enabled\n";
    }
    else
    {
        osmosdr_sink_->set_gain_mode(false);
        osmosdr_sink_->set_gain(struct_.gain_, 0);
        osmosdr_sink_->set_if_gain(struct_.rf_gain_, 0);
        osmosdr_sink_->set_bb_gain(struct_.if_gain_, 0);
        if (!struct_.osmosdr_args_.empty() && (struct_.osmosdr_args_.find("bladerf") != std::string::npos))
        {
            std::cout << "Actual LNA Gain: " << osmosdr_sink_->get_gain("LNA", 0) << " dB...\n";
            std::cout << "Actual VGA1 Gain: " << osmosdr_sink_->get_gain("VGA1", 0) << " dB...\n";
            std::cout << "Actual VGA2 Gain: " << osmosdr_sink_->get_gain("VGA2", 0) << " dB...\n";
        }
        else
        {
            if (!struct_.osmosdr_args_.empty() && (struct_.osmosdr_args_.find("xtrx") != std::string::npos))
            {
                osmosdr_sink_->set_gain(struct_.gain_, "LNA", 0);
                osmosdr_sink_->set_gain(struct_.rf_gain_, "TIA", 0);
                osmosdr_sink_->set_gain(struct_.if_gain_, "PGA", 0);
                std::cout << "Actual XTRX LNA Gain: " << osmosdr_sink_->get_gain("LNA", 0) << " dB...\n";
                std::cout << "Actual XTRX TIA Gain: " << osmosdr_sink_->get_gain("TIA", 0) << " dB...\n";
                std::cout << "Actual XTRX PGA Gain: " << osmosdr_sink_->get_gain("PGA", 0) << " dB...\n";
            }
            else
            {
                std::cout << "Actual TX Gain: " << osmosdr_sink_->get_gain() << " dB...\n";
            }
        }
    }

    // 5. set bandwidth
    if (struct_.if_bw_ > 0.0)
    {
        osmosdr_sink_->set_bandwidth(struct_.if_bw_, 0);
    }

    // Get actual bandwidth
    std::cout << "Actual Bandwidth: " << osmosdr_sink_->get_bandwidth(0) << " [Hz]...\n";

    if (samples_ != 0)
    {
        valve_ = make_valve(struct_.item_size_, samples_, queue);
    }

    if (out_stream_ > 0)
    {
    std::cerr << "A signal source does not have an output stream\n";
    }
    if (in_stream_ > 1)
    {
    std::cerr << "This implementation only supports one input stream\n";
    }
}

OsmosdrSink::OsmosdrSink(unsigned int instream, unsigned int outstream, FrontEnd in,
                         Concurrent_Queue<pmt::pmt_t> *queue) {
    struct_ = std::move(in);
    // 1. Make the driver instance
    driver_instance();

    // For LimeSDR: Set RX antenna
    if (!struct_.antenna_.empty())
    {
        osmosdr_sink_->set_antenna(struct_.antenna_, 0);
        std::cout << "Set TX Antenna: " << osmosdr_sink_->get_antenna(0) << '\n';
    }

    // 2 set sampling rate
    osmosdr_sink_->set_sample_rate(struct_.sample_rate_);
    std::cout << "Actual TX Rate: " << osmosdr_sink_->get_sample_rate() << " [SPS]...\n";

    // 3. set rx frequency
    osmosdr_sink_->set_center_freq(struct_.freq_);
    std::cout << "Actual TX Freq: " << osmosdr_sink_->get_center_freq() << " [Hz]...\n";

    // 4. set rx gain
    if (this->struct_.AGC_enabled_)
    {
        osmosdr_sink_->set_gain_mode(true);
        std::cout << "AGC enabled\n";
    }
    else
    {
        osmosdr_sink_->set_gain_mode(false);
        osmosdr_sink_->set_gain(struct_.gain_, 0);
        osmosdr_sink_->set_if_gain(struct_.rf_gain_, 0);
        osmosdr_sink_->set_bb_gain(struct_.if_gain_, 0);
        if (!struct_.osmosdr_args_.empty() && (struct_.osmosdr_args_.find("bladerf") != std::string::npos))
        {
            std::cout << "Actual LNA Gain: " << osmosdr_sink_->get_gain("LNA", 0) << " dB...\n";
            std::cout << "Actual VGA1 Gain: " << osmosdr_sink_->get_gain("VGA1", 0) << " dB...\n";
            std::cout << "Actual VGA2 Gain: " << osmosdr_sink_->get_gain("VGA2", 0) << " dB...\n";
        }
        else
        {
            if (!struct_.osmosdr_args_.empty() && (struct_.osmosdr_args_.find("xtrx") != std::string::npos))
            {
                osmosdr_sink_->set_gain(struct_.gain_, "LNA", 0);
                osmosdr_sink_->set_gain(struct_.rf_gain_, "TIA", 0);
                osmosdr_sink_->set_gain(struct_.if_gain_, "PGA", 0);
                std::cout << "Actual XTRX LNA Gain: " << osmosdr_sink_->get_gain("LNA", 0) << " dB...\n";
                std::cout << "Actual XTRX TIA Gain: " << osmosdr_sink_->get_gain("TIA", 0) << " dB...\n";
                std::cout << "Actual XTRX PGA Gain: " << osmosdr_sink_->get_gain("PGA", 0) << " dB...\n";
            }
            else
            {
                std::cout << "Actual TX Gain: " << osmosdr_sink_->get_gain() << " dB...\n";
            }
        }
    }

    // 5. set bandwidth
    if (struct_.if_bw_ > 0.0)
    {
        osmosdr_sink_->set_bandwidth(struct_.if_bw_, 0);
    }

    // Get actual bandwidth
    std::cout << "Actual Bandwidth: " << osmosdr_sink_->get_bandwidth(0) << " [Hz]...\n";

    if (samples_ != 0)
    {
        valve_ = make_valve(struct_.item_size_, samples_, queue);
    }

    if (out_stream_ > 0)
    {
        std::cerr << "A signal source does not have an output stream\n";
    }
    if (in_stream_ > 1)
    {
        std::cerr << "This implementation only supports one input stream\n";
    }
}

void OsmosdrSink::connect(const gr::top_block_sptr& top_block) {
    if (samples_ != 0){
        top_block->connect(valve_, 0, osmosdr_sink_, 0);
        std::cout << "connected value to osmosdr_sink_" << std::endl;
    }
    // if dumping is needed, you can connect the valve_ block to file sink block
}

void OsmosdrSink::disconnect(gr::top_block_sptr top_block) {
    if (samples_ != 0){
        top_block->disconnect(valve_, 0, osmosdr_sink_, 0);
        std::cout << "disconnected value to osmosdr_sink_" << std::endl;
    }
}

gr::basic_block_sptr OsmosdrSink::get_left_block() {
    if (samples_ != 0)
    {
        return valve_;
    }
    else
    {
        return osmosdr_sink_;
    }
}

gr::basic_block_sptr OsmosdrSink::get_right_block() {
    std::cout << "omsosdr_sink_ has no right block!";
    return {};
}

void OsmosdrSink::driver_instance() {
   try
   {
       if (!struct_.osmosdr_args_.empty())
       {
           std::cout << "OsmoSdr arguments: " << struct_.osmosdr_args_ << '\n';
       }
       osmosdr_sink_ = osmosdr::sink::make(struct_.osmosdr_args_);
   }
   catch (const boost::exception& e)
   {
       throw std::invalid_argument("Wrong OsmoSdr arguments");
   }
}


