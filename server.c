#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

int main(){
	printf("start\n");

	struct sockaddr_in serv_addr, cli_addr;
	int socketServer,clilen,dialogSocket;
	char buff[10] = "coucou";

	memset(&serv_addr, 0, sizeof(serv_addr));
	
	clilen = sizeof(cli_addr);
	/* configuration de serv_addr */
	serv_addr.sin_family = 	AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // on peut recevoir les messages de toute ip
	serv_addr.sin_port = htons(2499);



	if( (socketServer = socket(PF_INET, SOCK_STREAM,0))<0 ){
		perror("echec creation socket \n");
	}
	if(bind(socketServer,(struct sockaddr *) &serv_addr,sizeof(serv_addr) ) <0) {
		perror ("servecho: erreur bind\n");
		printf(" addr : %d\n", ntohl(serv_addr.sin_addr.s_addr));
		printf(" port : %d\n", ntohs(serv_addr.sin_port));
		exit (1);
  	}
	if(listen(socketServer, 2)<0){
		perror("echec\n");
	}

	dialogSocket = accept(socketServer, (struct sockaddr *) &cli_addr,(socklen_t *)&clilen);
	
	if(dialogSocket<0){
		perror("servecho : erreur accep \n");
		exit(1);
	}
	send(dialogSocket, buff, sizeof(buff),0);
	printf("end\n");
	return 0;
}