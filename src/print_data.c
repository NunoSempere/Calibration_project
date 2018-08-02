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

	fprintf(stdout,"\n\t%d: ", R.percentage_represented);
	for(i=0; i<percentage; i++){
		fprintf(stdout,"|");
	}
	for(i=i;i<105; i++){
		fprintf(stdout," ");
	}
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

void print_log_score_mod(table_predictions *TablePreds){
	fprintf(stdout,"\n Your logarithmic score,");
	fprintf(stdout,"\n Given as the sum over your predictions over");
	fprintf(stdout,"\n log(P/50)*5/log(2)");
	fprintf(stdout,"\n Where P is the probability initially assigned to the thing which happened");
	fprintf(stdout,"\n Is: %3.6f", TablePreds->score);
}

