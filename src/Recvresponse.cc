#include<vector>
#include<cassert>
#include"Vecstream.h"
#include"Recvresponse.h"
#include"Payload.h"

namespace Daw{
	std::vector<uint8_t> RecvResponse::get(){
		std::vector<uint8_t>result;
		get_append(result);
		return std::move(result);
	}

	void RecvResponse::get_append(std::vector<uint8_t>& out){
		push_u32(out,this->response);	
	}

	void RecvResponse::put(std::vector<uint8_t>&buffer,RecvResponse** parsed_section){
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
