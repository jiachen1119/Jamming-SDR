//
// Created by tang on 24-3-25.
//

#ifndef JAMMING_SDR_CHIRP_H
#define JAMMING_SDR_CHIRP_H

#include <gnuradio/fxpt_nco.h>
#include <gnuradio/sync_block.h>

enum ChirpType{
    Linear,
    Quadratic,
    Cubic,
    Exponential,
    Logarithmic,
    Trigonometric };

class Chirp : public gr::sync_block{

public:
    Chirp(double samp_rate, double min_freq, double max_freq, double period, ChirpType type);
    ~Chirp() override;

    static std::shared_ptr<Chirp> make(double samp_rate, double min_freq, double max_freq, double period, ChirpType type)
    {
        return gnuradio::make_block_sptr<Chirp>(samp_rate, min_freq, max_freq, period, type);
    }

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    void set_sampling_freq(double samp_rate);
    void set_period(double period);
    void set_max_freq(double max_freq);
    void set_min_freq(double min_freq);

    void reset_all();

private:
    ChirpType type_;
    double samplingFrequency_;
    double period_;
    double maxFrequency_;
    double minFrequency_;

    int samplesPerLoop_;
    std::vector<double> freqIncPerSample_;
    gr::fxpt_nco nco_;
    double count_;
    int freqIncCount_;

};
#endif //JAMMING_SDR_CHIRP_H
