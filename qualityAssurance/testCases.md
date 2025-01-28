- [Data Validation (DV)](#data-validation-dv)
  - [Input validation](#input-validation)
    - [Read a Small CSV File \[DV\_001\]](#read-a-small-csv-file-dv_001)
    - [Read a large CSV file \[DV\_002\]](#read-a-large-csv-file-dv_002)
  - [Graph structure](#graph-structure)
    - [Validate number of nodes \[DV\_003\]](#validate-number-of-nodes-dv_003)
    - [Validate number of edges \[DV\_004\]](#validate-number-of-edges-dv_004)
    - [Self-loops \[DV\_005\]](#self-loops-dv_005)
    - [Complete graph \[DV\_006\]](#complete-graph-dv_006)
    - [Non complete graph \[DV\_007\]](#non-complete-graph-dv_007)
    - [Isolated nodes \[DV\_008\]](#isolated-nodes-dv_008)
    - [All nodes isolated \[DV\_009\]](#all-nodes-isolated-dv_009)
  - [Error handling](#error-handling)
    - [Empty CSV \[DV\_010\]](#empty-csv-dv_010)
    - [Invalid text file \[DV\_011\]](#invalid-text-file-dv_011)
    - [Invalid JSON file \[DV\_012\]](#invalid-json-file-dv_012)
    - [Invalid formatting \[DV\_013\]](#invalid-formatting-dv_013)
    - [Missing fields \[DV\_014\]](#missing-fields-dv_014)
    - [Negative time \[DV\_015\]](#negative-time-dv_015)
    - [Duplicate rows \[DV\_016\]](#duplicate-rows-dv_016)
    - [Wrong data types \[DV\_017\]](#wrong-data-types-dv_017)
- [Algorithm (AL)](#algorithm-al)
    - [Shortest path (small file) \[AV\_018\]](#shortest-path-small-file-av_018)
    - [Shortest path (large file) \[AV\_019\]](#shortest-path-large-file-av_019)
    - [Output consistency \[AV\_020\]](#output-consistency-av_020)
    - [Paths with equal time \[AV\_021\]](#paths-with-equal-time-av_021)
    - [Wrong type input \[AV\_022\]](#wrong-type-input-av_022)
    - [Non-existing node \[AV\_023\]](#non-existing-node-av_023)
    - [Twice the same \[AV\_024\]](#twice-the-same-av_024)
- [REST API (RA)](#rest-api-ra)
    - [Get shortest path \[RA\_026\]](#get-shortest-path-ra_026)
  - [Error handling](#error-handling-1)
    - [GET invalid input \[RA\_027\]](#get-invalid-input-ra_027)
    - [Non-existing input \[RA\_028\]](#non-existing-input-ra_028)
    - [Twice the same \[RA\_029\]](#twice-the-same-ra_029)
  - [Performance](#performance)
    - [Parsing time for large datasets \[RA\_031\]](#parsing-time-for-large-datasets-ra_031)
    - [API response time \[RA\_032\]](#api-response-time-ra_032)
    - [Memory Usage \[RA\_033\]](#memory-usage-ra_033)


# Data Validation (DV)

## Input validation 

### Read a Small CSV File [DV_001]

**Test case ID**: DV_001

**Test case description**: Verify the program can successfully load and parse a small CSV file with 14 rows.

**Preconditions**:

- A CSV file named [`dataTest.csv`](./testFile/dataTest.csv) exists in the working directory.
- The file contains 14 rows formatted as `source ID, destination ID, travel time`, with valid integers.
- Content of `dataTest.csv`:

```
1,2,20
1,3,16
1,4,10
2,5,12
5,8,9
3,5,6
3,10,40
4,7,7
10,8,23
7,6,46
3,9,34
5,6,2
8,9,5
6,9,16
```

**Test steps**:

| Steps | Instructions | Expected behaviour| Working version | Issues |
|-------|--------------|-------------------|-----------------|--------|
| 01    | Place the `dataTest.csv` file in the program's working directory. | File is correctly placed in the directory where the program can access it.|||
| 02    | Run the program with `dataTest.csv` as an argument. | The program successfully loads the file without errors.|||
| 03    | Parse the CSV data. | All rows are parsed correctly: each row contains valid integers for source ID, destination ID, and travel time.|||
| 04    | Log the parsed data. | Logs display all parsed rows, matching the content of the input file.|||
| 05    | Validate parsed row count. | The number of parsed rows matches the total rows in the file (14 rows).|||
| 06    | Validate sampled rows for correctness. | Verify parsed values for rows 1, 3, 5, 7, and 10 match their corresponding input values.|||

**Expected output**:

```
=======================================
Finished reading 14 lines.

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 10
Number of edges read (excluding self-loops): 14
Number of self-loops found: 0

=======================================
Graph is fully connected.

=======================================
Cycle found => Graph is not acyclic.

=======================================
Number of isolated nodes (degree=0): 0

=======================================
Number of edges whose endpoints each have degree=1: 0
```

**Postconditions**:

- The parsed data is available for further processing.
- Logs confirm:
    - All rows were read and parsed correctly.
    - The adjacency list reflects the input file accurately.
    - The program handles errors (if any) gracefully.



### Read a large CSV file [DV_002]

**Test case ID**: DV_002

**Test case description**: Verify the program can successfully load and parse a large CSV file with approximately 28 million rows.

**Preconditions**:

- A CSV file named [`USA-roads.csv`](./testFile/USA-roads.csv) exists in the working directory.
- The file contains ~28 million rows formatted as `source ID, destination ID, travel time`, with valid integers.

**Test steps**:

| Steps | Instructions| Expected behaviour| Working version | Issues |
| ----- | ------------ | ---------------- | --------------- | ------ |
| 01    | Place the `USA-roads.csv` file in the program's working directory. | File is correctly placed in the directory where the program can access it.|||
| 02    | Run the program with `USA-roads.csv` as an argument.| The program successfully loads the file without errors.|||
| 03    | Parse the CSV data.| All rows are parsed correctly: each row contains valid integers for source ID, destination ID, and travel time. |||
| 04    | Log the parsing performance.| Logs display parsing time and memory usage, ensuring acceptable performance metrics.|||
| 05    | Validate parsed row count.| The number of parsed rows matches the total rows in the file (~24 million).|||
| 06    | Validate sampled rows for correctness.| Randomly select and verify 10 rows from the parsed data match their corresponding input values.|||

**Expected output**:

```
=======================================
Finished reading 28854312 lines.

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 23947347
Number of edges read (excluding self-loops): 28854312
Number of self-loops found: 0

=======================================
Graph is fully connected.

=======================================
Cycle found => Graph is not acyclic.

=======================================
Number of isolated nodes (degree=0): 0

=======================================
Number of edges whose endpoints each have degree=1: 0
```

**Postconditions**:

- The parsed data is available for further processing.
- Logs confirm:
    - All rows were read and parsed correctly.
    - The adjacency list reflects the input file accurately.
    - Performance metrics (e.g., parsing time, memory usage) are logged.


## Graph structure

### Validate number of nodes [DV_003]

**Test case ID**: DV_003

**Test case description**: Verify that the program correctly calculates the number of unique nodes in a given graph from a CSV file.

**Preconditions**:

- A CSV file named [`dataTest.csv`](./testFile/dataTest.csv) exists in the working directory.

**Test steps**:

| Steps | Instructions| Expected behaviour| Working version | Issues |
| ----- | ------------ | ---------------- | --------------- | ------ |
| 01    | Place the `dataTest.csv` file in the program's working directory. | File is correctly placed in the directory where the program can access it. |||
| 02    | Run the program with `dataTest.csv` as an argument. | The program successfully loads the file without errors. |||
| 03    | Parse the CSV data.| All rows are parsed correctly: each row contains valid integers for source ID, destination ID, and travel time. |||
| 04    | Compute the number of nodes.| The program calculates the total number of unique nodes in the graph (10). |||
| 05    | Log the number of nodes.| Logs display the total number of distinct nodes as 10. |||

**Additional checks**:

- Ensure duplicate nodes (if present) are counted only once. For example:
  - A duplicate row such as `1,2,5` and `2,1,5` should not inflate the node count.
- If there are nodes that appear only as destination IDs, they should still be included in the count.

**Expected output**:

```
=======================================
Finished reading 14 lines.

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 10
```

**Postconditions**:

- The total number of unique nodes is logged and matches the expected result.
- Logs confirm:
  - All rows were parsed correctly.
  - The adjacency list includes all nodes from both source and destination columns.
- The program handles potential edge cases such as:
  - Nodes appearing only as destination IDs.
  - Duplicate rows or entries.

---

### Validate number of edges [DV_004]

**Test case ID**: DV_004

**Test case description**: Verify that the program correctly calculates the number of unique edges in a given graph from a CSV file.

**Preconditions**:

- A CSV file named [`edgesTest.csv`](./testFile/edgesTest.csv) exists in the working directory.
- The file contains rows formatted as `source ID, destination ID, travel time`.
- Content of `edgesTest.csv`:

```
1,2,20
1,3,16
1,4,10
2,1,20
2,5,12
5,8,9
3,5,6
3,10,40
4,7,7
10,8,23
7,6,46
3,9,34
5,6,2
8,9,5
6,9,16
```

**Test steps**:

| Steps | Instructions| Expected behaviour| Working version | Issues |
| ----- | ------------ | ---------------- | --------------- | ------ |
| 01    | Place the `edgesTest.csv` file in the program's working directory. | File is correctly placed in the directory where the program can access it.                                      |                 |        |
| 02    | Run the program with `edgesTest.csv` as an argument.               | The program successfully loads the file without errors.                                                         |                 |        |
| 03    | Parse the CSV data.                                                | All rows are parsed correctly: each row contains valid integers for source ID, destination ID, and travel time. |                 |        |
| 04    | Compute the number of unique edges.                                | The program calculates the total number of unique edges in the graph (14).                                      |                 |        |
| 05    | Log the number of edges.                                           | Logs display the total number of unique edges as 14.                                                            |                 |        |

**Additional checks**:

- Validate that **bidirectional edges** are treated as undirected. 
    - `1,2,20` and `2,1,20` appear in the file, they count as a single edge.
- Validate that duplicate rows are ignored in edge count calculations.

**Expected output**:

```
=======================================
Finished reading 14 lines.

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 10
Number of edges read (excluding self-loops): 14
Number of self-loops found: 0
```

**Postconditions**:

- The total number of unique edges is logged and matches the expected result.
- Logs confirm:
    - All rows were parsed correctly.
    - The adjacency list reflects the edges accurately.
- The program handles potential edge cases such as:
    - Duplicate rows (treated as a single edge).
    - Bidirectional edges (treated as undirected edges).
    - Self-loops are excluded from the edge count.

---

### Self-loops [DV_005]

**Test case ID**: DV_005

**Test case description**: Verify that the program correctly detects and handles self-loops in a graph, ensuring they are identified and excluded from the edge count.

**Preconditions**:

- A CSV file named [`selfLoopsTest.csv`](./testFile/selfLoopsTest.csv) exists in the working directory.
- The file contains rows formatted as `source ID, destination ID, travel time`.
- Content of `selfLoopsTest.csv`:

```
1,2,20
1,3,16
2,2,12
3,3,15
4,5,8
5,6,9
6,6,14
7,8,10
8,9,11
9,10,7
10,10,20
```

**Test steps**:

| Steps | Instructions                                                           | Expected behaviour                                                                                              | Working version | Issues |
| ----- | ---------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------- | --------------- | ------ |
| 01    | Place the `selfLoopsTest.csv` file in the program's working directory. | File is correctly placed in the directory where the program can access it.                                      |                 |        |
| 02    | Run the program with `selfLoopsTest.csv` as an argument.               | The program successfully loads the file without errors.                                                         |                 |        |
| 03    | Parse the CSV data.                                                    | All rows are parsed correctly: each row contains valid integers for source ID, destination ID, and travel time. |                 |        |
| 04    | Detect self-loops.                                                     | The program identifies **4 self-loops** (`2,2`, `3,3`, `6,6`, and `10,10`) in the graph.                        |                 |        |
| 05    | Exclude self-loops from edge count.                                    | The program excludes the detected self-loops from the total edge count.                                         |                 |        |
| 06    | Log the results.                                                       | Logs display the total number of self-loops, distinct nodes, and valid edges.                                   |                 |        |

**Expected output**:

```
=======================================
Finished reading 11 lines.

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 10
Number of edges read (excluding self-loops): 7
Number of self-loops found: 4
```

**Postconditions**:

- Self-loops are identified and excluded from the edge count.
- Logs confirm:
    - The total number of self-loops.
    - Accurate node and edge counts.
    - Self-loops are logged for review.

---

### Complete graph [DV_006]

**Test case ID**: DV_006

**Test case description**: Validate whether the program correctly identifies if the graph is fully connected, meaning all nodes can be reached from any other node.


**Preconditions**:
 
- A CSV file named [`dataTest.csv`](./testFile/dataTest.csv) exists in the working directory.
- The file contains rows formatted as `source ID, destination ID, travel time`.

In this graph:

- All nodes (1 to 10) are interconnected, forming a single component.
- The graph is **fully connected**.

**Test steps**:

|Step|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `fullyConnected.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `fullyConnected.csv` as an argument.|The program successfully loads the file without errors.|||
|03|Parse the CSV data.|All rows are parsed correctly: each row contains valid integers for source ID, destination ID, and travel time.|||
|04|Perform connectivity analysis.|The program identifies that all nodes are part of a single connected component.|||
|05|Log the results.|Logs confirm that the graph is fully connected, with no isolated nodes or disconnected components.|||


**Expected output**:

```
=======================================
Finished reading 6 lines.

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 10
Number of edges read (excluding self-loops): 14
Number of self-loops found: 0

=======================================
Graph is fully connected.

=======================================
No cycle found => Graph is acyclic.

=======================================
Number of isolated nodes (degree=0): 0
Number of edges whose endpoints each have degree=1: 0
```


**Postconditions**:

- The program confirms the graph is fully connected.
- Logs confirm:
    - All nodes are reachable from any other node.
    - No isolated nodes or disconnected components exist.

---

### Non complete graph [DV_007]

**Test case ID**: DV_007

**Test case description**: Validate whether the program correctly identifies an incomplete graph where some nodes are not reachable from others.

**Preconditions**:

- A CSV file named [`notFullyConnected.csv`](./testFile/notFullyConnected.csv) exists in the working directory.
- The file contains rows formatted as `source ID, destination ID, travel time`.

**Content of `notFullyConnected.csv`**:

```
1,2,10
2,3,15
3,1,20
4,5,8
5,6,12
6,4,7
7,8,9
8,9,11
```

In this graph:

- Nodes {1, 2, 3} form one connected component.
- Nodes {4, 5, 6} form a second connected component.
- Nodes {7, 8, 9} form a third connected component.
- The graph is **not fully connected**.

**Test steps**:

|Step|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `notFullyConnected.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `notFullyConnected.csv` as an argument.|The program successfully loads the file without errors.|||
|03|Parse the CSV data.|All rows are parsed correctly: each row contains valid integers for source ID, destination ID, and travel time.|||
|04|Perform connectivity analysis.|The program identifies that the graph is not fully connected, and lists the number of components.|||
|05|Log the results.|Logs confirm that the graph contains multiple disconnected components.|||

**Expected output**:

```
=======================================
Finished reading 8 lines.

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 9
Number of edges read (excluding self-loops): 8
Number of self-loops found: 0

=======================================
Graph is NOT fully connected: visited only 3 of 9 nodes.

=======================================
No cycle found => Graph is acyclic.

=======================================
Number of isolated nodes (degree=0): 0
Number of edges whose endpoints each have degree=1: 0
```

**Postconditions**:

- The program correctly identifies that the graph is not fully connected.
- Logs confirm:
    - The graph contains three separate connected components.
    - No isolated nodes exist, but groups of disconnected nodes are highlighted.


---

### Isolated nodes [DV_008]

**Test case ID**: DV_008

**Test case description**: Validate the program's ability to detect nodes with no edges in the graph.

**Preconditions**:

- A CSV file named [`isolatedNodes.csv`](./testFile/isolatedNodes.csv) exists in the working directory.
- The file contains nodes connected by edges and nodes with no connections.

**Content of `isolatedNodes.csv`**:

```
1,2,10
2,3,15
4,5,20
6,6,0
7,7,0
```

**Test steps**:

|Step|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `isolatedNodes.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `isolatedNodes.csv` as input.|The program successfully loads the file without crashing.|||
|03|Parse the CSV data.|All rows are parsed correctly, and isolated nodes are detected.|||
|04|Validate isolated nodes in logs.|Logs indicate the presence of isolated nodes (e.g., Nodes 6 and 7).|||

**Expected output**:

```
=======================================
Number of distinct nodes in adjacency: 7
Number of edges read (excluding self-loops): 3
Number of self-loops found: 0

=======================================
Graph is NOT fully connected: visited only 5 of 7 nodes.

=======================================
No cycle found => Graph is acyclic.

=======================================
Number of isolated nodes (degree=0): 2
```

**Postconditions**:

- Isolated nodes are correctly identified and logged.
- The program gracefully handles disconnected nodes.

---

### All nodes isolated [DV_009]

**Test case ID**: DV_009

**Test case description**: Verify the program correctly handles a graph where all nodes are isolated (no edges).

**Preconditions**:

- A CSV file named [`allIsolatedNodes.csv`](./testFile/allIsolatedNodes.csv) exists in the working directory.
- The file contains the following rows:
    
    ```
    1,1,0
    2,2,0
    3,3,0
    4,4,0
    5,5,0
    ```
    

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `allIsolatedNodes.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `allIsolatedNodes.csv` as an argument.|The program successfully loads the file without crashing.|||
|03|Parse the CSV data.|All rows are parsed as self-loops and logged. No valid edges are added to the adjacency list.|||
|04|Validate the graph structure.|The adjacency list includes only nodes with no neighbors.|||
|05|Log the graph analysis results.|Logs confirm the graph has 5 nodes, 0 edges, and no connections between nodes.|||

**Expected output**:

```
=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 5
Number of edges read (excluding self-loops): 0
Number of self-loops found: 5

=======================================
Graph is NOT fully connected: visited only 0 of 5 nodes.

=======================================
No cycle found => Graph is acyclic.

=======================================
Number of isolated nodes (degree=0): 5

=======================================
Number of edges whose endpoints each have degree=1: 0
```

**Postconditions**:

- The graph structure reflects only isolated nodes with no edges.
- Logs confirm no connectivity or cycles in the graph.


## Error handling

### Empty CSV [DV_010]

**Test case ID**: DV_010

**Test case description**: Verify the program handles an empty CSV file without errors.

**Preconditions**:

- An empty CSV file named [`empty.csv`](./testFile/empty.csv) exists in the working directory.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `empty.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `empty.csv` as an argument.|The program successfully loads the file without crashing.|||
|03|Parse the CSV data.|The program detects the file is empty and does not attempt to parse rows.|||
|04|Log the result.|Logs indicate the file is empty and no data was processed.|||

**Expected output**:

```
=======================================
CSV file is empty. No processing will be done.

=======================================
```

**Postconditions**:

- The program gracefully exits after detecting the empty file.
- Logs confirm no data was processed.

---

### Invalid text file [DV_011]

**Test case ID**: DV_011

**Test case description**: Verify the program rejects text files with invalid content and logs appropriate errors.

**Preconditions**:

- A text file named [`textFile.txt`](./testFile/textFile.txt) exists in the working directory.

**Test steps**:

| Steps | Instructions                                                      | Expected behaviour                                                                 | Working version | Issues |
| ----- | ----------------------------------------------------------------- | ---------------------------------------------------------------------------------- | --------------- | ------ |
| 01    | Place the `textFile.txt` file in the program's working directory. | File is correctly placed in the directory where the program can access it.         |                 |        |
| 02    | Run the program with `textFile.txt` as input.                     | The program detects that the file format is invalid and logs an appropriate error. |                 |        |
| 03    | Log the error.                                                    | Logs indicate that the file is not in CSV format and is rejected.                  |                 |        |

**Expected output**:

```
=======================================
Error: Invalid file format. Only CSV files are accepted.
```

**Postconditions**:

- The program does not attempt to process the invalid text file.
- An error is logged specifying the issue with the file format.

---

### Invalid JSON file [DV_012]

**Test case ID**: DV_012

**Test case description**: Verify the program rejects JSON files and logs appropriate errors.

**Preconditions**:

- A JSON file named [`jsonFile.json`](./testFile/jsonFile.json) exists in the working directory.

**Test steps**:

| Steps | Instructions                                                       | Expected behaviour                                                                 | Working version | Issues |
| ----- | ------------------------------------------------------------------ | ---------------------------------------------------------------------------------- | --------------- | ------ |
| 01    | Place the `jsonFile.json` file in the program's working directory. | File is correctly placed in the directory where the program can access it.         |                 |        |
| 02    | Run the program with `jsonFile.json` as input.                     | The program detects that the file format is invalid and logs an appropriate error. |                 |        |
| 03    | Log the error.                                                     | Logs indicate that the file is not in CSV format and is rejected.                  |                 |        |

**Expected output**:

```
=======================================
Error: Invalid file format. Only CSV files are accepted.
```

**Postconditions**:

- The program does not attempt to process the invalid JSON file.
- An error is logged specifying the issue with the file format.

---

### Invalid formatting [DV_013]

**Test case ID**: DV_013

**Test case description**: Verify the program detects and logs rows with invalid formatting.

**Preconditions**:

- A malformed CSV file named [`invalidFormat.csv`](./testFile/invalidFormat.csv) exists in the working directory.
- Example content of `invalidFormat.csv`:

```
1,2,10
3,4
5,6,15,30
7-8-25
9,,10
```

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `invalidFormat.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `invalidFormat.csv` as an argument.|The program successfully loads the file without crashing.|||
|03|Parse the CSV data.|The program identifies and logs rows with invalid formatting.|||
|04|Log the errors.|Logs specify the issues with each invalid row.|||

**Expected output**:

```
=======================================
Error: Malformed row (missing fields) => 3,4
Error: Extra columns detected => 5,6,15,30
Error: Malformed row (missing fields) => 7-8-25
Error: Invalid value in row => 9,,10

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: [node count]
Number of edges read (excluding self-loops): [edge count]
Number of self-loops found: [self-loop count]

=======================================
Graph is [fully/not] connected.

=======================================
[Cycle found/No cycle found] => Graph is [not] acyclic.

=======================================
Number of isolated nodes (degree=0): [isolated node count]

=======================================
Number of edges whose endpoints each have degree=1: [isolated edge count]
```

**Postconditions**:

- Valid rows are parsed and processed.
- Invalid rows are skipped, with errors logged for review.

---
### Missing fields [DV_014]

**Test case ID**: DV_014

**Test case description**: Verify the program detects and handles rows with missing fields.

**Preconditions**:

- A CSV file named [`missingFields.csv`](./testFile/missingFields.csv) exists in the working directory.
- Example content of `missingFields.csv`:

```
1,2,10
3,4,
,6,15
7,,25
,,
```

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `missingFields.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `missingFields.csv` as an argument.|The program successfully loads the file without crashing.|||
|03|Parse the CSV data.|The program skips rows with missing fields and logs errors.|||
|04|Log the errors.|Logs specify the issues with each invalid row.|||

**Expected output**:

```
=======================================
Error: Malformed row (missing fields) => 3,4,
Error: Invalid value in row => ,6,15
Error: Invalid value in row => 7,,25
Error: Malformed row (missing fields) => ,,

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: [node count]
Number of edges read (excluding self-loops): [edge count]
Number of self-loops found: [self-loop count]

=======================================
Graph is [fully/not] connected.

=======================================
[Cycle found/No cycle found] => Graph is [not] acyclic.

=======================================
Number of isolated nodes (degree=0): [isolated node count]

=======================================
Number of edges whose endpoints each have degree=1: [isolated edge count]
```

**Postconditions**:

- Valid rows are parsed and processed.
- Rows with missing fields are logged and skipped.

---

### Negative time [DV_015]

**Test case ID**: DV_015

**Test case description**: Verify the program detects and logs rows with invalid negative travel times.

**Preconditions**:

- A CSV file named [`negativeTime.csv`](./testFile/negativeTime.csv) exists in the working directory.

**Content of `negativeTime.csv`**:

```
1,2,-10
3,4,20
5,6,-30
```

 **Test steps**:

| Steps | Instructions                                                          | Expected behaviour                                                         | Working version | Issues |
| ----- | --------------------------------------------------------------------- | -------------------------------------------------------------------------- | --------------- | ------ |
| 01    | Place the `negativeTime.csv` file in the program's working directory. | File is correctly placed in the directory where the program can access it. |                 |        |
| 02    | Run the program with `negativeTime.csv` as input.                     | The program successfully loads the file without crashing.                  |                 |        |
| 03    | Parse the CSV data.                                                   | The program logs errors for rows with negative travel times.               |                 |        |
| 04    | Log the errors.                                                       | Logs specify rows with negative travel times for review.                   |                 |        |

**Expected output**:

```
=======================================
Error: Invalid negative travel time => 1,2,-10
Error: Invalid negative travel time => 5,6,-30

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 6
Number of edges read (excluding self-loops): 1
Number of self-loops found: 0

=======================================
Graph is NOT fully connected: visited only 2 of 6 nodes.

=======================================
No cycle found => Graph is acyclic.

=======================================
Number of isolated nodes (degree=0): 1
Number of edges whose endpoints each have degree=1: 1
```

**Postconditions**:

- Valid rows are parsed and processed.
- Rows with negative travel times are skipped, and errors are logged.

---

### Duplicate rows [DV_016]

**Test case ID**: DV_016

**Test case description**: Verify the program detects and handles duplicate rows in the CSV file.

**Preconditions**:

- A CSV file named [`duplicateRows.csv`](./testFile/duplicateRows.csv) exists in the working directory.
- Example content of `duplicateRows.csv`:

```
1,2,10
3,4,15
5,6,25
1,2,10
3,4,15
```

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `duplicateRows.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `duplicateRows.csv` as an argument.|The program successfully loads the file without crashing.|||
|03|Parse the CSV data.|The program identifies duplicate rows and logs them.|||
|04|Log the duplicates.|Logs indicate duplicate rows and their locations.|||

**Expected output**:

```
=======================================
Duplicate rows found:
Duplicate row found => "3,4,15" (lines 2 and 5)
Duplicate row found => "1,2,10" (lines 1 and 4)

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 6
Number of edges read (excluding self-loops): 3
Number of self-loops found: 0

=======================================
Graph is NOT fully connected: visited only 2 of 6 nodes.

=======================================
Cycle found => Graph is not acyclic.

=======================================
Number of isolated nodes (degree=0): 0

=======================================
Number of edges whose endpoints each have degree=1: 1
```

**Postconditions**:

- Only unique rows are processed further.
- Duplicate rows are logged for review.

---


### Wrong data types [DV_017]

**Test case ID**: DV_017

**Test case description**: Verify the program detects and logs rows with invalid data types (e.g., non-integer values for source/destination IDs or travel time).

**Preconditions**:

- A CSV file named [`wrongType.csv`](./testFile/wrongType.csv) exists in the working directory.

**Content of `wrongType.csv`**:

```
1,2,10
A,3,20
4,B,30
5,6,abc
```

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `wrongType.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `wrongType.csv` as input.|The program successfully loads the file without crashing.|||
|03|Parse the CSV data.|The program logs errors for invalid data types in rows.|||
|04|Log the errors.|Logs specify rows with invalid data types for review.|||

**Expected output**:

```
=======================================
Error: Invalid value in row => A,3,20
Error: Invalid value in row => 4,B,30
Error: Invalid value in row => 5,6,abc

=======================================
Wrote adjacency to adjaAndNode.json in JSON-like format.

=======================================
Number of distinct nodes in adjacency: 2
Number of edges read (excluding self-loops): 1
Number of self-loops found: 0

=======================================
Graph is NOT fully connected: visited only 2 of 4 nodes.

=======================================
No cycle found => Graph is acyclic.

=======================================
Number of isolated nodes (degree=0): 2
Number of edges whose endpoints each have degree=1: 1
```

**Postconditions**:

- Valid rows are parsed and processed.
- Rows with invalid data types are skipped, and errors are logged.

# Algorithm (AL)

### Shortest path (small file) [AV_018]

**Test case ID**: AV_018

**Test case description**: Verify the program calculates the shortest path correctly for all possible source and destination pairs in a small dataset.

**Preconditions**:

- A CSV file named `dataTest.csv` exists in the working directory.
- Content of `dataTest.csv`:

```
1,2,20
1,3,16
1,4,10
2,5,12
5,8,9
3,5,6
3,10,40
4,7,7
10,8,23
7,6,46
3,9,34
5,6,2
8,9,5
6,9,16
```

**Test steps**:

| Steps | Instructions                                                               | Expected behaviour                                                         | Working version | Issues |
| ----- | -------------------------------------------------------------------------- | -------------------------------------------------------------------------- | --------------- | ------ |
| 01    | Place the `dataTest.csv` file in the program's working directory.          | File is correctly placed in the directory where the program can access it. |                 |        |
| 02    | Run the program with `dataTest.csv` and input source = 1, destination = 4. | The program calculates the shortest path from node 1 to node 4 correctly.  |                 |        |
| 03    | Verify the output.                                                         | The shortest path is `1 -> 2 -> 3 -> 4`, with a total time of 25.          |                 |        |

**Expected output**:

The program calculates the shortest path for all possible pairs, verifying each result matches the table under.

|Source|Destination|Expected Shortest Path|Expected Travel Time|Working version|Issues|
|---|---|---|---|---|---|
|1|2|1 -> 2|20|||
|1|3|1 -> 3|16|||
|1|4|1 -> 4|10|||
|1|5|1 -> 3 -> 5|22|||
|1|8|1 -> 3 -> 5 -> 8|31|||
|1|9|1 -> 3 -> 9|50|||
|1|10|1 -> 3 -> 10|56|||
|1|6|1 -> 3 -> 5 -> 6|24|||
|1|7|1 -> 4 -> 7|17|||
|2|6|2 -> 5 -> 6|14|||
|3|8|3 -> 5 -> 8|20|||
|4|9|4 -> 7 -> 6 -> 9|69|||
|7|10|7 -> 4 -> 1 -> 3 -> 10|73|||

**Postconditions**:

- The program processes all possible source-destination pairs accurately.
- Logs confirm each shortest path and its corresponding travel time.

---

### Shortest path (large file) [AV_019]

**Test case ID**: AV_019

**Test case description**: Verify the program calculates the shortest path correctly for selected source-destination pairs in a large dataset.

**Preconditions**:

- A large CSV file named `USA-roads.csv` exists in the working directory with approximately 28 million rows.
- Example paths to test:

| Source | Destination | Expected Travel Time |
| ------ | ----------- | -------------------- |
| 1      | 2           | 5062                 |
| 100    | 200         | 358307               |
| 300    | 400         | 277607               |
| 500    | 700         | 394325               |
| 1234   | 5678        | 2980378              |
| 7      | 12345678    | 7438024              |
| 9876234| 23359056    | 7502976              |

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `USA-roads.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `USA-roads.csv` as input and test the listed paths.|The program calculates the shortest paths correctly.|||
|03|Verify the output for each path.|Each path matches the expected shortest route and travel time.|||

**Expected output**:

The program calculates the shortest path for the provided source-destination pairs accurately, displaying the path and its travel time.

**Postconditions**:

- The program handles a large dataset correctly, efficiently calculating shortest paths for selected pairs.
- Logs confirm accurate and consistent results.

---

### Output consistency [AV_020]

**Test case ID**: AV_020

**Test case description**: Validate that the algorithm consistently produces the same output for repeated queries.

**Preconditions**:

- A CSV file named `dataTest.csv` exists in the working directory.
- Content of `dataTest.csv`:

```
1,2,20
1,3,16
1,4,10
2,5,12
5,8,9
3,5,6
3,10,40
4,7,7
10,8,23
7,6,46
3,9,34
5,6,2
8,9,5
6,9,16
```

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `dataTest.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `dataTest.csv` and input source = 1, destination = 9.|The program calculates the shortest path correctly.|||
|03|Repeat the same query 5 times.|The program produces the same result for all repeated queries.|||

**Expected output**:

```
=======================================
Shortest path from 1 to 9: 1 -> 3 -> 9
Total travel time: 50
=======================================
```

**Postconditions**:

- The program produces consistent output for repeated queries with the same inputs.
- Logs confirm accuracy and reliability of the results.

---

### Paths with equal time [AV_021]

**Test case ID**: AV_021

**Test case description**: Verify the program handles scenarios with multiple shortest paths having equal travel time.

**Preconditions**:

- A CSV file named `equalPathsGraph.csv` exists in the working directory.
- Content of `equalPathsGraph.csv`:

```
1,2,10
1,3,10
2,4,20
3,4,20
```

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `equalPathsGraph.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with `equalPathsGraph.csv` and input source = 1, destination = 4.|The program identifies multiple shortest paths and returns one.|||
|03|Verify the output.|The program returns a valid shortest path with the correct total time.|||

**Expected output**:

```
=======================================
Shortest path from 1 to 4: 1 -> 2 -> 4
Total travel time: 30
=======================================
```

**Postconditions**:

- The program handles scenarios with equal travel times correctly.
- Logs confirm the handling of multiple shortest paths.

---

### Wrong type input [AV_022]

**Test case ID**: AV_022

**Test case description**: Validate the program detects and handles queries with input types that are not integers (e.g., strings or special characters).

**Preconditions**:

- A CSV file named `dataTest.csv` exists in the working directory.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `dataTest.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with invalid inputs: source = "A", destination = "B".|The program detects invalid input and logs an error message.|||
|03|Run the program with special characters as inputs: source = "@", destination = "#".|The program detects invalid input and logs an error message.|||
|04|Run the program with mixed inputs: source = 1, destination = "B".|The program detects invalid input and logs an error message.|||

**Expected output**:

```
=======================================
Error: Invalid input. Source and destination must be integers.
=======================================
```

**Postconditions**:

- The program validates input types and gracefully handles invalid cases.
- Logs confirm errors were detected and handled appropriately.

---

### Non-existing node [AV_023]

**Test case ID**: AV_023

**Test case description**: Validate the program detects and handles queries for nodes that do not exist in the dataset.

**Preconditions**:

- A CSV file named `dataTest.csv` exists in the working directory.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `dataTest.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with source = 100, destination = 200.|The program detects that neither node exists and logs an error message.|||
|03|Run the program with source = 1, destination = 200.|The program detects that the destination node does not exist and logs an error message.|||
|04|Run the program with source = 100, destination = 2.|The program detects that the source node does not exist and logs an error message.|||

**Expected output**:

```
=======================================
Error: Node 100 does not exist in the dataset.
Error: Node 200 does not exist in the dataset.
=======================================
```

**Postconditions**:

- The program validates node existence for each query and logs errors for non-existing nodes.
- Logs confirm the handling of queries with non-existing nodes.

---

### Twice the same [AV_024]

**Test case ID**: AV_024

**Test case description**: Validate the program detects and handles queries where the source and destination are the same landmark.

**Preconditions**:

- A CSV file named `dataTest.csv` exists in the working directory.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Place the `dataTest.csv` file in the program's working directory.|File is correctly placed in the directory where the program can access it.|||
|02|Run the program with source = 1, destination = 1.|The program detects identical source and destination and logs a message.|||
|03|Run the program with source = 7, destination = 7.|The program detects identical source and destination and logs a message.|||
|04|Run the program with source = 9, destination = 9.|The program detects identical source and destination and logs a message.|||

**Expected output**:

```
=======================================
Error: Source and destination are the same. Please select different landmarks.
=======================================
```

**Postconditions**:

- The program validates that the source and destination are not identical.
- Logs confirm the handling of queries with identical source and destination inputs.

# REST API (RA)


### Get shortest path [RA_026]

**Test case ID**: RA_026

**Test case description**: Validate the REST endpoint for shortest path queries, ensuring the server responds correctly and provides the expected output.

**Preconditions**:

- A REST API server is running and accessible at `http://localhost:8080`.
- A dataset named `dataTest.csv` is loaded into the server.
- Content of `dataTest.csv`:

```
1,2,20
1,3,16
1,4,10
2,5,12
5,8,9
3,5,6
3,10,40
4,7,7
10,8,23
7,6,46
3,9,34
5,6,2
8,9,5
6,9,16
```

**Test steps**:

| Steps | Instructions                                                                | Expected behaviour                                             | Working version | Issues |
| ----- | --------------------------------------------------------------------------- | -------------------------------------------------------------- | --------------- | ------ |
| 01    | Send a GET request to `http://localhost:8080/path?source=1&destination=6`.  | The API returns the shortest path and its cost in JSON format. |                 |        |
| 02    | Send a GET request to `http://localhost:8080/path?source=4&destination=9`.  | The API returns the shortest path and its cost in JSON format. |                 |        |
| 03    | Send a GET request to `http://localhost:8080/path?source=2&destination=10`. | The API returns the shortest path and its cost in JSON format. |                 |        |

**Expected output**:

For `GET /path?source=1&destination=6`:

```json
{
    "path": [1, 3, 5, 6],
    "cost": 24
}
```

For `GET /path?source=4&destination=9`:

```json
{
    "path": [4, 7, 6, 9],
    "cost": 69
}
```

For `GET /path?source=2&destination=10`:

```json
{
    "path": [2, 5, 3, 10],
    "cost": 58
}
```

**Postconditions**:

- The API responds with accurate shortest paths and costs.
- The JSON structure matches the expected format.

## Error handling

### GET invalid input [RA_027]

**Test case ID**: RA_027

**Test case description**: Test the REST API's response to invalid input data.

**Preconditions**:

- A REST API server is running and accessible at `http://localhost:8080`.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Send a GET request with invalid source and destination: `GET /path?source=A&destination=B`.|The API returns an error message indicating invalid input types.|||
|02|Send a GET request with missing source: `GET /path?destination=5`.|The API returns an error message indicating missing parameters.|||
|03|Send a GET request with missing destination: `GET /path?source=1`.|The API returns an error message indicating missing parameters.|||

**Expected output**:

For `GET /path?source=A&destination=B`:

```json
{
    "error": "Invalid input. Source and destination must be integers."
}
```

For `GET /path?destination=5`:

```json
{
    "error": "Missing input. Both source and destination parameters are required."
}
```

For `GET /path?source=1`:

```json
{
    "error": "Missing input. Both source and destination parameters are required."
}
```

**Postconditions**:

- The API validates input parameters and returns appropriate error messages.

---

### Non-existing input [RA_028]

**Test case ID**: RA_028

**Test case description**: Test the REST API's response when querying non-existing nodes.

**Preconditions**:

- A REST API server is running and accessible at `http://localhost:8080`.
- A dataset named `dataTest.csv` is loaded into the server.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Send a GET request for non-existing nodes: `GET /path?source=100&destination=200`.|The API returns an error indicating the nodes do not exist.|||
|02|Send a GET request with one non-existing node: `GET /path?source=1&destination=100`.|The API returns an error indicating the destination node does not exist.|||

**Expected output**:

For `GET /path?source=100&destination=200`:

```json
{
    "error": "Node 100 does not exist in the dataset. Node 200 does not exist in the dataset."
}
```

For `GET /path?source=1&destination=100`:

```json
{
    "error": "Node 100 does not exist in the dataset."
}
```

**Postconditions**:

- The API validates node existence before processing the query.
- Appropriate error messages are logged and returned.

---

### Twice the same [RA_029]

**Test case ID**: RA_029

**Test case description**: Test the REST API's response when the source and destination are the same landmark.

**Preconditions**:

- A REST API server is running and accessible at `http://localhost:8080`.
- A dataset named `dataTest.csv` is loaded into the server.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Send a GET request with identical source and destination: `GET /path?source=1&destination=1`.|The API returns an error indicating that the source and destination are the same.|||
|02|Send a GET request with another identical source and destination: `GET /path?source=7&destination=7`.|The API returns an error indicating that the source and destination are the same.|||

**Expected output**:

For `GET /path?source=1&destination=1`:

```json
{
    "error": "Source and destination are the same. Please provide different landmarks."
}
```

For `GET /path?source=7&destination=7`:

```json
{
    "error": "Source and destination are the same. Please provide different landmarks."
}
```

**Postconditions**:

- The API validates that source and destination are not identical before processing.
- Logs confirm errors were detected and handled appropriately.

## Performance

### Parsing time for large datasets [RA_031]

**Test case ID**: RA_031

**Test case description**: Measure the time taken to parse large datasets during server startup.

**Preconditions**:

- A REST API server is running and accessible at `http://localhost:8080`.
- A large dataset named `USA-roads.csv` is used for the test.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Start the server with the `USA-roads.csv` dataset.|The server successfully loads and parses the dataset within acceptable time limits.|||
|02|Monitor and log parsing time during startup.|Parsing time is logged and remains under 30 seconds.|||

**Postconditions**:

- Parsing time for large datasets is optimized and logged for review.

---

### API response time [RA_032]

**Test case ID**: RA_032

**Test case description**: Measure the response time of the REST API for shortest path queries.

**Preconditions**:

- A REST API server is running and accessible at `http://localhost:8080`.
- A dataset named `dataTest.csv` is loaded into the server.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Send a GET request to `http://localhost:8080/path?source=1&destination=6`.|The API responds within 500 ms.|||
|02|Send a GET request to `http://localhost:8080/path?source=4&destination=9`.|The API responds within 500 ms.|||

**Postconditions**:

- The API response time meets performance benchmarks.

---

### Memory Usage [RA_033]

**Test case ID**: RA_033

**Test case description**: Monitor memory usage during large dataset processing.

**Preconditions**:

- A REST API server is running and accessible at `http://localhost:8080`.
- A large dataset named `USA-roads.csv` is used for the test.

**Test steps**:

|Steps|Instructions|Expected behaviour|Working version|Issues|
|---|---|---|---|---|
|01|Start the server with the `USA-roads.csv` dataset.|Memory usage does not exceed system capacity during dataset processing.|||
|02|Monitor memory usage during parsing and query handling.|Memory usage is logged and remains within acceptable limits.|||

**Postconditions**:

- Memory usage is optimized, and logs confirm resource-efficient operations.