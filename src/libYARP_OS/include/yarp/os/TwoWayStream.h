/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 * Copyright (C) 2006-2010 RobotCub Consortium
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_OS_TWOWAYSTREAM_H
#define YARP_OS_TWOWAYSTREAM_H

#include <yarp/conf/numeric.h>

#include <yarp/os/Contact.h>
#include <yarp/os/InputStream.h>
#include <yarp/os/OutputStream.h>

namespace yarp {
namespace os {

/**
 * A stream which can be asked to perform bidirectional communication.
 * It need not actually be capable of communication in both directions,
 * in which case it should fail if requested to communicate in an
 * unsupported direction.
 */
class YARP_OS_API TwoWayStream
{
public:
    /**
     * Destructor.
     */
    virtual ~TwoWayStream();

    /**
     * Get an InputStream to read from.
     *
     * @return the InputStream associated with this object.
     */
    virtual InputStream& getInputStream() = 0;

    /**
     * Get an OutputStream to write to.
     *
     * @return the InputStream associated with this object.
     */
    virtual OutputStream& getOutputStream() = 0;

    /**
     * Get the address of the local side of the stream.
     *
     * @return the address of the local side of the stream.
     * The address will be tagged as invalid if the stream is not set up.
     */
    virtual const Contact& getLocalAddress() const = 0;

    /**
     * Get the address of the remote side of the stream.
     *
     * @return the address of the remote side of the stream.
     * The address will be tagged as invalid if the stream is not set up.
     */
    virtual const Contact& getRemoteAddress() const = 0;

    /**
     *
     * Check if the stream is ok or in an error state.
     *
     * @return true iff the stream is ok
     *
     */
    virtual bool isOk() const = 0;

    /**
     * Reset the stream.
     */
    virtual void reset() = 0;

    /**
     *
     * Terminate the stream.
     *
     */
    virtual void close() = 0;

    /**
     *
     * Mark the beginning of a logical packet.  This is a unit that
     * should be treated in an atomic fashion by YARP.  If any part
     * is corrupted, the whole should be dropped.
     *
     */
    virtual void beginPacket() = 0;

    /**
     *
     * Mark the end of a logical packet (see beginPacket).
     *
     */
    virtual void endPacket() = 0;
};


/**
 * A "null" stream, always invalid.
 */
class YARP_OS_API NullStream : public TwoWayStream, public InputStream, public OutputStream
{
private:
    Contact address;

public:
    virtual ~NullStream();

    InputStream& getInputStream() override;
    OutputStream& getOutputStream() override;

    const Contact& getLocalAddress() const override;
    const Contact& getRemoteAddress() const override;

    bool isOk() const override;
    void reset() override;
    void close() override;
    void beginPacket() override;
    void endPacket() override;

    using yarp::os::InputStream::read;
    yarp::conf::ssize_t read(Bytes& b) override;

    using yarp::os::OutputStream::write;
    void write(const Bytes& b) override;
};

} // namespace os
} // namespace yarp

#endif // YARP_OS_TWOWAYSTREAM_H
