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
		In particular, if we write something like
		TablePercentages = New_pointer;
		Then only the version of TablePercentages in this function, but not anywhere else,
		will change,
		unless we propagate it.
		We knew this. 
		But not viscerally until we hunted the bug in a previous version of this function
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

row_percentage* create_table_percentages_aggregated(table_predictions *TablePreds){


	// This computes percentages in such a way that 60% and 40% feed into the same output.
	// Because saying that something will happen 60% of the time is the same as saying that
	// it's negation will happen 40% of the time

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
		if(floor(credence)>0 && floor(credence)<=50){
			if( state == 0){
				TablePercentages[(int) floor(credence)].num_false++;
			}
			else if(state == 1){
				TablePercentages[(int) floor(credence)].num_true++;
			}/**/

		}
		else if(floor(credence)<100 && floor(credence)>50){
			if( state == 0){
				TablePercentages[(int) floor(100-credence)].num_true++;
			}
			else if(state == 1){
				TablePercentages[(int) floor(100-credence)].num_false++;
			}/**/

		}
		else{
			fprintf(stdout, "One of your reported probabilities is not 0<P<100");
		}
	}

	compute_percentages(TablePercentages);	
	return TablePercentages;
}




float logarithmic_score_mod(table_predictions *TablePreds){

	/* 
	
	My proper scoring rule is going to be defined as the sum of log(p/0.5)*5/log(2), 
	where p is the reported probability.

	The 0.5 could be understood as a shitty prior
	or simply as a (positive) factor -log(0.5)*5/log(2) which allows the score to be positive.	

	Note that because I'm writing the input in percentages, p is in (0,100)
	So I'll use a log(p/50) factor

	*/

	int i, state;
	float score, temp;
	
	if(TablePreds == NULL || TablePreds->table ==NULL || TablePreds->num== NULL_STATE){
		fprintf(stdout,"\nERROR in an instantiation of logarithmic_score_mod,");
		fprintf(stdout,"\nwhich lives in: analyze_data.c");
		fprintf(stdout,"\nNULL pointer given for TablePreds/TablePreds->table/num");
	}
	
	score = 0;
	for(i=0; i<TablePreds->num; i++){
		
		state = TablePreds->table[i].state;
		// we look at the state to see if the prediction has been resolved;

		if(state == 1 | state == 0){

			if( state == 1){ 

				/* If the statement is true, 
				I calculate things with the credence given to it.*/

				temp = (float) TablePreds->table[i].credence / ( (float) 50);
			}
			
			else if(state == 0){ 

				/*If the statement is false, 
				I calculate things with the credence given to it's conjugate.*/

				temp = ( (float) (100 - TablePreds->table[i].credence) ) / ( (float) 50);
			}

			//fprintf(stdout, "\nCredence=%d", TablePreds->table[i].credence);
			// fprintf(stdout, "\nState = %d", TablePreds->table[i].state);
			// fprintf(stdout,"\nPurelog = %.6f\n", log(temp));

			score = score + log(temp)*5/log(2);

		}

		TablePreds->score = score;
	}
	
	TablePreds->score = score;

}


void brier_score_calc(table_predictions *TablePreds){


	/* 
	
		Brier score as defined in https://en.wikipedia.org/wiki/Brier_score#Definition

	*/

	int i, state;
	float score, temp;
	
	if(TablePreds == NULL || TablePreds->table ==NULL || TablePreds->num== NULL_STATE){
		fprintf(stdout,"\nERROR in an instantiation of brier_score_calc,");
		fprintf(stdout,"\nwhich lives in: analyze_data.c");
		fprintf(stdout,"\nNULL pointer given for TablePreds/TablePreds->table/num");
	}
	
	score = 0;
	for(i=0; i<TablePreds->num; i++){
		
		state = TablePreds->table[i].state;
		// we look at the state to see if the prediction has been resolved;

		if(state == 1 | state == 0){

			if( state == 1){ 

				/* If the statement is true, 
				I calculate things with the credence given to it.*/

				temp = (( (float) TablePreds->table[i].credence)/ ( (float) 100) )  - 1;
				temp = temp*temp;
				//printf("%f", temp);
			}
			
			else if(state == 0){ 

				/*If the statement is false, 
				I calculate things with the credence given to it's conjugate.*/

				temp = (( (float) TablePreds->table[i].credence)/ ( (float) 100) )  - 0;
				temp = temp*temp;
			}

			//fprintf(stdout, "\nCredence=%d", TablePreds->table[i].credence);
			// fprintf(stdout, "\nState = %d", TablePreds->table[i].state);
			// fprintf(stdout,"\nPurelog = %.6f\n", log(temp));

			score = score + temp;

		}

	}
	
	TablePreds->brier_score = (float) score / (float) TablePreds->num;
	

}

