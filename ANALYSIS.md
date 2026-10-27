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
| friends1.csv   | 10       | 19      | 0          | 67,875      |19       | 0          | 38,415        |
| friendssm.csv  | 10       | 12      | 1          | 40,500      |12       | 1          | 26,097        |
| friendsmed.csv | 1,000    | 3,927   | 4          | 10,358,125  |3,926    | 4          | 6,575,664     |
| friendslg.csv  | 100,000  | 416,102 | 29         | 914,688,875 |416,102  | 29         | 1,363,435,495 |


## Analysis
Answer the questions below.

### What seems to be the growth rate for your Friend Groups structure in terms of number of people?
The growth rate from friendsmed to friendslg looks to be about 207x more time with 100x more people. 
basing it in terms of people using a Log-log slope the growth rate is 1.1583. Which is worse than linear (1.0) but better than quadratic(2.0) so it's suggested to be about O(nlog(n)) which is in between of the two.

...

### Does it appear to grow faster or slower than expected?
The grow seems to be faster than expected as the instructor's is about linear at 0.97299.
...

### If your implementation is deviating, why do you believe your implementation is deviating from what might be expected?
It could be deviating then expected because of chosen union Find implementation. 
...

### What do you believe is the dominant structure/algorithm in your implementation?
My union find uses union by size and full path compression, so the operations themselves should be nearly constant time amortized. The extra growth likely comes from outside the union find logic.
...
