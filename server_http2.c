#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/sendfile.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<netdb.h>
#include<sys/stat.h>

char webpage[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><headh><title>MaPagita</title>\r\n"
"<style>body {background-color: #AA00A0 }</style></head>\r\n"
"<body><center><h1>Never gonna give you up!</h1><br>\r\n"
"<a href=\"pagina2.html\">Mais links</a>\r\n"
"<p><img src=\"pizzaEP.png\"width=460 height=400></p></center></body></html>\r\n";

char cabecalho[] =
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n";

int main(int argc, char *argv[]){

struct sockaddr_in server_addr;
struct sockaddr_in  client_addr;
socklen_t sin_len = sizeof(client_addr);
int fd_server, fd_client;
char buf[2048];
int fdimg, fdpag;
int on = 1;
struct stat stat_buf;

fd_server = socket(AF_INET, SOCK_STREAM, 0);

setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr("10.0.2.15");
server_addr.sin_port = htons(8001);

bind(fd_server, (struct sockaddr*) &server_addr, sizeof(server_addr));

listen(fd_server, 3);

while(1){
	fd_client = accept(fd_server, (struct sockaddr*) &client_addr, &sin_len);
	printf("conectado com o cliente\n");
	
	//if(!fork()){
		//processo filho
		//close(fd_server);
		memset(buf, 0, 2048);
		read(fd_client, buf, 2047);
		printf("Buffer -->%s\n", buf);

		if(!strncmp(buf, "GET /pizzaEP.png", 16)){
			fdimg = open("pizzaEP.png", O_RDONLY);
			fstat(fdimg, &stat_buf);
			sendfile(fd_client, fdimg, NULL, stat_buf.st_size);
			close(fdimg);		
		}
		else if(!strncmp(buf, "GET /pagina2.html", 16)){
			fdpag = open("pagina2.html", O_RDONLY);
			fstat(fdpag, &stat_buf);
			write(fd_client, cabecalho, sizeof(cabecalho) -1);
			sendfile(fd_client, fdpag, NULL, stat_buf.st_size);
			close(fdpag);	

		
		}
		else
			write(fd_client, webpage, sizeof(webpage) -1);

		//close(fd_server);

		close(fd_client);
		printf("conexao fechada\n");
		//exit(0);
	//}

	//processo pai
	//close(fd_client);
}





return 0;
}
