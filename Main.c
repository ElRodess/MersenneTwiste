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

char* AttaqueUnshift(Cyphertext cypher)
{
	int i,j;
	u_int32_t M[624];
	u_int32_t XorVal[624];
	char* tmp = "";
	j= 0;
	for(i=0;i<(624*4);i+=4)
	{
		tmp = append(tmp,(char*)cypher.cypher[i]);
		tmp = append(tmp,(char*)cypher.cypher[i+1]);
		tmp = append(tmp,(char*)cypher.cypher[i+2]);
		tmp = append(tmp,(char*)cypher.cypher[i+3]);
		XorVal[j] = tmp ^"AAAA";
		tmp = append("","");
	}
	for(i=0; i <624;i++)
		M[i] = untemper(XorVal[i]);
	return "oui";
}



int main(int argc, char **argv)
{
	int i = 0;
	char* clear_text = "salut";
	char* A = "";
	for(i =0;i<624;i++)
		A = append(A,"AAAA");
	clear_text = append(A,clear_text);
	u_int16_t seed = 123;
	Cyphertext Cypher = encrypt(clear_text,seed);
	char* decrypt= AttaqueUnshift(Cypher);
	
}

  
  

