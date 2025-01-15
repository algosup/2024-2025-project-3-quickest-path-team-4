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
 - [3. Algorithm Implementation](#3-algorithm-implementation)
   - [3.1 Algorithm Selection](#31-algorithm-selection)
   - [3.2 Algorithm Expectations](#32-algorithm-expectations)
 - [4. Product Details](#4-product-details)
   - [4.1 Non-Functional Requirements](#41-non-functional-requirements)
   - [4.2 Minimum Viable Product](#42-minimum-viable-product)
   - [4.3 Acceptance Criterias](#43-acceptance-criterias)
   - [4.4 Out of Scope](#44-out-of-scope)
 - [5. Rest API](#5-rest-api)
   - [5.1 Type of Web Application](#51-type-of-web-application)
   - [5.2 API Features](#52-api-features)
   - [5.3 User Interface](#53-user-interface)
   - [5.4 Prototype](#54-prototype)
 - [6. Security Measures](#6-security-measures)
 - [7. Glossary](#7-glossary)
</details>

## Document Evolution

| Author        | Paul NOWAK (Program Manager) |
|---------------|------------|
| Created       | 01/06/2025 |
| Last modified | 01/15/2025 |
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
- A **HTML page** that will contain a simple interface where the users will provide the inputs
- A **REST API** running on an HTTP server (localhost) called by the HTML page that will contain our algorithm, and be able to handle the XML and JSON formats.
- A **Data Validation tool**, which will be useful to verify the integrity of the provided .csv file. Its source code with instructions on how to use it has to be in our Github repository.

### 2.2. Constraints
At first, the product must be implemented in C++ to achieve optimal performance, allowing us the potential to loop fastly over large volumes of data.

Then, the API must be able to handle queries within 1 second on a typical laptop, encouraging us to provide a lot of optimization in our algorithm and to perform many essential testings.

The staff also advised us to prioritize speed for precision and use heuristics for getting approximative results. However, we are only allowed to return an approximative path with a 10% error margin compared the actual shortest path value.

Before using the dataset, we need to ensure the data integrity by performing the folliwng checks:
  - **Graph Validation**: Check that the file forms a Directed Acyclic Graph (DAG) and doesn't contain any loop.
  - **Connectivity Check**: Make sure that the graph is fully connected, allowing the navigation between any two landmarks.

One last thing: we shouldn't allow the user to provide the same place both as the **Source** and the **Destination**.

### 2.3. Risks and Assumptions
| Risks | Assumptions | 
| ------| ----------- |
| Frequent lagging issues due to the very huge size of the dataset. | Allowing the code to catch an error when the algorithm take too much time and stop everything. | 
| Apparition of vulnerabilities, such as attacks or insecure data footage, when creating a REST API. | Establishment of a plan to anticipate and treat vulnerabilities, and implement radical security measures.| 
| Constant update triggering an indirect reduce of the code quality and the algorithm's speed and efficiency, potentially stopping any real progress.  | Establishment of proper development plan to indicate the change, monitor the algorithm's testing and its progress through time.  | 
| Lack of advanced knowledge regarding REST APIs in the team. | Further research about REST APIs and their relationships with algorithms would be benefical. | 

## 3. Algorithm Implementation

### 3.1. Algorithm Selection

Our group has decided to choose the      algorithm to implement it.

The algorithm consist in...


At first, it wil sort the data provided in the .csv file, before getting the source and destination as the algorithm's inputs, and enter them in the algorithm that will perform all the required calculations before returning the result.

### 3.2. Algorithm Expectations

After the user entered the inputs and selected "confirm", the algorithm should take a quick time to calculate the path before providing the shortest route to take, with all the intermediate points we need to pass by, alongside the travel time as its 2 outputs.

Finally, the result should be quickly displayed on screen.


## 4. Product Details

### 4.1. Non-Functional Requirements

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

### 4.2. Minimum Viable Product

The following is a list of the potential different phases of our product in development. Each phase is updated based on the algorithm's progress depending on the non-functional specification.

|   **Phase**  |   **Targeted Non-Functional Requirement** | **Algorithm Improvements** | **Version**  |                     
|   :-------  |   :--------- | :--------- |  :-------------  |
|   **Phase 1**  |   Core Functionality & Scalability | Algorithm providing correct outputs, using complex structures of large and various sizes.|  0.2 |
|   **Phase 2**  |   Performance  | Improved runtime and reduced memory usage using advanced optimization techniques. |  0.4 (Alpha) |
|   **Phase 3**  |   Integrity | Implementation of the algorithm in a REST API with a clean interface for users. |  0.6  |
|   **Phase 4**  |   Robustness | Better versability and reliability, capable of providing outputs in JSON or XML format. |  0.8 (Beta) |
|   **Phase 5**  |   Maintainability | Refined algorithm depending on user feedback and additional insights, with optional enhancements or features. | 1.0 (Final)|

### 4.3. Acceptance Criterias

In order to determine this IT project as successful, the product must meet all the following criterias:

- The algorithm correctly processes and outputs valid results for inputs up to 24 million nodes within 1 second.
- The algorithm handles invalid inputs (e.g., missing fields, corrupted data) gracefully by returning appropriate error codes and messages in JSON and XML formats.
- API responses meet the specified payload structure for both JSON and XML formats.
- The solution achieves at least 90% accuracy for heuristic calculations without exceeding a 10% margin of error.
- The product is successfully deployed in a REST API with a functional interface tested on at least three representative use cases.

### 4.4. Out of Scope

Here are the list of features which we won't work on for this project or which we gave up during development:
  - Compatibility with other output formats other than XML or JSON.
  - Interactive map of the United States showing visually the output.
  - More detailed input choices by choosing the path from a landmark A to a landmark B.

## 5. Rest API

### 5.1. Type of Web Application
For creating the web application, we will create a HTML page that will contain the user interface required to receive the inputs and provide the user.

However, the page will also allow the user to send a HTTP request to have access to the REST API server, and retrieve the required data for our algorithm.

### 5.2. API Features
Our group has decided to use the REST API called **Boost.Beast**, a C++ library that simplifies the creation of HTTP servers. Furthermore, the library is extremely fast and easy to install.

### 5.3. User Interface
The HTML page should display a simple screen allowing the user to type the 2 required inputs (**Source** and **Destination**), with scrollable list where the user choose both places while making sure they aren't the same.

Then, a press button named **CONFIRM** will appear, and clicking it would launch the algorithm

Finally, the screen should have enough place to display the 2 outputs: the **Route** will be obviously represented as an ordered list, and **Travel Time** will simply be a label that will be placed right next to the list.


### 5.4. Prototype
Here is a link for a working prototype for our REST API:

-(LINK TO REST API)[]

## 6. Security Measures

To avoid any individual to use our REST API in any malevolent way, such has leaking personal data or virus implementation, our group have decided to employ several security measures.

- Most importantly, we create our web page in HTTPS format to communicate with our REST API.
- We make sure to keep our libraries up to date, such has Boost.Beast. 
- We implement a error handling program to anticipate any user input error and avoid exposing any sensitive information through error messages.

Thankfully, the Boost.Beast library is already provided with data encryption service, a WAF (Web Application Firewall), and other secure coding libraries to assist the developper.

## 7. Glossary

| Terms | Definitions |
| ----- | ----------- |
| <span id="Algorithm">Algorithm</span> | The . |
| <span id="Big O Notation">Big O Notation</span> | The . |
| <span id="C++">C++</span> | The . |
| <span id="DAG">DAG</span> | The . |
| <span id="Data Structure">Data Structure</span> | The . |
| <span id="Github">Github</span> | The . |
| <span id="Heuristics">Heuristics</span> | The . |
| <span id="HTML">HTML</span> | The . |
| <span id="HTTP">HTTP</span> | The . |
| <span id="HTTPS">HTTPS</span> | The . |
| <span id="Input">input</span> | The . |
| <span id="JSON">JSON</span> | The . |
| <span id="Landmark">Landmark</span> | The . |
| <span id="Low-Level">Low-Level</span> | The . |
| <span id="Output">Output</span> | The . |
| <span id="Query">Query</span> | The . |
| <span id="Rest API">Rest API</span> | The . |
| <span id="Space Complexity">Space Complexity</span> | The . 
| <span id="Time Complexity">Time Complexity</span> | The . |
| <span id="XML">XML</span> | The . |