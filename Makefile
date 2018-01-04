MODULE_big = pg_algorithms
OBJS = bubble_sort.o quick_sort.o $(WIN32RES)

EXTENSION = pg_algorithms
DATA = pg_algorithms--1.0.sql
PGFILEDESC = "pg_algorithms - popular algorithms implementation on PostgreSQL side"

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)