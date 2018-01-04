#include "postgres.h"
#include "fmgr.h"
#include "catalog/pg_type.h"
#include "utils/array.h"
#include "utils/lsyscache.h"


Datum quick_sort(PG_FUNCTION_ARGS);
static void quicksort(Datum *array, int first_index, int last_index);


PG_FUNCTION_INFO_V1(quick_sort);

/*
* Sort array using quick sort algorithm
*/
Datum
quick_sort(PG_FUNCTION_ARGS)
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
					(errmsg("array must not contain nulls")));

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
                    (errmsg("unsupported array element type with OID: %u",
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

    // apply quick sort algorithm
    quicksort(input_elems, 0, nelems - 1);

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
quicksort(Datum *array, int first_index, int last_index)
{
    // declaring index variables
    int pivot_index, temp, index1, index2;

    if(first_index < last_index)
    {
        // assigning first element index as pivot element
        pivot_index = first_index;
        index1 = first_index;
        index2 = last_index;

        // sorting in ascending
        while(index1 < index2)
        {
            while(DatumGetInt32(array[index1]) <= DatumGetInt32(array[pivot_index]) && index1 < last_index)
            {
                index1++;
            }
            while(DatumGetInt32(array[index2]) > DatumGetInt32(array[pivot_index]))
            {
                index2--;
            }

            if(index1 < index2)
            {
                // swapping operation
                temp = array[index1];
                array[index1] = array[index2];
                array[index2] = temp;
            }
        }

        // at the end of first iteration, swap pivot element with index2 element
        temp = array[pivot_index];
        array[pivot_index] = array[index2];
        array[index2] = temp;

        // recursive call for quick sort, with partitioning
        quicksort(array, first_index, index2 - 1);
        quicksort(array, index2 + 1, last_index);
    }
}