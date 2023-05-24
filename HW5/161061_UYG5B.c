#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <windows.h>

#define NUMOFITEMS 13

sem_t *semaphore_body, *semaphore_head,
		*semaphore_hand, *semaphore_leg, *semaphore_foot;
enum body
{
	HEAD,
	UBDY,
	HAND,
	LEG_,
	FOOT
};

int count = 0;

void dressItem(int part, char *name)
{ // write file
	FILE *file;
	file = fopen("161061_IsSisLabB2023BHR_UYG5_output.txt", "a");
	static const char *BODY_STRING[] = {"kafa ", "govde", "el   ", "bacak", "ayak "};

	if (count == 0)
	{
		fprintf(file, "%2d. \t\t\t\t\t--> Saglik calisanlarina sonsuz tesekkurler!..\n", count);
		printf("%2d. \t\t\t\t\t--> Saglik calisanlarina sonsuz tesekkurler!..\n", count);
		count++;
	}
	fprintf(file, "%2d. (%s) %s ", count, BODY_STRING[part], name);
	printf("%2d. (%s) %s ", count, BODY_STRING[part], name);
	if (count == NUMOFITEMS)
	{
		fprintf(file, "\t--> Goreve hazirim!\n");
		printf("\t--> Goreve hazirim!\n");
		count++;
	}
	else if (count >= 7)
	{
		fprintf(file, "\t--> Kalan oge sayisi: %2d\n", NUMOFITEMS - count);
		printf("\t--> Kalan oge sayisi: %2d\n", NUMOFITEMS - count);
		count++;
	}
	else
	{
		fprintf(file, "\n");
		printf("\n");
		count++;
	}
	fclose(file);
}

void funcHEAD(int p)
{
	sem_wait(semaphore_head);
	// critical section
	dressItem(p, "YuzDezenfektani          ");
	sem_wait(semaphore_head);
	dressItem(p, "SaglikMaskesi            ");
	dressItem(p, "Bone                     ");
	sem_post(semaphore_body);
	sem_wait(semaphore_head);
	dressItem(p, "KoruyucuPlastikYuzMaskesi");
}

void funcUBDY(int p)
{ // starting thread
	sem_wait(semaphore_body);
	// critical section
	dressItem(p, "Atlet                    ");
	dressItem(p, "Gomlek                   ");
	sem_post(semaphore_foot);
	sem_wait(semaphore_body);
	dressItem(p, "Tulum                    ");
	sem_post(semaphore_head);
}

void funcHAND(int p)
{
	sem_wait(semaphore_hand);
	// critical section
	dressItem(p, "ElDezenfektani           ");
	dressItem(p, "Eldiven                  ");
	sem_post(semaphore_head);
}

void funcLEG_(int p)
{
	sem_wait(semaphore_leg);
	// critical section
	dressItem(p, "Pantolon                 ");
	dressItem(p, "Kemer                    ");
	sem_post(semaphore_foot);
}

void funcFOOT(int p)
{
	sem_wait(semaphore_foot);
	// critical section
	dressItem(p, "Corap                    ");
	sem_post(semaphore_leg);
	sem_wait(semaphore_foot);
	dressItem(p, "Ayakkabi                 ");
	sem_post(semaphore_head);
	sem_post(semaphore_hand);
}

int main(int argc, char *argv[])
{ // thread refs
	pthread_t t1, t2, t3, t4, t5;
	// semaphore init for thread synchronization
	// Start body immediately others will wait for signal
	// used named semaphores instead unnamed
	// unlink existing semaphores first.
	sem_unlink("semaphore_body");
	sem_unlink("semaphore_foot");
	sem_unlink("semaphore_leg");
	sem_unlink("semaphore_head");
	sem_unlink("semaphore_hand");
	semaphore_body = sem_open("semaphore_body", O_CREAT, S_IRWXU, 1);
	if (semaphore_body == SEM_FAILED)
	{
		perror("semaphore_body failed");
		return 1;
	}
	semaphore_foot = sem_open("semaphore_foot", O_CREAT, S_IRWXU, 0);
	if (semaphore_foot == SEM_FAILED)
	{
		perror("semaphore_foot failed");
		return 1;
	}
	semaphore_leg = sem_open("semaphore_leg", O_CREAT, S_IRWXU, 0);
	if (semaphore_leg == SEM_FAILED)
	{
		perror("semaphore_leg failed");
		return 1;
	}
	semaphore_head = sem_open("semaphore_head", O_CREAT, S_IRWXU, 0);
	if (semaphore_head == SEM_FAILED)
	{
		perror("semaphore_head failed");
		return 1;
	}
	semaphore_hand = sem_open("semaphore_hand", O_CREAT, S_IRWXU, 0);
	if (semaphore_hand == SEM_FAILED)
	{
		perror("semaphore_hand failed");
		return 1;
	}
	// run threads
	pthread_create(&t1, NULL, funcUBDY, (void *)UBDY);
	pthread_create(&t2, NULL, funcFOOT, (void *)FOOT);
	pthread_create(&t3, NULL, funcLEG_, (void *)LEG_);
	pthread_create(&t4, NULL, funcHAND, (void *)HAND);
	pthread_create(&t5, NULL, funcHEAD, (void *)HEAD);
	// wait for threads to finish
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);

	sem_close(semaphore_body);
	sem_close(semaphore_head);
	sem_close(semaphore_leg);
	sem_close(semaphore_hand);
	sem_close(semaphore_foot);

	return 0;
}