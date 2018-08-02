#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "datatypes.h"
#include "extract_data.h"


prediction *parse_prediction(char *str){
/*
This function receives a string, f.ex:
"Didn't lose mobile; 95; T; -."
It creates a prediction* P, allocates memory, and fills it with the appropriate data.
*/




	int i;
	int credence;
	
	prediction *P;
	P= (prediction *) calloc(1, sizeof(prediction));


	P->credence = 0;
	if(P==NULL || initialize_prediction(P) ==0){
		fprintf(stdout,"\nERROR: in function parse_prediction");
		fprintf(stdout,"\nwhich lives in extract_data.c");
		fprintf(stdout,"\nposssibly propagated because of initialize_prediction(),");
		fprintf(stdout,"\nwhich lives in datatypes.c");
		fprintf(stdout,"\nP is not correctly initialized");
		return NULL;
	}
	
	i=0;
	while(str[i]!=';' && i< MAX_STATEMENT-1){
		P->statement[i]=str[i];

		i++;

	}
	P->statement[i]='\0';
	
	i++;

	while(str[i]==' '){
		i++;

	}

	credence=0;
	while((int)str[i]>=48 && (int)str[i] <=57){
		credence = credence*10 + (int) (str[i])-48;
		i++;	

	}
	
	P->credence = credence;

	while(str[i]==' ' || str[i] ==';'){
		i++;	
	}

	switch((int) str[i]){
		case (int) 'T':
			P->state = 1;
        		break;
	
		case (int) 'F':
			P->state = 0;
		        break;

		case (int) 'U':
			P->state = 2;
		        break;
		default:
			fprintf(stdout, "\nInvalid state for the prediction");
			fprintf(stdout, "\nError in parse_prediction\n\n");
	
	}
	
	// and now we ignore comments like a champ.
	return P;
	

}

table_predictions * parse_data(char * file_name){
/* 
This function opens a file 
and adds predictions 
to a variable called TablePreds, of the datatype table_predictions
which contains
	- a table with predictions
	- its size
The size is important, because if it is about to overflow, we gotta use a realloc
*/
	
	FILE *f;
	char *str;
	prediction *P; // We are not a cult.
	table_predictions *TablePreds;

	str = (char *) calloc(MAX_STRING, sizeof(char)); 

	TablePreds=new_table_predictions();
	if(TablePreds==NULL || TablePreds->table ==NULL){
		fprintf(stdout,"\nERROR in an instantiation of parse_data,");
		fprintf(stdout,"\nwhich lives in: extract_data.c");
		fprintf(stdout,"\nPropagated from new_table_predictions(),");
		fprintf(stdout,"\nWhich lives in datatypes.c");
		return NULL;
	}

	f=fopen(file_name,"r+");
	if(f==NULL){
		fprintf(stdout,"\nERROR in an instantiation of parse_data,");
		fprintf(stdout,"\nwhich lives in: extract_data.c");
		fprintf(stdout,"\n the file does not open\n");
		return NULL;
	}

	while(fgets(str, MAX_STRING, f)!=NULL){

		P=parse_prediction(str);
		//fprintf(stdout,"\ncredence = %d", P->credence);
		if(P==NULL){

			fprintf(stdout,"\nERROR in an instantiation of parse_data:");
			fprintf(stdout,"\nwhich lives in: extract_data.c");
			fprintf(stdout,"\npropagated from: parse_prediction");
			fprintf(stdout,"\nWhich lives in datatypes.c");
			fclose(f);
			return TablePreds;//puede continuar
		}

		if(add_prediction(P, TablePreds)==0){
			fprintf(stdout,"\nERROR in an instantiation of parse_data:");
			fprintf(stdout,"\nwhich lives in: extract_data.c");
			fprintf(stdout,"\npropagated from: add_prediction");
			fprintf(stdout,"\nWhich lives in datatypes.c");
			fclose(f); 		
			return NULL;
		}

	}

	//printf("\ntable_predictions successfully created");

   	fclose(f);
	free(str);
	return TablePreds;	
		

}
