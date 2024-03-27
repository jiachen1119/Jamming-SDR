//
// Created by tang on 24-3-23.
//

#include "ProcessThread.h"

ProcessThread::ProcessThread(QObject *parent) : QThread(parent) {
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,queue_.get());
//    source_ = std::make_unique<SignalSource>(0,1,gr::analog::gr_waveform_t::GR_SIN_WAVE,4e6,1575.42e6,1,0,0);
    source_ = std::make_unique<ChirpJamming>(0,1,4e6,1000,100000,10, ChirpType::Linear);
    topBlock_->connect(source_->get_right_block(),0,sink_->get_left_block(),0);
}

ProcessThread::ProcessThread(QObject *parent, const FrontEnd &in_struct, const ChirpStruct& jamming_struct) : QThread(parent){
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,in_struct,queue_.get());

    ChirpType type;
    if (jamming_struct.type == "Non-linear")
        type = Quadratic;
    else
        type = Linear;
    source_ = std::make_unique<ChirpJamming>(0,1,
                                             jamming_struct.sampling_freq,
                                             jamming_struct.min_freq,
                                             jamming_struct.max_freq,
                                             jamming_struct.period, type);
    std::cout << "Chirp Jamming" << std::endl;
    topBlock_->connect(source_->get_right_block(),0,sink_->get_left_block(),0);
}

ProcessThread::ProcessThread(QObject *parent, const FrontEnd &in_struct, SingleToneStruct jamming_struct) : QThread(parent) {
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,in_struct,queue_.get());

    source_ = std::make_unique<SignalSource>(0,1,
                                             gr::analog::gr_waveform_t::GR_SIN_WAVE,
                                             jamming_struct.sampling_freq,
                                             jamming_struct.wave_freq,
                                             jamming_struct.ampl,0,0);
    std::cout << "Single Tone Jamming" << std::endl;
    topBlock_->connect(source_->get_right_block(),0,sink_->get_left_block(),0);
}

ProcessThread::ProcessThread(QObject *parent, const FrontEnd &in_struct, SquareStruct jamming_struct) : QThread(parent) {
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,in_struct,queue_.get());

    source_ = std::make_unique<SignalSource>(0,1,
                                             gr::analog::gr_waveform_t::GR_SQR_WAVE,
                                             jamming_struct.sampling_freq,
                                             jamming_struct.wave_freq,
                                             jamming_struct.ampl,0,0);
    std::cout << "Square Jamming" << std::endl;
    topBlock_->connect(source_->get_right_block(),0,sink_->get_left_block(),0);
}

ProcessThread::ProcessThread(QObject *parent, const FrontEnd &in_struct, TriangeStruct jamming_struct) : QThread(parent) {
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,in_struct,queue_.get());

    source_ = std::make_unique<SignalSource>(0,1,
                                             gr::analog::gr_waveform_t::GR_TRI_WAVE,
                                             jamming_struct.sampling_freq,
                                             jamming_struct.wave_freq,
                                             jamming_struct.ampl,0,0);
    std::cout << "Triangle Jamming" << std::endl;
    topBlock_->connect(source_->get_right_block(),0,sink_->get_left_block(),0);
}

ProcessThread::ProcessThread(QObject *parent, const FrontEnd &in_struct, SawToothStruct jamming_struct) : QThread(parent) {
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,in_struct,queue_.get());

    source_ = std::make_unique<SignalSource>(0,1,
                                             gr::analog::gr_waveform_t::GR_SAW_WAVE,
                                             jamming_struct.sampling_freq,
                                             jamming_struct.wave_freq,
                                             jamming_struct.ampl,0,0);
    std::cout << "Saw Tooth Jamming" << std::endl;
    topBlock_->connect(source_->get_right_block(),0,sink_->get_left_block(),0);
}

ProcessThread::ProcessThread(QObject *parent, const FrontEnd &in_struct, MatchedStruct jamming_struct) : QThread(parent) {
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,in_struct,queue_.get());

    source_ = std::make_unique<MatchedSpectrumJamming>(0,1,jamming_struct.sampling_freq,jamming_struct.chip_rate);
    std::cout << "Matched Spectrum Jamming" << std::endl;
    topBlock_->connect(source_->get_right_block(),0,sink_->get_left_block(),0);
}

void ProcessThread::run() {

    QThread::msleep(500);
    topBlock_->start();
    topBlock_->wait();
}

ProcessThread::~ProcessThread() {
    std::cout << "destruction function is called!";
    topBlock_->stop();
}

void ProcessThread::startTopBlock() {
    topBlock_->run();
}

void ProcessThread::stopTopBlock() {
    topBlock_->stop();
}

void ProcessThread::lockTopBlock() {
    topBlock_->lock();
}

void ProcessThread::unlockTopBlock() {
    topBlock_->unlock();
}


