#ifndef WRITEBUFFER_H
#define WRITEBUFFER_H
#include<fstream>
#include<queue>
#include<vector>


namespace Daw{
	class WriteBuffer{
		protected:
			std::ofstream* out_stream=nullptr;
			std::queue<uint8_t>buffer;
			bool end_flag=false;
		public:
			constexpr static size_t DefaultBufferSize=1024*1024;

		protected:
			void write_file();
		public:
			WriteBuffer()=default;

			~WriteBuffer();

			explicit WriteBuffer(std::ofstream* stream);

			void open(std::ofstream* stream);

			void write(const std::vector<uint8_t>&result);

			void flush();
	};
}

#endif
