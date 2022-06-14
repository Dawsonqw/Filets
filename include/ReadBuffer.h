#ifndef READBUFFER_H
#define READBUFFER_H
#include<fstream>
#include<queue>

namespace Daw{

class ReadBuffer{
	protected:
		///in 
		std::ifstream * in_stream=nullptr;
		std::queue<uint8_t>buffer;
		bool end_flag=false;

	public:
		constexpr static size_t DefaultBufferSize=1024*1024;

	protected:
		void read_from_file();

	public:
		ReadBuffer()=default;
		
		explicit ReadBuffer(std::ifstream *stream);

		void open(std::ifstream* stream);

		std::vector<uint8_t> read(int size=-1);

		void read_append(std::vector<uint8_t>&out_buf,int size=-1);

		inline bool eof()const {return this->end_flag;};
};

}

#endif
