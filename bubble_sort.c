#include "postgres.h"
#include "fmgr.h"
#include "catalog/pg_type.h"
#include "utils/array.h"
#include "utils/lsyscache.h"


PG_MODULE_MAGIC;

Datum bubble_sort(PG_FUNCTION_ARGS);
static void swap(Datum *a, Datum *b);
static void bubblesort(Datum *array, int size);


PG_FUNCTION_INFO_V1(bubble_sort);

/*
* Sort array using bubble sorting algorithm
*/
Datum
bubble_sort(PG_FUNCTION_ARGS)
{
    ArrayType  *input_array = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *output_array;
    Datum      *input_elems;
    Oid         input_elmtype;
    int16       input_elmlen;
    bool        input_elmbyval;
    char        input_elmalign;
    int         nelems;

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

    // extract the array contents
    deconstruct_array(input_array,
                      input_elmtype,
                      input_elmlen,
                      input_elmbyval,
                      input_elmalign,
                     &input_elems,
                      (bool) 0,
                     &nelems);

    bubblesort(input_elems, nelems);

    output_array = construct_array(input_elems,
                                   nelems,
                                   input_elmtype,
                                   input_elmlen,
                                   input_elmbyval,
                                   input_elmalign);
    // return sorted array
    PG_RETURN_ARRAYTYPE_P(output_array);
}

static void 
bubblesort(Datum *array, int size)
{
    int i, j;

    for (i = 0;  i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if ( DatumGetInt32(array[j]) > DatumGetInt32(array[j+1]) )
                swap(&array[j], &array[j+1]);
        }
    }
}

static void
swap(Datum *a, Datum *b)
{
    Datum temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
