#include "postgres.h"
#include "fmgr.h"
#include "catalog/pg_type.h"
#include "utils/array.h"
#include "utils/lsyscache.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

Datum bubble_sort(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(bubble_sort);

/*
* Sort array using bubble sorting algorithm
*/
Datum
bubble_sort(PG_FUNCTION_ARGS)
{
    ArrayType  *input_array = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *output_array;
    Datum      *input_elems, *output_elems, temp;
    Oid         input_elmtype, output_elmtype;
    int16       input_elmlen, output_elmlen;
    bool        input_elmbyval, output_elmbyval;
    char        input_elmalign, output_elmalign;
    int         i, j, nelems;

    if (ARR_HASNULL(input_array) && array_contains_nulls(input_array))
			ereport(ERROR,
					(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
					 errmsg("array must not contain nulls")));

    if (ARR_NDIM(input_array) != 1)
        ereport(ERROR,
                (errmsg("one-dimensional array is required")));

    // determine the array element types
    input_elmtype = ARR_ELEMTYPE(input_array);

    get_typlenbyvalalign(input_elmtype,
                        &input_elmlen,
                        &input_elmbyval,
                        &input_elmalign);

    // validate input data type
    switch (input_elmtype)
    {
        case INT2OID:
        case INT4OID:
            break;
        default:
            ereport(ERROR,
                    (errmsg("Unsupported array element type with OID: %u",
                            input_elmtype)));
            break;
    }

    output_elmtype = INT4OID; //TODO: add float data types support

    get_typlenbyvalalign(output_elmtype,
                        &output_elmlen,
                        &output_elmbyval,
                        &output_elmalign);

    // extract the array contents
    deconstruct_array(input_array,
                      input_elmtype,
                      input_elmlen,
                      input_elmbyval,
                      input_elmalign,
                     &input_elems,
                      (bool) 0,
                     &nelems);

    // sort input array using bubble sorting algorithm
    for(i = 0; i < nelems - 1; i++)
    {
        for(j = 0; j < nelems - i - 1; j++)
        {
            if (DatumGetInt32(input_elems[j]) > DatumGetInt32(input_elems[j+1]))
            {
                temp = input_elems[j];
                input_elems[j] = input_elems[j+1];
                input_elems[j+1] = temp;
            }
        }
    }

    // construct result array
    output_elems = (Datum *)palloc(nelems * sizeof(Datum));

    for(i = 0; i < nelems; i++)
    {
        switch (output_elmtype)
        {
            case INT4OID:
                output_elems[i] = Int32GetDatum((int32)input_elems[i]);
                break;
        }

    }

    output_array = construct_array(output_elems,
                                   nelems,
                                   output_elmtype,
                                   output_elmlen,
                                   output_elmbyval,
                                   output_elmalign);
    // return sorted array
    PG_RETURN_ARRAYTYPE_P(output_array);
}