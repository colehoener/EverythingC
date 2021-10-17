/********************************************************************
*  NAME: client.c
*  BY: Cole Hoener
*  DATE: 24 Feburary, 2021
*  DESCRIPTION: Write a second program that accepts a port number as a command line argument, and starts an HTTP server. This server should constantly accept() connections, read requests of the form
GET /path HTTP/1.1\r\n\r\n
read the file indicated by /path, and send it over the “connect” file descriptor returned by the call to accept().
********************************************************************/

//Declare headers
#include <stdio.h>
#include <string.h>
#include "csapp.h"

/*******************************************************************
* NAME :            void readRequest(connfd)
*
* DESCRIPTION :     sends specified file contents to connected client
*
* INPUTS :
*       PARAMETERS:
*           int    connfd               the connection
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Read the requestion from the client
*                   [2]  Find the file requested
*                   [3]  Send the requested file to client
*
* NOTES :           
*          some code was translated from Echo files from blackboard
* CHANGES :
*/
void readRequest(int connfd)
{
    //Variable decleration
    rio_t rio;
    char request[MAXLINE];
    char requestType[MAXLINE];
    char fileRequested[MAXLINE], version[MAXLINE], filename[MAXLINE];
    char requestInfo[MAXLINE];
    char message[MAXLINE];
    ssize_t totalChar;
    int source;
    char filePath[MAXLINE];
    char ch;

    //Filepath for later
    strcpy(filePath, ".");

    //Get the request from the connection
    Rio_readinitb(&rio, connfd);
    Rio_readlineb(&rio, request, MAXLINE);

    //Get each part of the request
    sscanf(request, "%s %s %s", requestType, fileRequested, version);

    //Get infoformation from request
    Rio_readlineb(&rio, requestInfo, MAXLINE);
    printf("~Connection Info~\n%s", requestInfo);
    while (strcmp(requestInfo, "\r\n"))
    {
        Rio_readlineb(&rio, requestInfo, MAXLINE);
        printf("%s", requestInfo);
    }

    //Get the file that was requested
    printf("File Requested: %s\n", fileRequested);
    strcat(filePath, fileRequested);
    printf("File Path: %s\n", filePath);
    source = open(filePath, O_RDONLY, 0);

    //Make sure the file exists
    if (source < 0)
    {
        printf("\nFile not found.\nConnection Closed.\n---------------------\n");
        sprintf(message, "Unable to find file.");
        rio_writen(connfd, message, 30);
        return;
    }

    //Send file information to client
    while ((totalChar = rio_readn(source, message, sizeof(message))) != 0)
    {
        rio_writen(connfd, message, totalChar); //write to client
    }

    //Print to console
    printf("\nFile sucessfully delivered.\nConnection closed.\n---------------------\n");

    Close(source);
}

/*******************************************************************
* NAME :            void startServer(port)
*
* DESCRIPTION :     Connects to a server and retrieves a file
*
* INPUTS :
*       PARAMETERS:
*           int     port            the port number of the server
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Starts a listener for start of server
*                   [2]  Waits for connection
*                   [3]  Gets connection
*                   [4]  Calls readRequest
*                   [5]  Repeat 2-4
*
* NOTES :           
*           
* CHANGES :
*/
void startServer(int port)
{
    //Variable decleration
    int listenfd, connfd;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    char fileToReturn[MAXLINE];
    socklen_t clientlen;

    //Start listening on server
    listenfd = open_listenfd(port);
    printf("Running server on Port: %d\n", port);

    //Continues to accept connections (Code is translated from slides)
    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        haddrp = inet_ntoa(clientaddr.sin_addr);
        printf("\n---------------------\nServer connected to %s (%s)\n", hp->h_name, haddrp);
        readRequest(connfd);
        Close(connfd);
    }

    Close(listenfd); // close the listening connector
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
    int port;

    //Argument checking
    if (argc > 2)
    {
        printf("Too many arguments. Program terminated.");
    }
    else if (argc < 2)
    {
        printf("Not enough arguments. Program terminated.");
    }

    //copy arguments into variables
    port = atoi(argv[1]);

    startServer(port);
}