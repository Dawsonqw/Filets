#ifndef PAYLOAD_H
#define PAYLOAD_H

#include<vector>
#include<string>
#include"Frame.h"


namespace Daw{
	/**
	 *数据载体基类
	 * **/
	class Payload{
		public:
			//序列化操作 从具体子类数据成员拿到数据作为一个数组传出
			virtual std::vector<uint8_t> get(void)=0;

			//序列化操作的具体实现：拿到对应子类数据成员 转换数据到out中 
			//也可以作为单独接口，作为值提供out
			virtual void get_append(std::vector<uint8_t>&out)=0;

			//将payload的content成员指向传入的content
			static void put(std::vector<uint8_t>&content,Payload** payload);

			//比较两个payload是否相同
			virtual bool operator==(const Payload* other)const =0;

			virtual bool operator==(const Payload& other)const =0;
	};
}

#endif
