#ifndef PAYLOAD_H
#define PAYLOAD_H

#include<vector>
#include<string>
#include"Frame.h"


namespace Daw{
	class Payload{
		public:
			virtual std::vector<uint8_t> serialize(void)=0;

			virtual void serialize_append(std::vector<uint8_t>&out)=0;

			static void deserialize(std::vector<uint8_t>&content,Payload** payload);

			virtual bool operator==(const Payload* other)const =0;

			virtual bool operator==(const Payload& other)const =0;
	};
}

#endif
