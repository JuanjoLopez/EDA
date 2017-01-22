#include "/usr/local/pgsql/include/server/postgres.h"
#include "/usr/local/pgsql/include/server/fmgr.h" 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "BKTree.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

/////////////////////77
PG_FUNCTION_INFO_V1(SIMILAR_TO);

Datum 
SIMILAR_TO(PG_FUNCTION_ARGS)
{
	BKTree bk;
	bk.load(make_array(PG_GETARG_DATUM(0)));

	MAP_OUT result;
    bk.query(PG_GETARG_DATUM(1),PG_GETARG_DATUM(2), result);
    
    ArrayType  *resultOut = make_array(result);
 	PG_RETURN_ARRAYTYPE_P(resultOut);   
}
//////////////

////////////////////////////////////
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

    isnull = PG_ARGISNULL(0);
    if (isnull)
        element = (Datum) 0;
    else
        element = PG_GETARG_DATUM(0);

 
    ndims = 1;
    dims[0] = 1;
    lbs[0] = 1;

    get_typlenbyvalalign(element_type, &typlen, &typbyval, &typalign);
    result = construct_md_array(&element, &isnull, ndims, dims, lbs,
                                element_type, typlen, typbyval, typalign);

    PG_RETURN_ARRAYTYPE_P(result);
}

