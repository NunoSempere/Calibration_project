#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "analyze_data.h"
#include "datatypes.h"
#include "extract_data.h"

int initialize_table_percentages(row_percentage* TablePercentages){
	int i;
	
	/*
		Something we've learnt here.
		Suppose that we declared:
				TablePercentages = (row_percentage*) calloc(100, sizeof(row_percentage));
		here, in this function.
		Then it get's tricky to propagate the pointer to the main()
	*/	

	if(TablePercentages==NULL){
		fprintf(stdout,"\nERROR in an instantiation of initialize_table_percentages,");
		fprintf(stdout,"\nwhich lives in: analyze_data.c");
		fprintf(stdout,"\nNULL pointer given for TablePercentages");
		return 0;
	}
	
	for(i=0; i<100; i++){
		TablePercentages[i].percentage_represented = i;
		TablePercentages[i].proportion_of_true = NULL_STATE; 
		TablePercentages[i].num_true=0;
		TablePercentages[i].num_false=0;
	}

}

int compute_percentages(row_percentage* TablePercentages){
	if(TablePercentages==NULL){
		fprintf(stdout,"\nERROR in an instantiation of compute_percentages,");
		fprintf(stdout,"\nwhich lives in: analyze_data.c");
		fprintf(stdout,"\nNULL pointer given for TablePercentages");
		return 0;

	}
	int i, p, verdadero, falso;
	for(i=0; i<100; i++){
		verdadero = TablePercentages[i].num_true;
		falso = TablePercentages[i].num_false;
		if(verdadero > 0 || falso>0){
			p = 100*(float) verdadero/ (float) (verdadero + falso);
			TablePercentages[i].proportion_of_true = p; 
			//fprintf(stdout, "\ni = %d, %% = %d", i, p);
		}

	}
	return 1;
}

row_percentage* create_table_percentages(table_predictions *TablePreds){

	int i, max, state, credence;
	if(TablePreds==NULL){
		fprintf(stdout,"\nERROR in an instantiation of create_TablePercentages,");
		fprintf(stdout,"\nwhich lives in: analyze_data.c");
		fprintf(stdout,"\nNULL pointer given for TablePreds");
		return NULL;

	}
	
	row_percentage* TablePercentages;

	TablePercentages =(row_percentage*) calloc(100, sizeof(row_percentage));

	if(initialize_table_percentages(TablePercentages) == 0){
		fprintf(stdout,"\nERROR in an instantiation of create_TablePercentages,");
		fprintf(stdout,"\nwhich lives in: analyze_data.c");
		fprintf(stdout,"\npropagated from initialize_table_percentages,");
		fprintf(stdout,"\nwhich lives in: analyze_data.c");
		return NULL;
	}
	
	max= TablePreds->num;
	for(i=0; i<max; i++){
		state = TablePreds->table[i].state;
		credence = TablePreds->table[i].credence;
		//printf("\ncredence = %d", credence);
		if( state == 0){
			TablePercentages[(int) floor(credence)].num_false++;
		}
		else if(state == 1){
			TablePercentages[(int) floor(credence)].num_true++;
		}/**/
	}

	compute_percentages(TablePercentages);	
	return TablePercentages;
}
