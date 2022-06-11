#include<fstream>
#include<cassert>
#include<iostream>
#include"Daw.h"

using namespace std;

int main(){
	///测试：拿到存储数组
	std::ifstream in;
	in.open("../tests/text.txt");
	Daw::ReadBuffer rbuffer(&in);
	auto expend=rbuffer.read(100);
	cout<<expend.size()<<"\n";
	for(auto ch:expend)cout<<ch<<" ";
	in.close();
	return 0;
}
