#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

int main(){
	printf("start client \n");

	struct sockaddr_in client_addr;
	int dialogSocket;
	char message[10];

	client_addr.sin_addr.s_addr = inet_addr("192.168.1.44");
	client_addr.sin_port = htons(2499); /* on utilise htons pour le port */
	client_addr.sin_family = AF_INET;

	if( (dialogSocket = socket(PF_INET,SOCK_STREAM,0))<0){
		perror("echec de création socket \n");
	}

	
	if(connect(dialogSocket,(struct sockaddr *) &client_addr, sizeof(client_addr)) < 0){
		perror("erreur connect \n");
	}

	recv(dialogSocket , message , 10 , 0);
	printf("message : %s \n",message );
	printf("end client \n");
	return 0;
}