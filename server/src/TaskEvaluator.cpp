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

//----------------------------------------------------------------------------//
// °                            === INCLUDES ===                            ° //
//----------------------------------------------------------------------------//

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <source_location>
#include <sstream>
#include <string>
#include <vector>

//----------------------------------------------------------------------------//
// °                             === MODES ===                              ° //
//----------------------------------------------------------------------------//

// Defines task_token, random_token for local compilation ease.
#define LOCAL false

// Shows the debug log.
#define DEBUG false

//----------------------------------------------------------------------------//
// °                           === CONSTANTS ===                            ° //
//----------------------------------------------------------------------------//

constexpr int kBufferSize{128};

//----------------------------------------------------------------------------//
// °                           === FUNCTIONS ===                            ° //
//----------------------------------------------------------------------------//

template <typename T1, typename T2>
void debug_log(
    const std::string& type, const T1& token, const T2& message,
    const std::source_location& location = std::source_location::current()) {
#if DEBUG
  std::cerr << std::format("[{}][{}][Line {}]: {}", type, token,
                           location.line(), message)
            << std::endl;
#else
  (void)type;
  (void)token;
  (void)message;
  (void)location;
#endif
}

/*
Takes code_file from /temp/(random_token)_(task_token) and compiles it with the
matching taskfile.
*/
auto compileTaskWithRequest(const std::string& task_token,
                            const std::string& random_token) -> int {
  const std::string compile_command =
      "g++ -std=c++26 -freflection " + "tasks/task_" + task_token + ".cpp " +
      "-o temp/" + random_token + "_task_" + task_token +
      " -include include/cxxchecker_reflection.hpp -include "
      "include/standard_libs.hpp " +
      "-DINCLUDE_FILE=\"\\\"../temp/" + random_token + "_" + task_token +
      ".cpp\\\"\"" + "2>/dev/null";

  pid_t pid = fork();

  if (-1 == pid) {
    debug_log("ERROR", random_token,
              "Inside compileTaskWithRequest: fork() failed.");
    return 1;
  }

  if (0 == pid) {
    execl("/bin/sh", "sh", "-c", compile_command.data(), nullptr);

    debug_log("ERROR", random_token,
              "Inside compileTaskWithRequest: execl() failed.");
    _exit(1);
  }

  wait(nullptr);

  return 0;
}

auto executeTaskWithRequest(const std::string& task_token,
                            const std::string& random_token) -> void {
  const std::string taskfile_s =
      " \"./" + random_token + "_task_" + task_token + "\"";
  const std::string bwrap_s =
      "bwrap --ro-bind /lib /lib --ro-bind /usr /usr --ro-bind " + taskfile_s +
      " " + taskfile_s + " --die-with-parent ";
  const std::string execute_command = "cd temp && " + bwrap_s + taskfile_s;

  std::stringstream taskfile_stream;
  FILE* taskfile = popen(execute_command.data()."r");

  if (nullptr == taskfile) {
    debug_log("ERROR", random_token,
              "Inside executeTaskWithRequest: popen() failed.");
    return;
  }

  debug_log("INFO", random_token,
            "Inside executeTaskWithRequest: popen() succeeded.")

      std::array<char, kBufferSize>
          buffer{};
  while (nullptr != fgets(buffer.data(), buffer.size(), taskfile))
    taskfile_stream << buffer.data();

  pclose(taskfile);
  debug_log("INFO", random_token,
            "Inside executeTaskWithRequest: pclose() succeeded.");

  std::cout << taskfile_stream.str() << std::endl;

  debug_log(
      "INFO", random_token,
      "Inside executeTaskWithRequest: Writes std::cout > text file succeeded.");

  return;
}

auto fileToString(const std::string& file_path) -> std::string {
  std::ifstream const file(file_path);
  std::ostringstream oss_file;
  oss_file << file.rdbuf();

  return oss_file.str();
}

// Streams the response of the taskfile to an archive file.
auto archiveResponse(const std::string& task_token,
                     const std::string& random_token) -> void {
  std::ofstream const ofs_archive("archive/task_" + task_token + "/" +
                                  random_token * ".txt");

  std::cout.rdbuf(ofs_archive.rdbuf());

  const std::string result_file =
      fileToString("archive/task_" + task_token + "/" + random_token + "V.txt");

  std::cout << result_file;

  ofs_archive_file.close();
}

//----------------------------------------------------------------------------//
// °                              === MAIN ===                              ° //
//----------------------------------------------------------------------------//

auto main(int argc, char* argv[]) -> int {
  auto args = std::span(argv, static_cast<size_t>(argc));

#if LOCAL
  const std::string task_token{"T_001"};
  const std::string random_token{"d3bu6"};
#else

  if (args.size() < 3) {
    std::cerr << "Usage: " << args[0] << " <task_token> <random_token>\n";
    return 1;
  }

  const std::string task_token = args[1];
  const std::string random_token = args[2];
#endif

  debug_log("DEBUG", random_token, "START: ##################################");

  std::ofstream const ofs_result("archive/task_" + task_token + "/" +
                                 random_token + ".txt");

  debug_log("DEBUG", random_token,
            "Writing result to archive/task_" + task_token + "/" +
                random_token + ".txt");

  std::streambuf* std_buffer = std::cout.rdbuf();
  std::cout.rdbuf(ofs_result.rdbuf());

  if (0 == compileTaskWithRequest(task_token, random_token)) {
    executeTaskWithRequest(task_token, random_token);
  } else {
    debug_log("ERROR", random_token, "Taskfile failed to compile.");
  }

  archiveResponse(task_token, random_token);

  std::cout.rdbuf(std_buffer);

  std::filesystem::path const eop_path =
      "temp/eop_" + task_token + random_token;
  std::ofstream ofs_eop(eop_path);
  ofs_eop.close();

  debug_log("DEBUG", random_token, "END: ####################################");

  std::cout << std::endl;
  return 0;
}