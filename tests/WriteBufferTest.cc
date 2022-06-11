#include"Daw.h"
#include<fstream>
#include<vector>

using namespace std;

int main(){
	std::ofstream out;
	out.open("../tests/text.txt",std::ofstream::binary|std::ofstream::out);
	Daw::WriteBuffer buffer(&out);
	std::vector<uint8_t> vec={0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c,     0x64, 0x21};

	buffer.write(vec);
	out.close();
}
