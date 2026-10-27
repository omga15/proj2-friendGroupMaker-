# Make Friends Analysis

## Data
Fill out the remain parts of the following tables.
|            | CPU EPS |
|------------|---------|
| Instructor | 5671.61 |
| Student    | 518.77  |

|        | Scaling |
|--------|---------|
| I-to-S |10.93    |

Scale the instructor numbers with the I-to-S scaling.
| File           | I People | I Con   | I Add Con  | I Time (ns) | S Con   | S Add Con  | S Time (ns)   |
|----------------|----------|---------|------------|-------------|---------|------------|---------------|
| friends1.csv   | 10       | 19      | 0          | 67,875      |19       | 0          | 5,274,984     |
| friendssm.csv  | 10       | 12      | 1          | 40,500      |12       | 1          | 5,182,431     |
| friendsmed.csv | 1,000    | 3,927   | 4          | 10,358,125  |3,926    | 4          | 8,903,066     |
| friendslg.csv  | 100,000  | 416,102 | 29         | 914,688,875 |416,102  | 29         | 440,408,380   |


## Analysis
Answer the questions below.

### What seems to be the growth rate for your Friend Groups structure in terms of number of people?
The growth rate appears to be linear（O(N)） with respect to the number of people and connections. Comparing ⁠friendsmed.csv⁠-（1k people, ~8.9 ms）， to ⁠friendslg.csv⁠ -(100k people, ~440 ms), a 100x increase in input size resulted in roughly a 50x increase in execution time, which is strictly within a linear scaling bound and much better than quadratic or O(Nlog N) growth.
...

### Does it appear to grow faster or slower than expected?
The growth seems to be slower than expected. While the instructor's time scales almost linearly (at 0.97299), our implementation's time scaled by only 50x for a 100x increase in input size, indicating better efficiency.
...

### If your implementation is deviating, why do you believe your implementation is deviating from what might be expected?
It isn't deviating negatively anymore.There was a significant deviation when we first tried it，The earlier deviation was because our ⁠CMap⁠ used a Binary Search Tree which added O(log N) overhead to lookups. Switching it to a Hash Table fixed the extra growth.
### What do you believe is the dominant structure/algorithm in your implementation?
The two dominant structures are the Hash Table , and the Weighted Quick Union with full path compression. Together they make everything run in near constant amortized time.
