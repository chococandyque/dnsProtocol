#include <stdio.h>      // printf()
#include <stdlib.h>
#include <unistd.h>     // close()
#include <string.h>     // strlen()
#include <sys/socket.h> // sockaddr_in
#include <arpa/inet.h>  // inet_addr
#define PORT 53

int main(int argc,char *argv[])
{
   int socket_desc;
   struct sockaddr_in server;
   char domain_name[200] , server_respond[200];

   // for a creation and verification of the socket
   socket_desc = socket(AF_INET,SOCK_STREAM,0);
   if(socket_desc == -1)
   {
      printf("socket creation failed :(");
      exit(0);
   }
   else
      printf("Socket successfully created...\n");

   // assigning DNS IP address and DNS port
   server.sin_addr.s_addr = inet_addr("192.168.234.3");
   server.sin_family = AF_INET;
   server.sin_port = htons(PORT);

   // connect to DNS server
   if(connect(socket_desc,(struct sockaddr *)&server,sizeof(server)) < 0)
   {
      printf("connection with the DNS server failed :(");
      exit(0);
   }
   else
      printf("Connected to the DNS server...\n");

   // prompt enter domain name
   char c = 'y';
   while (c == 'y')
   {
      printf("Enter the domain name to lookup : ");
      scanf("%s",domain_name);

      // send domain name to DNS server
      if(send(socket_desc,domain_name,strlen(domain_name),0) < 0)
      {
         puts("sending failed");
         return 1;
      }
      puts("Done\n");

      // receive IP address from DNS server
      if(recv(socket_desc,server_respond,100,0) < 0)
      {
         puts("Receiving failed !");
      }
      puts("Done");

      // display domain name and IP address
      printf("\nName : %s \nAddress : ",domain_name);
      puts(server_respond);

      printf("\ncontinue ?[y-yes,n-no] ");
      scanf("%s",&c);
   }

   // close socket
   close(socket_desc);
   return 0;
}