#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "datatypes.h"
#include "extract_data.h"


int parse_statement(char *str, int* k, prediction* P){	

	int i = *k; // because k is a pointer, and I want to work with an integer.

	while(str[i]!=';' && i< MAX_STATEMENT-1){
		P->statement[i]=str[i];
		i++;
	}

	P->statement[i]='\0';
	i++;

	*k = i;

	return 1;

}

int parse_credence(char *str, int *k,prediction* P){

	int i = *k;

	int credence=0;

	while((int)str[i]>=(int)'0' && (int)str[i] <= (int)'9'){
		credence = credence*10 + (int) (str[i])- (int) '0';
		i++;	

	}	
	P->credence = credence;
	
	*k = i;

	return 1;

}

int parse_state(char *str, int *k, prediction* P){

	switch((int) str[*k]){
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

	return 1;

}

int parse_date_of_resolution(char *str, int *k,prediction* P){
	
	int i = *k;

	int j;
	char temp[4];

	for(j=0; j<4; j++){
		temp[j]='\0';
	}

	j=0;
	while(str[i]!='/' && j<2){
		temp[j]=str[i];
		j++;
		i++;
	}

	if(temp[1]=='\0'){ // the day has 1 digit; it's 1-9, not 10-31
		P->fecha.day = (int)temp[0] - (int)'0';
	}
	else{
		P->fecha.day = ( (int) temp[0] - (int) '0') + ( (int)temp[1] - (int)'0')*10;
	}

	// 	Nos hemos quedado en str[i]=='\', por lo que
	i++;
	// Y ahora vamos a por el mes.

	for(j=0; j<4; j++){
		temp[j]='\0';
	}

	j=0;

	while(str[i]!='/'){
		temp[j]=str[i];
		j++;
		i++;
	}
	if(temp[1]=='\0'){ // the month has 1 digit; it's 1-9, not 10-12.
		P->fecha.month = (int)temp[0] - (int)'0';
	}
	else{
		P->fecha.month = ( (int) temp[0] - (int) '0') + ( (int)temp[1] - (int)'0')*10;
	}

	// Now we are again at str[i]=='\', so
	i++;
	// And we go to the year
	P->fecha.year = ((int) str[i])*1000 + ((int)str[i+1])*100 + ((int)str[i+2])*10 +((int)str[i+3])*1;

	*k = i;

}

prediction *parse_prediction(char *str){
/*
This function receives a string, f.ex:
"Didn't lose mobile; 95; T; -."
It creates a prediction* P, allocates memory, and fills it with the appropriate data.
*/


	int i,j;
	int credence;
	char date[11];
	char temp[4];

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
	
	// We parse each part of the statement in a separate function. 
	parse_statement(str, &i,P);
	while(str[i]==' ' || str[i] ==';'){ i++; }

	parse_credence(str, &i,P);
	while(str[i]==' ' || str[i] ==';'){ i++; }
	
	parse_state(str, &i,P);
	while(str[i]==' ' || str[i] ==';'){ i++; }

	parse_date_of_resolution(str, &i,P);

	// So much fucking clearer than before.

	return P;
	

}


int is_comment(char *str){
	if((str[0]=='/' && str[1]=='/') || str[0]=='\n'){
		return 1;
	}
	return 0;
}


table_predictions * parse_data(FILE *f){
/* 
This function opens a file 
and adds predictions 
to a variable called TablePreds, of the datatype table_predictions
which contains
	- a table with predictions
	- its size
The size is important, because if it is about to overflow, we gotta use a realloc
*/
	

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

	if(f==NULL){
		fprintf(stdout,"\nERROR in an instantiation of parse_data,");
		fprintf(stdout,"\nwhich lives in: extract_data.c");
		fprintf(stdout,"\n the file does not open\n");
		return NULL;
	}

	while(fgets(str, MAX_STRING, f)!=NULL){

	
		if(is_comment(str)==0){

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

	}

	//printf("\ntable_predictions successfully created");

   	fclose(f);
	free(str);
	return TablePreds;	
		

}
