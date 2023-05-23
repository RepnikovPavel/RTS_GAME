#pragma once


#include "WebSockets/Public/IWebSocket.h"

// NOTE: non thread safe
class ClientNetProxy
{
public:
	ClientNetProxy();
	~ClientNetProxy();
private:
	TSharedPtr<IWebSocket> WebSocketPtr;
public:
	
	void OpenChannel(const FString& fstring);
	void CloseChannel();
	// TODO: refactor to secure code
	void WriteToChannel(const char* row_ascii);
};
