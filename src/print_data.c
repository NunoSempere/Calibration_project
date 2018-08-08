#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "datatypes.h"

void print_percentage(row_percentage R){

	int i;
	int percentage;
	
	percentage = floor(R.proportion_of_true);
	// Note: when we compile, we gotta add -lm: link to math, 'cause we're using the floor() function

	fprintf(stdout,"\n\t%d%c: ", R.percentage_represented, (char)' '*(R.percentage_represented<10));
	

	for(i=0; i<100; i++){
		if(i==R.percentage_represented){
			fprintf(stdout,"*");
		}		
		else if(i<percentage){		
			fprintf(stdout,"|");
		}
		else{
			fprintf(stdout," ");
		}
	}
	fprintf(stdout,"   ");

	fprintf(stdout,"\t %d/%d",  R.num_true, R.num_true + R.num_false);	
	fprintf(stdout,"\n");
	//fprintf(stdout,"\n\tnum_true = %d, num_false = %d -> %d %%", R.num_true, R.num_false, percentage);

}

void print_table_percentages(row_percentage* TablePercentages){
	int i;
	for(i=0; i<100; i++){
		if(TablePercentages[i].proportion_of_true != NULL_STATE){
			print_percentage(TablePercentages[i]);
		}

	}
	fprintf(stdout,"\n");

}

void print_scores(table_predictions *TablePreds){
	fprintf(stdout,"\n Your logarithmic score,");
	fprintf(stdout,"\n Given as the sum over your predictions over");
	fprintf(stdout,"\n log(P/50)*5/log(2)");
	fprintf(stdout,"\n Where P is the probability initially assigned to the thing which happened");
	fprintf(stdout,"\n Is: %3.6f", TablePreds->score);

	fprintf(stdout,"\n\n Your Brier score,");
	fprintf(stdout,"\n given as 1/N");
	fprintf(stdout,"\n of the sum over your predictions");
	fprintf(stdout,"\n of (forecasted P - outcome)^2");
	fprintf(stdout,"\n where P is between 0 and 1, and outcome is either 0 or 1,");
	fprintf(stdout,"\n Is: %3.6f\n", TablePreds->brier_score);

}



