# Graph-Theory-Project-Template
Project template of course - Graph Theory (EE6622E) in National Cheng Kung University.

## How to run

### Linux

```
# clone first (with submodule)
$ git clone --recursive https://github.com/<your-name>/Graph-Theory-Project-Template.git
# (Option) build libfakemn.a
$ cd fake-mininet && make lib && cd .. && cp fake-mininet/libfakemn.a .
# build
$ make 
# run 
$ ./main.out
```

### Windows

If your PC is `window 10`, then you need to install the related dependencies. For example, if you are using `VSCode` as your IDE, then you can install the plugin of `C/C++` in your vscode. And then install the following programs/packages:
* mingw
* git

Step by step to create `c_cpp_properties.json` and `tasks.json`:
* `Ctrl+Shift+P` -> `C/C++: Edit Configuration` -> then you have the first JSON file.
* `Ctrl+Shift+P` -> `Tasks: Configure Task` -> then you have the second JSON file.

Here is the setting of `c_cpp_properties.json` and `tasks.json`:
```json
# c_cpp_properties.json (If your mingw installed in another folder, then you have to change the value in `compilterPath`)
{
    "configurations": [
        {
            "name": "MinGW",
            "intelliSenseMode": "gcc-x64",
            "includePath": [
                "$(workspaceFolder)"
            ],
            "compilerPath": "C:/mingw/bin/gcc.exe",
            "cStandard": "c11",
            "cppStandard": "c++11"
        }
    ],
    "version": 4
}

# tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "main.cc",
                "-o",
                "main.exe",
                "-Ifake-mininet/lib",
                "-g3",
                "-L.",
                "-lfakemn_win",
                "-std=c++11"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

After all the settings have been done, we can press `Ctrl+Shift+B` to run the task, if your settings is correct, then there will have an executable file which named `main.exe`.

Or you can just [DOWNLOAD a pre-built VM images](http://gofile.me/39GpL/XU5tznyO6) provided by TA.

> [Guide of environment setting](https://hackmd.io/-5WZQC-1QqOeV3KUX65tEw?view) on Windows.

## TODO - Your descriptions about solutions/algorithms/results


### Abstrct
    
    1.In graph theory, the Chinese postman problem (CPP), is a problem to find a shortest closed path or circuit that visits every edge of an (connected) undirected graph.


    2.This program can finds the best solution under the condition that the number of vertex with an odd degree is less than 4.

### Solution

    1.Find out all vertex with an odd degree in this graph, and put them into a vector called Odd_Degree_Vertex, by the way, we also count the number of vertex with an odd degree.

    2-1.If the number of vertex with an odd degree is 0.
        Do nothing.
    2-2.If the number of vertex with an odd degree is 2.
        2-2-1.These two vertex are connected.
            Directly build the connection between these two vertex.
        2-2-2.These two vertex are not connected.
            Find the shortest path between these two vertex, and connect each vertex in shortest path.
    2-3.If the number of vertex with an odd degree is greater than 2.
            Find the minimum length pairwise matching of all vertex with an odd degree, then find the shortest path of each pair, and connect each vertex in shortest path.
        PS:Since the weight of each connection is 1, I use BFS algorithm to Find the shortest path instead of Dijkstra's algorithm.
    
    3.Use Hierholzer algorithm to find Euler Path.
    
        To find Euler path, I construct 2 stack, Euler_Path_stack and Temp_Euler_Path.
        
        First, I push vertex "a" into Temp_Euler_Path. 
        
        Second, if there is any vertex has connection with Temp_Euler_Path's top vertex, push it into Temp_Euler_Path and disconnect with Temp_Euler_Path's top vertex.

        Third, if there is no vertex has connection with Temp_Euler_Path's top vertex, push Temp_Euler_Path's top vertex into Euler_Path_stack until Temp_Euler_Path's top vertex has connection with any vertex. 


### File Name Identification
    
    1.main.cc:The main program.
    
    2.Graph.txt:The input graph.
    
    5.Euler_Path.dot:The dot file of result.
    
    6.Euler_Path.png:The png file of result.
    
    7.Euler_Path.txt:The txt file of result.


















