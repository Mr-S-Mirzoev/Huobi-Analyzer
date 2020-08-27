# Huobi-Analyzer

## Installation

Build and test benchmarks as:

    cd benchmark_tests
    make && ./benchmark && make clean
    
Build and test the programm itself:

    make && ./benchmark && make clean

## Data Structures and their complexity

| Data Structure | Average Search | Average Insertion | Average Deletion | Worst Search | Worst Insertion | Worst Deletion | Max/min element access | Does it suit our goal? |
|----------------|----------------|-------------------|------------------|--------------|-----------------|----------------|------------------------|------------------------|
| Linked List    | O(n)           | O(1)              | O(1)             | O(n)         | O(1)            | O(1)           | O(n)                   | maybe                  |
| Hash table     | O(log n)       | O(log n)          | O(log n)         | O(n)         | O(n)            | O(n)           | O(n)                   | yes                    |
| RB tree        | O(log n)       | O(log n)          | O(log n)         | O(log n)     | O(log n)        | O(log n)       | O(1)                   | yes                    |
| AVL tree       | O(log n)       | O(log n)          | O(log n)         | O(log n)     | O(log n)        | O(log n)       | O(1)                   | maybe                  |

Due to this info about complexity we might think of trees, since they look ideal from the point of average complexity. However, n is close to 20 and log(n) isn't dramatically less when n and it really depends on constants. Time to check them using benchmarking ;)

## Benchmarking

I tested my programm on model which had 7 elements in asks and bids in average on every iteration and 21-23 elements as max.

    -----------------------------------------------------------------------------------------
    Benchmark                                               Time             CPU   Iterations
    -----------------------------------------------------------------------------------------
    BM_Insert_On_Lists/iterations:1000000                3821 ns         3826 ns      1000000
    BM_Insert_On_Maps/iterations:1000000                 3636 ns         3642 ns      1000000
    BM_Insert_On_UnorderedMaps/iterations:1000000        3629 ns         3633 ns      1000000

    BM_FindMax_On_Lists/iterations:1000000               5265 ns         5194 ns      1000000
    BM_FindMax_On_Maps/iterations:1000000                1827 ns         1816 ns      1000000
    BM_FindMax_On_UnorderedMaps/iterations:1000000       5042 ns         5033 ns      1000000

So we see that Unordered Maps (usually based on Hash - Tables) and Maps (ususally implemented as Red and Black Trees) on Insertion, but Unordered Maps are dramatically slower than Maps. Lists failure goes without saying.

## Conclusion

My choice of data structure was quite good, unless AVL trees are better for this task than RB Trees.
