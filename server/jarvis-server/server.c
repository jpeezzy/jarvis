/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h> //for open();

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void saveFile(char* buffer, int fd); //saves buffer arrya to file

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	int buffer_size = 170000;
	char buffer[buffer_size];
	struct sockaddr_in serv_addr, cli_addr;
	ssize_t n;

	//ERROR CHECKING ////////////////
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //this is the socket i believe
	if (sockfd < 0) 
		error("ERROR opening socket");
	////////////////////////////////////
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/////////////ERROR ON BINDING///////
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	////////////////////////////////////

	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 
			(struct sockaddr *) &cli_addr, 
			&clilen);
	if (newsockfd < 0) 
		error("ERROR on accept");
	bzero(buffer,buffer_size);
	
	//n = read(newsockfd,buffer,buffer_size-1);
	//IMPORTANT TO NOTE! when you run functions like saveFile, recv, and sendfile, 
	//They mess with the actual file descriptor by offsetting the value as it readsa
	//leading to fd being empty with done. you may need to make multiple copies of fd
	//also not at this moment, you must alter wav player by removing first four bytes 
	saveFile(buffer, newsockfd);
	
	n = recv(newsockfd, buffer, buffer_size-1, MSG_WAITALL);
	printf("the bytes read from socket is %d \n", n);

	if (n < 0) error("ERROR reading from socket");
	//SUCCESS IF REACHED HERE ///
	printf("Here is the message: %s \n",buffer);
	//saveFile(buffer, newsockfd);
	n = write(newsockfd,"I got your message",18);
	if (n < 0) error("ERROR writing to socket");
	//saveFile(buffer, newsockfd);
	close(newsockfd);
	close(sockfd);
	return 0; 
}

void saveFile(char* buffer, int fd)
{
	FILE *f = fopen("output3.wav", "wb");
	int fdout = open("output3.wav", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	ssize_t nrd;
	while(nrd = read(fd,buffer,50))
	{
		//printf("its in the while loop \n");
		write(fdout, buffer, nrd);
	}
	fclose(f);
	printf("it gets to the save the file? \n");
}
