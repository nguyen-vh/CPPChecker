// Copyright (c) 2026-present Hoang Nguyen
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This software uses Crow C++ for certain functionalities.
//
// Crow C++:
// Copyright (c) 2020-2022 CrowCpp
// License: BSD 3-Clause License
// Visit https://github.com/CrowCpp/Crow/blob/master/LICENSE for details.

//----------------------------------------------------------------------------//
// °                            === INCLUDES ===                            ° //
//----------------------------------------------------------------------------//

#include <sys/wait.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>
#include <thread>

#include "include/crow_all.hpp"

//----------------------------------------------------------------------------//
// °                           === CONSTANTS ===                            ° //
//----------------------------------------------------------------------------//

const int PORT{8008};
const int THREADS{10};
const int SUCCESS_CODE{200};
const int FAILED_CODE{400};

//----------------------------------------------------------------------------//
// °                           === FUNCTIONS ===                            ° //
//----------------------------------------------------------------------------//

auto randomToken() -> std::string {
  std::random_device rd;
  std::mt19937 rng(rd());
  const std::string charset =
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "0123456789";

  std::uniform_int_distribution<> dist(0, charset.size() - 1);

  std::string result;
  for (int i = 0; i < 5; i++) {
    result += charset[dist(rng)];
  }

  return result;
}

auto executeTaskEvaluator(const std::string& task_token,
                          const std::string& random_token) -> int {
  pid_t pid = fork();

  if (-1 == pid) {
    std::cerr << "Error: Fork failed.\n";
    return 1;
  }

  if (0 == pid) {
    execl("./TaskEvaluator", "./TaskEvaluator", task_token.data(),
          random_token.data(), nullptr);
    std::cerr << "Error: execl failed.\n";
    _exit(1);
  }

  int status{};
  waitpid(pid, &status, 0);

  return (WIFEXITED(status) && 0 == WEXITSTATUS(status))
             ? 0
             : (std::cerr << "Error: TaskEvaluator execution failed.\n", 1);
}

auto cleanupTempFiles(const std::string& task_token,
                      const std::string& random_token) -> void {
  const std::filesystem::path eop_path =
      "temp/eop_" + task_token + random_token;

  while (!std::filesystem::exists(eop_path))
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::filesystem::remove(eop_path);

  const std::filesystem::path code_file =
      "temp/" + random_token + "_" + task_token + ".cpp";
  if (std::filesystem::exists(code_file)) std::filesystem::remove(code_file);

  const std::filesystem::path execution_file =
      "temp/" + random_token + "_task_" + task_token;
  if (std::filesystem::exists(execution_file))
    std::filesystem::remove(execution_file);
}

//----------------------------------------------------------------------------//
// °                              === MAIN ===                              ° //
//----------------------------------------------------------------------------//

auto main(int /*argc*/, char* /*argv*/[]) -> int {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/healthcheck")
  ([]() { return "Still running strong!"; });

  CROW_ROUTE(app, "/<string>")
      .methods("POST"_method)(
          [](const crow::request& request, crow::response& response,
             const std::string& task_token) {
            response.set_header("Content-Type", "text/plain");

            const std::string content_type =
                request.get_header_value("Content-Type");

            if ("text/plain" == content_type) {
              std::string const text_body = request.body;
              std::string random_token = randomToken();

              const std::string code_file =
                  "temp/" + random_token + "_" + task_token + ".cpp";

              std::ofstream ofs_code_file(code_file);
              ofs_code_file << text_body;
              ofs_code_file.close();

              const std::filesystem::path archive_path =
                  "archive/task_" + task_token + "/";

              if (!std::filesystem::exists(archive_path))
                std::filesystem::create_directories(archive_path);

              if (0 == executeTaskEvaluator(task_token, random_token)) {
                const std::string response_path =
                    "archive/task_" + task_token + "/" + random_token + ".txt";

                std::ifstream ifs_response(response_path);
                if (ifs_response.is_open()) {
                  std::stringstream buffer;
                  buffer << ifs_response.rdbuf();
                  std::string const response_file = buffer.str();

                  ifs_response.close();

                  response.write(response_file);
                }
                response.code = SUCCESS_CODE;
              } else {
                response.code = FAILED_CODE;
                response.write("ERROR occurred.");
              }

              response.end();

              cleanupTempFiles(task_token, random_token);

            } else {
              response.code = FAILED_CODE;
              response.write("EMPTY request.");
              response.end();
            }
          }

      );

  app.port(PORT).multithreaded().concurrency(THREADS).run_async();

  return 0;
}