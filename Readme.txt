Project Assessment:

CrossMonitor is a console based client application for monitoring system resources. CrossMonitor application is under development and currently monitors  CPU, memory utilization and process count every few minutes and writes to the console output. How this information is transferred to the server is out of the scope of this project assessment and not implemented.

Project Notes:
  -  The current implementation has few bugs.
  -  Next user story is to implement the process count for the system.
  
Tasks :
    1. Find and fix the bugs.
    2. Implement the process count function.
    3. Client/application_client.cpp is implemented poorly. Refactor it to follow the best practices.

Prerequisites:
        Xcode 9.4.1

How to run :
        Open the cross-monitor-cpp-xcode.xcodeproj file in Xcode.
        Build the project and run the Client with appropriate arguments.
        The project uses the boost, cpprestsdk, googletest, googlemock libraries.
        Install and configure using your preferred mechanism or use hints below.
        brew install boost
        brew install cpprestsdk
        wget https://github.com/google/googletest/archive/release-1.8.0.zip
        unzip release-1.8.0.zip

        //Install gtest
        cd googletest-release-1.8.0/googletest/
        mkdir build
        cd build
        cmake ..
        make
        cp -a ../include/gtest /usr/local/include/
        cp -a *.a /usr/local/lib
        
        //Install gmock
        cd ../../googlemock/
        mkdir build        
        cd build
        cp -a ../include/gmock/ /usr/local/include
        cp -a *.a /usr/local/lib

        

How to deliver :
This is how we are going to access and evaluate your submission, so please make sure to go through the following steps before submitting your answer.

1) Make sure to run unit tests, ensure that the application is compiling and all dependencies are included.
2) Delete the Debug and Packages folder to reduce the size of submission.
2) Zip the project and store/upload it to a shared location where Crossover team can access and download the project for evaluation, and add a link to the shared file in the answer field of this question.