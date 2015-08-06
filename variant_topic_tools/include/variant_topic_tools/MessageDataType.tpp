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

#include <variant_topic_tools/Exceptions.h>

namespace variant_topic_tools {

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <typename T>
MessageDataType::ImplT<T>::ImplT() :
  Impl(ros::message_traits::template definition<T>()) {
  BOOST_STATIC_ASSERT(ros::message_traits::IsMessage<T>::value);
}

template <typename T>
MessageDataType::ImplT<T>::~ImplT() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

template <typename T>
const std::string& MessageDataType::ImplT<T>::getIdentifier() const {
  static std::string identifier(ros::message_traits::template datatype<T>());
  return identifier;
}

template <typename T>
size_t MessageDataType::ImplT<T>::getSize() const {
  return ros::message_traits::template isFixedSize<T>() ? sizeof(T) : 0;
}

template <typename T>
const std::string& MessageDataType::ImplT<T>::getMD5Sum() const {
  static std::string md5Sum(ros::message_traits::template md5sum<T>());
  return md5Sum;
}

template <typename T>
const std::string& MessageDataType::ImplT<T>::getDefinition() const {
  static std::string definition(ros::message_traits::template definition<T>());
  return definition;
}

template <typename T>
bool MessageDataType::ImplT<T>::isSimple() const {
  return ros::message_traits::template isSimple<T>();
}

template <typename T>
bool MessageDataType::ImplT<T>::isFixedSize() const {
  return ros::message_traits::template isFixedSize<T>();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

template <typename T> MessageDataType MessageDataType::create() {
  MessageDataType messageDataType;
  messageDataType.impl.reset(new ImplT<T>());
  
  return messageDataType;
}

template <typename T> MessageConstant MessageDataType::addConstant(const
    std::string& name, const T& value) {
  return this->addConstant(name, Variant(value));
}

template <typename T> MessageVariable MessageDataType::addVariable(const
    std::string& name) {
  return this->addVariable(name, typeid(T));
}

template <typename T>
void MessageDataType::ImplT<T>::addMember(const MessageMember& member) {
  throw ImmutableDataTypeException();
}

}