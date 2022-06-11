#include"DataPayload.h"
#include<cassert>
#include<string>
#include<vector>
#include"Vecstream.h"

namespace Daw{
	std::vector<uint8_t> DataPayload::serialize(void){
		std::vector<uint8_t>result;
		serialize_append(result);
		return std::move(result);
	}

	///将内容放到out中
	void DataPayload::serialize_append(std::vector<uint8_t>&out){
		out.insert(out.end(),this->content.begin(),this->content.end());
	}

	///function:传入指针指向传入数据？
	void DataPayload::deserialize(std::vector<uint8_t>&content,DataPayload** parsed_section){
		///*parsed_section存放的是地址 这段地址存放的是一个指针变量
		//payload拿到的是parsed_section指向的地址
		//parsed_section是DataPayload**变量 存放的就是DataPayload*变量 payload推导为Dadapyload& 是一个引用 todo：分析
		auto &payload=*parsed_section;
		assert(nullptr!=parsed_section&&nullptr==payload);
		///这里可以看出是一个DataPayload*变量
		payload=new DataPayload();
		payload->content=content;
	}

	bool DataPayload::operator==(const Payload& other)const{
		const auto cur=dynamic_cast<const DataPayload&>(other);
		return this->content==cur.content;
	}

	bool DataPayload::operator==(const Payload* other)const{
		const auto cur=dynamic_cast<const DataPayload*>(other);
		return cur->content==this->content;
	}
}

