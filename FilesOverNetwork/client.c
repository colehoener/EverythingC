/********************************************************************
*  NAME: client.c
*  BY: Cole Hoener
*  DATE: 24 Feburary, 2021
*  DESCRIPTION: Using network sockets, write a C program called client that receives three command-line arguments in the form:
'client host port file' and sends a request to a web server. Your program should create a client socket that connects to the server indicated by host,
and send the following:
GET /index.html HTTP/1.1\r\n Host: www.google.com\r\n \r\n
Then, your program should read the entire result and display it on the screen.
********************************************************************/

//Declare headers
#include <stdio.h>
#include <string.h>
#include "csapp.h"

//Declare constants
const int STRING_SIZE = 32;

/*******************************************************************
* NAME :            void getFileFromServer(host, port, file)
*
* DESCRIPTION :     Connects to a server and retrieves a file
*
* INPUTS :
*       PARAMETERS:
*           char    host            the host to connect to
*           int     port            the port number where the rrequest is sent
*           char    file            the name of the file to get from the server
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Connects to host
*                   [2]  Sends request for file
*                   [3]  Recieves file
*                   [4]  Prints file to console
*
* NOTES :           
*           May throw an error if there is some problem on the server end for delivering file
* CHANGES :
*/
void getFileFromServer(char host[STRING_SIZE], int port, char file[STRING_SIZE])
{
    //Declare variables
    char getRequest[MAXBUF];
    int clientfd = Open_clientfd(host, port);
    rio_t rio;
    ssize_t write;
    ssize_t result;

    //Establish connection
    Rio_readinitb(&rio, clientfd);

    //Create request (what is going to be sent over connection)
    sprintf(getRequest, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", file, host);

    //send the request to the server
    write = rio_writen(clientfd, getRequest, strlen(getRequest));
    if (write < 0)
    {
        printf("Can not write to server.\n");
        exit(0);
    }

    //read the request and print to screen (this is translated from the echo function from the slides)
    while ((result = rio_readlineb(&rio, getRequest, MAXLINE)) != 0)
    {
        if (result < 0)
        {
            printf("Can not read from server.\n");
            exit(0);
        }
        printf("%s", getRequest);
    }

    //close the connection
    Close(clientfd);
}

/*******************************************************************
* NAME :            int main(argc, **argv)
*
* DESCRIPTION :     takes arguemnts and calls getFileFromServer()
*
* INPUTS :
*       PARAMETERS:
*           int     argc                the total number of arguments provided
*           char    argv                the arguments provided
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Check number of arguments
*                   [2]  Calls getFileFromServer()
*
* NOTES :           
*  
* CHANGES :
*/
int main(int argc, char **argv)
{
    //Declare variables
    char host[STRING_SIZE];
    int port;
    char file[STRING_SIZE];

    //Argument checking
    if (argc > 4)
    {
        printf("Too many arguments. Program terminated.\n");
    }
    else if (argc < 4)
    {
        printf("Not enough arguments. Program terminated.\n");
    }

    //copy arguments into variables
    strcpy(host, argv[1]);
    port = atoi(argv[2]);
    strcpy(file, argv[3]);

    getFileFromServer(host, port, file);
}