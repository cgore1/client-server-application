#include "sem.h"
#define NO_OF_PORTS 100
#define MSG_LENGTH 10

typedef struct struct_port
{
	int messages[MSG_LENGTH][MSG_LENGTH];
	semaphore_t *empty;
	semaphore_t *full;
	semaphore_t *mutex;
	int writeIndex, readIndex; // messages count
} port_t;

port_t *ports[NO_OF_PORTS]; 

void initPorts()
{
  int i;
  for(i=0; i< NO_OF_PORTS; i++)
  {
	ports[i] = malloc(sizeof(port_t));
	ports[i] -> full = createSem(10);
	ports[i] -> empty = createSem(0);
	ports[i] -> mutex = createSem(1);	
	ports[i] -> writeIndex = ports[i] -> readIndex = 0;
  }

}

void send(int portNo,int message[MSG_LENGTH])
{
	port_t *port = ports[portNo];
	
	P(port -> full);
		P(port -> mutex);
			int i;
			for(i=0; i<MSG_LENGTH; i++)
			{	
				port -> messages[port->writeIndex][i] = message[i];
			}
			port->writeIndex++;
			port->writeIndex %= MSG_LENGTH; 
		V(port -> mutex);	
	V(port -> empty);
	
}

void rcv(int portNo, int *messageBuffer)
{
	port_t *port = ports[portNo];
	P(port -> empty);
		P(port -> mutex);
			int i;
			for(i=0; i<MSG_LENGTH; i++)
			{	
				messageBuffer[i] = port -> messages[port->readIndex][i];
			}
			port->readIndex++;
			port->readIndex %= MSG_LENGTH; 	
		V(port -> mutex);
	V(port -> full);
}
