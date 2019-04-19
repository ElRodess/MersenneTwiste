#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "MersenneTwister.h"
#include "CrackSeed.h"
#include "UnShift.h"
#include <string.h>

struct CYPHERTEXT
{
   u_int8_t* cypher;
   int size;
};
typedef struct CYPHERTEXT Cyphertext;



Cyphertext encrypt(char* clear_text,u_int16_t key)
{
	seed_mt(key);
	Cyphertext Cypher;
	Cypher.cypher = malloc((strlen(clear_text)) * sizeof(u_int8_t));
	Cypher.size = strlen(clear_text);
	u_int8_t bytes[4];
	u_int32_t out_MT;
	int i;
	for(i = 0; i < strlen(clear_text); i++){
		if(i % 4 == 0){
			out_MT = extract_number();
			//~ printf("%x \n", out_MT);
			bytes[3] = (out_MT >> 24) & 0xFF;
			bytes[2] = (out_MT >> 16) & 0xFF;
			bytes[1] = (out_MT >> 8) & 0xFF;
			bytes[0] = out_MT & 0xFF;
		}
		Cypher.cypher[i] = clear_text[i] ^ bytes[i % 4] & 0xFF;
		//~ printf("%x xor %x = %x , %d \n", clear_text[i], bytes[i % 4], Cypher.cypher[i], i % 4);
	}
	return Cypher;
}

char* decrypt(Cyphertext cypher, u_int16_t key) {
	seed_mt(key);
	char* clear_text = malloc((cypher.size + 1) * sizeof(char));
	u_int8_t bytes[4];
	u_int32_t out_MT;
	int i;
	for(i = 0; i < cypher.size; i++){
		if(i % 4 == 0){
			out_MT = extract_number();
			//~ printf("%x \n", out_MT);
			bytes[3] = (out_MT >> 24) & 0xFF;
			bytes[2] = (out_MT >> 16) & 0xFF;
			bytes[1] = (out_MT >> 8) & 0xFF;
			bytes[0] = out_MT & 0xFF;
		}
		clear_text[i] = cypher.cypher[i] ^ bytes[i%4];
	}
	clear_text[i+1] = '\0';
	return clear_text;
}

char* append(char* txt, char* c)
{
	char* tmp = malloc(strlen(txt)+strlen(c)+1);
	tmp[0] = '\0';
	strcat(tmp,txt);
	strcat(tmp,c);
	return tmp;
}

u_int16_t routineV2(u_int32_t val,int k)
{
	//printf("V1 :  %u |V2 : %u \n",val1,val2);
	u_int16_t seed= 0;
	u_int32_t try = 0;
	int i = 0;
	while(try != val)
	{			
		usleep(rand()%1000000 +40000);
		seed = time(NULL);
		seed_mt(seed);
		for(i=0;i<k;i++)
			printf("%u || ",extract_number());
		try = extract_number();
		printf("seed = %u : %u\n",seed,try);
	}
	return seed;
}


u_int16_t AttaqueForceSeed(Cyphertext cypher,int taille_clair)
{
	taille_clair = taille_clair -14; // on enleve ceux dont on connait la valeur
	int tmp = taille_clair %4;
	int pos = 0; int i;
	u_int32_t val = 0; u_int16_t seed = 0;
	switch (tmp){ // cherche le debut d'une valeur craquable
		case 0 :
			pos = taille_clair + 4;
			break;
		case 1 :
			pos = taille_clair + 3;
			break;
		case 2 :
			pos = taille_clair + 2;
			break;
		case 3:
			pos = taille_clair + 1;
			break;
	}
	for(i = 0;i<4;i++)
	{
		val = val << 8 ;
		val = val | (cypher.cypher[pos + i] ^ 0x41);
		printf("val it: %d = %u \n",i,val);
	}
	//val ^= 0x41414141;// val de AAAA;
	seed = routineV2(val,pos/4);
	return seed;
}

char* AttaqueUnshift(Cyphertext cypher) // A debuguer
{
	int i,j,k;
	u_int32_t XorVal[624];
	u_int8_t tmp[4];
	char* temp[4];
	j= 0;
	for(i=0;i<(624*4);i+=4)
	{
		tmp[0] = cypher.cypher[i] ^ 0x41;
		tmp[1] = cypher.cypher[i+1] ^ 0x41;
		tmp[2] = cypher.cypher[i+2] ^ 0x41;
		tmp[3] = cypher.cypher[i+3] ^ 0x41;
		XorVal[j] = tmp[0] ;
		for(k =1;k<3;k++)
		{
			XorVal[j] = XorVal[j]<< 8;
			XorVal[j] = XorVal[j] | tmp[k];
		}
		j++;
	}
	printf("%x \n",XorVal[j]);
	for(i=0; i <624;i++)
	{
		MT[i] = untemper(XorVal[i]);
	}
	indx = 1;
	char* clear_text = malloc((cypher.size + 1) * sizeof(char));
	u_int8_t bytes[4];
	u_int32_t out_MT;
	for(i = 1; i < cypher.size; i++){
		if(i % 4 == 0){
			out_MT = extract_number();
			//~ printf("%x \n", out_MT);
			bytes[3] = (out_MT >> 24) & 0xFF;
			bytes[2] = (out_MT >> 16) & 0xFF;
			bytes[1] = (out_MT >> 8) & 0xFF;
			bytes[0] = out_MT & 0xFF;
		}
		clear_text[i] = cypher.cypher[i] ^ bytes[i%4];
	}
	clear_text[i+1] = '\0';	
	return clear_text;
}



int main(int argc, char **argv)
{
	//~ int i = 0;
	char* clear_text = "salut";
	char* A = "AAAAAAAAAAAAAA";
	//~ for(i =0;i<624;i++)
		//~ A = append(A,"AAAA");
	clear_text = append(clear_text,A);
	u_int16_t seed = time(NULL) + 5;
	Cyphertext Cypher = encrypt(clear_text,seed);
	 //~ printf("%s \n",AttaqueUnshift(Cypher));
	printf("key = %u \n",seed);
	printf("longueur : %d \n",strlen(clear_text));
	u_int16_t cracked_key = AttaqueForceSeed(Cypher,strlen(clear_text)-1);
	printf("%x \n","AAAA");
}

  
  

