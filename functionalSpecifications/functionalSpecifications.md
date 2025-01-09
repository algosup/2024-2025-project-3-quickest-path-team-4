# Functional Specifications

## Table of Contents

<details open>
<summary>Table of Contents</summary>

 - [1. Overview](#1-overview)
   - [1.1 Document Purpose](#11-document-purpose)
   - [1.2 Context](#12-context)
   - [1.3 Data Source](#13-data-source)
 - [2. Product Goal](#2-product-goal)
   - [2.1 Project Scope](#21-project-scope)
   - [2.2 Constraints](#22-constraints)
   - [2.3 Risks and Assumptions](#23-risks-and-assumptions)
 - [3. Audience study](#3-audience-study)
   - [3.1 User Personas](#31-user-personas)
   - [3.2 Additional requirements](#32-additional-requirements)
 - [4. Algorithm Implementation](#4-algorithm-implementation)
   - [4.1 Algorithm Selection](#41-algorithm-selection)
   - [4.2 Data Structures Choices](#42-data-structure-choices)
   - [4.3 Time and Space Complexity](#43-time-and-space-complexity)
   - [4.4 Heuristics](#44-heuristics)
 - [5. Product Details](#5-product-details)
   - [5.1 Non-Functional Requirements](#51-non-functional-requirements)
   - [5.2 Minimum Viable Product](#52-minimum-viable-product)
   - [5.3 Acceptance Criterias](#53-acceptance-criterias)
   - [5.4 Out of Scope](#54-out-of-scope)
 - [6. Rest API](#6-rest-api)
   - [6.1 Type of Web Application](#61-type-of-web-application)
   - [6.2 API Features](#62-api-features)
   - [6.3 User Interface](#63-user-interface)
   - [6.4 Implementation](#64-implementation)
   - [6.5 Prototype](#65-prototype)
 - [7. Testing Strategy](#7-testing-strategy)
 - [8. Glossary](#8-glossary)
</details>

## Document Evolution

| Author        | Paul NOWAK (Program Manager) |
|---------------|------------|
| Created       | 01/06/2025 |
| Last modified | 01/09/2025 |
| Document deadline | 01/15/2025 |

## 1. Overview

### 1.1. Document Purpose

The purpose of the document is to provide clear and detailed instructions about the product and its goal for developers, designers and stakeholders.

Indeed, it must describe how the product will work while declaring its intended behavior and its implemented features.

In fact, the document works as a contract between the development team and the stakeholders, where the requirements and constraints that must be satisfied will be defined. 

### 1.2. Context
The project imagined by ALGOSUP is to develop a high performance software solution with an algorithm that calcuates the quickest path between two landmarks in the United States. 

ALGOSUP wanted to encourage us to work as a team to explore and implement efficient algorithms tailored to handle large scale datasets, while also considering real-world constraints like speed and accuracy.

### 1.3. Data Source
To assist us in the testing process of our project, Franck provided us with a file (USA-roads.csv) that contains approximately 24 millions of nodes in the following format: *Landmark_A_ID,Landmark_B_ID,Time*.

In this file, each line represents a connection between two unspecified landmarks in the United States with a travel time expressed as an integer in an unspecified but proportional unit of time.

Additionally, the different connections are bidirectional, meaning if a connection exists from A to B, the same applies for B to A.

## 2 Product Goal

### 2.1. Project Scope

The scope of the project, with the most important features

Our product will be developed with the following features:

- An performant and efficient **algorithm** that receive 2 inputs (**Source** and **Destination**) and provide 2 outputs (**travel time** and **an ordered list of the landmarks in the path**).
- A **REST API** running on an HTTP server (localhost) with a simple interface that will contain our algorithm, and be able to handle the XML and JSON formats.
- A **Data Validation tool**, which will be useful to verify the integrity of the provided .csv file. Its source code with instructions on how to use it has to be in our Github repository.
- AAA
- AAA

### 2.2. Constraints
At first, the product must be implemented in C++ to achieve optimal performance, allowing us the potential to loop fastly over large volumes of data.

Then, the API must be able to handle queries within 1 second on a typical laptop, encouraging us to provide a lot of optimization in our algorithm and to perform many essential testings.

The staff also advised us to prioritize speed for precision and use heuristics for getting approximative results. However, we are only allowed to return an approximative path with a 10% error margin compared the actual shortest path value.

Before using the dataset, we need to ensure the data integrity by performing the folliwng checks:
  - **Graph Validation**: Check that the file forms a Directed Acyclic Graph (DAG) and doesn't contain any loop.
  - **Connectivity Check**: Make sure that the graph is fully connected, allowing the navigation between any two landmarks.

### 2.3. Risks and Assumptions
| Risks | Assumptions | 
| ------| ----------- |
| Frequent lagging issues due to the very huge size of the dataset. | Allowing the code to catch an error when the algorithm take too much time and stop everything. | 
| Apparition of vulnerabilities, such as attacks or insecure data footage, when creating a REST API. | Establishment of a plan to anticipate and treat vulnerabilities, and implement radical security measures.| 
| Constant update triggering an indirect reduce of the code quality and the algorithm's speed and efficiency, stopping any real progress.  | Establishment of proper development plan to indicate the change, monitor the algorithm's testing and its progress through time.  | 
| Lack of advanced knowledge regarding REST APIs in the team. | Further research about REST APIs and their relationships with algorithms would be benefical. | 

## 3. Audience study

### 3.1. User Personas
The user personas who could need our product and their use case

### 3.2. Additional requirements

What kind of new requirements our product would need depending on our audience study .

## 4. Algorithm Implementation

### 4.1. Algorithm Selection

What algorithm we decided to use and why

### 4.2. Data Structures Choices

The data structures we plan to use for our algorithm and why

### 4.3. Time and Space Complexity

Big O notation for the main algorithms.

### 4.4. Heuristics

To prioritize speed over precision, our solution may use 
heuristics, and we define a potential list.

## 5. Product Details

### 5.1. Non-Functional Requirements

Here are the different criteria for the non-functional requirements:


#### Functionality
The algorithm must be simple, space-efficient, and solve the problem correctly.

#### Scalability
The algorithm must handle large and complex inputs, including .csv files with up to 24 million nodes, while maintaining performance.

#### Performance
The algorithm must use minimal memory and respond to all queries within 1 second on a typical laptop.

#### Robustness
The algorithm must handle invalid inputs, edge cases, and errors reliably. Heuristic solutions must not exceed the shortest path duration by more than 10%.

#### Integrity
The algorithm must provide a clean API supporting real-world use and respond with XML and JSON payloads. A simpler, less efficient implementation is acceptable for initial support.

#### Maintainability 
The algorithm must allow updates and modifications based on user feedback, supporting long-term development.

### 5.2. Minimum Viable Product

The following is a list of the potential different phases of our product in development. Each phase is updated based on the algorithm's progress depending on the non-functional specification.

|   **Phase**  |   **Targeted Non-Functional Requirement** | **Algorithm Improvements** | **Version**  |                     
|   :-------  |   :--------- | :--------- |  :-------------  |
|   **Phase 1**  |   Core Functionality & Scalability | Algorithm providing correct outputs, using complex structures of large and various sizes.|  0.2 |
|   **Phase 2**  |   Performance  | Improved runtime and reduced memory usage using advanced optimization techniques. |  0.4 (Alpha) |
|   **Phase 3**  |   Integrity | Implementation of the algorithm in a REST API with a clean interface for users. |  0.6  |
|   **Phase 4**  |   Robustness | Better versability and reliability, capable of providing outputs in JSON or XML format. |  0.8 (Beta) |
|   **Phase 5**  |   Maintainability | Refined algorithm depending on user feedback and additional insights, with optional enhancements or features. | 1.0 (Final)|

### 5.3. Acceptance Criterias

In order to determine this IT project as successful, the product must meet all the following criterias:

### 5.4. Out of Scope

What we won't do.

## 6. Rest API

### 6.1. Type of Web Application

What kind of web application we will us.

### 6.2. API Features

What kind of HTTP server, of inputs, outputs, and of response formats.

### 6.3. User Interface

What our app should look like and how the user would interact with it.

### 6.4. Implementation

What we plan to implement our algorithm within our API.

### 6.5. Prototype

Link to a working prototype of our product.

## 7. Testing Strategy

The strategy listing what kind of tests must be performed for checking our algorithm.

## 8. Glossary

| Terms | Definitions |
| ----- | ----------- |
| <span id="Algorithm">Algorithm</span> | The . |
| <span id="Big O Notation">Big O Notation</span> | The . |
| <span id="C++">C++</span> | The . |
| <span id="DAG">DAG</span> | The . |
| <span id="Data Structure">Data Structure</span> | The . |
| <span id="Github">Github</span> | The . |
| <span id="Heuristics">Heuristics</span> | The . |
| <span id="HTTP">HTTP</span> | The . |
| <span id="Input">input</span> | The . |
| <span id="JSON">JSON</span> | The . |
| <span id="Landmark">Landmark</span> | The . |
| <span id="Output">Output</span> | The . |
| <span id="Query">Query</span> | The . |
| <span id="Rest API">Rest API</span> | The . |
| <span id="Space Complexity">Space Complexity</span> | The . 
| <span id="Time Complexity">Time Complexity</span> | The . |
| <span id="XML">XML</span> | The . |