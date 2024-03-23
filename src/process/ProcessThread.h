//
// Created by tang on 24-3-23.
//

#ifndef JAMMING_SDR_PROCESSTHREAD_H
#define JAMMING_SDR_PROCESSTHREAD_H

#include <QThread>
#include "OsmosdrSink.h"
#include "SignalSource.h"

class ProcessThread : public QThread{
Q_OBJECT
public:
    ProcessThread(QObject *parent);

    void run() override;
    ~ProcessThread() override;

    void startTopBlock();
    void stopTopBlock();

private:
    std::shared_ptr<gr::top_block> topBlock_;
    std::shared_ptr<Concurrent_Queue<pmt::pmt_t>> queue_;
    std::shared_ptr<OsmosdrSink> sink_;
    std::shared_ptr<SignalSource> source_;

};


#endif //JAMMING_SDR_PROCESSTHREAD_H
