#include"WriteBuffer.h"
#include<cassert>
#include<fstream>

namespace Daw{

	WriteBuffer::WriteBuffer(std::ofstream* stream){
		assert(nullptr!=stream);
		this->open(stream);
	}

	void WriteBuffer::open(std::ofstream* stream){
		assert(stream->is_open());
		this->out_stream=stream;
	}

	///直接将数组中内容写到文件流中
	void WriteBuffer::write(const std::vector<uint8_t>&result){
		this->out_stream->write(reinterpret_cast<const char*>(result.data()),result.size());
	}

	//todo:完善接口 没有queue喝buffer的转换 上面仅仅是通过数组写入数据
	void WriteBuffer::write_file(){
		auto size=WriteBuffer::DefaultBufferSize;
		if(this->buffer.size()>=size/2)return;
	}


	///析构时完成
	void WriteBuffer::flush(){
		auto size_to_write=buffer.size();
		std::vector<uint8_t>t_buffer(size_to_write);
		///这里是从queue（buffer转移到临时数组中
		while(!this->buffer.empty()){
			t_buffer.push_back(this->buffer.front());
			this->buffer.pop();
		}
		//将queue中的内容写到文件流中
		this->out_stream->write(reinterpret_cast<char*>(t_buffer.data()),size_to_write);
		this->out_stream->flush();
	}

	WriteBuffer::~WriteBuffer(){
		this->flush();
	}

}
