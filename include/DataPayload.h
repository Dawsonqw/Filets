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
			std::vector<uint8_t> get(void)override;

			void get_append(std::vector<uint8_t>&out) override;

			static void put(std::vector<uint8_t>&content,DataPayload** parsed_section);

			bool operator==(const Payload* other)const override;

			bool operator==(const Payload& other)const override;
	};
}

#endif
