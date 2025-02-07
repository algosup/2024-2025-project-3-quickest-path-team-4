# 2024 - 2025 Project-3 quickest-path Team-4 - Project Charter

## Project Definition

This project aims to develop a high-performance algorithm solution that calculates the quickest path between two landmarks in the United States.

The client is the director of ALGOSUP, Mr Franck JEANNIN. Our contact point is Franck JEANNIN himself.


## Scope

This project should be done using C++ and expose it's functionality through a REST API running on an HTTP server that is locally hosted. It needs to return a result in less than 1 second.

This implementation will need to use heuristics, therefore lowering the accuracy. The returned path should not exceed the shortest path duration by more than 10%.

## Stakeholders

| Role            | Representative                        | Expectation                                                            |
| --------------- | ------------------------------------- | ----------------------------------------------------------------------                              |
| School director | Franck JEANNIN (ALGOSUP)              | The algorithm in addition to clear documentation and management based on the skills learnt in class. |

## Team Members and Responsibilities

| Name             | Role              | Responsibilities                                                                                                                     | Performance criteria                                                                                                                      |
| ---------------- | ----------------- | ------------------------------------------------------------------------------------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------- |
| Emilien CHINSY  | Project Manager   | Management (time, resources)<br>Workload distribution<br>Risk anticipation and mitigation<br>Report to the client.                  | Project delivered on time<br>Working algorithm delivered<br>Program runs in less than a second. |
| Paul NOWAK | Program Manager   |Functional specification delivery<br>Risk management<br>Communication with the client. | Functional specification,<br>Client approval of the functionalities<br>close collaboration with the Technical Writer as specified in the call for tender.                                                           |
| Thibaud MARLIER   | Technical Leader  | Define coding conventions<br>Technical specification delivery<br>Manages developer tasks.              | Technical specification.                                                                                                                   |
| Ian LAURENT  | Software engineer | Write the code<br>Fix bugs<br>Document the code<br>Create the tests if needed for the code.                                         | All required functionalities implemented<br>Bug-free code.                                                                             |
| Clémentine CUREL     | Quality assurance | Verify documents<br>Test the program<br>Create unit tests and verify the quality of the used dataset <br>Confirm we match the client expectations<br>Test plan delivery.                               | Test Plan<br>Identification of bugs<br>Ensure the documentation is comprehensive and exhaustive.                                                      |
| Laurent BOUQUIN   | Technical Writer  |User Manual, ensure clarity in communication between the developpers and the users.                                                                                                                      | User Manual<br> close collaboration with the Program Manager as specified in the call for tender.                                                                                                                                         |

## Project Plan

This project will be using the agile project method due to the limited timeframe and the small scope of the project. However, we plan to use some aspects of SCRUM management with iterations over an MVP. This incrementation will allow us to always stay within the scope of the project and will avoid most major issues that could occur if we made the whole project at once.

The planning will be made by defining the tasks and objectives the team decided on during the first project day. Each of these will be sorted by importance and distributed accordingly. To manage them, we will use a GitHub project in our repository to centralize all the resources. Additional management tools will be used to track the achievements and bottlenecks during the project and keep the client informed during the whole duration of the project.

After the final presentation which will take place on the 14th of January 2025, we will do a post-mortem analysis to summarize what happened and make a report to the client.

## Milestones

| Date       | Time   | Milestones                         |
| ---------- | ------ | ---------------------------------  |
| 2025/01/06 | 2 P.M. | Project meeting with the team.     |
| 2025/01/17 | 5 P.M. | Functional Specification delivery. |
| 2025/01/24 | 5 P.M. | Technical Specification delivery.  |
| 2025/01/31 | 5 P.M. | Test Plan delivery.                |
| 2025/02/07 | 5 P.M. | Algorithm and server delivery.     |
| 2025/02/07 | 5 P.M. | User Manual delivery.              |
| 2025/02/14 | 9 A.M. | Final Presentation pitch.          |

## Deliverables

The main deliverable is the algorithm.

Additional documents will be given to the client:

- Functional Specification
- Technical Specification
- Test Plan
- User Manual
- Management Planning & Weekly reports

In addition, a presentation of our work will be done to the client as a 15-minute long presentation.

## Allocated Resources

Budget: 0€,

Workforce allocated: 6 team members,

Worktime: 16 half-days of 3h30 each,

Total human hours estimation: 336h.

## Risks

| ID  | Description                                                                      | Consequence                                                                                      | Impact   | Likelihood | Mitigation/Avoidance                                                                                      |
| --- | -------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------ | -------- | ---------- | --------------------------------------------------------------------------------------------------------- |
| 1   | We are not yet used to Rest API.                                                 | Development pace might be hindered                                                              | High     | Medium     | Ask for help to the other team members or Georgios, our teacher                                           |
| 2   | We might have issues with the web hosting server on d-day.                       | We would be unable to present our work and thus be discredited.                                 | Critical | Low        | Make extensive testing and have at least one backup server.                                              |
| 3   | We might create a clone of an already existing solution and infringe a patent.   | We would be in breach of the call for tender.                                                   | High     | Low        | Only use other algorithms as a basis for our own and verify if our solution already exists.              |
| 4   | Team member leaving.                                                             | Tasks left to the remaining members without any assignee.                                       | High     | Unlikely   | Sharing the tasks among the remaining team members.                                                      |
| 5   | Dataset may contain corrupted or incomplete entries.                             | Algorithm might fail or produce incorrect results.                                              | High     | Medium     | Perform data cleaning and validation before running the algorithm.                                       |
| 6   | Unexpected complexity in the dataset structure.                                  | Increased development time and potential roadblocks.                                            | High     | Medium     | Allocate additional time for understanding the dataset and preparing the data accordingly.               |
| 7   | Algorithm performance might not meet the required speed for large datasets.      | Could render the solution impractical for real-world applications.                              | High     | Medium     | Optimize the algorithm and test extensively on subsets of the dataset before scaling up.                 |
| 8   | Incorrect assumptions about the connectivity of nodes in the dataset.            | Algorithm might fail to find a valid path or produce invalid results.                           | Critical | Low        | Verify dataset assumptions early and adjust the algorithm to handle edge cases, such as isolated nodes.  |
| 9   | Lack of clarity in defining "shortest path" criteria (e.g., distance vs. weight).| Discrepancies in expected and actual results from the algorithm.                                | Medium   | Medium     | Clearly define path criteria and ensure team alignment on the algorithm's goal.                          |
| 10  | Miscommunication within the team.                                                | Delayed progress and inconsistencies in implementation.                                         | Medium   | Medium     | Regular team meetings and use collaborative tools for task management and communication.                  |
| 11  | Insufficient testing on realistic edge cases.                                    | Undetected issues might arise during the final demonstration or deployment.                     | High     | Medium     | Develop comprehensive test cases covering all possible scenarios, including edge cases.                  |
| 12  | Misinterpretation of problem requirements.                                       | The solution might fail to meet the expectations or requirements of the project.                | High     | Medium     | Frequently review requirements and get feedback from stakeholders to ensure proper alignment.            |
| 13  | Over-reliance on A.I. libraries.                                          | Could lead to issues if we are unable to understand or explain the code.                         | High   | Low        | Make most of the code ourselves, and if we need to use A.I. make sure we understand the code very well. |