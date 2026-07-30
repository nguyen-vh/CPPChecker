<h3 align="center">REST API for CPPChecker</h3>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-server">About The Server</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>



<!-- ABOUT THE SERVER -->
## About The Server
There are many ways to use the cppchecker header; one of them is to use it as a tool for checking previously created tasks. A REST server can then be used to send code with the attached task token to receive an evaluation of the request. This server is intended to help me illustrate the use of cppchecker in a real-world scenario.



### Built With
* [![C++][cpp26-badge]][cpp-url]
* [![CrowCpp][crowcpp-badge]][crowcpp-url]
* [![Docker][docker-badge]][docker-url]



<!-- GETTING STARTED -->
## Getting Started
In this section, I will explain the steps you can take to get the server up and running.


### Prerequisites
The only requirement for running the server is that Docker Compose is installed on your computer.
On a desktop computer, simply installing [Docker Desktop](https://www.docker.com/products/docker-desktop/) is sufficient.

If you are using a minimal image like Alpine, running this command will install Docker Compose.
```sh
apk add docker-compose
```

To make things easier, you can also install "make" to use Makefiles.
There are two easy ways to install the program on Windows:
* [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm)
* Using [Chocolatey](https://chocolatey.org/): ` choco install make ` 


### Installation
1. Clone the repository or copy this "server" folder to your computer
   ```sh
   git clone https://github.com/nguyen-vh/CPPChecker.git
   ```
2. In the terminal, navigate to the "server" folder
3. If "make" is installed: run the ` make ` command; otherwise, run ` docker-compose up --build ` command to build the server



<!-- USAGE -->
## Usage
How can you use it now? In the "tasks" folder, you will find a template and some examples. You can clone the template and start writing your own task, but be sure to follow this naming convention for the task files: task_<task_token>.cpp

In the task file, you technically only need to write code in the main function with CPPChecker to verify your requirements, but I recommend adding instructions and a solution as well.

> [!NOTE]  
> For information on how to use CPPChecker, see the other [README](https://github.com/nguyen-vh/CPPChecker/blob/main/README.md) file or the [wiki](https://github.com/nguyen-vh/CPPChecker/wiki), if it has already been set up.

Once the server is running and you have created your task, using it is very simple: Send your code corresponding to your task to the server by specifying its IP address (if the server is on the same computer as the sending computer, use "localhost", "0.0.0.0", or "127.0.0.1"), the port (the default is 8008), and the <task_token> as the route.
I have an example where I use [Postman](https://www.postman.com/) to send a POST request with my code to my server. The URL here is localhost:8008/Rec21T. Make also sure that the Content-Type is text/plain.

![Postman example][postman-example]



<!-- LICENSE -->
## License
All source files include the license information at the beginning. Files that use other projects—such as "RestApi.cpp", which uses CrowCpp—also include the relevant license information.

For the general license, see [LICENSE][license].



<!-- MARKDOWN LINKS & IMAGES -->
[cpp26-badge]:https://img.shields.io/badge/C++26-00599C?style=for-the-badge&logo=cplusplus
[cpp-url]:https://isocpp.org/
[crowcpp-badge]:https://img.shields.io/badge/CrowCpp-0A2B4E?style=for-the-badge&logo=cplusplus
[crowcpp-url]:https://github.com/crowcpp/crow
[docker-badge]:https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white
[docker-url]:https://www.docker.com/
[postman-example]:https://github.com/nguyen-vh/CPPChecker/blob/main/src/common/images/Postman_example.png
[license]:https://github.com/nguyen-vh/CPPChecker/blob/main/LICENSE.md