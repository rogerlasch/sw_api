Simple C++ REST API
# Introduction
This API was developed as part of a practical exercise in the Web Services class, covering the topics discussed in the classroom. It represents a Music Request API, allowing users to register music requests for a radio host to attend to later. To make a request, users need to provide information such as the song's name, the artist's name, their own name, and optionally, a message.

# Requirements
Make sure to meet the following requirements before proceeding:

- C++20 or higher

- Crow

- pqxx

- curl (usually, Windows 11 comes with the command-line tool)

- Visual Studio build tools (Visual Studio Community 2022 was used)

# Installing the Vcpkg Package Manager
Before getting started, ensure you have Git installed on your system, as you will use Git to clone the Vcpkg repository.

-  Open a terminal or command prompt and navigate to the directory where you want to install Vcpkg.
-  Execute the following command to clone the official Vcpkg repository:

git clone https://github.com/microsoft/vcpkg.git

This will download the Vcpkg repository to your system.

## Compiling Vcpkg
-  Navigate to the Vcpkg directory you just cloned:

cd vcpkg

-  Compile Vcpkg by running the following command:

.\bootstrap-vcpkg.bat

This will set up Vcpkg on your system.

## Installing Vcpkg
Now you can install Vcpkg globally on your system. To do this, run the following command:

.\vcpkg integrate install

This will allow you to use Vcpkg in any C++ project.

## Installing Packages with Vcpkg
You can use Vcpkg to install C++ libraries and dependencies in your projects. For example, to install the Crow library, you can run the following command:

.\vcpkg install crow
Vcpkg will download, compile, and install the Crow library on your system.

# Compiling the Project
-  Use Vcpkg to install the Crow and pqxx libraries.
-  Open a Visual Studio Developer Command Prompt and navigate to the root of the sw_api repository.
-  Run the "build.bat" command to compile from the command line. You can also compile using one of the project files created.
-  Open the sw_api.sln solution in Visual Studio Community and compile the project. The executable will be in the sw_api folder.

# Database
This API uses Postgresql for data persistence. In the "db.sql" file, there is an SQL statement to create the table used. Create a database named "songs_db" for the API to work. You can also adjust the user, password, and database name in "src/SongRequestController.cpp."

# Testing the API
To test the API, you can use your preferred tool, such as Postman, Thunder client, or curl. In the "curl_testes" file, there are some curl commands to test the API. Just copy each of them and execute in a command line, provided that the curl tool is available.

# Acknowledgments
If you found this project interesting, please star it. For critiques, questions, or suggestions, you can send an email to rogerlasch@gmail.com.
