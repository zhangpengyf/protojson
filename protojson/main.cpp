#include "json/json.h"
#include "json/json.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include "sample.pb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#ifdef _MSC_VER
#define snprintf _snprintf
#endif

using namespace ::google::protobuf;

void ProtoToJson(Json::Value& value, const ::google::protobuf::Message& msg);
void GetRepeatedField(Json::Value& value, const ::google::protobuf::Message& msg, const google::protobuf::FieldDescriptor *field, const ::google::protobuf::Reflection *reflection);

void ProtoToJson(Json::Value& value, const ::google::protobuf::Message& msg) {
	const Descriptor* descriptor = msg.GetDescriptor();
	const Reflection* reflection = msg.GetReflection();

	const int count = descriptor->field_count();

	for (int i = 0; i < count; ++i) {
		const FieldDescriptor* field = descriptor->field(i);

		if (field->is_repeated()) {
			if (reflection->FieldSize(msg, field) > 0) {
				GetRepeatedField(value[field->name()], msg, field, reflection);
			}
			continue;
		}

		if (!reflection->HasField(msg, field)) {
			continue;
		}

		switch (field->type()) {
		case FieldDescriptor::TYPE_MESSAGE:
		{
			const Message& tmp_msg = reflection->GetMessage(msg, field);
			if (0 != tmp_msg.ByteSize()) {
				ProtoToJson(value[field->name()], tmp_msg);
			}
		}
		break;
		case FieldDescriptor::TYPE_INT32:
			value[field->name()] = reflection->GetInt32(msg, field);
			break;
		case FieldDescriptor::TYPE_UINT32:
			value[field->name()] = reflection->GetUInt32(msg, field);
			break;
		case FieldDescriptor::TYPE_INT64:
		{
			static char int64str[25];
			memset(int64str, 0, sizeof(int64str));
			snprintf(int64str, sizeof(int64str), "%lld", (long long)reflection->GetInt64(msg, field));
			value[field->name()] = int64str;
		}
		break;
		case FieldDescriptor::TYPE_UINT64:
		{
			static char uint64str[25];
			memset(uint64str, 0, sizeof(uint64str));
			snprintf(uint64str, sizeof(uint64str), "%llu", (unsigned long long)reflection->GetUInt64(msg, field));
			value[field->name()] = uint64str;
		}
		break;
		case FieldDescriptor::TYPE_STRING:
		case FieldDescriptor::TYPE_BYTES:
		{
			value[field->name()] = reflection->GetString(msg, field);
		}
		break;
		case FieldDescriptor::TYPE_ENUM:
			value[field->name()] = reflection->GetEnumValue(msg, field);
			break;
		default:
			break;
		}
	}
}

void GetRepeatedField(Json::Value& value, const ::google::protobuf::Message& msg, const google::protobuf::FieldDescriptor *field, const ::google::protobuf::Reflection *reflection) {
	if (NULL == field || NULL == reflection) {
		ProtoToJson(value, msg);
	}

	for (int i = 0; i < reflection->FieldSize(msg, field); ++i) {
		Json::Value tmp_value;
		switch (field->type()) {
		case FieldDescriptor::TYPE_MESSAGE:
		{
			const Message& tmp_msg = reflection->GetRepeatedMessage(msg, field, i);
			if (0 != tmp_msg.ByteSize()) {
				ProtoToJson(tmp_value, tmp_msg);
			}
		}
		break;
		case FieldDescriptor::TYPE_INT32:
			tmp_value = reflection->GetRepeatedInt32(msg, field, i);
			break;
		case FieldDescriptor::TYPE_UINT32:
			tmp_value = reflection->GetRepeatedUInt32(msg, field, i);
			break;
		case FieldDescriptor::TYPE_INT64:
		{
			static char int64str[25];
			memset(int64str, 0, sizeof(int64str));
			snprintf(int64str, sizeof(int64str), "%lld", (long long)reflection->GetRepeatedInt64(msg, field, i));
			tmp_value = int64str;
		}
		break;
		case FieldDescriptor::TYPE_UINT64:
		{
			static char uint64str[25];
			memset(uint64str, 0, sizeof(uint64str));
			snprintf(uint64str, sizeof(uint64str), "%llu", (unsigned long long)reflection->GetRepeatedUInt64(msg, field, i));
			tmp_value = uint64str;
		}
		break;
		case FieldDescriptor::TYPE_STRING:
		case FieldDescriptor::TYPE_BYTES:
			tmp_value = reflection->GetRepeatedString(msg, field, i);
			break;
		default:
			break;
		}
		value.append(tmp_value);
	}
}
int main(){
	protojson::Person person;
	person.set_name("zhangpeng");
	person.set_email("zhangpeng01@fenbi.com");
	person.set_id(1001);

	protojson::Person_PhoneNumber* phone1 = person.add_phone();
	phone1->set_number("15601196529");
	phone1->set_type(protojson::Person_PhoneType_HOME);

	protojson::Person_PhoneNumber* phone2 = person.add_phone();
	phone2->set_number("13693646751");
	phone2->set_type(protojson::Person_PhoneType_MOBILE);

	Json::Value value;
	ProtoToJson(value, person);
	std::string str = value.toStyledString();
	std::cout << str;
	return 0;
}

