/* pg_algorithms--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION pg_algorithms" to load this file. \quit

-- Sort input array using bubble sorting algorithm
CREATE FUNCTION bubble_sort(int[])
RETURNS int[]
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT STABLE;

-- Sort input array using quicksort sorting algorithm
CREATE FUNCTION quick_sort(int[])
RETURNS int[]
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT STABLE;