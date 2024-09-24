#include        "sock.h"


int main(int argc, char **argv){

        int srvfd, clifd;
        char buffer[255];


        struct sockaddr_in servsock;

        if ((srvfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
                printf("Socket creation failed\n");
                exit(1);
        }

        bzero(&servsock,sizeof(servsock));

        servsock.sin_family = AF_INET;
        servsock.sin_port = htons(5002);
        servsock.sin_addr.s_addr = inet_addr(argv[1]);
        //inet_aton(argv[1], &servsock.sin_addr);

        if ((bind(srvfd, (struct sockaddr*)&servsock, sizeof(servsock))) < 0){
                printf("bind failed\n");
                exit(1);
        }

        if(listen(srvfd,5) < 0){
                printf("listen failed\n");
                exit(1);
        }

        //< 0 if error
        clifd = accept(srvfd,NULL,NULL);

        for( ;; ){

                bzero(buffer,255);

                //assign integer to this and chek if its < 0 then it will be error
                read(clifd, buffer, 255);

                //display buffer
                printf("Client: %s\n", buffer);

                bzero(buffer,255);

                printf("Enter the mesege: ");
                fgets(buffer, 255, stdin);

                //can chech validation by < 0 check
                write(clifd, buffer, strlen(buffer));



        }

        close(clifd);
        close(srvfd);

        return 0;

}

