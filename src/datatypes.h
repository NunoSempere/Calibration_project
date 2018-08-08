#ifndef _DATATYPES_H_
#define _DATATYPES_H_

#include <stdlib.h>
#include <string.h>

/*
	We put the following datatype definitions uphere because we want to access them from other places.
	We could write 10 functions like extract_prediction_statement, but we don't want to.
*/

typedef struct _date{
	int year;
	int month;
	int day;

}date;


typedef struct _prediction {

	char *statement;
	int state; // -1 = Unmodified_state; 0=False; 1=True; 2= Undecided.
	int credence; // From 1 to 99.
	date fecha; // fecha is date in Spanish.
	//char *comments;
} prediction;

/* 
	Q: What is the difference between _prediction and prediction
	A: See: https://stackoverflow.com/questions/1675351/typedef-struct-vs-struct-definitions
	Note that I could have written nothing instead of _prediction.
*/ 

typedef struct _table_predictions {
	int size;
	int num;
	prediction* table;
	float score;
	/* 
	
	My proper scoring rule is going to be defined as the sum of log(p/0.5)*5/log(2), 
	where p is the reported probability.

	The 0.5 could be understood as a shitty prior
	or simply as a (positive) factor -log(0.5)*5/log(2) which allows the score to be positive.	

	*/
	float brier_score;

} table_predictions;

typedef struct _row_percentage {

	int percentage_represented; // note that this can be implied merely by it's position in a table.
	float proportion_of_true; 
	int num_true;
	int num_false;

} row_percentage;

/*
	typedef struct _table_percentages table percentages;
		Note that we don't need this datatype, since we can just
		have a row_percentage table[100], or a row_percentage *table
*/

int initialize_prediction(prediction *P);
table_predictions *new_table_predictions();
int increase_size(table_predictions *TablePreds);
int cut_paste_preds(prediction *Origin, prediction *Destination);
int add_prediction(prediction *P, table_predictions *TablePreds);

#endif
