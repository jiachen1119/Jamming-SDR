//
// Created by tang on 24-3-25.
//

#include "Chirp.h"
#include <gnuradio/math.h>

using output_type = gr_complex;

Chirp::Chirp(double samp_rate, double min_freq, double max_freq, double period)
        : gr::sync_block("Chirp",
                         gr::io_signature::make(0, 0, 0),
                         gr::io_signature::make(
                                 1, 1, sizeof(output_type))),
          type_(ChirpType::Trigonometric),
          samplingFrequency_(samp_rate),
          period_(period),
          maxFrequency_(max_freq),
          minFrequency_(min_freq),
          count_(0),
          freqIncCount_(0)
{
    this->reset_all();
}

Chirp::~Chirp() = default;

int Chirp::work(int noutput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items)
{
    auto out = static_cast<output_type*>(output_items[0]);
    float sin_num,cos_num;

    for(int i = 0; i < noutput_items ; i++)
    {
        nco_.sincos(&cos_num,&sin_num);
        *out++= gr_complex(sin_num,cos_num);
        // the purpose of sampleCount_ is to avoid too small adjust-frequency, leading to 0 in every step
        count_ += 2 * GR_M_PI * freqIncPerSample_.at(freqIncCount_) / samplingFrequency_;
        auto count_fixed = gr::fxpt::float_to_fixed((float) count_);
        if (count_fixed != 0){
            nco_.adjust_freq((float)count_);
            count_ = count_ - gr::fxpt::fixed_to_float(count_fixed);
        }
        nco_.step();
        freqIncCount_++;

        // judge whether the count out of vector range
        if (freqIncCount_ >= freqIncPerSample_.size() - 1){
            freqIncCount_ = 0;
        }

        auto curfreq = nco_.get_freq();
        if(curfreq > 2 * GR_M_PI * maxFrequency_ / samplingFrequency_){
            nco_.set_freq(2 * GR_M_PI * minFrequency_ / samplingFrequency_);
            freqIncCount_ = 0;
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

void Chirp::set_sampling_freq(double samp_rate)
{
    this->samplingFrequency_ = samp_rate;
    this->reset_all();
}

void Chirp::set_period(double period)
{
    this->period_ = period;
    this->reset_all();
}

void Chirp::set_min_freq(double min_freq)
{
    this->minFrequency_ = min_freq;
    this->reset_all();
}

void Chirp::set_max_freq(double max_freq)
{
    this->maxFrequency_ = max_freq;
    this->reset_all();
}

void Chirp::reset_all()
{
    std::cout << "reset all " << std::endl;
    freqIncPerSample_.clear();
    if (type_ == ChirpType::Linear){
        // set d_samples per loop
        double samples_per_loop = period_ * samplingFrequency_;
        samplesPerLoop_ = (int) samples_per_loop;

        // if the difference between the max freq and min freq is too small,
        // and the period is too long, the freq increasing per sample/sampling frequency is less than 1/2^32
        // set frequency increments per sample
        freqIncPerSample_ .push_back((maxFrequency_ - minFrequency_) / (double)samplesPerLoop_);
    }
    if (type_ == ChirpType::Quadratic){
        double samples_per_loop = period_ * samplingFrequency_;
        samplesPerLoop_ = (int) samples_per_loop;
        for (int i = 0; i < samplesPerLoop_; ++i) {
            freqIncPerSample_.push_back(minFrequency_ + (maxFrequency_ - minFrequency_)/(samplesPerLoop_^2)*(i^2));
        }
    }
    if (type_ == ChirpType::Trigonometric){
        double samples_per_loop = period_ * samplingFrequency_;
        samplesPerLoop_ = (int) samples_per_loop;
        for (int i = 0; i < samplesPerLoop_; ++i) {
            freqIncPerSample_.push_back(minFrequency_ + (maxFrequency_ - minFrequency_)/(samplesPerLoop_^3)*(i^3));
        }
    }

    nco_.set_freq(2 * GR_M_PI * minFrequency_ / samplingFrequency_);
}

