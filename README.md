# Road Runner - Find the quickest path across America! 

Road Runner will help you find the quickest path from Landmark to Landmark in America! With quick responses and multiple reponse formats, Road Runner is here to help!

## What Is Road Runner?

Road Runner isn’t just an algorithm, it's your personal helper. Powered by advanced algorithms, Road Runner navigates the roads between landmarks, providing accurately and efficiently the quickest paths.

## Meet The Team 

<div align="center">

| Picture | Name       | Role               | Links                                                             |
| ----- | --------------- | ------------------------ | ----------------------------------------------------------------- |
| <img src="https://avatars.githubusercontent.com/u/182214919?v=4" width=80> | Emilien CHINSY | Project manager | [LinkedIn](https://www.linkedin.com/in/emilien-chinsy-5a794632b/) [GitHub](https://github.com/EmilienChinsy) |
| <img src="https://avatars.githubusercontent.com/u/91249965?v=4" width=80> | Paul NOWAK | Program manager | [LinkedIn](https://www.linkedin.com/in/paul-nowak-0757a61a7/) [GitHub](https://github.com/PaulNowak36)  |
| <img src="https://avatars.githubusercontent.com/u/146005163?v=4" width=80> | Thibaud MARLIER | Tech lead| [LinkedIn](https://www.linkedin.com/in/thibaudmarlier/) [GitHub](https://github.com/Biohazardyee) |
| <img src="https://avatars.githubusercontent.com/u/146005340?v=4" width=80> | Ian LAURENT | Software engineer | [LinkedIn](https://www.linkedin.com/in/ian-h-laurent/) [GitHub](https://github.com/Ianlaur) |
| <img src="https://avatars.githubusercontent.com/u/78617457?v=4" width=80> | Clémentine CUREL | Quality assurance | [LinkedIn](https://www.linkedin.com/in/clementinecurel/) [GitHub](https://github.com/Clementine951) |
| <img src="https://avatars.githubusercontent.com/u/71769489?v=4" width=80> | Laurent BOUQUIN | Tech writer | [LinkedIn](https://www.linkedin.com/in/laurentb22/) [GitHub](https://github.com/laurentbouquin) |

</div>

## Links to the documentation:

### Specifications

- [Functional Specifications](https://github.com/algosup/2024-2025-project-3-quickest-path-team-4/blob/main/functionalSpecifications/functionalSpecifications.md)
- [Technical Specifications](https://github.com/algosup/2024-2025-project-3-quickest-path-team-4/blob/main/technicalSpecification/technicalSpecifications.md)

### Project Management

- [Management Artifact](https://github.com/algosup/2024-2025-project-3-quickest-path-team-4/blob/main/management/managementArtifacts.md)
- [Weekly Reports](https://github.com/algosup/2024-2025-project-3-quickest-path-team-4/blob/main/management/weeklyReports/globalReport.md)

### Quality Assurance       

- [Test Plan](https://github.com/algosup/2024-2025-project-3-quickest-path-team-4/blob/main/qualityAssurance/documents/testPlan.md)
- [Test Cases](https://github.com/algosup/2024-2025-project-3-quickest-path-team-4/blob/main/qualityAssurance/documents/testCases.md)

### User Manual

- [User Manual](https://github.com/algosup/2024-2025-project-3-quickest-path-team-4/blob/main/userManual/Road_Runner_User_Manual_Team_4.pdf)

## How to download Road Runner?

Maybe you want to read or modify the code, here is how you do it:

1. Download the project:

    1. Open your terminal.
   
        - For Windows:
   
            - Type the `windows+R` keys, type `cmd` and press enter.
   
        - For MacOS:
   
            - Type the `command+space` keys, type `terminal` and press enter.

    2. Clone this repository by typing git clone `https://github.com/algosup/2024-2025-project-3-quickest-path-team-4`.

    3. Type cd `2024-2025-project-3-quickest-path-team-4` to get into the project's directory.

3. Check if everything was installed correctly:

    1. Still in the terminal, type `cd src` to get into the source folder.

    2. Make sure there is a `.csv` files in the `src` folder.

## How to run the program:

To directly run a road runner server from your computer:

1. Install all the required software:

    - For macOS : 

        - Install hombrew: [https://docs.brew.sh/Installation](https://docs.brew.sh/Installation).

        - Install the compiler: [https://formulae.brew.sh/formula/gcc](https://formulae.brew.sh/formula/gcc).

    - For Windows : 

        - Install Clang: [https://youtu.be/QGOVWA2FcQE?si=Zu_eZCeabhLEGmgH](https://youtu.be/QGOVWA2FcQE?si=Zu_eZCeabhLEGmgH)

        - Install MinGW-w64: [https://www.mingw-w64.org/downloads/](https://www.mingw-w64.org/downloads/).

        - Type this `vcpkg install pthreads` in the MinGW terminal.

2. Open your terminal:

    - For Windows:
        - Type the `windows+R` keys, type `cmd` and press enter.
    - For macOS:
        - Type the `command+space` keys, type `terminal` and press enter.

3. Navigate to the right folder:

    - For Windows:

        1. Open file explorer.

        2. Navigate to the folder in which the server.cpp file is located.

        3. copy the file path located on the top of file explorer.

        4. In the terminal, type: `cd "thefilepathyoujustcopied"`.

        Note: Make sure to include quotes around the path if it contains spaces.

    - For macOS:

        1. Open Finder.

        2. Navigate to the folder containing the server.cpp file.

        3. Right-click the folder name at the top of Finder (or use `Control + Click) and select "Copy as Pathname".
      
        4. In the terminal, type: `cd "thefilepathyoujustcopied"`.

4. Compile and run the code:

    - For Windows:

        1. In the terminal, type: `clang++ -std=gnu++20 -O3 -I../boost_1_82_0 -D_WIN32_WINNT=0x0601 -D_CRT_SECURE_NO_WARNINGS server.cpp algorithm.cpp loading.cpp -o server.exe -lws2_32`.

        2. Then type `.\server.exe`.

        3. Road Runner is now ready to go from your machine!

    - For macOS:

        1. In the terminal, type: `clang++ -std=gnu++20 -O3 -I../boost_1_82_0 serverMac.cpp algorithm.cpp loading.cpp -o server -lpthread`.

        2. Then type `./server`.

        3. Road Runner is now ready to go from your machine!

## How to use Road Runner?

Road Runner is available anywhere!

1. Connect to the same wifi: 

    - Be connected to the same wifi as Road Runner's server.

2. Open your terminal: 

    - For Windows:
        - Type the `windows+R` keys, type `cmd` and press enter.
    - For macOS:
        - Type the `command+space` keys, type `terminal` and press enter.

3. Move to the client's folder: 
    - in the terminal, type `cd "thepathtotheclientfile"


4. Compile and run the client:
    - for Windows:
        1. compile the client by writing this in your terminal: `clang++ -std=gnu++20 -O3 -I../boost_1_82_0 -D_WIN32_WINNT=0x0601 -D_CRT_SECURE_NO_WARNINGS client.cpp -o client.exe -lws2_32`
        2. run the client by writing this in your terminal: `.\client.exe`
    
    - for macOS:
        1. compile the client by writing this in your terminal: `clang++ -std=gnu++20 -O3 -I../boost_1_82_0 client.cpp -o client -lpthread`
        2. run the client by writing this in your terminal : `./client`


5. Type your start and end point:
    - Give Road Runner the ID's of the starting and ending landmark.


6. Choose your results format:
    - Type 1 to get your results in JSON format or 2 to get your results in XML format.
