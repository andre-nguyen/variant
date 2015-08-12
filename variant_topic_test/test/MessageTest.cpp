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

#include <gtest/gtest.h>

#include <std_msgs/Bool.h>

#include <variant_msgs/Test.h>

#include <variant_topic_tools/Message.h>

using namespace variant_topic_tools;

TEST (Message, Conversion) {
  variant_msgs::Test m1;
  m1.builtin_int = 42;
  m1.builtin_string = "Test";
  variant_topic_tools::Message m2 = m1;
  variant_msgs::Test::Ptr m3 = m2.toInvariant<variant_msgs::Test>();
  
  EXPECT_EQ(ros::message_traits::datatype<variant_msgs::Test>(),
    m2.getType().getDataType());
  EXPECT_EQ(ros::message_traits::md5sum<variant_msgs::Test>(),
    m2.getType().getMD5Sum());
  EXPECT_EQ(ros::message_traits::definition<variant_msgs::Test>(),
    m2.getType().getDefinition());
  EXPECT_EQ(m1.builtin_int, m3->builtin_int);
  EXPECT_EQ(m1.builtin_string, m3->builtin_string);
  EXPECT_ANY_THROW(m2.toInvariant<std_msgs::Bool>());
}