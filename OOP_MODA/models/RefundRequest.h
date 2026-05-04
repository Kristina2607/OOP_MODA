#pragma once
#include "MyString.h"

class Client;
class Order;

class RefundRequest
{
private:
	static unsigned nextID;
	unsigned ID = 0;

	const Order* order;
    Client* client;
	MyString reason;

	bool isProcessed = false;
	bool isApproved = false;

public:
	RefundRequest() = default;
	RefundRequest(const MyString& reason, const Order* order, Client* client);
	const Order* getOrder() const;
	unsigned getID() const;
	Client* getClient() const;
	MyString getReason() const;
	bool getIsProcessed() const;
	bool getIsApproved() const;

	void approve();
	void reject();
	void process();

	void printRefundRequest() const;

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};

