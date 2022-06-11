#include"Daw.h"
#include<iostream>
#include<vector>

int main(){

	std::vector<uint8_t>buffer;
	Daw::push_u8(buffer,0x65);
	Daw::push_u16(buffer,0x6511);
	Daw::push_u32(buffer,0x05aabbcc);
	for(auto ch:buffer)std::cout<<ch<<"\n";
	auto it=buffer.begin();
	auto one=Daw::get_u8(it);
	std::cout<<one<<"\n";
	auto two=Daw::get_u16(it);
	std::cout<<two<<"\n";
}
