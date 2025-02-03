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

## How to use Road Runner?

Road Runner is available anywhere

1. Connect to the same wifi: 
    - be connected to the same wifi as Road Runner's server.

2. Open your terminal: 
    - type the `windows+R` keys, type `cmd` and press enter.

3. Type in the request: 
    - If you want your response in a .xml file, type in this command: `curl -o result.xml "http://localhost:8080/path?start=x&end=y" -H "Accept: application/xml"`
    - If you want your response in a .JSON file, type in this command: `curl -o result.json "http://localhost:8080/path?start=x&end=y"`
    - Replace the x from `start=x` and y from `end=y` to the start and end node you wish.

4. Type your start and end point:
    - Give Road Runner the ID's of the starting and ending landmark.

5. Choose your results format:
    - You can get your results, which include the travel times and landmarks you will pass through in `JSON` or `XML` format.

# How to download Road Runner?

Maybe you want to read or modify the code, here is how you do it:
1. Download the project:
- Open your terminal.
- Clone this repository by typing git clone `https://github.com/algosup/2024-2025-project-3-quickest-path-team-4`.
- Type cd `2024-2025-project-3-quickest-path-team-4` to get into the project's directory.
2. Check if everything works fine:
- Still in the terminal, type `cd src` to get into the source folder.
- Make sure there is a `.csv` files in the `src` folder.

To run the program:

(I will add stuff there when we have all the files ready)

Link to the documentation:

(The links will be added when the files have been pushed in the main)