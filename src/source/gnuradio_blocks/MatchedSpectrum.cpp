//
// Created by tang on 24-3-28.
//

#include "MatchedSpectrum.h"

MatchedSpectrum::MatchedSpectrum(double samp_freq, double chip_rate) : gr::sync_block("MatchedSpectrum",
                                                                                      gr::io_signature::make(0,0,0),
                                                                                      gr::io_signature::make(1,1,sizeof(gr_complex))),
                                                                                      samplingFreq_(samp_freq),chipRate_(chip_rate),currentValue_(1),rng_(0,0,2)
{
    // Limits are [minimum, maximum)
    rng_.set_integer_limits(0,2);
    rng_.reseed(1);
    samplePerChip_ = (int) round(samplingFreq_/chipRate_);
}

int
MatchedSpectrum::work(int noutput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items) {
    auto out = static_cast<gr_complex *>(output_items[0]);
    int count = 0;
    while(count < noutput_items)
    {
        while(currentSampleCount_ < samplePerChip_)
        {
            *out++ = gr_complex(currentValue_,0);
            currentSampleCount_++;
            count++;
        }
        int temp = rng_.ran_int();
        if(temp == 0) currentValue_ = -1;
        else currentValue_ = 1;

        currentSampleCount_ = 0;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}
