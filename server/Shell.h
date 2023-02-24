#ifndef CAVESHOOT_SHELL_H
#define CAVESHOOT_SHELL_H

#include <fcntl.h>
#include <thread>
#include <chrono>
#include <sys/wait.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <SFML/Network.hpp>
#include <iostream>

#define LOG(x) std::cout << x << std::endl

struct Shell {

    Shell() {
        popen2("bash", &kid);
    }

    ~Shell() {
        close(kid.to_child);
        printf("kill(%d, 0) -> %d\n", kid.child_pid, kill(kid.child_pid, 0));
        printf("waitpid() -> %d\n", waitpid(kid.child_pid, NULL, 0));
        printf("kill(%d, 0) -> %d\n", kid.child_pid, kill(kid.child_pid, 0));
    }


    auto exec(const std::string &cmd, std::chrono::seconds timeout) {
        std::stringstream result{};
        success = true;
        auto cmd2 = cmd + "; echo \"END\"\n";
        write(kid.to_child, cmd2.c_str(), cmd2.size());

        auto start = std::chrono::system_clock::now();
        fcntl(kid.from_child, F_SETFL, O_NONBLOCK);

        while (true) {
            auto now = std::chrono::system_clock::now();
            if (now - start > timeout) {
                result << "\nprogram end. timeout.END";
                success = false;
                break;
            }
            char temp;
            if (read(kid.from_child, &temp, 1) > 0) {
                result << temp;
                auto string = result.str();
                if (string.find("END") != std::string::npos) {
                    break;
                }
            }
        }

        LOG(result.str());
        return result.str().substr(0, result.str().size() - 3);
//        char buf[1000];
//        memset(buf, 0, 1000);
//        read(kid.from_child, buf, 1000);
//        LOG(buf);
    }

    bool isSuccess() const {
        return success;
    }

private:
    struct popen2 {
        pid_t child_pid;
        int from_child, to_child;
    };
    popen2 kid;
    bool success;


    int popen2(const char *cmdline, struct popen2 *childinfo) {
        pid_t p;
        int pipe_stdin[2], pipe_stdout[2];

        if (pipe(pipe_stdin)) return -1;
        if (pipe(pipe_stdout)) return -1;

//        printf("pipe_stdin[0] = %d, pipe_stdin[1] = %d\n", pipe_stdin[0], pipe_stdin[1]);
//        printf("pipe_stdout[0] = %d, pipe_stdout[1] = %d\n", pipe_stdout[0], pipe_stdout[1]);

        p = fork();
        if (p < 0) return p; /* Fork failed */
        if (p == 0) { /* child */
            close(pipe_stdin[1]);
            dup2(pipe_stdin[0], 0);
            close(pipe_stdout[0]);
            dup2(pipe_stdout[1], 1);
            execl("/bin/sh", "sh", "-c", cmdline, NULL);
            perror("execl");
            exit(99);
        }
        childinfo->child_pid = p;
        childinfo->to_child = pipe_stdin[1];
        childinfo->from_child = pipe_stdout[0];
        close(pipe_stdin[0]);
        close(pipe_stdout[1]);
        return 0;
    }
};

#endif //CAVESHOOT_SHELL_H
