#ifndef _ANALYZE_DATA_H_
#define _ANALYZE_DATA_H_

#include <stdlib.h>

#include "constants.h"
#include "datatypes.h"
#include "extract_data.h"

row_percentage* create_table_percentages(table_predictions *TablePreds);
float logarithmic_score_mod(table_predictions *TablePreds);

#endif
