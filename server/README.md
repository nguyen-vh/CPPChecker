# REST API and Webpage for CPPChecker



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
    <li><a href="#usage">Usage</a>
    <ul>
        <li><a href="#webpage">Webpage</a></li>
        <li><a href="#without-webpage">Without Webpage</a></li>
      </ul>
    </li>
    <li><a href="#limitations">Limitations</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>



<!-- ABOUT THE SERVER -->
## About The Server
You can use the cppchecker header in many ways. One way is to use it to check tasks that you have already created. You can then use a REST server to send code with the attached task token to receive an evaluation of the request. This server is intended to help me show how to use cppchecker in a real-world scenario.



### Built With
* [![C++][cpp26-badge]][cpp-url]
* [![CrowCpp][crowcpp-badge]][crowcpp-url]
* [![Bubblewrap][bubblewrap-badge]][bubblewrap-url]
* [![Docker][docker-badge]][docker-url]
* [![Vue][vue-badge]][vue-url]



<!-- GETTING STARTED -->
## Getting Started
In this section, I will explain how to set up the server.


### Prerequisites
The only thing you need to run the server is Docker Compose, which you can install on your computer.
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
3. If you have installed "make", run the ` make ` command. If not, run the ` docker-compose up --build ` command to build the server


> [!TIP]  
> If you only want the REST API without frontend, run ` make back `.

<!-- USAGE -->
## Usage
How can you use it now? In the "tasks" folder, you will find a template and some examples. You can make a copy of the template and start writing your own task, but make sure you follow this naming rule for the task files: task_<task_token>.cpp

In the task file, you technically only need to write code in the main function with CPPChecker to verify your requirements, but I recommend adding instructions and a solution as well.

> [!NOTE]  
> To find out how to use CPPChecker, look at the other [README](https://github.com/nguyen-vh/CPPChecker/blob/main/README.md) file or the [wiki](https://github.com/nguyen-vh/CPPChecker/wiki), if it has already been set up.


### Webpage
Once the server is up and running, you can go to your browser and type in the server's IP address. If it's running on your computer, go to [http://localhost:5173/] (http://localhost:5173/).

The webpage should show a list of tasks. In this case, it should show the example tasks that I created. If you want to add more of your own custom tasks to the webpage, edit [server/src/frontend/src/App.vue] (https://github.com/nguyen-vh/CPPChecker/tree/main/server/src/frontend/src/App.vue). The structure of the webpage should be straightforward.

![Webpage example][webpage-example]


### Without Webpage
Once the server is running, you can also just use the backend without the frontend webpage. Send your code to the server. You can find the IP address of the server (if the server is on the same computer as the sending computer, use "localhost", "0.0.0.0", or "127.0.0.1"), the port (the default is 8008), and the <task_token> as the route.
I have an example of [Postman](https://www.postman.com/) to send a POST request with my code to my server. The URL here is localhost:8008/Rectangle1. Make sure that the 'Content-Type' is set to 'text/plain'.

![Postman example][postman-example]



<!-- LIMITATIONS -->
## Limitations
The current version of the project takes 2.4 seconds for the request to reach the server, be compiled, and executed within [Bubblewrap][bubblewrap-url]—to meet high security standards—and for the result to be sent back to the client. This time was measured when the client and server were on the same machine. I get this performance by using precompiled headers and optimization flags when I compile. But I think this time should be a lot shorter. If you have any ideas on how to make the process faster, please start a chat in the [discussions](https://github.com/nguyen-vh/CPPChecker/discussions) section.



<!-- LICENSE -->
## License
All source files include the license information at the beginning. Files that use other projects, such as "RestApi.cpp", which uses CrowCpp, also include the relevant license information.

For the general license, see [LICENSE][license].



<!-- MARKDOWN LINKS & IMAGES -->
[cpp26-badge]:https://img.shields.io/badge/C++26-00599C?style=for-the-badge&logo=cplusplus
[cpp-url]:https://isocpp.org/
[crowcpp-badge]:https://img.shields.io/badge/CrowCpp-0A2B4E?style=for-the-badge&logo=cplusplus
[crowcpp-url]:https://github.com/crowcpp/crow
[bubblewrap-badge]:https://img.shields.io/badge/bubblewrap-487CB8?style=for-the-badge&logo=c
[bubblewrap-url]:https://github.com/containers/bubblewrap
[docker-badge]:https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white
[docker-url]:https://www.docker.com/
[vue-badge]:https://img.shields.io/badge/Vue-4FC08D?style=for-the-badge&logo=vuedotjs&logoColor=white
[vue-url]:https://vuejs.org/guide/typescript/overview.html

[webpage-example]:https://github.com/nguyen-vh/CPPChecker/blob/main/src/common/images/webpage_example.png
[postman-example]:https://github.com/nguyen-vh/CPPChecker/blob/main/src/common/images/postman_example.png
[license]:https://github.com/nguyen-vh/CPPChecker/blob/main/LICENSE.md
