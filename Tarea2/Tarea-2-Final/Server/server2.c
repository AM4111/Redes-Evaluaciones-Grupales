//https://github.com/nikhilroxtomar/TCP-Client-Server-Implementation-in-C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>


// transform /# -> #.#.#.#
void calmask(int numMask,char mask[]){
	int bit_on = 7;
    	char string[3]=""; 
    	int cont = 0;
    	int num = 0;
    	
    	if (numMask <=32 ) {
		//printf("numMask: %d  \n",numMask);	
		//255
	    	for (int i = 0; i < (numMask/8) ; i++ ){
				//printf("numMask/8: %d  \n",numMask/8);
	    		if (i == 3 ) {
		   		strcat(mask,"255");
			}
			else {
		   		strcat(mask,"255.");
			}
			//printf("mascara: %s  \n",mask);
	    	}
		cont = (numMask/8);
		
		
		if (cont <4 ) {
			// 0 - 254
			for (int j = 0; j < numMask-(8*cont) ; j++ ){
				
				if (bit_on > 0 ) {
					int a = pow(2,bit_on);
					num = num + a;
			   		bit_on --;
				}
			}
			sprintf(string, "%d", num);
			//itoa(num,string,10);
			strcat(mask,string);
			cont ++;
			
			for (cont; cont < 4 ; cont++ ){
				strcat(mask,".0");
			}

		   
		}
    
	}else{
		printf("Mascara  incorrecta ");
	}

}

// pasa de #.#.#.# a lista [#,#,#,#]
void direct_List(char* p_direct, int* list_direct, int* ip_correct){
		char *c_direct = strtok(p_direct,".");
		int index = 0;
		while (c_direct != NULL )
    	{	
			if(atoi(c_direct)>255 || atoi(c_direct)<0 || index>=4){
				*ip_correct==1;
			}
			list_direct[index] = atoi(c_direct);
			c_direct = strtok(NULL, ".");
			index++;
    	}	

}

// Valida la mascara y si la mascara entra en formato /# la convierte a #.#.#.#
void Validar_mask(char* p_direct, char* maskcalc,int* mask_list, int* ip_correct){
	if (strrchr(p_direct , '/')!= NULL){
		char *cadena = strtok(p_direct,"/");
		int mask = (int) strtol(cadena, NULL, 10);
		calmask(mask,maskcalc);

		//printf("mascara %s -> %s \n", p_direct, maskcalc);

		direct_List(maskcalc, mask_list, ip_correct);
		//printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
		
	}else {
		direct_List(p_direct, mask_list, ip_correct);
		//printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
	}	
}

//convierte el resultado a string para retornar
void result_str(char* result, int* list){
	for (int i =0 ; i<4; i++){
		char string[3]="";
		sprintf(string, "%d", list[i]);
		//itoa(num,string,10);
		strcat(result,string);
		if (i<=2){
			strcat(result,".");
		}
	}	
}

//Genera el numero final del hhost posible
void val_fin(int* broadcast_list,int* Final_range_res){

	if(broadcast_list[3] == 0){
		if(broadcast_list[2] != 0){
			Final_range_res[2] == broadcast_list[2]-1;
			Final_range_res[3] == 255;
		}else{
			if(broadcast_list[1] != 0){
				Final_range_res[1] == broadcast_list[1]-1;
				Final_range_res[2] == 255;
				Final_range_res[3] == 255;
			}else{
				if(broadcast_list[0] != 0){
					Final_range_res[0] == broadcast_list[0]-1;
					Final_range_res[1] == 255;
					Final_range_res[2] == 255;
					Final_range_res[3] == 255;
				}
			}
		}
	}
}

