#include<vector>
#include<cassert>
#include"Vecstream.h"
#include"Recvresponse.h"
#include"Payload.h"

namespace Daw{
	std::vector<uint8_t> RecvResponse::serialize(){
		std::vector<uint8_t>result;
		serialize_append(result);
		return std::move(result);
	}

	void RecvResponse::serialize_append(std::vector<uint8_t>& out){
		push_u32(out,this->response);///bool变量为什么用32位？
	}

	void RecvResponse::deserialize(std::vector<uint8_t>&buffer,RecvResponse** parsed_section){
		auto &payload=*parsed_section;

		assert(nullptr!=parsed_section&&nullptr==payload);

		auto it=buffer.begin();
		bool server_ack_code=get_u32(it)!=0;
		payload=new RecvResponse();
		payload->response=server_ack_code;
	}

	bool RecvResponse::operator==(const Payload* other)const{
		const auto *cur=dynamic_cast<const RecvResponse*>(other);

		return this->response==cur->response;
	}

	bool RecvResponse::operator==(const Payload& other)const{
		const auto cur=dynamic_cast<const RecvResponse&>(other);
		return this->response==cur.response;
	}
}
