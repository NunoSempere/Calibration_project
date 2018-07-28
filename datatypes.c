#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "datatypes.h"
#include "constants.h"


int initialize_prediction(prediction *P){
	
	int i;
	
/*
	This step fucks everything up if we call from a TablePreds hierarchy:
	P= (prediction *) calloc(1, sizeof(prediction));
	if(P==NULL){
		fprintf(stdout, "\nError in an instance of initialize_prediction,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nMemory allocation to Prediction P failed");
		return NULL;
	}
*/
	P->statement = (char*) calloc(MAX_STATEMENT, sizeof(char));
	if(P->statement==NULL){
		fprintf(stdout, "\nError in an instance of initialize_prediction:");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nMemory allocation to P->statement failed");
		return 0;
	}
	
	for(i=0; i<MAX_STATEMENT; i++){
		P->statement[i]='\0';
	}

	P->state = NULL_STATE;
	P->credence = NULL_STATE;

	return 1;

}


table_predictions *new_table_predictions(){
	
	table_predictions *TablePreds;
	TablePreds = calloc(1, sizeof(table_predictions));
	TablePreds->table = (prediction *) calloc(64, sizeof(prediction));

	if(TablePreds == NULL || TablePreds->table == NULL){
		fprintf(stdout, "\nError in an instance of new_table_predictions,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nMemory allocation to TablePreds or to TablePreds->table failed");
		return NULL;
	}
	
	TablePreds->size =64;
	TablePreds->num=0;

	return TablePreds;
}

int increase_size(table_predictions *TablePreds){
	
	if(TablePreds == NULL){
		fprintf(stdout, "\nError in an instance of new_table_predictions,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nNULL pointer received for var TablePreds");
		return 0;
	}
	int size = TablePreds->size;
	
	if(TablePreds->table == NULL){
		fprintf(stdout, "\nError in an instance of new_table_predictions,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nNULL pointer received for var TablePreds->table");
		return 0;
	}
	
	TablePreds->table = realloc(TablePreds->table, (TablePreds->size)*sizeof(prediction)*2);
	TablePreds->size = (TablePreds->size)*2;

	return 1;

}

int cut_paste_preds(prediction *Origin, prediction *Destination){

	if(Origin == NULL || Destination == NULL || Origin->statement == NULL){
		fprintf(stdout, "\nError in an instance of copy_paste_preds,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nNULL pointer received for var Origin or Destination or Origin->statement");

		return 0;	
	}

	if(initialize_prediction(Destination)==0){
		fprintf(stdout, "\nError in an instance of copy_paste_preds,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nError propagated from initialize_prediction");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		return 0;	
	}

	Destination->state = Origin->state;
	Destination->credence = Origin->credence;
	strcpy(Destination->statement, Origin->statement);

	free(Origin->statement);	
	free(Origin);
	return 1;
	
}

int add_prediction(prediction *P, table_predictions *TablePreds){
	
	/*
		I'm probably soon going to degenerate into:
		if(TablePreds == NULL || TablePreds -> table == NULL || P == NULL){...}
	*/	


	if(TablePreds == NULL || TablePreds -> table == NULL || P == NULL){
		fprintf(stdout, "\nError in an instance of add_prediction,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nNULL pointer received for var TablePreds, TablePreds->table, or P");
		return 0;
	}

	/*if(TablePreds->num==TablePreds->size){
		if(increase_size(TablePreds)==0){
			fprintf(stdout, "\nError in an instance of add_prediction,");
			fprintf(stdout, "\nwhich lives in datatypes.c");
			fprintf(stdout, "\nPropagated from increase_size,");
			fprintf(stdout, "\nwhich lives in datatypes.c");
		}
		
	}*/


	if(cut_paste_preds(P, &TablePreds->table[TablePreds->num])==0){
		fprintf(stdout, "\nError in an instance of add_prediction,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
		fprintf(stdout, "\nPropagated from cut_paste_preds,");
		fprintf(stdout, "\nwhich lives in datatypes.c");
	}
	TablePreds->num++;
	// Note that this line must go afterwards
	// Because otherwise we'd be leaving position 0 empty
	return 1;

}
