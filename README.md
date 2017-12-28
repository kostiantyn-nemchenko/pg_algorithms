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
    - <del>QuickSort</del>
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

