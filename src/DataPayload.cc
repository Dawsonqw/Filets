#include"DataPayload.h"
#include<cassert>
#include<string>
#include<vector>
#include"Vecstream.h"

namespace Daw{
	std::vector<uint8_t> DataPayload::get(void){
		std::vector<uint8_t>result;
		get_append(result);
		return std::move(result);
	}

	///将内容放到out中
	void DataPayload::get_append(std::vector<uint8_t>&out){
		out.insert(out.end(),this->content.begin(),this->content.end());
	}

	///提供第二个参数原因是因为多态 需要传入一个具体子类对象指针的地址
	void DataPayload::put(std::vector<uint8_t>&content,DataPayload** parsed_section){
		//引用拿到一级指针变量的内存地址
		//*parsed_section是一个指针 auto& payload=DataPayload& payload
		auto &payload=*parsed_section;
		assert(nullptr!=parsed_section&&nullptr==payload);
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

