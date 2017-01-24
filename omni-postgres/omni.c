#include "/usr/local/pgsql/include/server/postgres.h"
#include "/usr/local/pgsql/include/server/fmgr.h" 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Comni.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(SIMILAR_TO);

Datum
SIMILAR_TO(PG_FUNCTION_ARGS)
{

	// Selected column for the query
	Datum column_data = PG_GETARG_ARRAYTYPE_P(0);

	// Text to perform the query
	Datum text = PG_GETARG_TEXT_P(1);

	// Distance for the number of neighbors
	Datum distance = PG_GETARG_INT32(2);

	//Loading data from the selected column
	Comni *t = NULL;
	t = omnisequential_new(make_array(column_data));

	//Performing the query with the corresponding text and distance
	Datum result; 
	omni_query( t, VARDATA(text), VARDATA(distance), VARDATA(result));

	//Returning the results from the query
	PG_RETURN_ARRAYTYPE_P(result);
	
}
///////////////////////////////

PG_FUNCTION_INFO_V1(make_array);
Datum
make_array(PG_FUNCTION_ARGS)
{
    ArrayType  *result;
    Oid         element_type = get_fn_expr_argtype(fcinfo->flinfo, 0);
    Datum       element;
    bool        isnull;
    int16       typlen;
    bool        typbyval;
    char        typalign;
    int         ndims;
    int         dims[MAXDIM];
    int         lbs[MAXDIM];

    if (!OidIsValid(element_type))
        elog(ERROR, "could not determine data type of input");

    /* get the provided element, being careful in case it's NULL */
    isnull = PG_ARGISNULL(0);
    if (isnull)
        element = (Datum) 0;
    else
        element = PG_GETARG_DATUM(0);

    /* we have one dimension */
    ndims = 1;
    /* and one element */
    dims[0] = 1;
    /* and lower bound is 1 */
    lbs[0] = 1;

    /* get required info about the element type */
    get_typlenbyvalalign(element_type, &typlen, &typbyval, &typalign);

    /* now build the array */
    result = construct_md_array(&element, &isnull, ndims, dims, lbs,
                                element_type, typlen, typbyval, typalign);

    PG_RETURN_ARRAYTYPE_P(result);
}

///////////////////////////