// Realiza las solicitudes de calculadora
void calc(char* buffer,char* result)
{
// variables
	char* buffer_list[100];

	char *c_direct = strtok(buffer," ");
	int index = 0;
	while (c_direct != NULL )
    	{	
			buffer_list[index] = c_direct;
			c_direct = strtok(NULL, " ");
			index++;
    	}	
	//printf("PRUEBA 2: %s\n", buffer_list[0]);
    char maskcalc[16]="",
    del_semicolon[] = ";",
    del_backslash[] = "/";

	int IP_ip_correct  = 0;
	int MASK_ip_correct  = 0;
	int num_red_correct  = 0;


    int list_mask[5] ;
	int comp_mask_list[4] ;
	int num_red_list[4] ;
	int broadcast_list[4] ;
	int mask_list[4] ;
	int ip_list[4];
	int Start_range_res[4];
	int Final_range_res[4];

    unsigned char* mask_cal;

	if (strcmp(buffer_list[0], "GET") == 0){
		if (strcmp(buffer_list[1], "BROADCAST") == 0){
			if (strcmp(buffer_list[2], "IP") == 0){
				direct_List(buffer_list[3], ip_list,&IP_ip_correct);
				if (IP_ip_correct == 1){
					printf("ip invalido \n");
				}else{
					//printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

					if (strcmp(buffer_list[4], "MASK") == 0){
						Validar_mask(buffer_list[5],maskcalc,mask_list,&MASK_ip_correct);
						if (MASK_ip_correct == 1){
							printf("mask invalido \n");
						}else{
							//printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);

							for (int i =0 ; i<4; i++){
								//NUm red
								num_red_list[i] = ip_list[i]&mask_list[i] ;
								// saca complemento de la mascara
								comp_mask_list[i] = 255^mask_list[i] ;
								//broadcast
								broadcast_list[i] = num_red_list[i]|comp_mask_list[i] ;
							}
							//printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
							//printf("comp_mask_list:%d.%d.%d.%d \n", comp_mask_list[0], comp_mask_list[1], comp_mask_list[2], comp_mask_list[3]);
							//printf("broadcast_list:%d.%d.%d.%d \n", broadcast_list[0], broadcast_list[1], broadcast_list[2], broadcast_list[3]);
							result_str(result,broadcast_list);
							//printf("Resultado: %s \n",&result);
							//return (result);
						}
					}else{
						printf("Comando no reconocido, se esperaba comandos MASK \n");
					}
				}
			}
			else{
				printf("Comando no reconocido, se esperaba comandos IP \n");
			}
		}else if (strcmp(buffer_list[1], "NETWORK") == 0){
			if (strcmp(buffer_list[2], "NUMBER") == 0){
				if (strcmp(buffer_list[3], "IP") == 0){
					direct_List(buffer_list[4], ip_list,&IP_ip_correct);
					if (IP_ip_correct == 1){
						printf("ip invalido \n");
					}else{
						//printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

						if (strcmp(buffer_list[5], "MASK") == 0){
							Validar_mask(buffer_list[6],maskcalc,mask_list,&MASK_ip_correct);
							if (MASK_ip_correct == 1){
								printf("mask invalido \n");
							}else{
								//printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);

								for (int i =0 ; i<4; i++){
									//NUm red
									num_red_list[i] = ip_list[i]&mask_list[i] ;
								}
								//printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
								result_str(result,num_red_list);
								//printf("Resultado: %s \n",&result);
								//return (result);
							}
						}else{
							printf("Comando no reconocido, se esperaba comandos MASK \n");
						}
					}
				}else{
					printf("Comando no reconocido, se esperaba comandos IP \n");
				}
			}
		
		}else if (strcmp(buffer_list[1], "HOSTS") == 0){
			if (strcmp(buffer_list[2], "RANGE") == 0){
				if (strcmp(buffer_list[3], "IP") == 0){
					direct_List(buffer_list[4], ip_list,&IP_ip_correct);
					if (IP_ip_correct == 1){
						printf("ip invalido \n");
					}else{
						printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

						if (strcmp(buffer_list[5], "MASK") == 0){
							Validar_mask(buffer_list[6],maskcalc,mask_list,&MASK_ip_correct);
							if (MASK_ip_correct == 1){
								printf("mask invalido \n");
							}else{
								printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);

								for (int i =0 ; i<4; i++){
									//NUm red
									num_red_list[i] = ip_list[i]&mask_list[i] ;
									// saca complemento de la mascara
									comp_mask_list[i] = 255^mask_list[i] ;
									//broadcast
									broadcast_list[i] = num_red_list[i]|comp_mask_list[i] ;
									if (i<=2){
										Start_range_res[i] = num_red_list[i] ;
										Final_range_res[i] = broadcast_list[i] ;
									}else{
										Start_range_res[i] = num_red_list[i]+1;
										Final_range_res[i] = broadcast_list[i]-1;
									}
									
								}
								printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
								printf("comp_mask_list:%d.%d.%d.%d \n", comp_mask_list[0], comp_mask_list[1], comp_mask_list[2], comp_mask_list[3]);
								printf("broadcast_list:%d.%d.%d.%d \n", broadcast_list[0], broadcast_list[1], broadcast_list[2], broadcast_list[3]);
								printf("INICIO:%d.%d.%d.%d \n", Start_range_res[0], Start_range_res[1], Start_range_res[2], Start_range_res[3]);
								printf("fin:%d.%d.%d.%d \n", Final_range_res[0], Final_range_res[1], Final_range_res[2], Final_range_res[3]);
								
								
								if(broadcast_list == num_red_list){
									Start_range_res[3] = num_red_list[3] +1;
								}
								
									val_fin(broadcast_list,Final_range_res);
									strcat(result,"{");
									result_str(result,Start_range_res);
									strcat(result," - ");
									result_str(result,Final_range_res);
									strcat(result,"}");
									//printf("Resultado: %s \n",&result);
									printf("INICIO:%d.%d.%d.%d \n", Start_range_res[0], Start_range_res[1], Start_range_res[2], Start_range_res[3]);
									printf("fin:%d.%d.%d.%d \n", Final_range_res[0], Final_range_res[1], Final_range_res[2], Final_range_res[3]);
								
															
								//return (result);
							}
						}else{
							printf("Comando no reconocido, se esperaba comandos MASK \n");
						}
					}
				}else{
					printf("Comando no reconocido, se esperaba comandos IP \n");
				}
			}
		
		}/*else if (strcmp(argv[2], "RANDOM") == 0){
			if (strcmp(argv[3], "SUBNETS") == 0){
				if (strcmp(argv[4], "NETWORK") == 0){
					if (strcmp(argv[4], "NUMBER") == 0){
						direct_List(argv[5], num_red_list,&num_red_correct);
						if (num_red_correct == 1){
							printf("num red invalido \n");
						}else{
							printf("num_red:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
							if (strcmp(argv[6], "MASK") == 0){
								Validar_mask(argv[7],maskcalc,mask_list,&MASK_ip_correct);
								if (MASK_ip_correct == 1){
									printf("mask invalido \n");
								}else{
									printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
									
								}
							}else{
								printf("Comando no reconocido, se esperaba comandos MASK \n");
							}
						}
					}
					}else{
						printf("Comando no reconocido, se esperaba comandos NUMBER \n");
					}
				}else{
					printf("Comando no reconocido, se esperaba comandos NETWORK \n");
				}
			}else{
				printf("Comando no reconocido, se esperaba comandos SUBNETS \n");
			}
		}*/
		else{
		printf("Comando no reconocido, se esperaba alguno de los siguientes comandos (BROADCAST,NETWORK,HOSTS,RANDOM) \n");
		}
	}else{
		printf("Comando no reconocido \n");
	}
	printf("PRUEBA: %s\n", result);
    //return result;
	//return 0;

}

