//
// Created by tang on 24-3-23.
//

#include "ProcessThread.h"

ProcessThread::ProcessThread(QObject *parent) : QThread(parent) {
    // the instantiation of top block is necessary
    topBlock_ = gr::make_top_block("Jamming_SDR Flowgraph");
    queue_ = std::make_shared<Concurrent_Queue<pmt::pmt_t>>();
    sink_ = std::make_unique<OsmosdrSink>(1,0,queue_.get());
    source_ = std::make_unique<SignalSource>(0,1,gr::analog::gr_waveform_t::GR_SIN_WAVE,
                                                 4e6,1575.42e6,1,0,0);
//    source_ = Chirp::make(4e6,1000,10000,10);
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


