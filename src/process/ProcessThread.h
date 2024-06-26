//
// Created by tang on 24-3-23.
//

#ifndef JAMMING_SDR_PROCESSTHREAD_H
#define JAMMING_SDR_PROCESSTHREAD_H

#include <QThread>
#include "OsmosdrSink.h"
#include "SignalSource.h"
#include "ChirpJamming.h"
#include "MatchedSpectrumJamming.h"
#include "Variable.h"
#include <QObject>

class ProcessThread : public QThread{
Q_OBJECT
public:
    ProcessThread(QObject *parent);
    ProcessThread(QObject *parent, const FrontEnd& in_struct, const ChirpStruct& jamming_struct);
    ProcessThread(QObject *parent, const FrontEnd& in_struct, SingleToneStruct jamming_struct);
    ProcessThread(QObject *parent, const FrontEnd& in_struct, SquareStruct jamming_struct);
    ProcessThread(QObject *parent, const FrontEnd& in_struct, TriangeStruct jamming_struct);
    ProcessThread(QObject *parent, const FrontEnd& in_struct, SawToothStruct jamming_struct);
    ProcessThread(QObject *parent, const FrontEnd& in_struct, MatchedStruct jamming_struct);

    void run() override;
    ~ProcessThread() override;

    void startTopBlock();
    void stopTopBlock();
    void lockTopBlock();
    void unlockTopBlock();

private:
    std::shared_ptr<gr::top_block> topBlock_;
    std::shared_ptr<Concurrent_Queue<pmt::pmt_t>> queue_;
    std::shared_ptr<OsmosdrSink> sink_;
    std::shared_ptr<BlockInterface> source_;
//    std::shared_ptr<Chirp> source_;
};


#endif //JAMMING_SDR_PROCESSTHREAD_H
