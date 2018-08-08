#include <stdlib.h>
#include <stdio.h>


#include "datatypes.h"
#include "constants.h"
#include "extract_data.h"
#include "analyze_data.h"
#include "print_data.h"


char *get_filename_from_user(){

	int i;
	char* filename;
	filename = (char*) calloc(20, sizeof(char));
	char c;

	fprintf(stdout, "Greetings, user!\n");
	fprintf(stdout, "What is the file in which your predictions are saved?\n");
	fprintf(stdout, "[make sure that it's in the same folder as this program]\n");
	fprintf(stdout, "Write it as 'name.txt'");
	fprintf(stdout, "or subfolder/name.txt if it's in a subfolder\n");
	fprintf(stdout, "or press ENTER to assume that it's 'datos/data.txt'\n");

	i=0;
	c=fgetc(stdin);
	while(c!='\n'){
		filename[i]=c;
		c=fgetc(stdin);
		i++;
	}
	filename[i]='\0';
	if(i==0){
		strcpy(filename, "datos/data.txt");
	}
	return filename;
}

row_percentage* ask_if_aggregate(table_predictions *TablePreds){
	char c;	
	fprintf(stdout,"\nDo you want to aggregate your data?");
	fprintf(stdout,"\nThat is, do you want to interpret '60%% to X' as '40%% to not X' s");
	fprintf(stdout,"\n[Y/n]: ");
	do{		
		c=fgetc(stdin);
		
		if(c=='n'){
			return create_table_percentages(TablePreds);
		}
		else if(c=='Y'){
			return create_table_percentages_aggregated(TablePreds);
		}
		else{
			fprintf(stdout,"\nAbandon the error of your ways: write either Y or n: ");
		}
	}while(c!='Y' && c!='n');
	return NULL;
}

int main(){

	int i;
	FILE *f;
	char* filename;

	
	table_predictions *TablePreds;
	row_percentage* TablePercentages;

	filename = get_filename_from_user();
	f=fopen(filename,"r+");

	if(f!=NULL){

		TablePreds=parse_data(f);

		TablePercentages=ask_if_aggregate(TablePreds);

		logarithmic_score_mod(TablePreds);
		brier_score_calc(TablePreds);
		print_scores(TablePreds);


		print_table_percentages(TablePercentages);


	/*	Now we tidy everything up.
		And we make sure
		that when we use valgrind
		there are no leaks left behind

		valgrind --leak-check=full -v ./main 

	*/
		
		free(TablePercentages);

		for(i=0; i<=TablePreds->num; i++){
			free(TablePreds->table[i].statement);
			//free(TablePreds->table[i].comments);
			// At the moment, we are not parsing comments.
		}

		free(TablePreds->table);
		free(TablePreds);
	
	}

	free(filename);

	return 1;
}


