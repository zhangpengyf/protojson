# protojson
Decode protobuf to json format

# interface is simple

    void ProtoToJson(std::string& value, const ::google::protobuf::Message& msg);
    void ProtoToJson(Json::Value& value, const ::google::protobuf::Message& msg);

# dependency

## jsoncpp

## protobuf