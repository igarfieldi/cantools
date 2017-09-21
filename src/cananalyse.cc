#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip>
#include <set>

std::vector<std::string> split(const std::string &str) {
	std::istringstream iss(str);
	
	std::vector<std::string> result;
	
	return std::vector<std::string>(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
}

int main(int argc, char **argv) {
	if(argc < 3) {
		std::cout << "Usage: " << argv[0] << " CAN-ID msg-count [wait-for-input=true]" << std::endl;
		std::cout << "Logs the given number of CAN messages from the given device twice and puts out the differences between the two" << std::endl;
		return -1;
	}
	
	std::string dump1 = "cananalyse-dump-1.txt";
	std::string dump2 = "cananalyse-dump-2.txt";
	std::string canId = argv[1];
	size_t msgCount = std::stoul(argv[2]);
	bool waitBetween = true;
	if(argc > 3) {
		std::istringstream(argv[3]) >> waitBetween;
	}
	
	std::string cmd1 = "candump " + canId + " -n " + std::to_string(msgCount) + " > " + dump1;
	std::string cmd2 = "candump " + canId + " -n " + std::to_string(msgCount) + " > " + dump2;
	
	// Create first dump
	std::cout << "Starting first dump..." << std::endl;
	system(cmd1.c_str());
	
	if(waitBetween) {
		std::cout << "Waiting to resume...";
		std::cout.flush();
		std::cin.get();
	}
	
	// Create second dump
	std::cout << "Starting second dump..." << std::endl;
	system(cmd2.c_str());
	
	std::ifstream in1(dump1);
	std::map<size_t, std::set<std::string>> msgs1;
	std::ifstream in2(dump2);
	std::map<size_t, std::set<std::string>> msgs2;
	
	std::string line;
	
	while(std::getline(in1, line)) {
		auto tokens = split(line);
		size_t id = std::stoull(tokens[1], 0, 16);
		std::string payload;
		for(size_t i = 3; i < tokens.size(); ++i) {
			payload += tokens[i];
		}
		
		msgs1[id].insert(payload);
	}
	
	while(std::getline(in2, line)) {
		auto tokens = split(line);
		size_t id = std::stoull(tokens[1], 0, 16);
		std::string payload;
		for(size_t i = 3; i < tokens.size(); ++i) {
			payload += tokens[i];
		}
		
		msgs2[id].insert(payload);
	}
	
	std::cout << "New IDs:\n";
	for(auto msg : msgs1) {
		if(msgs2.find(msg.first) == msgs2.end()) {
			std::cout << '\t' << msg.first << '\n';
			/*for(auto data : msg.second) {
				std::cout << "\t\t\t" << data << "\n";
			}*/
		}
	}
	
	std::cout << "IDs with changed payload:\n";
	for(auto msg : msgs1) {
		auto entry = msgs2.find(msg.first);
		if(entry != msgs2.end()) {
			for(auto msg2 : msg.second) {
				if(entry->second.find(msg2) == entry->second.end()) {
					std::cout << '\t' << msg.first << '\n';
					break;
				}
			}
			/*for(auto data : msg.second) {
				std::cout << "\t\t\t" << data << "\n";
			}*/
		}
	}
	
	return 0;
}
