# 2024 - 2025 Project-3 quickest path Team-4 - Management Artifacts

This document aims to centralize all the management artifact links and resources listed below:

- [2024 - 2025 Project-3 quickest path Team-4 - Management Artifacts](#2024---2025-Project-3-quickest-path-Team-4---Management-Artifacts)
  - [Tasks \& Schedules](#tasks--schedule)
  - [RACI Matrix](#raci-matrix)
  - [Risks \& Assumptions](#risks--assumptions)
  - [Key Performance Indicators](#key-performance-indicators)
    - [Definition of our KPIs](#definition-of-our-kpis)
    - [Link to the project's KPIs](#link-to-the-projects-kpis)
      - [Documents](#documents)
      - [Development](#development)
      - [Design](#design)
      - [Mood](#mood)
  - [Weekly Reports](#weekly-reports)
  - [Post Mortem Analysis](#post-mortem-analysis)

## Tasks & Schedules

To view the current status of the tasks our team has identified, follow this link [this link](https://docs.google.com/spreadsheets/d/1CwzIMlFXa4_e0lZcfqYYREnHONU2Ed1wMpm5CHMeARk/edit?usp=sharing).

The tasks and schedule have been written down in Google Sheets, ensuring a good comprehension as it is a modular tool that can implement metrics. Consequently, the client can easily track the challenges and achievements done during the project.

## RACI Matrix

The RACI matrix of this project can be found [here](https://docs.google.com/spreadsheets/d/1vy4L9r8V3n6dAgAR7JzQ41-nfrjRHLCymahQHND4CFs/edit?usp=sharing) considering the [Project Charter](./projectCharter.md)

## Risks & Assumptions

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
| 13  | Over-reliance on third-party libraries.                                          | Could lead to issues if the library has bugs or lacks certain features.                         | Medium   | Low        | Evaluate the libraries thoroughly before use and have backup plans to develop critical features in-house. |

## Key Performance Indicators

### Definition of our KPIs

To enable the team and the client to track our project's milestones and progress. We have defined several quantitatively measurable KPIs.


### Link to the project's KPIs

To take a look at our project's KPIs which will be explained below along with their calculations, follow: [this link](https://docs.google.com/spreadsheets/d/1PbVny66MCrmY9__otZJfC5omaUoG7xctKVIPduSYmQc/edit?usp=sharing).

#### Documents

The following KPIs in this section are:

- **Functional specifications**
- **Technical specifications**
- **Test Plan**
- **User Manual**

The progress of these documents is measured using the following formula:

$$\text{percentage} = (\frac{\text{current number of sections}} {\text{total number of sections}})\times{100}$$

Where:

- **Current_number_of_sections**: The number of completed sections
- **Total_number_of_sections**: The number of predefined sections in the document's outline.

#### Development

This section tracks the following KPIs:

- **Algorithm design/choice**
- **Algorithm optimization**
- **Web Server prepping and hosting**

Given the complexity and time required for development, we include progress on partially completed features. We will calculate the progress using:

$$\text{percentage} = (\frac{({\text{current number of fully coded pages + sum percentages unfinished pages}})} {\text{total designed pages}})\times{100}$$

Where:

- **current_number_of_fully_coded_pages**: The number of fully completed pages.
- **sum_unfinished_pages_advancements**: The cumulative progress of each unfinished page, with progress for each page ranging from 0 to 1.
- **total_designed_pages**: The number of pages defined during project analysis and design.

#### Design

This section covers the design for the web server. Having a user interface for the web server is optional but would make our project more accessible. The KPIs in this section include:

- **Graphical Chart**
- **Designed Web Server**

To calculate the percentage progress of these KPIs, we use this formula:

$$\text{percentage} = (\frac{\text{(current number of graphical chart pages completed + number of pages for the design code)}} {\text{total number of pages to design/write}})\times{100}$$

Where:

- **Current_number_of_graphical_chart_pages_completed**: The number of completed pages in the graphical chart.
- **Number_of_pages_for_the_design_code**: The number of code pages specifically for the web server's design.
- **Total_number_of_pages_to_design**: The total number of pages agreed upon during the project analysis.

#### Mood

We calculate the mood percentage by averaging the weekly grades out of 10. These grades reflect their overall motivation and well-being from a personal perspective, as well as considering the project's milestones and challenges.

By utilizing these formulas, we ensure that our progress tracking is clear and consistent, which provides a realistic view of our project's status to the client. We will round the KPIs to the nearest 5% for better readability and understanding.

## Weekly Reports

You can find the weeklyReports folder by following [this link](weeklyReports ).

You can directly access the reports individually following the below bullet points:

- [Access Report for Week 1](weeklyReports/week1.md)
- [Access Report for Week 2](weeklyReports/week2.md)
- [Access Report for Week 3](weeklyReports/week3.md)
- [Access Report for Week 4](weeklyReports/week4.md)
- [Access Report for Week 5](weeklyReports/week5.md)
- [Access Report for Week 6](weeklyReports/week6.md)

For a centralized collection of copies of all the reports in a single document, please refer to the globalReport File for Weekly Reports:

- [Access globalReport file for all 6 weeks](weeklyReports/globalReport.md)

## Post Mortem Analysis

You can refer to our Post Mortem Analysis to have a retrospective of our project following [this link](postMortem.md)