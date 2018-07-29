#ifndef _EXTRACT_DATA_H_
#define _EXTRACT_DATA_H_


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "datatypes.h"


prediction *parse_prediction(char *str);
table_predictions * parse_data(char * file_name);


#endif
