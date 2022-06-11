#ifndef DATAPAYLOAD_H
#define DATAPAYLOAD_H
#include<vector>
#include<string>
#include"Payload.h"

namespace Daw{
	class DataPayload final :public Payload{
		public:
			std::vector<uint8_t>content;

		public:
			std::vector<uint8_t> serialize(void)override;

			void serialize_append(std::vector<uint8_t>&out) override;

			static void deserialize(std::vector<uint8_t>&content,DataPayload** parsed_section);

			bool operator==(const Payload* other)const override;

			bool operator==(const Payload& other)const override;
	};
}

#endif
