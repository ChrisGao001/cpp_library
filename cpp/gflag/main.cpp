#include  <gflags/gflags.h>
#include <iostream>

DECLARE_string(name);
DECLARE_int32(age);

DEFINE_string(name, "lili", "name ...");
DEFINE_int32(age, 11, "age ...");

int main(int argc, char**argv) {
	const char* flag_file = "./gflag.conf";
        google::SetCommandLineOption("flagfile", flag_file);
        // google::ParseCommandLineFlags(&argc, &argv, false);
	std::cout << "name:" << FLAGS_name << ",age:" << FLAGS_age << std::endl;

	return 0;
}


