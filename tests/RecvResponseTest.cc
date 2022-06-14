#include"Daw.h"
#include<vector>
#include<iostream>

int main(){
	Daw::RecvResponse payload;
	payload.response=true;

	std::vector<uint8_t>app={0x60,0x61,0x62};
	payload.get_append(app);
	std::vector<uint8_t>buffer=payload.get();
	for(auto ch:buffer)std::cout<<ch;


	Daw::RecvResponse* res=nullptr;
	Daw::RecvResponse::put(app,&res);
}
