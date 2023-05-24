#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define SIZE 12

void *child(const char *path, int reverse_array[], int fd[])
{
	FILE *file;
	FILE *file2;
	struct stat fileStat;
	time_t lastModifiedTime = 0;

	close(fd[0]); // Close the unused read end of the pipe

	while (1)
	{
		if (stat(path, &fileStat) < 0)
		{
			file2 = fopen("161061_IsSisLabB2023BHR_UYG4_output.txt", "a");
			fprintf(file2, "Failed to get file information.\n");
			fclose(file2);
			printf("Failed to get file information.\n");
			break;
		}

		time_t currentModifiedTime = fileStat.st_mtime;

		if (currentModifiedTime != lastModifiedTime)
		{
			long long input = 0;
			int i = 0;

			// read file as long int
			file = fopen(path, "r");
			fscanf(file, "%lld", &input);

			file2 = fopen("161061_IsSisLabB2023BHR_UYG4_output.txt", "a");
			fprintf(file2, "%lld\n", input);
			fclose(file2);

			// parse the whole integer as digits.
			while (input)
			{
				if (i >= SIZE)
				{
					file2 = fopen("161061_IsSisLabB2023BHR_UYG4_output.txt", "a");
					fprintf(file2, "Warning! (Please enter a 12-digit number)\n");
					fclose(file2);
					printf("Warning! (Please enter a 12-digit number)\n");
					break;
				}
				reverse_array[i] = input % 10;
				input /= 10;
				i++;
			}

			// Array size check.
			if (i < SIZE)
			{
				file2 = fopen("161061_IsSisLabB2023BHR_UYG4_output.txt", "a");
				fprintf(file2, "Warning! (Please enter a 12-digit number)\n");
				fclose(file2);
				printf("Warning! (Please enter a 12-digit number)\n");
			}

			fclose(file);

			file2 = fopen("161061_IsSisLabB2023BHR_UYG4_output.txt", "a");
			fprintf(file2, "Last modification time: %s\n", ctime(&currentModifiedTime));
			fclose(file2);

			printf("Last modification time: %s\n", ctime(&currentModifiedTime));
			lastModifiedTime = currentModifiedTime;

			// Write the reverse_array to the pipe
			write(fd[1], reverse_array, sizeof(int) * SIZE);

			sleep(4);
		}
	}

	close(fd[1]); // Close the write end of the pipe
	exit(0);
}

void terminationHandler(pid_t pid)
{
	printf("Termination handler called.\n");
}

int main(int argc, char *argv[])
{
	FILE *file;
	FILE *file2;
	FILE *file3;
	char *path = argv[1];
	struct stat fileStat;
	time_t lastModifiedTime = 0;
	int reverse_array[SIZE];

	// argument count check
	if (argc != 2)
	{
		printf("Error! (argv size out of range)\n");
		return 1;
	}
	printf("arg=%s\n", argv[1]);

	int fd[2];
	pipe(fd);

	pid_t pid, wpid;
	int status = 0;
	pid = fork();
	if (pid != 0) // parent process
	{
		close(fd[1]); // Close the unused write end of the pipe

		while (1)
		{
			read(fd[0], reverse_array, sizeof(int) * SIZE);
			for (int i = SIZE - 1; i >= 0; i--)
			{
				printf("%d", reverse_array[i]);
			}
			printf("\n");
			// Alt durumlar
			// a : müh-mim ve bilg müh
			if (reverse_array[11] == 1 && reverse_array[10] == 5 &&
					reverse_array[9] == 2 && reverse_array[8] == 1)
			{
				file3 = fopen("161061_IsSisLabB2023BHR_UYG4_exp.txt", "a");
				fprintf(file3, "a: Müh.-Mim. Fak. Bilg. Müh.\n");
				fclose(file3);
				printf("a: Müh.-Mim. Fak. Bilg. Müh.\n");
			}
			else if ((reverse_array[7] * 1000) + (reverse_array[6] * 100) +
									 (reverse_array[5] * 10) + (reverse_array[4] * 1) >=
							 2017)
			{ // wait 4 sec and kill child process.
				file3 = fopen("161061_IsSisLabB2023BHR_UYG4_exp.txt", "a");
				fprintf(file3, "b: Giriş yılı >= 2017\n");
				fclose(file3);
				printf("b: Giriş yılı >= 2017\n");
				sleep(4);
			}
			else if (reverse_array[11] == 3 && reverse_array[10] == 0)
			{
				// wait 6 sec kill parent process.
				file3 = fopen("161061_IsSisLabB2023BHR_UYG4_exp.txt", "a");
				fprintf(file3, "c: Dış Üniversite.\n");
				fclose(file3);
				printf("c: Dış Üniversite.\n");
				sleep(6);
				atexit(terminationHandler);
				return 0;
			}
			else
			{
				file3 = fopen("161061_IsSisLabB2023BHR_UYG4_exp.txt", "a");
				fprintf(file3, "d: Diğer\n");
				fclose(file3);
				printf("d: Diğer\n");
			}
		}
	}
	else // child process
	{
		close(fd[0]); // Close the unused read end of the pipe
		child(path, reverse_array, fd);
	}

	pause();
	return 0;
}
