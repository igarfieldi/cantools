#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

std::vector<std::string> split(const std::string &str) {
	std::istringstream iss(str);
	
	std::vector<std::string> result;
	
	return std::vector<std::string>(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
}

int main(int argc, char **argv) {
	if(argc < 2) {
		std::cout << "Usage: " << argv[0] << " file" << std::endl;
		std::cout << "Puts out a wireshark filter ignoring all CAN-IDs logged in the provided file" << std::endl;
		return -1;
	}
	
	std::ifstream in(argv[1]);
	std::vector<size_t> ids;
	
	std::string line;
	
	while(std::getline(in, line)) {
		ids.push_back(std::stoull(split(line)[1], 0, 16));
	}
	
	std::sort(ids.begin(), ids.end());
	ids.erase(std::unique(ids.begin(), ids.end()), ids.end());
	
	std::cout << std::hex;
	
	for(size_t id : ids) {
		std::cout << "(can.id!=0x" << id << ") and ";
	}
	std::cout << std::dec << std::endl;
	
	return 0;
}
