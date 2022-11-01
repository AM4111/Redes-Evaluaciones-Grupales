#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void Validar_mask(char* p_direct, char* maskcalc,int* mask_list, int* ip_correct){
	if (strrchr(p_direct , '/')!= NULL){
		char *cadena = strtok(p_direct,"/");
		int mask = (int) strtol(cadena, NULL, 10);
		calmask(mask,maskcalc);

		printf("mascara %s -> %s \n", p_direct, maskcalc);

		direct_List(maskcalc, mask_list, ip_correct);
		//printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
		
	}else {
		direct_List(p_direct, mask_list, ip_correct);
		//printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
	}	
}

int main(int  argc, char* argv[])
{
// variables
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
/*
	//Res
	char broadcast_res[];
	char Num_Red_res[];
	char Start_range_res[];
	char Final_range_res[];
	char Subnets_res[];
*/

    unsigned char* mask_cal;
/*
	// obtener ip parametro para trabajar
	direct_List(argv[1], ip_list);
	printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);
	
	// obtener mask parametro para trabajar
	if (strrchr(argv[2] , '/')!= NULL){
		char *cadena = strtok(argv[2],del_backslash);
		int mask = (int) strtol(cadena, NULL, 10);
		calmask(mask,maskcalc);

		printf("mascara %s -> %s \n", argv[2] , maskcalc);

		direct_List(maskcalc, mask_list);
		printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
		
	}else {
		
		direct_List(argv[2], mask_list);
		printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);
	}

	// # Red
	for (int i =0 ; i<4; i++){
		//NUm red
		num_red_list[i] = ip_list[i]&mask_list[i] ;
	}
	printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);

	
	// saca complemento de la mascara
	for (int i =0 ; i<4; i++){
		comp_mask_list[i] = 255^mask_list[i] ;
	}
	printf("comp_mask_list:%d.%d.%d.%d \n", comp_mask_list[0], comp_mask_list[1], comp_mask_list[2], comp_mask_list[3]);

    //broadcast
	for (int i =0 ; i<4; i++){
		broadcast_list[i] = num_red_list[i]|comp_mask_list[i] ;
	}
	printf("broadcast_list:%d.%d.%d.%d \n", broadcast_list[0], broadcast_list[1], broadcast_list[2], broadcast_list[3]);
*/
	if (strcmp(argv[1], "GET") == 0){
		if (strcmp(argv[2], "BROADCAST") == 0){
			if (strcmp(argv[3], "IP") == 0){
				direct_List(argv[4], ip_list,&IP_ip_correct);
				if (IP_ip_correct == 1){
					printf("ip invalido \n");
				}else{
					printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

					if (strcmp(argv[5], "MASK") == 0){
						Validar_mask(argv[6],maskcalc,mask_list,&MASK_ip_correct);
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
							}
							printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
							printf("comp_mask_list:%d.%d.%d.%d \n", comp_mask_list[0], comp_mask_list[1], comp_mask_list[2], comp_mask_list[3]);
							printf("broadcast_list:%d.%d.%d.%d \n", broadcast_list[0], broadcast_list[1], broadcast_list[2], broadcast_list[3]);
						}
					}else{
						printf("Comando no reconocido, se esperaba comandos MASK \n");
					}
				}
			}
			else{
				printf("Comando no reconocido, se esperaba comandos IP \n");
			}
		}else if (strcmp(argv[2], "NETWORK") == 0){
			if (strcmp(argv[3], "NUMBER") == 0){
				if (strcmp(argv[4], "IP") == 0){
					direct_List(argv[5], ip_list,&IP_ip_correct);
					if (IP_ip_correct == 1){
						printf("ip invalido \n");
					}else{
						printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

						if (strcmp(argv[6], "MASK") == 0){
							Validar_mask(argv[7],maskcalc,mask_list,&MASK_ip_correct);
							if (MASK_ip_correct == 1){
								printf("mask invalido \n");
							}else{
								printf("mask:%d.%d.%d.%d \n", mask_list[0], mask_list[1], mask_list[2], mask_list[3]);

								for (int i =0 ; i<4; i++){
									//NUm red
									num_red_list[i] = ip_list[i]&mask_list[i] ;
								}
								printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
							}
						}else{
							printf("Comando no reconocido, se esperaba comandos MASK \n");
						}
					}
				}else{
					printf("Comando no reconocido, se esperaba comandos IP \n");
				}
			}
		
		}else if (strcmp(argv[2], "HOSTS") == 0){
			if (strcmp(argv[3], "RANGE") == 0){
				if (strcmp(argv[4], "IP") == 0){
					direct_List(argv[5], ip_list,&IP_ip_correct);
					if (IP_ip_correct == 1){
						printf("ip invalido \n");
					}else{
						printf("ip:%d.%d.%d.%d \n", ip_list[0], ip_list[1], ip_list[2], ip_list[3]);

						if (strcmp(argv[6], "MASK") == 0){
							Validar_mask(argv[7],maskcalc,mask_list,&MASK_ip_correct);
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
								}
								printf("num_red_list:%d.%d.%d.%d \n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]);
								printf("comp_mask_list:%d.%d.%d.%d \n", comp_mask_list[0], comp_mask_list[1], comp_mask_list[2], comp_mask_list[3]);
								printf("broadcast_list:%d.%d.%d.%d \n", broadcast_list[0], broadcast_list[1], broadcast_list[2], broadcast_list[3]);
								printf("RANGOO: {%d.%d.%d.%d - %d.%d.%d.%d }\n", num_red_list[0], num_red_list[1], num_red_list[2], num_red_list[3]+1, broadcast_list[0], broadcast_list[1], broadcast_list[2], broadcast_list[3]-1);
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



    return 0;
}
