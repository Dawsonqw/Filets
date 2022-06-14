#include"ReadBuffer.h"
#include<vector>
#include<cassert>
#include<algorithm>
#include<fstream>

namespace Daw{
	
	ReadBuffer::ReadBuffer(std::ifstream* stream){
		assert(nullptr!=stream);
		this->open(stream);
	}

	void ReadBuffer::open(std::ifstream* stream){
		assert(stream->is_open());///判断文件是否打开并且与当前流关联
		this->in_stream=stream;
	}

	///读取当前对象size字节后返回一个vector对象
	std::vector<uint8_t> ReadBuffer::read(int size){
		std::vector<uint8_t>result;
		this->read_append(result,size);
		return result;
	}

	void ReadBuffer::read_append(std::vector<uint8_t>&out_buf,int size){
		this->read_from_file();///buffer已经有了传入文件流的元素
		///将buffer中内容转移到out_buf
		if(size<0)size=ReadBuffer::DefaultBufferSize;

		auto size_to_read=std::min((size_t)size,this->buffer.size());
		
		while(size_to_read--){
			auto ch=this->buffer.front();
			out_buf.push_back(ch);
			this->buffer.pop();
		}
	}

	///完成了将in_stream指向内容转移到queue（buffer中 
	//逻辑：通过read方法将文件流中内容读取到一个临时vector 之后再将vector内容转移到queue
	///明确：读和写的对象都是文件流 read就是从文件流中读取内容 write就是向文件流写入内容
	void ReadBuffer::read_from_file(){
		auto size=ReadBuffer::DefaultBufferSize;
		if(this->end_flag||this->buffer.size()>=size/2)return;
		auto size_to_read=size-buffer.size();
		std::vector<uint8_t>t_buffer(size_to_read);
		///强制类型转换 fstream read方法第一个参数是const对象 再将文件流写入数组中
		this->in_stream->read(reinterpret_cast<char*>(t_buffer.data()),size_to_read);
		///内容读取到buffer中 todo:一个一个字节转换效率太低了 改进 实际上直接读取到vector就可以了 不需要转换
		for_each(t_buffer.begin(),t_buffer.begin()+this->in_stream->gcount(),//gcount:当前流中字节数
				[this](uint8_t ch){
				this->buffer.push(ch);
				});
		if(this->in_stream->eof())this->end_flag=true;
	}
}

