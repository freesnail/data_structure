#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definition of ring buffer
typedef struct ring_buffer{
	char *buffer;      //buffer to store the data
	int in_pos;	   //flag to track the input pointer
	int out_pos;       //flag to track the output point
	int size;	   //buffer size
	int data_num;	   //the used buffer size
}rbuffer;


int init_ring_buffer(rbuffer * rbuf, int size) //init buffer
{
	rbuf->buffer = (char *)malloc(size * sizeof(char));
	if(rbuf->buffer == NULL){
		printf("Cannot allocte memory!\n");
		exit(1);
	}

	rbuf->in_pos = 0;
	rbuf->out_pos = 0;
	rbuf->data_num = 0
	rbuf->size = size;
	
	return 0;
}

rbuffer *input_data(rbuffer *rbuf, char *buf, int len) //input data
{	
	if(len <= 0)
		return rbuf;

	if(len < rbuf->size - rbuf->in_pos){
		memcpy(rbuf->buffer + rbuf->in_pos, buf, len);
		rbuf->in_pos += len;
	}
	else{
		memcpy(rbuf->buffer + rbuf->in_pos, buf, rbuf->size - rbuf->in_pos);
		memcpy(rbuf->buffer, buf + rbuf->size - rbuf->in_pos, len - (rbuf->size - rbuf->in_pos));
		rbuf->in_pos = len - (rbuf->size - rbuf->in_pos);
	}

	rbuf->data_num += len;

	return rbuf;
}

rbuffer *output_data(rbuffer *rbuf, char *buf, int len)  //out put data
{
	if(len <= 0)
		return rbuf;

	if(len > rbuf->data_num){
		printf("No enough data!\n");
		return rbuf;
	}
	if(len < rbuf->size - rbuf->out_pos){
		memcpy(buf, rbuf->buffer + rbuf->out_pos, len);
		rbuf->out_pos += len;
	}	
	else{
		memcpy(buf, rbuf->buffer + rbuf->out_pos, rbuf->size - rbuf->out_pos);
		memcpy(buf +  rbuf->size - rbuf->out_pos, rbuf->buffer, len - (rbuf->size - rbuf->out_pos));
		rbuf->out_pos = len - rbuf->out_pos;
	}

	rbuf->data_num -= len;

	return rbuf;
}

void show_buf(char *buf, int num)
{
	int i;
	for(i = 0; i < num; i++){
		printf("%d  ", buf[i]);
	}
	printf("\n");
}

int main()
{
	int ret;
	char testbuf1[3] = {1, 2, 3};
	char testbuf2[5] = {1, 2, 3, 4, 5};
	char outbuf[5];
	rbuffer *mbuf;
	
	mbuf = (rbuffer *)malloc(sizeof(rbuffer));	
	if(ret = init_ring_buffer(mbuf, 5) !=0){
		printf("malloc error\n");
		return 1;
	}

	mbuf = input_data(mbuf, testbuf1, 2 );
	show_buf(mbuf->buffer, 5);
	
	mbuf = input_data(mbuf, testbuf2, 5 );
	show_buf(mbuf->buffer, 5);

	mbuf = output_data(mbuf, outbuf, 2);
	show_buf(outbuf,2);	
	mbuf = output_data(mbuf, outbuf, 2);
	show_buf(outbuf,2);	
	mbuf = output_data(mbuf, outbuf, 4);
	show_buf(outbuf,4);	

	return 0;
}
