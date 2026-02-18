#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#define FSPATH "C:\\Program Files (x86)\\Steam\\steamapps\\common\\FALLSTRUKTUR\\res\\FALLSTRUKTUR"

struct FileString {
	std::string s;
	size_t idx;
};

int main(int argc, char** argv) {
	std::string scenePath = FSPATH;
	scenePath += "\\world.scene";
	std::ifstream handle(scenePath, std::ios::binary);
	std::stringstream contentHandle;
	contentHandle << handle.rdbuf();
	std::string content = contentHandle.str();
	handle.close();
	std::vector<std::string> strings;
	for (size_t i = 0; i < content.size(); i++) {
		unsigned char c = (unsigned char)content[i];
		std::string s = "";
		if(i+c < content.size()){
			bool invalidString = false;
			for (unsigned char _i = 0; _i < c - 1; _i++) {
				unsigned char _c = content[i + _i + 1];
				if(_c >= 32)
					s += content[i + _i + 1];
				else {
					invalidString = true;
					break;
				}
			}
			if (s != "" && !invalidString) {
				strings.push_back(s);
			}
		}
	}
	std::ofstream out("strings.txt");
	size_t count = 0;
	for (const std::string& s : strings) {
		out << count << " : " << s << std::endl;
		count++;
	}
	out.close();
}