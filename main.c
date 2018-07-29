#include <stdlib.h>
#include <stdio.h>


#include "datatypes.h"
#include "constants.h"
#include "extract_data.h"
#include "analyze_data.h"
#include "print_data.h"


int main(){

	int i;

	table_predictions *TablePreds;
	TablePreds=parse_data("datos/data.txt");

	row_percentage* TablePercentages;
	TablePercentages = create_table_percentages(TablePreds);
	logarithmic_score_mod(TablePreds);

	print_log_score_mod(TablePreds);
	print_table_percentages(TablePercentages);


/*	Now we tidy everything up: 
	And we make sure
	that when we use valgrind
	there are no leaks left behind

	valgrind --leak-check=full -v ./main 

*/
	
	free(TablePercentages);

	for(i=0; i<=TablePreds->num; i++){
		free(TablePreds->table[i].statement);
	}

	free(TablePreds->table);
	free(TablePreds);

	return 1;
}

