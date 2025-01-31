# Tested shortest paths

This document contains the shortest path tests that were successfully executed.

## Small dataset - `dataTest.csv`

| Test ID | Source | Destination | Number of nodes | Path | Distance units | Dijkstra | Bidirectional |
| ------- | ------ | ----------- | --------------- | ---- | -------------- | -------- | ------------- |
|AL_018_01||||||||

## Large dataset - `USA-roads.csv`

| Test ID   | Source    | Destination | Number of nodes | Path to the result                             | Distance units | Dijkstra | Execution time |
| --------- | --------- | ----------- | --------------- | ---------------------------------------------- | -------------- | -------- | -------------- |
| AL_019_01 | 1         | 17,902,846  | 3,610           | [AL_019_01](./testing/testingResuts/AL_019_01) |                | V.2      | 6,745 ms       |
| AL_019_02 | 1         | 2           | 2               | [AL_019_02](./testing/testingResuts/AL_019_02) | 5,062          | V.2      | 1,274 ms       |
| AL_019_03 | 100       | 200         | 38              | [AL_019_03](./testing/testingResuts/AL_019_03) | 358,307        | V.2      | 1,319 ms       |
| AL_019_04 | 300       | 400         | 35              | [AL_019_04](./testing/testingResuts/AL_019_04) | 277,607        | V.2      | 1,276 ms       |
| AL_019_05 | 500       | 700         | 38              | [AL_019_05](./testing/testingResuts/AL_019_05) | 394,325        | V.2      | 1,296 ms       |
| AL_019_06 | 1,234     | 5,678       | 610             | [AL_019_06](./testing/testingResuts/AL_019_06) | 2,980,378      | V.2      | 1,441 ms       |
| AL_019_07 | 7         | 12,345,678  | 2,230           | [AL_019_07](./testing/testingResuts/AL_019_07) | 7,438,024      | V.2      | 2,803 ms       |
| AL_019_08 | 9,876,234 | 23,359,056  | 2,017           | [AL_019_08](./testing/testingResuts/AL_019_08) | 7,502,976      | V.2      | 1,959 ms       |
| AL_019_09 | 1         | 22,382,040  | 10,192          | [AL_019_09](./testing/testingResuts/AL_019_09) |                | V.2      | 13,214 ms      |
| AL_019_10 | 534,968   | 5,342,161   | 1,892           | [AL_019_10](./testing/testingResuts/AL_019_10) |                | V.2      | 2,169 ms       |
| AL_019_11 | 9,489,093 | 22,377,087  | 13,323          | [AL_019_11](./testing/testingResuts/AL_019_11) |                | V.2      | 12,654 ms      |
| AL_019_12 | 9,489,093 | 22,377,087  | 13,323          | [AL_019_12](./testing/testingResuts/AL_019_12) |                | V.3      | 12,291 ms      |
| AL_019_13 | 9,489,093 | 22,377,086  | 13,322          | [AL_019_13](./testing/testingResuts/AL_019_13) |                | V.3      | 12,145 ms      |
| AL_019_14 | 9,489,093 | 22,377,088  | 13,323          | [AL_019_14](./testing/testingResuts/AL_019_14) |                | V.3      | 12,134 ms      |
| AL_019_15 | 1         | 22,382,040  | 10,192          | [AL_019_15](./testing/testingResuts/AL_019_15) |                | V.3      | 13,177 ms      |

