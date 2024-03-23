//
// Created by tang on 24-3-22.
//

#ifndef JAMMING_SDR_BLOCKINTERFACE_H
#define JAMMING_SDR_BLOCKINTERFACE_H

#include <gnuradio/top_block.h>
#include <cassert>
#include <string>
#include <utility>  // for std::forward


// clang-format off
#if GNURADIO_USES_STD_POINTERS
#include <memory>
template <typename T>
using gnss_shared_ptr = std::shared_ptr<T>;
template <typename C, typename... Args>
gnss_shared_ptr<C> gnss_make_shared(Args &&... args)
{
    return std::make_shared<C>(std::forward<Args>(args)...);
}
#else
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
template <typename T>
using shared_ptr = boost::shared_ptr<T>;
template <typename C, typename... Args>
shared_ptr<C> make_shared(Args &&... args)
{
    return boost::make_shared<C>(std::forward<Args>(args)...);
}
#endif
// clang-format on

class BlockInterface
{
public:
    virtual ~BlockInterface() = default;
    virtual size_t item_size() = 0;
    virtual void connect(gr::top_block_sptr top_block) = 0;
    virtual void disconnect(gr::top_block_sptr top_block) = 0;

    virtual gr::basic_block_sptr get_left_block() = 0;
    virtual gr::basic_block_sptr get_right_block() = 0;

    /*!
     * \brief Start the flow of samples if needed.
     */
    virtual void start(){};
};

#endif //JAMMING_SDR_BLOCKINTERFACE_H
