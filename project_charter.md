# 2024 - 2025 Project-3-quickest-path Team-4 - Project Charter

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

| Date       | Time   | Milestones                        |
| ---------- | ------ | --------------------------------- |
| 2025/01/06 | 2 P.M. | Project meeting with the team.     |
| 2025/01/17 | 5 P.M. | Functional Specification delivery. |
| 2025/01/24 | 5 P.M. | Technical Specification delivery.  |
| 2025/01/31 | 5 P.M. | Test Plan delivery.                |
| 2025/02/07 | 5 P.M. | Final product codebase delivery.   |
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

| Type                                                                | Description                                                                                                                | Likelihood | Impact                  | Mitigation                                                     |
| ------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | ---------- | ----------------------- | -------------------------------------------------------------- |
| Wrong interpretation of the requirements.                            | We might forget a key point in our solution or misinterpret a requirement.                                                  | Medium     | High                    | Regular communications about what's being done with the client. |
| Runtime issues on different machines than the ones used for testing. | We might test on computers that are too performant, thus overestimating the level of optimisation our algorithm has.         | Low        | Very High               | Testing on very old machines of machines of very poor quality.  |