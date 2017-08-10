/*
*  Copyright (c) 2017 zhangpengyf@gmail.com All Rights Reserved.
*
*  Use of this source code is governed by a BSD-style license.
*/

#ifndef PROTO_2_JSON_H_INCLUDE
#define PROTO_2_JSON_H_INCLUDE

#include "json/json.h"
#include "json/json.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

void ProtoToJson(std::string& value, const ::google::protobuf::Message& msg);
void ProtoToJson(Json::Value& value, const ::google::protobuf::Message& msg);

#endif
