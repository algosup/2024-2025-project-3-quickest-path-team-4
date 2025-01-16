  
# Introduction

This **test plan** provides a concise overview of the strategies, methods, and resources used to verify the functionality, performance, and reliability of the **2024–2025 Project 3: Call for Tender** software solution.

Designed to calculate the quickest path between two landmarks in the United States, the solution combines a **C++** back-end and a **REST API**[^1] with support for **XML and JSON** outputs. Given the stringent requirement to respond within **1 second** for large-scale datasets, ensuring the chosen path is within **10%** of the absolute shortest route.

This plan details how the testing team will validate data integrity, measure algorithmic efficiency, and confirm functional and technical specifications conformance.

# Test objectives

### Validate functional accuracy

- Confirm that the algorithm reliability provides the quickest route *( tolerance of 10% )* between any two U.S. landmarks.

### Ensure performance

- Verify that all valid requests receive a response in under one second, even when handling a dataset[^2] of approximately 24 million nodes.

### Check data integrity

- Validate the integrity of the CSV file (e.g., USA-roads.csv)
- Verifying graph structure, ensuring it's free of loops[^4], and confirming full connectivity[^5] between landmarks.

### Verify REST API compliance

- Confirm that the single GET[^19] endpoint[^20] correctly accepts source/destination IDs.
- Return both XML and JSON formats.
- Handles error conditions gracefully.

### Alignment with specifications 

- Confirm that all tested functionalities map to the requirements outlined in the project's functional and technical specifications.

# Testing scope

## In scope

### Documentation

- Verify that the documentation is accurate, consistent, and maps to the software's features.
### Data

- Input file (USA-roads.csv).
	- Confirm the ability to detect isolated nodes/edges[^6] and verify full connectivity where expected.
- Data reorganisation tool.
	- Ensure the correctness of the JSON outputs and confirm adjacency[^7] is built accurately.
### Algorithm

- Test correctness.
- Evaluate performance under varying loads.
	- Small vs. large datasets.
- Validate time/space complexity[^8] claims.
- #//todo What does this mean?

### REST API

- Get endpoint
	- Validate correct handling of source/destination IDs, return formats (XML[^9] & JSON[^10]), and response codes.
	- Confirm a 1-second response time for typical requests on an average laptop[^11].
- Endpoint compliance
	- Check error/exception handling(e.g., invalid or missing parameters).

### Big O notation

- Verify the documented Big O complexities[^12] match actual performance.
- Confirm that the approach scales with ~24 million nodes within acceptable resource constraints.
- #//todo what is acceptable
- #//todo is this should be here?
### Code

- Static code analysis.
	- Checking for memory leaks[^13], and performance bottlenecks[^14].
- Validate standard compliance and minimal dependencies 
	- Only STL[^18] + required Web server libraries.
	- #//todo what is stl?

### Test suite

- Unit test coverage
    - Unit, integration, and system-level tests for the algorithm and REST API.
    - Regression tests ensure new changes don’t break existing functionality.
- Automation
    - Confirm that tests can be run via a CI/CD[^15] pipeline (e.g., GitHub Actions).

## Out of scope

### Robustness

- While basic performance within 1 second is tested, extreme stress[^3] or reliability testing is **out of scope**

### Security

- Authentification, authorisation, and penetration testing for the API are **not covered** in this test plan.

### UI design

- Any graphical or front-end interface design is **not part** of the testing scope, as the primary interface is the REST API.

# Testing sample

A sample dataset[^16] serves as a small graph with clearly defined edges and travel times. 
- Shortest path accuracy.
	- Easily trace individual routes and confirm whether the algorithm identifies the quickest path within the required 10% approximation threshold.
- Connectivity verification
	- Visualise the entire graph to ensure proper connectivity and spot potential cycles[^17].
- Input/output validation
	- Keep file parsing straightforward and confirm the adjacency list.
	- Confirm it generates the expected output formats (JSON and XML).

## Sample data

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

- Total nodes: 10.
- Edges: 14.
- Travel time: From 2 to 46.

![[TestSample]]

# Data verification

This program analyses the CSV input to confirm that the graph meets the fundamental criteria for valid pathfinding.

## Breadth First Search (BFS)[^21]

- Executes a BFS[^21] from an arbitrary start node.
- Compares the number of visited nodes to the total node count.
- Logs a message if the graph is **fully connected** or reports partial connectivity otherwise.

