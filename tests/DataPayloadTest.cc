#include"Daw.h"
#include<vector>
#include<iostream>
int main(){
	Daw::DataPayload payload;

	std::string content="hello world!";
	std::vector<uint8_t>test(content.begin(),content.end());

	payload.content=test;

	std::vector<uint8_t>buffer=payload.get();
	for(auto ch:buffer)std::cout<<ch<<"";
}
