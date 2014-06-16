// websocketserver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

using namespace std;

class WebSocketRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		try
		{
			WebSocket ws(request, response);
			char buffer[1024];
			int flags;
			int n;
			do{
				n = ws.receiveFrame(buffer, sizeof(buffer), flags);
				cout << "recv data" << endl;
				ws.sendFrame(buffer, n, flags);
			} while (n > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
		}
		catch (WebSocketException& exc)
		{
			switch (exc.code())
			{
			case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
				response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				// fallthrough
			case WebSocket::WS_ERR_NO_HANDSHAKE:
			case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
			case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
				response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
				response.setContentLength(0);
				response.send();
				break;
			}
		}
	}
};

class WebSocketRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
	HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
	{
		return new WebSocketRequestHandler;
	}
};

class MyServerApp : public ServerApplication
{
protected:
	int main(const vector<string> &)
	{
		ServerSocket ss(8080);
		HTTPServer server(new WebSocketRequestHandlerFactory, ss, new HTTPServerParams);
		server.start();
		waitForTerminationRequest();
		server.stop();
		return 0;
	}
};

int main(int argc, char** argv) {
	MyServerApp app;
	
	return app.run(argc, argv);
}
