#include "ClientNetProxy.h"

#include "Modules/ModuleManager.h"
#include "WebSockets/Public/WebSocketsModule.h"

ClientNetProxy::ClientNetProxy()
{
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		auto module_ptr = FModuleManager::Get().LoadModule("WebSockets");
		if (module_ptr==nullptr)
		{
			exit(EXIT_FAILURE);
		}
	}

}

ClientNetProxy::~ClientNetProxy()
{
	
}

void ClientNetProxy::OpenChannel(const FString& fstring)
{
	//TODO: if fstring is correct format of URL
	WebSocketPtr = FWebSocketsModule::Get().CreateWebSocket(fstring);
	WebSocketPtr->Connect();
}

void ClientNetProxy::CloseChannel()
{
	if (WebSocketPtr->IsConnected())
	{
		WebSocketPtr->Close();
	}
}

void ClientNetProxy::WriteToChannel(const char* row_ascii)
{
	WebSocketPtr->Send(row_ascii, strlen(row_ascii),false);
}
