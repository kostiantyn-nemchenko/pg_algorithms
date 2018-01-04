# pg_algorithms: Popular algorithms implementation on PostgreSQL side

`pg_algorithms` is PostgreSQL extension that provides an implementation of the most well-known algorithms. This is a pet project and its main purpose is to learn PostgreSQL hacking, so **do not use** it **in the production environment**.


## Supported algorithms
  * ### Sorting
    - Bubble sort
    - <del>Bucket Sort</del>
    - <del>Counting Sort</del>
    - <del>Heap Sort</del>
    - <del>Insertion Sort</del>
    - <del>Merge Sort</del>
    - QuickSort
    - <del>Radix Sort</del>
    - <del>Selection Sort</del>
    - <del>ShellSort</del>


## Installation and configuration
To install `pg_algorithms`, take the following steps:
```
git clone https://github.com/kostiantyn-nemchenko/pg_algorithms
cd pg_algorithms
make install
```
After that, execute this statement in psql:
```
CREATE EXTENSION pg_algorithms;
```

## Usage examples
```
postgres=# select bubble_sort('{9876, 0, -1, 23786, 124, 7, -17000, 93, 5, 60, 313}'::int[]);
                bubble_sort
--------------------------------------------
 {-17000,-1,0,5,7,60,93,124,313,9876,23786}
(1 row)
```

```
postgres=# select quick_sort('{9876, 0, -1, 23786, 124, 7, -17000, 93, 5, 60, 313}'::int[]);
                 quick_sort
--------------------------------------------
 {-17000,-1,0,5,7,60,93,124,313,9876,23786}
(1 row)

```
