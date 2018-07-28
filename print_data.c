#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "datatypes.h"

void print_percentage(row_percentage R){

	int i;
	int percentage;
	
	percentage = floor(R.proportion_of_true );
	// Note: when we compile, we gotta add -lm: link to math, 'cause we're using the floor() function

	fprintf(stdout,"\n\t%d: ", R.percentage_represented);
	for(i=0; i<percentage; i++){
		fprintf(stdout,"|");
	}
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

}
