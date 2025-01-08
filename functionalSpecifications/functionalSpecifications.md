Functional Specifications

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
| Last modified | 01/06/2025 |
| Document deadline | 01/15/2025 |

## 1. Overview

### 1.1. Document Purpose

Why we make this document

### 1.2. Context

The project context, history behind it, and why we make it

### 1.3. Data Source

Details about the provided Data source to test

## 2 Product Goal

### 2.1. Project Scope

The scope of the project, with the most important features

### 2.2. Constraints

The constraints and limits of ressources and technologies to use

### 2.3. Risks and Assumptions

The list of the potential risks we could encounter and the potential decisions to anticipate.

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
|   **Phase 1**  |   Core Functionality | Very simple algorithm providing correct outputs for small and straight-forward outputs.|  0.1 |
|   **Phase 2**  |   Scalability | Enhanced algorithm which can handle more complex structures of larger and various sizes.  |  0.2 |
|   **Phase 3**  |   Performance | Improved runtime and reduced memory usage using advanced optimization techniques. |  0.4 (Alpha) |
|   **Phase 4**  |   Robustness | Better versability and reliability, ensuring compatibility with different types of input formats. |  0.6 |
|   **Phase 5**  |   Integrity | Packaged algorithm and integration in larger systems with a clean interface for users. |  0.8 (Beta) |
|   **Phase 6**  |   Maintainability | Refined algorithm depending on user feedback and additional insights, with optional enhancements or features. | 1.0 (Final)|

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
| <span id="Data Structure">Data Structure</span> | The . |
| <span id="Heuristics">Heuristics</span> | The . |
| <span id="HTTP">HTTP</span> | The . |
| <span id="Landmark">Landmark</span> | The . |
| <span id="Rest API">Rest API</span> | The . |
| <span id="Space Complexity">Space Complexity</span> | The . 
| <span id="Time Complexity">Time Complexity</span> | The . |