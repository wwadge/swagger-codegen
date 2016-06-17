
#include "UserApi.h"
#include "IHttpBody.h"
#include "JsonBody.h"
#include "MultipartFormData.h"

#include <unordered_set>

#include <boost/algorithm/string/replace.hpp>

namespace io {
namespace swagger {
namespace client {
namespace api {

using namespace io::swagger::client::model;

UserApi::UserApi( std::shared_ptr<ApiClient> apiClient )
    : m_ApiClient(apiClient)
{
}

UserApi::~UserApi()
{
}

pplx::task<void> UserApi::createUser(std::shared_ptr<User> body)
{
    
    // verify the required parameter 'body' is set
    if (body == nullptr)
    {
        throw ApiException(400, U("Missing required parameter 'body' when calling UserApi->createUser"));
    }
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user");
        
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->createUser does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

        web::json::value json;
 
        json = ModelBase::toJson(body);
        
        
        httpBody = std::shared_ptr<IHttpBody>( new JsonBody( json ) );
        
    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
        std::shared_ptr<MultipartFormData> multipart(new MultipartFormData);
        
        if(body.get())
        {
            body->toMultipart(multipart, U("body"));
        }
        

        httpBody = multipart;
        requestHttpContentType += U("; boundary=") + multipart->getBoundary();
    }
    else
    {
        throw ApiException(415, U("UserApi->createUser does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("POST"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling createUser: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling createUser: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        return void();
            });            
}
pplx::task<void> UserApi::createUsersWithArrayInput(std::vector<std::shared_ptr<User>> body)
{
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user/createWithArray");
        
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->createUsersWithArrayInput does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

        web::json::value json;
 
        
        {
            std::vector<web::json::value> jsonArray;
            for( auto& item : body )
            {
                jsonArray.push_back( item.get() ? item->toJson() : web::json::value::null() );
                
            }
            json = web::json::value::array(jsonArray);
        }
        
        
        httpBody = std::shared_ptr<IHttpBody>( new JsonBody( json ) );
        
    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
        std::shared_ptr<MultipartFormData> multipart(new MultipartFormData);
        
        {
            std::vector<web::json::value> jsonArray;
            for( auto& item : body )
            {
                jsonArray.push_back( item.get() ? item->toJson() : web::json::value::null() );
                
            }
            multipart->add(ModelBase::toHttpContent(U("body"), web::json::value::array(jsonArray), U("application/json")));
        }
        

        httpBody = multipart;
        requestHttpContentType += U("; boundary=") + multipart->getBoundary();
    }
    else
    {
        throw ApiException(415, U("UserApi->createUsersWithArrayInput does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("POST"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling createUsersWithArrayInput: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling createUsersWithArrayInput: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        return void();
            });            
}
pplx::task<void> UserApi::createUsersWithListInput(std::vector<std::shared_ptr<User>> body)
{
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user/createWithList");
        
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->createUsersWithListInput does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

        web::json::value json;
 
        
        {
            std::vector<web::json::value> jsonArray;
            for( auto& item : body )
            {
                jsonArray.push_back( item.get() ? item->toJson() : web::json::value::null() );
                
            }
            json = web::json::value::array(jsonArray);
        }
        
        
        httpBody = std::shared_ptr<IHttpBody>( new JsonBody( json ) );
        
    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
        std::shared_ptr<MultipartFormData> multipart(new MultipartFormData);
        
        {
            std::vector<web::json::value> jsonArray;
            for( auto& item : body )
            {
                jsonArray.push_back( item.get() ? item->toJson() : web::json::value::null() );
                
            }
            multipart->add(ModelBase::toHttpContent(U("body"), web::json::value::array(jsonArray), U("application/json")));
        }
        

        httpBody = multipart;
        requestHttpContentType += U("; boundary=") + multipart->getBoundary();
    }
    else
    {
        throw ApiException(415, U("UserApi->createUsersWithListInput does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("POST"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling createUsersWithListInput: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling createUsersWithListInput: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        return void();
            });            
}
pplx::task<void> UserApi::deleteUser(utility::string_t username)
{
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user/{username}");
    boost::replace_all(path, U("{") U("username") U("}"), ApiClient::parameterToString(username));
    
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->deleteUser does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    
    {
        
    }
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
    }
    else
    {
        throw ApiException(415, U("UserApi->deleteUser does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("DELETE"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling deleteUser: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling deleteUser: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        return void();
            });            
}
pplx::task<std::shared_ptr<User>> UserApi::getUserByName(utility::string_t username)
{
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user/{username}");
    boost::replace_all(path, U("{") U("username") U("}"), ApiClient::parameterToString(username));
    
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->getUserByName does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    
    {
        
    }
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
    }
    else
    {
        throw ApiException(415, U("UserApi->getUserByName does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("GET"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling getUserByName: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling getUserByName: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        std::shared_ptr<User> result(new User());
        
        if(responseHttpContentType == U("application/json"))
        {
            web::json::value json = web::json::value::parse(response);
            
            result->fromJson(json);
        }
        // else if(responseHttpContentType == U("multipart/form-data"))
        // {
        // TODO multipart response parsing    
        // }
        else 
        {
			throw ApiException(500
				, U("error calling findPetsByStatus: unsupported response type"));
        }
        
        return result;
    });            
}
pplx::task<utility::string_t> UserApi::loginUser(utility::string_t username, utility::string_t password)
{
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user/login");
        
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->loginUser does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    
    {
        queryParams[U("username")] = ApiClient::parameterToString(username);
        
    }
    
    {
        queryParams[U("password")] = ApiClient::parameterToString(password);
        
    }
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
    }
    else
    {
        throw ApiException(415, U("UserApi->loginUser does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("GET"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling loginUser: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling loginUser: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        utility::string_t result(U(""));
        
        if(responseHttpContentType == U("application/json"))
        {
            web::json::value json = web::json::value::parse(response);
            
            result = ModelBase::stringFromJson(json);
            
        }
        // else if(responseHttpContentType == U("multipart/form-data"))
        // {
        // TODO multipart response parsing    
        // }
        else 
        {
			throw ApiException(500
				, U("error calling findPetsByStatus: unsupported response type"));
        }
        
        return result;
    });            
}
pplx::task<void> UserApi::logoutUser()
{
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user/logout");
        
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->logoutUser does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
    }
    else
    {
        throw ApiException(415, U("UserApi->logoutUser does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("GET"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling logoutUser: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling logoutUser: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        return void();
            });            
}
pplx::task<void> UserApi::updateUser(utility::string_t username, std::shared_ptr<User> body)
{
    
    // verify the required parameter 'body' is set
    if (body == nullptr)
    {
        throw ApiException(400, U("Missing required parameter 'body' when calling UserApi->updateUser"));
    }
    
    
    std::shared_ptr<ApiConfiguration> apiConfiguration( m_ApiClient->getConfiguration() );
    utility::string_t path = U("/user/{username}");
    boost::replace_all(path, U("{") U("username") U("}"), ApiClient::parameterToString(username));
    
    std::map<utility::string_t, utility::string_t> queryParams;
    std::map<utility::string_t, utility::string_t> headerParams( apiConfiguration->getDefaultHeaders() );
    std::map<utility::string_t, utility::string_t> formParams;
    std::map<utility::string_t, std::shared_ptr<HttpContent>> fileParams;

    std::unordered_set<utility::string_t> responseHttpContentTypes;
    responseHttpContentTypes.insert( U("application/xml") );
responseHttpContentTypes.insert( U("application/json") );
    
    utility::string_t responseHttpContentType;
    
    // use JSON if possible
    if ( responseHttpContentTypes.size() == 0 || responseHttpContentTypes.find(U("application/json")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("application/json");
    }
    // multipart formdata 
    else if( responseHttpContentTypes.find(U("multipart/form-data")) != responseHttpContentTypes.end() )
    {
        responseHttpContentType = U("multipart/form-data");
    }
    else
    {
        throw ApiException(400, U("UserApi->updateUser does not produce any supported media type"));
    }    
    
    headerParams[U("Accept")] = responseHttpContentType;
    
    std::unordered_set<utility::string_t> consumeHttpContentTypes;
        
    
    {
        
    }
    

    std::shared_ptr<IHttpBody> httpBody;
    utility::string_t requestHttpContentType;
   
    // use JSON if possible
    if ( consumeHttpContentTypes.size() == 0 || consumeHttpContentTypes.find(U("application/json")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("application/json");

        web::json::value json;
 
        json = ModelBase::toJson(body);
        
        
        httpBody = std::shared_ptr<IHttpBody>( new JsonBody( json ) );
        
    }
    // multipart formdata 
    else if( consumeHttpContentTypes.find(U("multipart/form-data")) != consumeHttpContentTypes.end() )
    {
        requestHttpContentType = U("multipart/form-data");
        
        std::shared_ptr<MultipartFormData> multipart(new MultipartFormData);
        
        if(body.get())
        {
            body->toMultipart(multipart, U("body"));
        }
        

        httpBody = multipart;
        requestHttpContentType += U("; boundary=") + multipart->getBoundary();
    }
    else
    {
        throw ApiException(415, U("UserApi->updateUser does not consume any supported media type"));
    }    
    
    
    return m_ApiClient->callApi(path, U("PUT"), queryParams, httpBody, headerParams, formParams, fileParams, requestHttpContentType)
    .then([=](web::http::http_response response)
    {
		// 1xx - informational : OK
		// 2xx - successful	   : OK
		// 3xx - redirection   : OK 
		// 4xx - client error  : not OK
		// 5xx - client error  : not OK
		if (response.status_code() >= 400)
		{
			throw ApiException(response.status_code()
				, U("error calling updateUser: ") + response.reason_phrase()
				, std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
		}
        
        // check response content type
        if(response.headers().has(U("Content-Type")))
        {
            utility::string_t contentType = response.headers()[U("Content-Type")];
            if( contentType.find(responseHttpContentType) == std::string::npos )
            {
                throw ApiException(500
                    , U("error calling updateUser: unexpected response type: ") + contentType
                    , std::make_shared<std::stringstream>(response.extract_utf8string(true).get()));
            }
        }
        
        return response.extract_string();
    })
    .then([=](utility::string_t response)
    {
        return void();
            });            
}

}
}
}
}