int main(int  argc, char* argv[]){

  char *ip = "127.0.0.1";
  char result[100]="";
  char buffer[1024]="";
  char str[1024] = "x";
  int port = 9666;
  char *token;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  //char buffer[1024];
  int n;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  
  //printf("[+]TCP server socket created.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(ip);

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("[-]Bind error");
    exit(1);
  }
  printf("[+]Bind to the port number: %d\n", port);

  listen(server_sock, 5);
  printf("Listening...\n");

  while(1){
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+]Client connected.\n");

	bzero(buffer, 1024);
	strcpy(buffer, "Para salir escriba: x \n");
    //printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);

	int flag = 1;
	while(flag==1){
		bzero(buffer, 1024);
		recv(client_sock, buffer, sizeof(buffer), 0);
		printf("%d", strcmp(buffer,"x"));
		strcpy(str, buffer);
		token = strtok(str," ");
		if (strcmp(buffer,"x")==13){	
			
			flag = 0;
			
		}
		else{
			calc(buffer, result);
			//printf("Server: %s\n", result);
			send(client_sock, result, strlen(result), 0);

			bzero(result, 100);
			bzero(buffer, 1024);
			strcpy(buffer, "\nPara salir escriba: x \n");
			//printf("Server: %s\n", buffer);
			send(client_sock, buffer, strlen(buffer), 0);
		}
		

	}
	bzero(buffer, 1024);
    strcpy(buffer, "DESCONECTADO!");
	send(client_sock, buffer, strlen(buffer), 0);
	close(client_sock);
    // char * token = strtok(buffer, " ");
    // // loop through the string to extract all other tokens
    // while( token != NULL ) {
    //     printf( " %s\n", token ); //printing each token
    //     token = strtok(NULL, " ");
    // }
    // printf("Client: %s\n", buffer);
    // bzero(buffer, 1024);
    // strcpy(buffer, "HI, THIS IS SERVER. HAVE A NICE DAY!!!");
    // printf("Server: %s\n", buffer);
  }
  return 0;
}

// for (int i =0; i<argc;i++){
// 		strcat(buffer,argv[i]);
// 		strcat(buffer," ");
// 	}
// 	printf("%s",buffer);

// 	//calc(argv, result);
	
// 	calc(buffer, result);