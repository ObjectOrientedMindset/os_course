#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int depth;
    char buffer[2000];

    time_t mytime;
    mytime = time(NULL);
    FILE *fp;
    // argumanlar.
    if (argc == 2)
    {
        depth = atoi(argv[1]); // normal arguman.
    }
    else if (argc == 5)
    {
        printf("152120161061 Mithat Uçar\n");
        depth = atoi(argv[4]); // option arguman.
    }
    else
    { // arguman verilmemişse depth 1.
        depth = 1;
    }

    pid_t pid;

    pid = fork(); // Child1

    if (pid == 0)
    {
        sprintf(buffer + strlen(buffer), "Child PID %d , Parent PID %d\n", getpid(), getppid());
        fp = fopen("./logs/161061_IsSisLabB2023BHR_UYG2_logAll.log", "a");
        fprintf(fp, buffer);
        fclose(fp);
        printf("Child PID %d , Parent PID %d\n", getpid(), getppid());
        sleep(2);

        for (size_t i = 0; i < depth - 1; i++)
        {
            // Child1 den çocuk process üret.
            pid = fork(); // child process
            if (pid == 0)
            {
                sprintf(buffer, "Child PID %d , Parent PID %d\n", getpid(), getppid());
                fp = fopen("./logs/161061_IsSisLabB2023BHR_UYG2_logAll.log", "a");
                fprintf(fp, buffer);
                fclose(fp);
                printf("Child PID %d , Parent PID %d\n", getpid(), getppid());
                sleep(2);
            }
            else if (pid > 0)
            {
                // parent process
                sleep(2);
                break;
            }
        }
        exit(0); // process terminate.
    }
    else if (pid > 0)
    {
        // parent process
        sprintf(buffer + strlen(buffer), "Child PID %d , Parent PID %d\n", getpid(), getppid());
        printf("Parent PID %d , Parent PID %d\n", getpid(), getppid());
        // log dosyası oluşturup tarih bilgisi yazılır.
        fp = fopen("./logs/161061_IsSisLabB2023BHR_UYG2_logAll.log", "a");
        fprintf(fp, ctime(&mytime));
        fclose(fp);
        sleep(1);
    }

    pid = fork(); // Child2

    if (pid == 0)
    {
        // child process
        sprintf(buffer + strlen(buffer), "Child PID %d , Parent PID %d\n", getpid(), getppid());
        fp = fopen("./logs/161061_IsSisLabB2023BHR_UYG2_logAll.log", "a");
        fprintf(fp, buffer);
        fclose(fp);
        printf("Child PID %d , Parent PID %d\n", getpid(), getppid());
        sleep(2);
    }
    else if (pid > 0)
    {
        // parent process
        sleep(1);
    }
    pause();
    return 0;
}
