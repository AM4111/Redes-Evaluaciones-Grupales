//https://github.com/nikhilroxtomar/TCP-Client-Server-Implementation-in-C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

void ip_binary(unsigned long result,int valores[4]){
	
	for(int value = 3 ; value >= 0 ; value--)
	{	
		valores[value]= result & 255;
		result = result >> 8 ;
	}

}

//retorna int de de la operacion 
unsigned long int  ip_INT(int list[4]){
	unsigned long int result=0;
	for(int value = 0 ; value < 4 ; value++)
	{	
		result = result << 8 ;
		result = result | list[value];
	}
	return  result;
}

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

		   //GET BROADCAT IP 10.8.2.5 MASK /29
		   //GET RANDOM SUBNETS NETWORK NUMBER 10.0.0.0 MASK /8 NUMBER 3 SIZE /24
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

    char maskcalc[16]="",
    del_semicolon[] = ";",
    del_backslash[] = "/";

	int IP_ip_correct  = 0;
	int MASK_ip_correct  = 0;
	int MASK_ip_correct_subnet  = 0;
	int num_red_correct  = 0;


    int list_mask[5] ;
	int comp_mask_list[4] ;
	int SubNet_res[4] ;
	int num_red_list[4] ;
	int broadcast_list[4] ;
	int mask_list[4] ;
	int mask_list_subnet[4] ;
	int ip_list[4];
	int Start_range_res[4];
	int Final_range_res[4];

    unsigned char* mask_cal;
	unsigned char* maskcalc_subnet;

	if (strcmp(buffer_list[0], "GET") == 0){
		if (strcmp(buffer_list[1], "BROADCAST") == 0){
			if (strcmp(buffer_list[2], "IP") == 0){
				direct_List(buffer_list[3], ip_list,&IP_ip_correct);
				if (IP_ip_correct == 1){
					//printf("ip invalido \n");
					strcat(result,"ip invalido \n");
				}else{
					//printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

					if (strcmp(buffer_list[4], "MASK") == 0){
						Validar_mask(buffer_list[5],maskcalc,mask_list,&MASK_ip_correct);
						if (MASK_ip_correct == 1){
							//printf("mask invalido \n");
							strcat(result,"mask invalido \n");
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
						//printf("Comando no reconocido, se esperaba comandos MASK \n");
						strcat(result,"Comando no reconocido, se esperaba comandos MASK \n");
					}
				}
			}
			else{
				//printf("Comando no reconocido, se esperaba comandos IP \n");
				strcat(result,"Comando no reconocido, se esperaba comandos IP \n");
			}
		}else if (strcmp(buffer_list[1], "NETWORK") == 0){
			if (strcmp(buffer_list[2], "NUMBER") == 0){
				if (strcmp(buffer_list[3], "IP") == 0){
					direct_List(buffer_list[4], ip_list,&IP_ip_correct);
					if (IP_ip_correct == 1){
						//printf("ip invalido \n");
						strcat(result,"ip invalido \n");
					}else{
						//printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

						if (strcmp(buffer_list[5], "MASK") == 0){
							Validar_mask(buffer_list[6],maskcalc,mask_list,&MASK_ip_correct);
							if (MASK_ip_correct == 1){
								//printf("mask invalido \n");
								strcat(result,"mask invalido \n");
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
							//printf("Comando no reconocido, se esperaba comandos MASK \n");
							strcat(result,"Comando no reconocido, se esperaba comandos MASK \n");
						}
					}
				}else{
					//printf("Comando no reconocido, se esperaba comandos IP \n");
					strcat(result,"Comando no reconocido, se esperaba comandos IP \n");
				}
			}
		
		}else if (strcmp(buffer_list[1], "HOSTS") == 0){
			if (strcmp(buffer_list[2], "RANGE") == 0){
				if (strcmp(buffer_list[3], "IP") == 0){
					direct_List(buffer_list[4], ip_list,&IP_ip_correct);
					if (IP_ip_correct == 1){
						//printf("ip invalido \n");
						strcat(result,"ip invalido \n");
					}else{
						//printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

						if (strcmp(buffer_list[5], "MASK") == 0){
							Validar_mask(buffer_list[6],maskcalc,mask_list,&MASK_ip_correct);
							if (MASK_ip_correct == 1){
								//printf("mask invalido \n");
								strcat(result,"mask invalido \n");
							}else{
								//printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);

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
								//printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
								//printf("comp_mask_list:%d.%d.%d.%d \n", comp_mask_list[0], comp_mask_list[1], comp_mask_list[2], comp_mask_list[3]);
								//printf("broadcast_list:%d.%d.%d.%d \n", broadcast_list[0], broadcast_list[1], broadcast_list[2], broadcast_list[3]);
								//printf("INICIO:%d.%d.%d.%d \n", Start_range_res[0], Start_range_res[1], Start_range_res[2], Start_range_res[3]);
								//printf("fin:%d.%d.%d.%d \n", Final_range_res[0], Final_range_res[1], Final_range_res[2], Final_range_res[3]);
								
								
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
									//printf("INICIO:%d.%d.%d.%d \n", Start_range_res[0], Start_range_res[1], Start_range_res[2], Start_range_res[3]);
									//printf("fin:%d.%d.%d.%d \n", Final_range_res[0], Final_range_res[1], Final_range_res[2], Final_range_res[3]);
								
															
								//return (result);
							}
						}else{
							//printf("Comando no reconocido, se esperaba comandos MASK \n");
							strcat(result,"Comando no reconocido, se esperaba comandos MASK \n");
						}
					}
				}else{
					//printf("Comando no reconocido, se esperaba comandos IP \n");
					strcat(result,"Comando no reconocido, se esperaba comandos IP \n");

				}
			}
		//GET RANDOM SUBNETS NETWORK NUMBER 10.0.0.0 MASK /8 NUMBER 3 SIZE /24
		}else if (strcmp(buffer_list[1], "RANDOM") == 0){
			if (strcmp(buffer_list[2], "SUBNETS") == 0){
				if (strcmp(buffer_list[3], "NETWORK") == 0){
					if (strcmp(buffer_list[4], "NUMBER") == 0){
						direct_List(buffer_list[5], ip_list,&IP_ip_correct);
						if (num_red_correct == 1){
							//printf("num red invalido \n");
                            strcat(result,"num red invalido \n");
						}else{
						    //printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

						    if (strcmp(buffer_list[6], "MASK") == 0){
								
                                Validar_mask(buffer_list[7],maskcalc,mask_list,&MASK_ip_correct);
								printf("%s \n",maskcalc);
								printf("%s \n",mask_list);
								printf("%s \n",MASK_ip_correct);
								printf("%s \n",buffer_list[7]);
                                if (MASK_ip_correct == 1){
                                    //printf("mask invalido \n");
                                    strcat(result,"mask invalido \n");
                                
                                }else{
                                    //printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
                                    if (strcmp(buffer_list[8], "NUMBER") == 0){
										
				
                                        if (atoi(buffer_list[9]) > 0){
											
                                        	printf("ip1:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);
											//printf("%s",buffer_list[10]);
                                            if (strcmp(buffer_list[10], "SIZE") == 0){
												printf("ip2:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);
												//GET RANDOM SUBNETS NETWORK NUMBER 10.0.0.0 MASK /8 NUMBER 3 SIZE /24
												//Validar_mask(buffer_list[7],maskcalc,mask_list,&MASK_ip_correct);
												
                                                printf("%s \n",maskcalc_subnet);
                                                printf("%s \n",mask_list_subnet);
                                                printf("%s \n",MASK_ip_correct_subnet);
												printf("%s \n",buffer_list[11]);
                                                Validar_mask(buffer_list[11],maskcalc_subnet,mask_list_subnet,&MASK_ip_correct_subnet);
                                                printf("ip3:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);
												if (MASK_ip_correct_subnet == 1){
                                                    //printf("size invalido \n");
                                                    strcat(result,"size invalido \n");
                                                
                                                }else{
													
                                                    printf("mask:%d.%d.%d.%d \n", mask_list_subnet[0], mask_list_subnet[1], mask_list_subnet[2], mask_list_subnet[3]);

                                                
                                                    for (int i =0 ; i<4; i++){
                                                        //NUm red
                                                        num_red_list[i] = ip_list[i]&mask_list[i] ;
                                                        // saca complemento de la mascara
                                                        comp_mask_list[i] = 255^mask_list[i] ;
                                                        //broadcast
                                                        broadcast_list[i] = num_red_list[i]|comp_mask_list[i] ;
                                                        if (i<=2){
                                                            Start_range_res[i] = num_red_list[i] ;
                                                            SubNet_res[i]= num_red_list[i] ;
                                                            Final_range_res[i] = broadcast_list[i] ;
                                                        }else{
                                                            Start_range_res[i] = num_red_list[i]+1;
                                                            SubNet_res[i]= num_red_list[i] +1;
                                                            Final_range_res[i] = broadcast_list[i]-1;
                                                        }
                                                        
                                                    }
                                                    
                                                    if(broadcast_list == num_red_list){
                                                        Start_range_res[3] = num_red_list[3] +1;
                                                    }
                                                    
                                                    val_fin(broadcast_list,Final_range_res);

                                                    // complemento de la mascara se manda a funcion 
                                                    unsigned long int  num_hosts = ip_INT(comp_mask_list);
                                                    
                                                    //divide entre num red solicitadas genera tamanno_subnet
                                                    unsigned long int tamanno_subnet  = num_hosts/atoi(buffer_list[9]);

                                                    for(int i = 0 ; i < atoi(buffer_list[9])-1; i++){
                                                        // #subnet uiltima se manda a funcion 
                                                        unsigned long int  num_subnet = ip_INT(SubNet_res);

                                                        ip_binary(num_subnet,SubNet_res);

                                                        result_str(result,SubNet_res);    
                                                        strcat(result," "); 
                                                        strcat(result,buffer_list[11]);   
                                                        strcat(result,"\n"); 

                                                        num_subnet +=tamanno_subnet;
                                                    }                         
                                                    
                                                }
                                            }else{
                                                //printf("Comando no reconocido, se esperaba comandos SIZE \n");
                                                strcat(result,"Comando no reconocido, se esperaba comando SIZE \n");
                                            }

                                        }
                                        
                                        else{
                                            //printf("num  invalido \n");
                                            strcat(result,"num  invalido \n");
                                        }
                                    }else{
                                        //printf("Comando no reconocido, se esperaba comando NUMBER \n");
                                        strcat(result,"Comando no reconocido, se esperaba comando NUMBER \n");
                                    }
                                        
                                                                
                                    
                                }
                            }else{
                                //printf("Comando no reconocido, se esperaba comandos MASK \n");
                                strcat(result,"Comando no reconocido, se esperaba comando MASK \n");
                            }

						}
					
					}else{
						//printf("Comando no reconocido, se esperaba comando NUMBER \n");
                        strcat(result,"Comando no reconocido, se esperaba comando NUMBER \n");
					}
				}else{
					//printf("Comando no reconocido, se esperaba comandos NETWORK \n");
                    strcat(result,"Comando no reconocido, se esperaba comandos NETWORK \n");
				}
			}else{
				//printf("Comando no reconocido, se esperaba comandos SUBNETS \n");
                strcat(result,"Comando no reconocido, se esperaba comandos SUBNETS \n");
			}
		}
		else{
		//printf("Comando no reconocido, se esperaba alguno de los siguientes comandos (BROADCAST,NETWORK,HOSTS,RANDOM) \n");
		strcat(result,"Comando no reconocido, se esperaba alguno de los siguientes comandos (BROADCAST,NETWORK,HOSTS,RANDOM)\n");
		}
	}else{
		//printf("Comando no reconocido \n");
		strcat(result,"Comando no reconocido, se esperaba comandos GET \n");
	}

    //return result;
	//return 0;

}

int main(int  argc, char* argv[]){

  char *ip = "127.0.0.1";
  char result[100]="";
  char buffer[2048]="";
  char str[2048] = "x";
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

	bzero(buffer, 2048);
	strcpy(buffer, "Para salir escriba: x \n");
    //printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);

	int flag = 1;
	while(flag==1){
		bzero(buffer, 2048);
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
			bzero(buffer, 2048);
			strcpy(buffer, "\nPara salir escriba: x \n");
			//printf("Server: %s\n", buffer);
			send(client_sock, buffer, strlen(buffer), 0);
		}
		

	}
	bzero(buffer, 2048);
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