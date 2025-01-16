# Technical Specifications Shortest Path Algorithm

- [Technical Specifications Shortest Path Algorithm](#technical-specifications-shortest-path-algorithm)
  - [Introduction](#introduction)
    - [Project Introduction](#project-introduction)
    - [Document Purpose](#document-purpose)
  - [Development Environment](#development-environment)
    - [Programming Language](#programming-language)
      - [Why C++?](#why-c)
      - [Compiler Recommendations](#compiler-recommendations)
    - [Development Environment Setup](#development-environment-setup)
      - [Resources](#resources)
    - [File Architecture](#file-architecture)
    - [Dependencies](#dependencies)
      - [STL](#stl)
        - [Usage of STL](#usage-of-stl)
      - [REST API](#rest-api)
        - [Boost.Beast](#boostbeast)
          - [Boost.Beast C++ Implementation](#boostbeast-c-implementation)
        - [Localhost](#localhost)
        - [API Flow](#api-flow)
    - [System Architecture](#system-architecture)
  - [Algorithm](#algorithm)
    - [Algorithm Description](#algorithm-description)
    - [Data Source](#data-source)
    - [Data Integrity Verification](#data-integrity-verification)
      - [Functional Specifications](#functional-specifications)
      - [Graph Validation Verification](#graph-validation-verification)
      - [Connectivity Checks](#connectivity-checks)
    - [Data Flow](#data-flow)
    - [Performance](#performance)
      - [Big-O Notation](#big-o-notation)
    - [Data Integrity Verification \& Validation](#data-integrity-verification--validation)

## Introduction

### Project Introduction

The objective of this project is to develop a high-performance software solution designed to calculate the shortest travel path between two specified landmarks within the United States. The software will utilize advanced algorithms to efficiently determine the quickest route, considering various travel times between landmarks. Given the scale of the dataset, which includes approximately 24 million nodes, the solution must be optimized for speed, reliability, and scalability.

The software will be developed in C++ to fully exploit the language's performance capabilities, particularly for large-scale graph processing. It will expose its functionality through a REST API, allowing external users to query the system for the shortest path between two landmarks. The system will support both JSON and XML formats for API responses, ensuring broad compatibility.

### Document Purpose

This document outlines the code guidelines, technologies, algorithms used, and dependencies required for the project. It provides a clear understanding of the system's architecture, performance goals, and data handling, ensuring consistency and quality in development.

It sets standards for coding practices and collaboration between internal developers and external contributors. For the client, it offers insight into the technical specifications and how the solution meets their needs for calculating the shortest path between landmarks.

## Development Environment

### Programming Language

Our team selected C++ as the programming language for this project due to its powerful features and suitability for performance-critical applications.

#### Why C++?

- Performance: Direct memory management and low-level hardware access allow for optimized performance.
- Scalability: Ideal for handling large datasets like the 24 million-node graph in this project.
- Standard Template Library (STL): Provides efficient data structures (e.g., priority queues, maps) critical for shortest path algorithms.
- Portability: Easily deployable across different operating systems with minimal changes.

#### Compiler Recommendations

To ensure compatibility and performance, we recommend the following compilers:

- GCC (GNU Compiler Collection) 9.3 or later
- Clang 10 or later

### Development Environment Setup

To contribute to this project, you need to use an Integrated Development Environment (IDE). If you are unfamiliar with IDEs, we recommend you use Visual Studio Code and install the [C++ extensions pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) to set up your development environment.

#### Resources

For C++'s documentation: [C++ Reference](https://cplusplus.com/reference/)

### File Architecture

```md
2024-2025-project-3-quickest-path-team-4/src
├─── 
│   ├─── 
│   │   └─── 
│   ├─── 
│   │   └───
│   ├─── 
│   │   └─── 
│   └─── 
│       
├─── 
└─── 
```

### Dependencies

#### STL

The C++ Standard Template Library (STL) is a set of template classes and functions that provides the implementation of common data structures and algorithms such as lists, stacks, arrays, sorting, searching, etc. It also provides the iterators and functors which makes it easier to work with algorithms and containers. /
We were asked as a requirement not to use external libraries for the project, we solemnly rely on STL for this project. Our team doesn't have to install any other libraries.

##### Usage of STL

STL offers a wide range of containers, which are the data structures used to store objects and data. For this project, our team mostly uses vectors.

```c++
#include <vector>
```

#### REST API

A REST API (also called a RESTful API or RESTful web API) is an application programming interface (API) that conforms to the design principles of the representational state transfer (REST) architectural style.

REST APIs provide a flexible, lightweight way to integrate applications and connect components in micro-services architectures. Distributed file systems send and receive data via REST.

Rest APIs have to follow 5 principles:

- Uniform interface: All API requests for the same resource should look the same, no matter where the request comes from.
- Client-server decoupling: In REST API design, client and server applications must be completely independent of each other.
- Statelessness: REST APIs are stateless, meaning that each request needs to include all the information necessary for processing it.
- Cacheability: When possible, resources should be cacheable on the client or server side. Server responses also need to contain information about whether caching is allowed for the delivered resource.
- Layered system architecture: In REST APIs, the calls and responses go through different layers. Don’t assume that the client, and server applications connect directly to each other.

For this project, we have to include a single GET endpoint. The endpoint shows where the resource is located. It typically includes a Uniform Resource Identifier (URI). In our case, the URI is located on a local-hosted server.

The sequence diagram below explains how the user, server, and algorithm communicate.
![alt text](./image/technicalSpecifications/sequenceDiagramAPI.png)

##### Boost.Beast

Boost.Beast is a C++ library that provides low-level HTTP and WebSocket functionality. It allows developers to implement REST APIs by handling HTTP requests and responses efficiently.

We decided to use Boost.Beast as it is tailored to our project, is fast and resilient, Boost.Beast is the backbone of our REST API.

###### Boost.Beast C++ Implementation

To implement and set up Boost.Beast in our project:

1. Download the [the latest Boost.Beast version](https://www.boost.org/users/history/).
2. Extract the files into your project's source folder.
3. Navigate to the extracted folder using your terminal.
4. Execute the command: `tar --bzip2 -xf /path/to/boost_1_82_0.tar.bz2`

Boost.Beast is now installed and initialized in your project's directory.

Here's a sample program to open a local-hosted port 8080:

```c++
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

int main() {
    try {
        net::io_context ioc;
        net::ip::tcp::acceptor acceptor(ioc, {net::ip::tcp::v4(), 8080});
        net::ip::tcp::socket socket(ioc);

        std::cout << "Server listening on port 8080...\n";

        acceptor.accept(socket);

        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        std::cout << "Received request: " << req << "\n";

        http::response<http::string_body> res{
            http::status::ok, req.version()};
        res.set(http::field::server, "Boost.Beast");
        res.set(http::field::content_type, "text/plain");
        res.body() = "Hello, world!";
        res.prepare_payload();

        http::write(socket, res);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
```

Execute this program using: `g++ -std=c++17 -Iboost_1_82_0  main.cpp -o beast_example -lpthread` \
You can use this starting point to set up the initial server for the project.

##### Localhost

##### API Flow

### System Architecture

## Algorithm

### Algorithm Description

### Data Source

The client provided the dataset as a `.csv` file containing approximately 24 million nodes. Each row in the file represents a connection between two landmarks and is formatted as follows: \
`Landmark_A_ID,Landmark_B_ID,Time`

Here:

- Landmark_A_ID and Landmark_B_ID are unique identifiers for landmarks.
- Time represents the travel time between the two landmarks in an unspecified unit, time being an unit of time itself.

These connections can be visualized as edges in a graph, where landmarks serve as nodes, and the Time represents the edge weights.

To use this data effectively:

1. We parse the .csv file, separating the elements by the comma delimiter.
2. Each row is then processed to extract the source (Landmark_A_ID), destination (Landmark_B_ID), and weight (Time).
3. Finally, the data is stored in an adjacency matrix, for efficient graph traversal during algorithm execution.

Below is the improved explanation along with pseudocode to parse the data:

```pseudocode
function parseCSV(file_path):
    graph = empty adjacency_matrix[]

    open file at file_path
    for each line in file:
        data = split(line, ",")
        landmark_A = int(data[0])
        landmark_B = int(data[1])
        time = float(data[2])

        if landmark_A not in graph:
            graph[landmark_A] = empty list()
        if landmark_B not in graph:
            graph[landmark_B] = empty list()

        graph[landmark_A].append((landmark_B, time))
        graph[landmark_B].append((landmark_A, time))  # if the graph is undirected

    close file
    return graph
```

### Data Integrity Verification

#### Functional Specifications

#### Graph Validation Verification

#### Connectivity Checks

### Data Flow

How data moves through the system from input to processing and output.

![I/O Diagram](image/technicalSpecifications/ioDiagram.png)

### Performance

#### Big-O Notation

### Data Integrity Verification & Validation
