#ifndef MyController_hpp
#define MyController_hpp

#include <iostream>
#include <ctime>

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController: public oatpp::web::server::api::ApiController {
public:
	/**
	 * Constructor with object mapper.
	 * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
	 */
	MyController( OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
			: oatpp::web::server::api::ApiController(objectMapper)
			{}
		public:

			ENDPOINT("GET", "/", root) {
				time_t rawtime;
				struct tm * timeinfo;
				char buffer[80];

				time (&rawtime);
				timeinfo = localtime(&rawtime);

				strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
				std::string str(buffer);

				auto dto = MyDto::createShared();
				dto->statusCode = 200;
				dto->message = str.c_str();
				return createDtoResponse(Status::CODE_200, dto);
			}

			ENDPOINT("GET", "/endpoint1", additional) {
				auto dto = MyDto::createShared();
				dto->statusCode = 200;
				dto->message = "Endpoint 1";
				return createDtoResponse(Status::CODE_200, dto);
			}

		};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
