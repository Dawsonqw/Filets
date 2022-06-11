#ifndef VECSTREAM_H
#define VECSTREAM_H
#include<vector>
#include<string>
namespace Daw{
	void push_string(std::vector<uint8_t>&out_buf,const std::string& s);

	std::string get_string(std::vector<uint8_t>::iterator &it);

	void push_u8(std::vector<uint8_t>&output_buffer,const uint8_t x);

	uint8_t get_u8(std::vector<uint8_t>::iterator& it);

	void push_u16(std::vector<uint8_t>&output_buffer,const uint16_t x);

	uint16_t get_u16(std::vector<uint8_t>::iterator& it);

	void push_u32(std::vector<uint8_t>&output_buffer,const uint32_t x);

	uint32_t get_u32(std::vector<uint8_t>::iterator& it);

	/** 用不了也无法实现
	void push_u64(std::vector<uint8_t>&output_buffer,const uint64_t x);

	uint32_t get_u64(std::vector<uint8_t>::iterator& it);
	**/
}

#endif

