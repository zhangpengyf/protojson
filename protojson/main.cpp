#include "sample.pb.h"
#include "protojson.h"
#include <iostream>

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

	std::string value;
	ProtoToJson(value, person);
	std::cout << value;
	return 0;
}
