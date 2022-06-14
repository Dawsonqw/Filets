#include"Daw.h"
#include<vector>
#include<string.h>
#include<iostream>

int main(){
	Daw::RequestPayload payload;
	payload.client_name="client";
	payload.file_name="text.txt";
	payload.file_id=0x12345;
	payload.file_size=0x5A8A;
	payload.block_size=1024;

	std::vector<uint8_t>buffer=payload.get();
		
	for(auto ch:buffer)std::cout<<ch<<" ";
}
