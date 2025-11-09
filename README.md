# Average Housing Cost Estimator
By Kailash Shankar, Jaden Lannning and Aryan Mukherjee

# The Problem
Due to current market trends and economic factors such as inflation, home prices are increasing rapidly. Many neighborhoods are becoming increasingly unaffordable for the middle class, and many families are relocating to different cities or even states in search of more affordable housing. 

# Our Solution
Introducing Home Price Estimator, a quick and easy-to-use web application that allows you to instantly see which neighborhoods in the US fit your budget. This tool allows you to enter in your zip code and see what the average housing price is in that neighborhood, as well as some other statistics about the housing in that area. Whether you are moving and want to see which neighborhood in the area is the most affordable, or are just curious about what the most affordable places to live in are in the US, this app provides a useful tool to find average home pricing estimates. 

# Tech Stack
This product utilizes two data structures, a **Red-Black Tree** and a **B Tree** coded in a C++ backend, as well as a React frontend and httplib to create a backend server that connects to the frontend.

# Setup Instructions
Clone this repository, and then follow the following steps to set up and run the application.

# Step 1: Download Visual Studio 
Download Visual Studio 2022 Community [here](https://visualstudio.microsoft.com/downloads/). This is necessary in order for the backend server to work.

Opening the downloaded exe file will run the Visual Studio Installer. In the installer, select the _**Desktop development with C++**_ workload and click _**Install**_.

# Step 2: Start backend server
Use your computer's start menu to search for and open _**x64 Native Tools Command Prompt for VS 2022**_. 
Navigate to the project's _Backend_ folder and then run:
~~~
cl /EHsc /std:c++17 /DWIN32_LEAN_AND_MEAN /I. data.cpp ws2_32.lib wsock32.lib /Fe:server.exe
~~~
This will compile the backend code. Then run:
~~~
server.exe
~~~
This will start the backend server.

# Step 3: Start the frontend application
Now that the backend is running, the application is ready to use.
In a new terminal, navigate to the root directory of the project and run:
~~~
npm run dev
~~~

This will start the frontend and create a localhost server. Click on the link to access the application.



