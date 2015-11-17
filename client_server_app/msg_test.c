#include"msg.h"
#include<string.h>

int clientId = 1;
semaphore_t *mutex;

void increment(int *message, int portNo)
{
	int i=0;
	for(i=0; i<MSG_LENGTH; i++)
	{
		message[i] = message[i] + 1;
	}
	message[MSG_LENGTH - 1] = portNo;
}

void initMsg(int *message, int portNo)
{
	int i;
	for(i=0; i<MSG_LENGTH; i++)
	{
		message[i] = 0;
	}
	message[MSG_LENGTH - 1] = portNo;
}

void printMsg(int *message)
{
	int i;
	for(i=0;i<MSG_LENGTH - 1;i++)
		printf("%d ",message[i]);
	printf("\n");
}

void client()
{
	int message[MSG_LENGTH];
	P(mutex);
	int portNo = clientId++;
	V(mutex);
	initMsg(message, portNo);

	while(1)
	{
		printf("Client #%d: Sending message to port 0\n", portNo);
		printMsg(message);
		send(0, message);
		printf("sent!\n");

		sleep(1);

		int reply[MSG_LENGTH];
		printf("Client #%d: Receiving message on port %d\n\n", portNo, portNo);
		rcv(portNo, reply);
		printf("Client #%d:Received\n", portNo);
		printMsg(reply);

		memcpy(message, reply, sizeof(int) * MSG_LENGTH);
		increment(message, portNo);
		sleep(1);
	}
}

void server()
{
	int portNo = 0;

	while(1)
	{
		int reply[MSG_LENGTH];
		printf("Server: Receiving message on port %d", portNo);
		rcv(portNo, reply);
		printf("Server: Received from port %d, client #%d\n", reply[9], reply[9]);
		printMsg(reply);

		sleep(1);

		int replyPort = reply[9];
		int message[MSG_LENGTH];
		memcpy(message, reply, sizeof(int) * MSG_LENGTH);
		increment(message, replyPort);
		printf("Server: Sending message on client #%d\n", replyPort);
		printMsg(message);
		send(replyPort, message);
		printf("Server:sent!\n\n");
		sleep(1);
	}
}


int main()
{
	initPorts();
	mutex = createSem(1);

	start_thread(server);
	start_thread(client);
	start_thread(client);
	start_thread(client);

	run();
	while (1) sleep(1);
}
