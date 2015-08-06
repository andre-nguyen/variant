/******************************************************************************
 * Copyright (C) 2014 by Ralf Kaestner                                        *
 * ralf.kaestner@gmail.com                                                    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file Message.h
  * \brief Header file providing the Message class interface
  */

#ifndef VARIANT_TOPIC_TOOLS_MESSAGE_H
#define VARIANT_TOPIC_TOOLS_MESSAGE_H

#include <vector>
#include <boost/concept_check.hpp>

#include <ros/ros.h>

#include <variant_msgs/Variant.h>

#include <variant_topic_tools/MessageHeader.h>
#include <variant_topic_tools/MessageType.h>

namespace variant_topic_tools {
  /** \brief Variant message type
    * 
    * The variant message type can be used to subscribe to any topic.
    * It is heavily inspired by the ShapeShifter message type provided
    * in the topic_tools package.
    */
  class Message {
  public:
    /** \brief Default constructor
      */ 
    Message(const MessageHeader& header = MessageHeader(), const
      MessageType& type = MessageType(), const std::vector<uint8_t>&
      data = std::vector<uint8_t>());
    
    /** \brief Copy constructor
      */ 
    Message(const Message& src);
    
    /** \brief Destructor
      */ 
    ~Message();

    /** \brief Access the message header
      */
    void setHeader(const MessageHeader& header);
    MessageHeader& getHeader();
    const MessageHeader& getHeader() const;
    
    /** \brief Access the message type
      */
    void setType(const MessageType& type);
    MessageType& getType();
    const MessageType& getType() const;

    /** \brief Access the message data
      */
    void setData(const std::vector<uint8_t>& data);
    std::vector<uint8_t>& getData();
    const std::vector<uint8_t>& getData() const;
    
    /** \brief Access the message size
      */
    uint32_t getSize() const;

    /** \brief Morph the message
      */
    template <class Invariant> void morph();

    /** \brief Attempt to convert the message to a variant
      */
    boost::shared_ptr<variant_msgs::Variant> toVariant() const;
      
    /** \brief Attempt to convert the message to an invariant
      */
    template <class Invariant> boost::shared_ptr<Invariant> toInvariant()
      const;

    /** \brief Read serialized message contents from stream
      */ 
    template <typename Stream> void read(Stream& stream);

    /** \brief Write serialized message contents to stream
      */
    template <typename Stream> void write(Stream& stream) const;

  protected:
    MessageHeader header;
    MessageType type;
    std::vector<uint8_t> data;
  };
};

#include <variant_topic_tools/Message.tpp>

#include <variant_topic_tools/MessageTraits.h>
#include <variant_topic_tools/Serialization.h>

#endif