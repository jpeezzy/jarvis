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
#include <sys/wait.h> //wait();
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void saveFile(char* buffer, int fd); //saves buffer arrya to file

char* speechToText(char* filename); //analyzes wav file using cmusphinx
char* fileString();
int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	int buffer_size = 256;
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
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	////////////////////////////////////

	listen(sockfd,60);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 	(struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) 
		error("ERROR on accept");
	bzero(buffer,buffer_size);
	
	n = read(newsockfd, buffer, 255);
	if (n < 0) error("ERROR reading from socket");
	//SUCCESS IF REACHED HERE ///
	//printf("Here is the message: %s \n",buffer);
	char message[buffer_size];
	strcpy(message, speechToText("output.wav"));
	//now we must grab text file information, place here as string 
	n = write(newsockfd, "jarvis says", 11);
	if (n < 0) error("ERROR writing to socket");
	while(n = read(newsockfd,buffer,256) & strcmp(buffer, "ready") != 0 )
	{ 
		n = write(newsockfd, message, 256);
	}
	n = write(newsockfd, message, 256);
	if (n < 0) error("ERROR writing to socket");
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

char* speechToText(char* filename)
{
	//printf("does it get to start of speechtoText \n");
	pid_t child, wpid;
	int status =0;
	FILE* cmusphinx;
	int cmuStatus;
	cmusphinx = popen("pocketsphinx_continuous -infile output.wav -logfn nul | tee ./words.txt", "w");
	cmuStatus = pclose(cmusphinx);
	//get the phrase inside words.txt
	char* phrase;
	phrase = fileString();
	return phrase; 
}

char* fileString()
{
	char* phrase;
	phrase = malloc(256 +1); //alocate memory
	printf("passss while loop");
	FILE* inFile = fopen("words.txt", "rb");
	if (inFile == NULL)
	{
		printf(" cannot find file specified");
		return phrase = "";
	}
	else
	{
		//printf("gets to else statement");
		while(fgets(phrase, 256, inFile))
		{
		}
		printf ("phrase: %s\n", phrase);
	}
	fclose(inFile); 
	return phrase;
}
