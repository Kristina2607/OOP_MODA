#include "ListOrdersClient.h"

ListOrdersClient::ListOrdersClient(System& system):Command(system){}

void ListOrdersClient::execute()
{
	system.listOrdersClient();
}
