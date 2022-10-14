#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
typedef struct node
{
	int data;
	struct node *next;
}node_t;
typedef node_t *list_t;
list_t head=NULL;
void *product(void *arg)
{
	while(1)
	{
		//产节点；
	    node_t *new;
	    new=(node_t *)malloc(sizeof(node_t));
	    new->data=rand()%1000+1;
	    new->next=NULL;
	    printf("p:%d\n",new->data);
	    pthread_mutex_lock(&mutex);
	    new->next=head;
	    head=new;
	    pthread_mutex_unlock(&mutex);
	    pthread_cond_signal(&cond);
	    sleep(rand()%3+1);
	}
	return NULL;
}
void *consume(void *arg)
{
	node_t *tmp;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(head==NULL)
		pthread_cond_wait(&cond,&mutex);
		tmp=head;
		head=head->next;
		pthread_mutex_unlock(&mutex);
		printf("c:%d\n",tmp->data);
		free(tmp);
		tmp=NULL;
		sleep(rand()%3+1);
		}
	return NULL;
}

int main(void)
{
	srand(time(NULL));
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_t pid,cid;
	pthread_create(&pid,NULL,product,NULL);
	pthread_create(&cid,NULL,consume,NULL);
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);
	pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);  
	return 0;
}
