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
 - [3. Algorithm Goal](#3-algorithm-goal)
 - [4. Product Details](#4-product-details)
   - [4.1 Non-Functional Requirements](#41-non-functional-requirements)
   - [4.2 Minimum Viable Product](#42-minimum-viable-product)
   - [4.3 Acceptance Criteria](#43-acceptance-criteria)
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

| Author        | Paul NOWAK (Program Manager) |
|---------------|------------|
| Created       | 01/06/2025 |
| Last modified | 01/16/2025 |
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

## 2 Product Goal

### 2.1. Project Scope
Our product will be developed with the following features:

- An performant and efficient **algorithm**<sup><a href="#1">[1]</a></sup> that receive 2 inputs<sup><a href="#13">[13]</a></sup> (**Source** and **Destination**) and provide 2 outputs<sup><a href="#16">[16]</a></sup> (**travel time** and **an ordered list of the landmarks<sup><a href="#15">[15]</a></sup> in the path**).
- A **HTML page** that will contain a simple interface where the users will provide the inputs<sup><a href="#13">[13]</a></sup>.
- A **REST API** running on an HTTP<sup><a href="#11">[11]</a></sup> server (localhost) called by the HTML<sup><a href="#10">[10]</a></sup> page that will contain our algorithm<sup><a href="#1">[1]</a></sup>.
- A **Data Validation tool**, which will be useful to verify the integrity of the provided .csv file. Its source code with instructions on how to use it has to be in our GitHub<sup><a href="#7">[7]</a></sup> repository.

### 2.2. Constraints
At first, the product must be implemented in C++<sup><a href="#3">[3]</a></sup> to achieve optimal performance, allowing us the potential to loop fast over large volumes of data.

Then, the API<sup><a href="#2">[2]</a></sup> must be able to handle queries<sup><a href="#17">[17]</a></sup> within 1 second on a typical laptop, encouraging us to provide a lot of optimization in our algorithm<sup><a href="#1">[1]</a></sup> and to perform many essential tests.

The staff also advised us to prioritize speed for precision and use heuristics<sup><a href="#9">[9]</a></sup> for getting approximative results. However, we are only allowed to return an approximative path with a 10% error margin compared to the actual shortest path value.

Before using the dataset<sup><a href="#5">[5]</a></sup>, we need to ensure the data integrity by performing the following checks:
- **Graph Validation**: Check that the file forms a Directed Acyclic Graph<sup><a href="#8">[8]</a></sup> (DAG<sup><a href="#4">[4]</a></sup>) and doesn't have any loop.
- **Connectivity Check**: Make sure the graph<sup><a href="#8">[8]</a></sup> is fully connected, allowing the navigation between any two landmarks<sup><a href="#15">[15]</a></sup>.
Lastly: we shouldn't allow the user to provide the same landmark<sup><a href="#15">[15]</a></sup> as both the **Source** and the **Destination**.

### 2.3. Risks and Assumptions
| Risks | Assumptions | 
| ------| ----------- |
| Frequent lagging issues due to the large size of the dataset<sup><a href="#5">[5]</a></sup>. | Allowing the code to catch an error when the algorithm<sup><a href="#1">[1]</a></sup> takes too much time and stops everything. | 
| Apparition of vulnerabilities, such as attacks or insecure data footage, when creating a REST API<sup><a href="#18">[18]</a></sup>. | Establishment of a plan to anticipate and treat vulnerabilities, and implement radical security measures.| 
| Constant updates that trigger an indirect reduction of the code quality and the algorithm<sup><a href="#1">[1]</a></sup>'s speed and efficiency, potentially stopping any real progress.  | Establishment of a proper development plan to indicate the change, and monitor the algorithm<sup><a href="#1">[1]</a></sup>'s testing and its progress through time.| 
| Lack of advanced knowledge regarding REST APIs<sup><a href="#18">[18]</a></sup> in the team. | Further research about REST APIs<sup><a href="#18">[18]</a></sup> and their relationships with algorithms<sup><a href="#1">[1]</a></sup> would be beneficial. | 

## 3. Algorithm Goal
The algorithm<sup><a href="#1">[1]</a></sup> finds the shortest path between landmark<sup><a href="#15">[15]</a></sup> A and landmark<sup><a href="#15">[15]</a></sup> B, making calculations depending on their proximity and the other intermediate nodes that can be found.

At first, it will sort the data provided in the .csv file, before getting the source and destination as the algorithm<sup><a href="#1">[1]</a></sup>'s inputs<sup><a href="#13">[13]</a></sup>, and enter them in the algorithm<sup><a href="#1">[1]</a></sup> that will perform all the required calculations before returning the result.

After the user enters the inputs<sup><a href="#13">[13]</a></sup> and selects "confirm", the algorithm<sup><a href="#1">[1]</a></sup> should quickly and efficiently calculate the path before providing the shortest route, with all the intermediate points we need to pass by, alongside the travel time as its 2 outputs<sup><a href="#16">[16]</a></sup>.

Finally, the results should be returned in under 1 second.

## 4. Product Details

### 4.1. Non-Functional Requirements
Here are the different criteria for the non-functional requirements:

#### Functionality
The algorithm<sup><a href="#1">[1]</a></sup> must be stable, accurate, space-efficient, and solve the problem correctly.

#### Scalability
The algorithm<sup><a href="#1">[1]</a></sup> must handle large and complex inputs<sup><a href="#13">[13]</a></sup>, including .csv files with up to 24 million nodes while maintaining performance.

#### Performance
The algorithm<sup><a href="#1">[1]</a></sup> must use minimal memory and respond to all queries<sup><a href="#17">[17]</a></sup> within 1 second on a typical laptop.

#### Robustness
The algorithm<sup><a href="#1">[1]</a></sup> must handle invalid inputs<sup><a href="#13">[13]</a></sup>, edge cases, and errors reliably. Heuristic solutions must not exceed the shortest path duration by more than 10%.

#### Integrity
The algorithm<sup><a href="#1">[1]</a></sup> must provide a clean API<sup><a href="#2">[2]</a></sup> that supports real-world use and responds with XML<sup><a href="#19">[19]</a></sup> and JSON<sup><a href="#14">[14]</a></sup> payloads. A simpler, less efficient implementation is acceptable for initial support.

#### Maintainability 
The algorithm<sup><a href="#1">[1]</a></sup> must allow updates and modifications based on user feedback, supporting long-term development.

### 4.2. Minimum Viable Product
The following is a list of the potential different development phases of our product. Each phase is updated based on the algorithm<sup><a href="#1">[1]</a></sup>'s progress depending on the non-functional specification.

|**Phase** |**Targeted Non-Functional Requirements** | **Algorithm Improvements** | **Version** |
|:------- |:--------- | :--------- |:-------------|
|**Phase 1** |Core Functionality & Scalability | Algorithm<sup><a href="#1">[1]</a></sup> providing correct outputs<sup><a href="#16">[16]</a></sup>, using complex structures of large and various sizes.| 0.2 |
|**Phase 2** |Performance| Improved runtime and reduced memory usage using advanced optimization techniques. |0.4 (Alpha) |
|**Phase 3** |Integrity | Implementation of the algorithm<sup><a href="#1">[1]</a></sup> in a REST API<sup><a href="#18">[18]</a></sup> with a clean User Interface. |0.6|
|**Phase 4** |Robustness | Better versability and reliability, capable of providing outputs<sup><a href="#16">[16]</a></sup> in JSON<sup><a href="#14">[14]</a></sup> or XML<sup><a href="#19">[19]</a></sup> format. | 0.8 (Beta) |
|**Phase 5** | Maintainability | Refined algorithm<sup><a href="#1">[1]</a></sup> depending on user feedback and additional insights, with optional enhancements or features. | 1.0 (Final)|

### 4.3. Acceptance Criteria
To determine if this IT project is successful, the product must meet all the following criteria:

- The algorithm<sup><a href="#1">[1]</a></sup> correctly processes and outputs<sup><a href="#16">[16]</a></sup> valid results for inputs<sup><a href="#13">[13]</a></sup> up to 24 million nodes within 1 second.
- The algorithm<sup><a href="#1">[1]</a></sup> handles invalid inputs<sup><a href="#13">[13]</a></sup> (e.g., missing fields, corrupted data) gracefully by returning appropriate error codes and messages in JSON<sup><a href="#14">[14]</a></sup> and XML<sup><a href="#19">[19]</a></sup> formats.
- API<sup><a href="#2">[2]</a></sup> responses meet the specified payload structure for both JSON<sup><a href="#14">[14]</a></sup> and XML<sup><a href="#19">[19]</a></sup> formats.
- The solution achieves at least 90% accuracy for heuristic calculations without exceeding a 10% margin of error.
- The product is successfully deployed in a REST API<sup><a href="#18">[18]</a></sup> with a functional interface tested on at least three representative use cases.

### 4.4. Out of Scope

Here is the list of features that we won't work on for this project or that we gave up during development:
- Compatibility with other output<sup><a href="#16">[16]</a></sup> formats.
- Interactive map of the United States as the output<sup><a href="#16">[16]</a></sup>.
- More detailed input<sup><a href="#13">[13]</a></sup> choices by choosing the path from landmark<sup><a href="#15">[15]</a></sup> A to landmark<sup><a href="#15">[15]</a></sup> B.

## 5. Rest API

### 5.1. Type of Web Application
To create the web application, we will build an HTML<sup><a href="#10">[10]</a></sup> page containing the user interface required to receive the inputs<sup><a href="#13">[13]</a></sup> and allow the user to test the algorithm.

Furthemore, the page will also allow the user to send an HTTP<sup><a href="#11">[11]</a></sup> request to have access to the REST API<sup><a href="#18">[18]</a></sup> server and retrieve the required data for our algorithm<sup><a href="#1">[1]</a></sup>.

### 5.2. API Features
Among all the main specific HTTP<sup><a href="#11">[11]</a></sup> requests possible, the API<sup><a href="#2">[2]</a></sup> will allow us to use a **GET** endpoint<sup><a href="#6">[6]</a></sup> to request with the following features:
- **Input**: IDs of the source and destination landmarks<sup><a href="#15">[15]</a></sup>. They must be selected by the user before running the algorithm<sup><a href="#1">[1]</a></sup>.
- **Output**: Travel time and the ordered list of landmarks<sup><a href="#15">[15]</a></sup> in the path. They should be provided quickly and clearly to the client once the calculations are performed.
- **Response Formats**: Support XML<sup><a href="#19">[19]</a></sup> and JSON<sup><a href="#14">[14]</a></sup> for response payloads.

Additionally, all these features must be compatible with C++<sup><a href="#3">[3]</a></sup>, efficient, fast, and robust.

### 5.3. User Interface
The HTML<sup><a href="#10">[10]</a></sup> page should display a simple screen allowing the user to type the 2 required inputs<sup><a href="#13">[13]</a></sup> (**Source** and **Destination**), with text boxes where the user types both places while making sure they aren't the same.

Then, the user clicks on a press button named **CONFIRM** will appear, launching the algorithm<sup><a href="#1">[1]</a></sup>.

Finally, the screen should have enough space to display the 2 outputs<sup><a href="#16">[16]</a></sup>: the **Route** will obviously be represented as an ordered list, and **Travel Time** will simply be a label placed right next to the list.

### 5.4. Prototype
Here is a link to a working prototype for our REST API<sup><a href="#18">[18]</a></sup>:

- (LINK TO REST API)[]

## 6. Security Measures
To prevent anyone from using our REST API<sup><a href="#18">[18]</a></sup> in any malevolent way, such as leaking personal data or virus implementation, our group has decided to employ several security measures.

- Most importantly, we will create our web page in HTTPS<sup><a href="#12">[12]</a></sup> format to communicate with our REST API<sup><a href="#18">[18]</a></sup>.
- We will make sure to keep our libraries up to date. 
- We will implement an error handling program to anticipate any input<sup><a href="#13">[13]</a></sup> error and avoid exposing any sensitive information through error messages.

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
| <span id="14">**JSON**</span> | Meaning *JavaScript Object Notation*, open standard file and data interchange format that uses human-readable text to store and transmit data objects containing name-value pairs and arrays (or other serializable values). |
| <span id="15">**Landmark**</span> | Something used to mark the boundary of land. |
| <span id="16">**Output**</span> | Refers to the result, response, or data generated by a system after processing the input<sup><a href="#13">[13]</a></sup>. |
| <span id="17">**Query**</span> | Request for data that we can access, manipulate, delete, or retrieve from a database. |
| <span id="18">**Rest API**</span> | Meaning *Representational State Transfer API*, follows the REST architectural style, which provides rules for building lightweight, flexible web APIs<sup><a href="#2">[2]</a></sup>. |
| <span id="19">**XML**</span> | Meaning *Extensible Markup Language*, markup language and file format for storing, transmitting, and reconstructing data. |
