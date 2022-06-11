#include"Vecstream.h"
#include<vector>
#include<string.h>
#include<queue>

namespace Daw{

	void push_string(std::vector<uint8_t>&out_buf,const std::string& s){
		auto string_size=static_cast<uint16_t>(s.size());
		auto buf_size=static_cast<uint16_t>(out_buf.size());
		
		push_u16(out_buf,string_size);

		out_buf.resize((buf_size+2)+string_size);

		if(string_size!=0)
			memcpy(&out_buf[buf_size+2],&s[0],string_size);
	}

	std::string get_string(std::vector<uint8_t>::iterator& it){
		auto size=get_u16(it);
		auto end=it+size;
		
		std::string result(size,'\0');

		for(auto dst=result.begin();it!=end;++it,++dst)*dst=*it;

		return std::move(result);///
	}

	///已经规定了传入的是8位大小的内容 也就是一个char大小 并且vector也是8位的 可以保证连续空间中能够进行统一处理
	void push_u8(std::vector<uint8_t>&out_buf,const uint8_t x){
		out_buf.push_back(x);
	}

	uint8_t get_u8(std::vector<uint8_t>::iterator &it){
		uint8_t result=*(it++);
		return result;
	}

	void push_u16(std::vector<uint8_t>&out_buf,const uint16_t x){
		push_u8(out_buf,x>>8);
		push_u8(out_buf,x&255);
	}

	uint16_t get_u16(std::vector<uint8_t>::iterator &it){
		///先左移8位再进行与操作
		uint16_t result=get_u8(it)<<8;
		return result|get_u8(it);
	}

	void push_u32(std::vector<uint8_t>&out_buf,const uint32_t x){
		push_u16(out_buf,x>>16);
		push_u16(out_buf,x&65535);
	}

	uint32_t get_u32(std::vector<uint8_t>::iterator &it){
		///先左移8位再进行与操作
		uint32_t result=get_u16(it)<<16;
		return result | get_u16(it);
	}

	/**
	void push_u64(std::vector<uint8_t>&out_buf,const uint64_t x){
		push_u32(out_buf,x>>32);
		push_u32(out_buf,x&(65535<<16|65535));
	}

	uint64_t get_u64(std::vector<uint8_t>::iterator& it){
		uint64_t result=get_u32(it)<<32;
		return result | get_u32(it);
	}
	**/

}