**Verification goal:** detects disconnected components that could disrupt path calculation.

### Depth First Search (DFS)[^22]

- Performs a DFS[^22] across all connected components, treating the graph as undirected[^23].
- Identifies any cycles[^17] by checking if a visited neighbour is not the current parent node.

**Verification goal:** ensures the data has no cycles[^17].

## Isolated nodes

- Scans the adjacency list to locate nodes with no neighbours.
	- Degree = 0.
- Reports how many isolated nodes exist.

**Verification goal:** identifies stray or unusable nodes that might cause route-finding errors or produce misleading results.

## Isolated edges

- Checks each edge to see if **both endpoints**[^20]  have degree = 1.
- Counts how many edges meet this condition.

**Verification goal:** flags minimal connections where nodes have no other links. These often represent dead-end routes or special cases in large graphs. 

## Expected output

- Fully connected graph.
	- All nodes should appear reachable.
- Cycle detection.
	- A warning if any cycle exists where it shouldn't.
- Isolated node/edges report.
	- A count of disconnected elements.

#//todo link to the program
Refer to the [GitHub repository](https://github.com/YourRepoURL) for the full source code of the data integrity program.

# The algorithm

  

# The REST API

  

# Test cases

  

# Environments and tools

  

## Environment

  

## Tools

  

# Risks and assumptions

  

# Timeline

  

# GitHub issues

  

# Continuous integration CI/CD

GitHub actions 
unit tests

# Urgency plan


# References

testCases.md

# Footnotes

[^1]: REST API: A style of web service that uses HTTP requests to access and manipulate data. Short for _Representational State Transfer Application Programming Interface_.
[^2]: A structured collection of data, such as CSV files or databases, used as input for algorithms or analyses.
[^3]: Sustaining millions of concurrent requests or node failures
[^4]: Indicates a graph with no self-loop edges (where a node connects to itself).
[^5]: Describes a state where every node in a graph can reach every other node, ensuring no isolated subgraphs exist.
[^6]: Nodes with no connections. Edges whose endpoints is the same node.
[^7]: A representation of which nodes (or vertices) are connected to which others in a graph, often stored as a list or matrix.
[^8]: An analysis of how an algorithm’s runtime (time complexity) and memory usage (space complexity) scale with input size.
[^9]: _Extensible Markup Language_: A structured format commonly used for data representation and exchange.
[^10]: _JavaScript Object Notation_: A lightweight data-interchange format that is easy for humans to read and write and easy for machines to parse and generate.
[^11]: Refers to a typical consumer laptop with moderate processing power (e.g., mid-range CPU, 8–16 GB RAM), used as a baseline for performance tests.
[^12]: A notation that describes the worst-case growth rate of an algorithm’s runtime or space usage relative to the size of the input (n).
[^13]: Situations where a program fails to release memory that is no longer needed, leading to steadily increasing memory usage over time.
[^14]: Points in a system (e.g., a code function or hardware component) where performance limits are reached, slowing down the entire process.
[^15]: _Continuous Integration/Continuous Deployment_: A set of practices that automate building, testing, and deploying code, often through tools like GitHub Actions or Jenkins.
[^16]: A small or medium-sized subset of real or synthetic data used to test functionality and correctness before scaling up to larger datasets.
[^17]: In graph theory, a cycle occurs when a path forms a closed loop, returning to the starting node without reusing edges in a directed graph—or revisiting the parent node in an undirected context.
[^18]: Standard template library: A C++ library providing common data structures (e.g., vector, map) and algorithms (e.g., sort, find) widely used for software development.
[^19]: A standard HTTP method (GET) that requests a representation of a specified resource, often used for fetching data from a web server. 
[^20]: A specific route or URL on a server where an API receives or sends data. In REST, typically something like `GET /api/v1/resource`.
[^21]: Breadth First Search: A graph traversal algorithm that explores all neighbours of a node before moving on to the next level of neighbours, useful for finding shortest paths in unweighted graphs or determining connectivity.
[^22]: Depth First Search: A graph traversal algorithm that explores one branch of a graph deeply before backtracking, often used for cycle detection and path exploration.
[^23]: Describes a graph whose edges do not have a direction; travelling from node A to node B is equivalent to travelling from node B to node A.