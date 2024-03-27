//
// Created by tang on 24-3-28.
//

#ifndef JAMMING_SDR_MATCHEDSPECTRUM_H
#define JAMMING_SDR_MATCHEDSPECTRUM_H

#include <gnuradio/sync_block.h>
#include <gnuradio/random.h>

class MatchedSpectrum : public gr::sync_block{
public:
    MatchedSpectrum(double samp_freq, double chip_rate);
    ~MatchedSpectrum() override = default;

    static std::shared_ptr<MatchedSpectrum> make(double samp_rate, double chip_rate){
        return gnuradio::make_block_sptr<MatchedSpectrum>(samp_rate,chip_rate);
    }

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

private:
    double samplingFreq_;
    double chipRate_;

    int currentValue_;
    int samplePerChip_;
    int currentSampleCount_;

    gr::random rng_;

};


#endif //JAMMING_SDR_MATCHEDSPECTRUM_H
