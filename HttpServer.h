/*
 * HttpServer.h
 *
 *  Created on: Aug 30, 2017
 *      Author: kolban
 */

#ifndef COMPONENTS_CPP_UTILS_HTTPSERVER_H_
#define COMPONENTS_CPP_UTILS_HTTPSERVER_H_
#include <stdint.h>
#include <regex>
#include <vector>
#include "SockServ.h"
#include "HttpRequest.h"
class HttpResponse;
class HttpServerTask;

class PathHandler {
	public:
		PathHandler(
			std::string method,
			std::string pathPattern,
			void (*webServerRequestHandler)(HttpRequest* pHttpRequest, HttpResponse* pHttpResponse));
		bool match(std::string method, std::string path);
		void invoke(HttpRequest* request, HttpResponse* response);
	private:
		std::string m_method;
		std::regex m_pattern;
		void (*m_requestHandler)(HttpRequest* pHttpRequest, HttpResponse* pHttpResponse);
}; // PathHandler




class HttpServer {
public:
	HttpServer();
	virtual ~HttpServer();
	void addPathHandler(std::string method,
		std::string pathExpr,
		void (*webServerRequestHandler)(
			HttpRequest* pHttpRequest,
			HttpResponse* pHttpResponse) );
	uint16_t getPort();
	void start(uint16_t portNumber);
private:
	friend class HttpServerTask;
	uint16_t m_portNumber;
	std::vector<PathHandler> m_pathHandlers;
}; // HttpServer

#endif /* COMPONENTS_CPP_UTILS_HTTPSERVER_H_ */
