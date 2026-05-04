#include "RefundRequest.h"
#include "Order.h"
#include "Client.h"

unsigned RefundRequest::nextID = 1;

RefundRequest::RefundRequest(const MyString& reason, const Order* order, Client* client)
	: ID(nextID++), reason(reason), order(order), client(client) {}

const Order* RefundRequest::getOrder() const
{
	return order;
}

unsigned RefundRequest::getID() const
{
	return ID;
}

Client* RefundRequest::getClient() const
{
	return client;
}

MyString RefundRequest::getReason() const
{ 
	return reason;
}

bool RefundRequest::getIsProcessed() const
{
	return isProcessed;
}

bool RefundRequest::getIsApproved() const
{
	return isApproved;
}

void RefundRequest::approve()
{
	isApproved = true;
	isProcessed = true;
}

void RefundRequest::reject()
{
	isApproved = false;
	isProcessed = true;
}

void RefundRequest::process()
{
	isProcessed = 1;
}

void RefundRequest::printRefundRequest() const
{
	std::cout << ID << "|" << client->getName() << "|" << order->getTotalPrice() << "|" << "Reason: " << reason << std::endl;
}

void RefundRequest::serialize(std::ofstream& ofs) const
{
	ofs.write((const char*)& ID, sizeof(unsigned));
	MyString::writeStringToFile(ofs, reason);
	ofs.write((const char*)&isProcessed, sizeof(bool));
	ofs.write((const char*)&isApproved, sizeof(bool));
}

void RefundRequest::deserialize(std::ifstream& ifs)
{
	ifs.read((char*)&ID, sizeof(unsigned));
	reason = MyString::readStringFromFile(ifs);
	ifs.read((char*)&isProcessed, sizeof(bool));
	ifs.read((char*)&isApproved, sizeof(bool));
	this->client = client;
	this->order = order;
}
