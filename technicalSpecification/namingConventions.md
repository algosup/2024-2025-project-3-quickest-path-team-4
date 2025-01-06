# Naming Conventions Quickest Path Team 4

<details>
<summary> Table Of Content </summary>

- [Naming Conventions Quickest Path Team 4](#naming-conventions-quickest-path-team-4)
  - [Document Overview](#document-overview)
  - [Naming Conventions](#naming-conventions)
    - [Branches, Folders \& Files](#branches-folders--files)
    - [Code](#code)
      - [Functions and Methods](#functions-and-methods)
      - [Variables](#variables)
      - [Constants](#constants)
      - [Macros](#macros)
      - [Classes and Structures](#classes-and-structures)
      - [Enumerations](#enumerations)
      - [Indentation \& Spacing](#indentation--spacing)
  - [Commit Naming Convention](#commit-naming-convention)
    - [Commit Types](#commit-types)
    - [Format Guidelines](#format-guidelines)
    - [Examples](#examples)
  - [Mistakes to avoid](#mistakes-to-avoid)

</details>

## Document Overview

This document guides individuals who wish to contribute to the project. It outlines the naming conventions for branches, folders, files, functions, variables, and other elements to ensure consistency, readability, and maintainability across the project.

---

## Naming Conventions

### Branches, Folders & Files

- **Branches, folders, and files** should follow camelCase naming conventions. Examples:
  - Branches: `featureImplementation`, `bugFixLoginPage`
  - Folders: `projectResources`, `userInterfaces`
  - Files: `mainAlgorithm.cpp`, `readMe.md`

- Avoid special characters, spaces, and overly long names.
- Use meaningful names that describe the purpose or content.

---

### Code

The code naming conventions are inspired by standard practices in C++ programming, as detailed in [GeeksforGeeks](https://www.geeksforgeeks.org/naming-convention-in-c/).

#### Functions and Methods

- **Naming Convention:** PascalCase (capitalize each word).
- Examples:
  - `CalculateShortestPath()`
  - `InitializeGameSettings()`
  - `ValidateInputData()`

#### Variables

- **Naming Convention:** camelCase (first word lowercase, subsequent words capitalized).
- Examples:
  - `totalDistance`
  - `currentPlayerScore`
  - `isGameOver`

#### Constants

- **Naming Convention:** UPPER_CASE with words separated by underscores.
- Examples:
  - `MAX_NUMBER_OF_NODES`
  - `DEFAULT_PLAYER_LIVES`

#### Macros

- **Naming Convention:** UPPER_CASE with underscores.
- Examples:
  - `#define ARRAY_SIZE 100`
  - `#define PI 3.14159`

#### Classes and Structures

- **Naming Convention:** PascalCase.
- Examples:
  - `GameController`
  - `NodeAttributes`

#### Enumerations

- **Naming Convention:** PascalCase for enum names and UPPER_CASE for values.
- Examples:

  ```c
  enum Color {
      RED,
      BLUE,
      GREEN
  };

#### Comments

- Use inline comments (//) for single-line explanations and block comments (/**/) for multi-line descriptions.
  - Example:
    - `// Calculate the shortest path using Dijkstra's algorithm`

- Ensure all functions and complex code segments are well-documented with comments explaining their purpose.
  - Example:

```c++
/*
 * This function initializes path settings, including:
 * - Distance
 * - Time
 */
void InitializePathSettings() { ... }
```

#### Indentation & Spacing

- Use 4 spaces for indentation (no tabs).

- Ensure consistent spacing around operators and after commas for better readability:

```c++
int total = a + b;
```

---

## Commit Naming Convention

Commit messages should follow a consistent format to make it easier to understand what changes have been made and why. Each commit message should include:

1. **Type of Change** (keyword in uppercase)
2. **Short Description** (clear and concise summary of the change)
3. **Optional Details** (brief explanation of why the change was made or additional context)

### Commit Types

- **FIX**: Use this for bug fixes or corrections.
  - Example: `FIX: Resolve crash issue on login page`
  - Optional Details: `Corrected a null pointer exception caused by missing user input validation.`

- **FEAT**: Use this for new features or functionalities.
  - Example: `FEAT: Add shortest path calculation algorithm`
  - Optional Details: `Implemented Dijkstra's algorithm for improved route optimization.`

- **UPDATE**: Use this for updates, enhancements, or improvements to existing code, features, or documentation.
  - Example: `UPDATE: Optimize rendering speed for game graphics`
  - Optional Details: `Reduced frame drop issues by caching assets more efficiently.`

- **DELETION**: Use this for deletions, removals of deprecated code, or redundant files.
  - Example: `DELETION: Remove unused class NodeManager`
  - Optional Details: `The class was no longer relevant after refactoring.`

- **DOC**: Use this for modification, creation, or deletion made to document(s).
  - Example: `DOC: Creation of technicalSpecifications.md`
  - Optional Details: `Added table of content`

### Format Guidelines

1. **Message Structure**:
   - TYPE: (Short Description) (Optional Details)

2. **Short Description**:

- Must be clear, concise, and written in an imperative mood (e.g., "Fix bug," not "Fixed bug").
- Limit to 50 characters or fewer if possible.

3. **Optional Details**:

- Provide additional context or explain the rationale for the change if necessary.
- Can include technical details, references to tickets/issues, or any notes for reviewers.

### Examples

- **FIX**: Correct off-by-one error in loop Adjusted index range to properly iterate over all elements.

- **FEAT**: Add user authentication functionality Includes token-based login and logout processes.

- **UPDATE**: Refactor code in GameController class Improved readability and reduced duplicate code.

- **DELETION**: Remove obsolete config files Replaced with a new configuration system in the latest update.

---

## Mistakes to avoid

- Inconsistent naming styles: Avoid mixing camelCase and PascalCase within the same context.

- Overly long names: Use concise but descriptive names.
  - ❌ CalculateTheDistanceBetweenTwoNodesForPathFinding
  - ✅ CalculateNodeDistance

- Unclear abbreviations: Avoid cryptic abbreviations that are not self-explanatory.
