#include"RequestPayload.h"
#include"Vecstream.h"
#include<vector>
#include<string>
#include"Payload.h"
#include<cassert>

namespace Daw{
	std::vector<uint8_t>RequestPayload::serialize(){
		std::vector<uint8_t>result;

		serialize_append(result);
		return std::move(result);
	}

	void RequestPayload::serialize_append(std::vector<uint8_t>&out){
		Daw::push_string(out,this->client_name);
		Daw::push_string(out,this->file_name);
		Daw::push_u32(out,file_id);
		Daw::push_u32(out,file_size);
		Daw::push_u16(out,block_size);
	}

	void RequestPayload::deserialize(std::vector<uint8_t>&content,RequestPayload** parsed_section){
		auto& payload=*parsed_section;
		auto it=content.begin();

		assert(nullptr!=parsed_section&&nullptr==payload);

		payload=new RequestPayload();
		payload->client_name=Daw::get_string(it);
		payload->file_name=Daw::get_string(it);
		payload->file_id=Daw::get_u32(it);
		payload->file_size=Daw::get_u32(it);
		payload->block_size=Daw::get_u16(it);
	}


	bool RequestPayload::operator==(const Payload* other)const{
		const auto* cur=dynamic_cast<const RequestPayload*>(other);
		
		return cur->client_name==this->client_name&&
			cur->file_name==this->file_name&&
			cur->file_id==this->file_id&&
			cur->file_size==this->file_size&&
			cur->block_size==this->block_size;
	}

	bool RequestPayload::operator==(const Payload& other)const{
		const auto cur=dynamic_cast<const RequestPayload&>(other);
		
		return cur.client_name==this->client_name&&
			cur.file_name==this->file_name&&
			cur.file_id==this->file_id&&
			cur.file_size==this->file_size&&
			cur.block_size==this->block_size;
	}
}
