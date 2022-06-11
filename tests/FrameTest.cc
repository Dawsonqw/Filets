#include"Daw.h"
#include<vector>
#include<string>
#include<iostream>
int main(){
	Daw::Frame frame;
	auto *payload=new Daw::RequestPayload();
	
	payload->client_name="test";
	payload->file_name="file_name";
	payload->file_size=0x56;
	payload->file_id=0x01;
	payload->block_size=1024;

	frame.seq=0xffffffff;
	frame.ack=0x01010101;
	frame.type=Daw::FrameType::SendRequest;
	frame.put(payload);

	auto buffer=frame.serialize();

	for(auto ch:buffer)std::cout<<ch;


	   std::vector<uint8_t> buf = {
            0x00, 0x34, 0x12, 0x56, 0x00, 0x34, 0x12, 0x57, 0x01, 0x08, 0x26, 0x95, 0xb9, 0x00, 0x09, 0x41, 0x6e, 0x74,
            0x43, 0x6c,
            0x69, 0x65, 0x6e, 0x74, 0x00, 0x09, 0x66, 0x69, 0x6c, 0x65, 0x2d, 0x6e, 0x61, 0x6d, 0x65, 0x00, 0x00, 0x00,
            0x01, 0x00,
            0x00, 0x01, 0x00, 0x04, 0x00
    };
	   std::cout<<"=================================\n";

	   auto result=Daw::Frame::deserialize(buf);
	   std::cout<<result.seq<<"\n";
	   std::cout<<result.ack<<"\n";

}
