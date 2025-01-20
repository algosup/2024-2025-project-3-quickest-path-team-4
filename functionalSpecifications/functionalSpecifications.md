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
   - [2.3 Risks and Mitigations](#23-risks-and-mitigations)
 - [3. Algorithm Goal](#3-algorithm-goal)
 - [4. Product Details](#4-product-details)
   - [4.1 Memory Requirements](#41-memory-requirements)
   - [4.2 Non-Functional Requirements](#42-non-functional-requirements)
   - [4.3 Minimum Viable Product](#43-minimum-viable-product)
   - [4.4 Acceptance Criteria](#44-acceptance-criteria)
   - [4.5 Out of Scope](#45-out-of-scope)
 - [5. REST API Features](#5-rest-api-features)
 - [6. Security ](#6-security-measures)
   - [6.1 Security Measures](#61-security-measures)
   - [6.2 Error Handling](#62-error-handling)
 - [7. Glossary](#7-glossary)
 
</details>

## Document Evolution
<!-- Won't change -->
| Author| Paul NOWAK (Program Manager) |
|---------------|------------|
| Created | 01/06/2025 |
| Last modified | 01/20/2025 |
| Document deadline | 02/07/2025 |

## 1. Overview

### 1.1. Document Purpose

The document's purpose is to provide clear and detailed instructions about the product and its goal for developers, designers, and stakeholders.

Indeed, it must describe how the product will work while declaring its intended behavior and implemented features.

The document works as a contract between the development team and the stakeholders, where the requirements and constraints that must be satisfied will be defined. 

### 1.2. Context
The project imagined by ALGOSUP is to develop a high-performance software solution with an algorithm<sup><a href="#1">[1]</a></sup> that calculates the quickest path between two landmarks<sup><a href="#15">[15]</a></sup> in the United States. 

ALGOSUP wanted to encourage us to work as a team to explore and implement efficient algorithms<sup><a href="#1">[1]</a></sup> tailored to handle large-scale datasets<sup><a href="#5">[5]</a></sup> while also considering real-world constraints like speed and accuracy.

### 1.3. Data Source
To assist us in the testing process of our project, Franck provided us with a file (USA-roads.csv) that contains approximately 24 million nodes in the following format: *Landmark_A_ID, Landmark_B_ID, Time*.

In this file, each line represents a connection between two unspecified landmarks<sup><a href="#15">[15]</a></sup> in the United States with a travel time expressed as an integer in an unspecified but proportional unit of time.

Additionally, the different connections are bidirectional, meaning if a connection exists from A to B, the same applies to B to A.

You can find the file in a .zip format in the README file. <!-- Don't forget to add it in the README -->

## 2. Product Goal

### 2.1. Project Scope
Our product will be developed with the following features:

- An performant and efficient **algorithm**<sup><a href="#1">[1]</a></sup> that receive 2 inputs<sup><a href="#13">[13]</a></sup> (**Source** and **Destination**) and provide 2 outputs<sup><a href="#16">[16]</a></sup> (**travel time** and **an ordered list of the landmarks<sup><a href="#15">[15]</a></sup> in the path**).
- A **REST API** running on an HTTP<sup><a href="#11">[11]</a></sup> server (localhost) called by the HTML<sup><a href="#10">[10]</a></sup> page that will contain our algorithm<sup><a href="#1">[1]</a></sup>. Upon receiving a user's request, the API will deliver response payloads in both JSON and XML<sup><a href="#20">[20]</a></sup> formats.
- A **Data Validation tool**, that will be useful to verify the integrity of the provided .csv file. Its source code with instructions on how to use it has to be in our GitHub<sup><a href="#7">[7]</a></sup> repository. Before using the dataset<sup><a href="#5">[5]</a></sup>, we also need to ensure that the file forms a Directed Acyclic Graph<sup><a href="#8">[8]</a></sup> (DAG<sup><a href="#4">[4]</a></sup>) and doesn't have any loop. Indeed, the graph<sup><a href="#8">[8]</a></sup> must be fully connected, allowing the navigation between any two landmarks<sup><a href="#15">[15]</a></sup>.

### 2.2. Constraints
At first, the product must be implemented in C++<sup><a href="#3">[3]</a></sup> to achieve optimal performance, allowing us the potential to loop fast over large volumes of data.

Then, the API<sup><a href="#2">[2]</a></sup> must be able to handle queries<sup><a href="#17">[17]</a></sup> within 1 second, encouraging us to provide a lot of optimization in our algorithm<sup><a href="#1">[1]</a></sup> and to perform many essential tests. 

Its access doesn't require any Internet connection if we use the laptop where we created the local server. However, the Internet will be needed if the client uses another computer.

The use of heuristics<sup><a href="#9">[9]</a></sup> is also possible to prioritize speed for precision and get approximative results. However, we must return an approximative path with a 10% error margin compared to the actual shortest path value.

Lastly: we shouldn't allow the user to provide the same landmark<sup><a href="#15">[15]</a></sup> as both the **Source** and the **Destination**.

### 2.3. Risks and Mitigations
| Risks | Mitigations | 
| ------| ----------- |
| Frequent lagging issues due to the large size of the dataset<sup><a href="#5">[5]</a></sup>. | Allowing the code to catch an error when the algorithm<sup><a href="#1">[1]</a></sup> takes too much time and stops everything. | 
| Apparition of vulnerabilities, such as attacks or insecure data footage, when creating a REST API<sup><a href="#18">[18]</a></sup>. | Establishment of a plan to anticipate and treat vulnerabilities, and implement radical security measures.| 
| Constant updates that trigger an indirect reduction of the code quality and the algorithm<sup><a href="#1">[1]</a></sup>'s speed and efficiency, potentially stopping any real progress.  | Establishment of a proper development plan to indicate the change, and monitor the algorithm<sup><a href="#1">[1]</a></sup>'s testing and its progress through time.| 
| Lack of advanced knowledge regarding REST APIs<sup><a href="#18">[18]</a></sup> in the team. | Further research about REST APIs<sup><a href="#18">[18]</a></sup> and their relationships with algorithms<sup><a href="#1">[1]</a></sup> would be beneficial. | 

## 3. Algorithm Goal
The algorithm<sup><a href="#1">[1]</a></sup> finds **the shortest path between landmark<sup><a href="#15">[15]</a></sup> A and landmark<sup><a href="#15">[15]</a></sup> B**, making calculations depending on their proximity and the other intermediate nodes that can be found.

At first, it will sort the data provided in the .csv file, before getting the source and destination as the algorithm<sup><a href="#1">[1]</a></sup>'s inputs<sup><a href="#13">[13]</a></sup>, and enter them in the algorithm<sup><a href="#1">[1]</a></sup> that will perform all the required calculations before returning the result.

After the user enters the inputs<sup><a href="#13">[13]</a></sup> and selects "confirm", the algorithm<sup><a href="#1">[1]</a></sup> should quickly and efficiently calculate the path before providing the shortest route, with all the intermediate points we need to pass by, alongside the travel time as its 2 outputs<sup><a href="#16">[16]</a></sup>.

Finally, the results should be returned in **under 1 second**.

## 4. Product Details

### 4.1. Memory Requirements
Understanding the input and output types is crucial when using an adjacency list to represent the graph, as it helps determine the minimal memory required for our product.

First, there are 24 million nodes, each represented by an unsigned integer varying from 0 to 4294967295. Knowing that each edge is bidirectional, the total number of edges would be *24 million lines in the CSV file * 2 = 48 million edges*.

Each edge entry in the adjacency list stores:

- The target node (unsigned integer, 4 bytes).
- Travel time (unsigned integer, 4 bytes).
- A pointer or index for linked list or vector (typically 8 bytes on 64-bit systems).

So, the total memory required to store the adjacency list would be:

\[
\text{Memory for adjacency list} = \text{Edges} \times (\text{Target Node} + \text{Travel Time} + \text{Pointer})
\]

\[
= 48 \, \text{million} \times (4 + 4 + 8) \, \text{bytes} = 768 \, \text{MB}
\]

By accounting for miscellaneous structures such as visited flags, input/output buffers, and REST API[18] handling, we can estimate an additional memory requirement of approximately **50 MB**.

In the end, the minimal memory required would be **768 MB** (adjacency list) + **50 MB** (miscellaneous structures) = **818 MB**.


### 4.2. Non-Functional Requirements
Here are the different criteria for the non-functional requirements:

#### Functionality
The algorithm<sup><a href="#1">[1]</a></sup> must be stable, accurate, space-efficient, and solve the problem correctly.

#### Scalability
The algorithm<sup><a href="#1">[1]</a></sup> must handle large and complex inputs<sup><a href="#13">[13]</a></sup>, including .csv files with up to **24 million nodes** while maintaining performance.

#### Performance
The algorithm<sup><a href="#1">[1]</a></sup> must use a minimal memory of **818 MB** and respond to all queries<sup><a href="#17">[17]</a></sup> **within 1 second** on any kind of computer.

#### Robustness
The algorithm<sup><a href="#1">[1]</a></sup> must handle invalid inputs<sup><a href="#13">[13]</a></sup>, edge cases, and errors reliably. Heuristic solutions must not exceed the shortest path duration by **more than 10%**. <!-- It measures the unexpected loss so yes it's robustness. -->

#### Integrity
The algorithm<sup><a href="#1">[1]</a></sup> must provide a clean API<sup><a href="#2">[2]</a></sup> that supports real-world use and responds with **XML**<sup><a href="#20">[20]</a></sup> and **JSON**<sup><a href="#14">[14]</a></sup> payloads. 

#### Maintainability 
The algorithm<sup><a href="#1">[1]</a></sup> must allow updates and modifications based on user feedback, supporting long-term development.

### 4.3. Minimum Viable Product
The following is a list of the potential different development phases of our product. Each phase is updated based on the algorithm<sup><a href="#1">[1]</a></sup>'s progress depending on the non-functional specification.

|**Phase** |**Targeted Non-Functional Requirements** | **Algorithm Improvements** | **Version** |
|:------- |:--------- | :--------- |:-------------|
|**Phase 1** |Core Functionality & Scalability | Algorithm<sup><a href="#1">[1]</a></sup> providing correct outputs<sup><a href="#16">[16]</a></sup>, using complex structures of large and various sizes.| 0.2 |
|**Phase 2** |Performance| Improved runtime and reduced memory usage using advanced optimization techniques. |0.4 (Alpha) |
|**Phase 3** |Integrity | Implementation of the algorithm<sup><a href="#1">[1]</a></sup> in a clean REST API<sup><a href="#18">[18]</a></sup>. |0.6|
|**Phase 4** |Robustness | Better versability and reliability, capable of providing outputs<sup><a href="#16">[16]</a></sup> in JSON<sup><a href="#14">[14]</a></sup> or XML<sup><a href="#20">[20]</a></sup> format. | 0.8 (Beta) |
|**Phase 5** | Maintainability | Refined algorithm<sup><a href="#1">[1]</a></sup> depending on user feedback and additional insights, with optional enhancements or features. | 1.0 (Final)|

### 4.4. Acceptance Criteria
To determine if this IT project is successful, the product must meet all the following criteria:

- The algorithm<sup><a href="#1">[1]</a></sup> correctly processes and outputs<sup><a href="#16">[16]</a></sup> valid results for inputs<sup><a href="#13">[13]</a></sup> up to 24 million nodes within 1 second.
- The algorithm<sup><a href="#1">[1]</a></sup> handles invalid inputs<sup><a href="#13">[13]</a></sup> (e.g., missing fields, corrupted data) gracefully by returning appropriate error codes and messages in JSON<sup><a href="#14">[14]</a></sup> and XML<sup><a href="#20">[20]</a></sup> formats.
- API<sup><a href="#2">[2]</a></sup> responses meet the specified payload structure for both JSON<sup><a href="#14">[14]</a></sup> and XML<sup><a href="#20">[20]</a></sup> formats.
- The solution achieves at least 90% accuracy for heuristic calculations without exceeding a 10% margin of error.
- The product is successfully deployed in a REST API<sup><a href="#18">[18]</a></sup> that can be called with efficient queries.

### 4.5. Out of Scope

Here is the list of features that we won't work on for this project or that we gave up during development:
- Compatibility with other output<sup><a href="#16">[16]</a></sup> formats.
- Interactive map of the United States as the output<sup><a href="#16">[16]</a></sup>.
- More detailed input<sup><a href="#13">[13]</a></sup> options allow us to specify not only the source and destination landmarks<sup><a href="#15">[15]</a></sup> but also any intermediate landmarks<sup><a href="#15">[15]</a></sup>  that we want the path to pass through..
- User Interface created as a HTML page where the user enter the source and destination landmarks' IDs and press "Confirm" to display the route and the total time travel.

## 5. REST API Features

We will build the code that will create a server hosting the REST API, and that will be able to store all the data contained within the .csv file.

Furthemore, the user will be able to send an HTTP<sup><a href="#11">[11]</a></sup> request to have access to the REST API<sup><a href="#18">[18]</a></sup> server and retrieve the required data for our algorithm<sup><a href="#1">[1]</a></sup>.

Among all the main specific HTTP<sup><a href="#11">[11]</a></sup> requests possible, the API<sup><a href="#2">[2]</a></sup> will allow us to use a **GET** endpoint<sup><a href="#6">[6]</a></sup> to request with the following features:
- **Input**: IDs of the source and destination landmarks<sup><a href="#15">[15]</a></sup>. They must be entered by the user before running the algorithm<sup><a href="#1">[1]</a></sup>.
- **Output**: Travel time and the ordered list of landmarks<sup><a href="#15">[15]</a></sup> in the path. They should be provided quickly and clearly to the client once the calculations are performed.
- **Response Formats**: Support XML<sup><a href="#20">[20]</a></sup> and JSON<sup><a href="#14">[14]</a></sup> for response payloads.

The JSON/XML<sup><a href="#20">[20]</a></sup> file should return both the route required from the source landmark to the destination landmark and the total travel time. 

#### JSON Output structure

```json
{
  "route": {"1", "4", "2", "6"},
  "total_travel_time": "15 Units of Time" 
}
```

#### XML Output structure

```xml
<output>
  <route>
    <landmark>1</landmark>
    <landmark>4</landmark>
    <landmark>2</landmark>
    <landmark>6</landmark>
  </route>
  <totalTravelTime>15 Units of Time</totalTravelTime>
</output>
```

Additionally, all these features must be compatible with C++<sup><a href="#3">[3]</a></sup>, efficient, fast, and robust.


## 6. Security 

### 6.1. Security Measures
To prevent anyone from using the REST API<sup><a href="#18">[18]</a></sup> in any malevolent way, such as leaking personal data or virus implementation, we will employ several security measures.

- Most importantly, we will create our web page in HTTPS<sup><a href="#12">[12]</a></sup> format to communicate with our REST API<sup><a href="#18">[18]</a></sup>, preventing attackers to intercept, manipulate, or steal data transmitted or received by your REST API<sup><a href="#18">[18]</a></sup>.
- We will make sure to keep our libraries up to date. 
- We will use a TLS (Transport Layer Security) to provide data encryption service for our REST API<sup><a href="#18">[18]</a></sup>, and help maintain data integrity and confidentiality by preventing man-in-the-middle attacks.
- We will implement an error handling program to anticipate any input<sup><a href="#13">[13]</a></sup> error and avoid exposing any sensitive information through error messages. 

### 6.2. Error Handling
Here is the following error cases the program will handle:

| **Case** | **Error Handling** |
| ----- | ----------- |
| Entering characters other than numbers in the landmark<sup><a href="#15">[15]</a></sup> inputs<sup><a href="#13">[13]</a></sup>. | It should show the error message: "Please use only integer numbers." |
| Accessing the REST API<sup><a href="#18">[18]</a></sup> with another computer without an Internet connexion. | The browser should display the error message "Error 503, Service Unavailable." |
| The user reloads the page while the algorithm<sup><a href="#1">[1]</a></sup> is running. | The algorithm<sup><a href="#1">[1]</a></sup> halts due to the reload, requiring the user to re-enter the command lines.|
| The user's computer lacks sufficient memory to execute the algorithm<sup><a href="#1">[1]</a></sup> effectively. | The program displays a loading icon with the following message: "Insufficient memory detected. Please free up some memory and try again." |
| In one of the landmarks inputs, the user types an ID integer below 1 or above 24 millions. | The program displays a pop-up message saying: "ID out of range. Please select a number between 0 and 24 000 000." |

## 7. Glossary

| **Terms** | **Definitions** |
| ----- | ----------- |
| <span id="1">**Algorithm**</span> | Finite set of rules or instructions that specify a sequence of computational steps to solve a specific problem efficiently. |
| <span id="2">**API**</span> | Meaning *Application Programming Interface*, a set of functions and procedures allowing the creation of applications that access the features or data of an operating system, application, or other service. |
| <span id="3">**C++**</span> | Compiled language that is popular for creating computer programs and widely used in game development. Developed as an extension of C, it shares almost the same syntax. |
| <span id="4">**DAG**</span> | Meaning *Directed Acyclic Graph*, a type of graph<sup><a href="#8">[8]</a></sup> consisting of vertices and directed edges (arcs), where each edge points from one vertex to another, and no cycles exist. |
| <span id="5">**Dataset**</span> | Collection of data taken from a single source or intended for a single project. |
| <span id="6">**Endpoint**</span> | Specific location within an API<sup><a href="#2">[2]</a></sup> that accepts requests and sends back responses. |
| <span id="7">**Github**</span> | Cloud-based platform that allows its users to create coding projects through a repository and work together to store and share code. Indeed, it allows us to track and manage our changes over time. |
| <span id="8">**Graph**</span> | Diagram that represents a collection of vertices and edges that join pairs of vertices. |
| <span id="9">**Heuristics**</span> | Mental shortcuts or pragmatic approaches are used to solve problems quickly and efficiently when time, resources, or information are limited. These methods do not guarantee an optimal or perfect solution but provide results that are "good enough" to be useful in practical situations. |
| <span id="10">**HTML**</span> | Meaning *Hypertext Markup Language*, text-based format describing how content is structured in a file, and displaying text, images, and other forms of multimedia on a webpage. |
| <span id="11">**HTTP**</span> | Meaning *Hypertext Transfer Protocol*, a set of rules adjusting file transfer (texts, images, sounds...) on the Web, and indirectly used when we connect and open a web browser. |
| <span id="12">**HTTPS**</span> | Meaning *Hyper Text Transfer Protocol Secure*, a secured extension of the HTTP<sup><a href="#11">[11]</a></sup> protocol, allowing the data transferred between the user and the webserver to be encrypted and can't be leaked or modified. |
| <span id="13">**Input**</span> | Refers to the data, signals, or instructions provided to a system (e.g., a computer program, device, or process) to trigger specific operations or produce a result. |
| <span id="13.5">**Integer**</span> | Refers to a whole number (not a fractional one) that can be positive, negative, or zero. |
| <span id="14">**JSON**</span> | Meaning *JavaScript Object Notation*, open standard file and data interchange format that uses human-readable text to store and transmit data objects containing name-value pairs and arrays (or other serializable values). |
| <span id="15">**Landmark**</span> | Something used to mark the boundary of land. |
| <span id="15.5">**Localhost**</span> | Local server environment that can be used to test and run server side scripts on a computer. |
| <span id="16">**Output**</span> | Refers to the result, response, or data generated by a system after processing the input<sup><a href="#13">[13]</a></sup>. |
| <span id="17">**Query**</span> | Request for data that we can access, manipulate, delete, or retrieve from a database. |
| <span id="18">**Rest API**</span> | Meaning *Representational State Transfer (REST) API*, it follows the REST architectural style, defines rules for creating lightweight and flexible web APIs<sup><a href="#2">[2]</a></sup>. A RESTful API<sup><a href="#2">[2]</a></sup> must comply with a client-server architecture, stateless communication, cacheable data, a uniform interface enabling resource manipulation and hypermedia navigation, a layered system design, and optionally, code-on-demand for extended client functionality. |
| <span id="19">**TLS**</span> | Meaning *Transport layer Security*, data encryption system between clients and servers that protect sensitive information like API<sup><a href="#2">[2]</a></sup> keys and access tokens from being intercepted. |
| <span id="20">**XML**</span> | Meaning *Extensible Markup Language*, markup language and file format for storing, transmitting, and reconstructing data. |

<!-- #9 -->
