#include <bits/stdc++.h>
void synchronization();
int dining_philosophers();
int producer_consumer();
int move(struct producer_info *arr, int k, int total);
void consume(int *empty, int *full, int *mutex);
void produce(int *empty, int *full, int *mutex);
void reader_writer();
void read(int *mutex);
void write(int *mutex);
void signal(int *s);
void wait(int *s);
void swap(int a[], int i, int j);
void sort_bub(int a[], int n);
void CLOOK();
void CSCAN();
void FCFS();
void LOOK();
void SCAN();
void SSTF();
void dine(int *chopsticks, int i, int n);

void FCFS_sche();
void LJFS();
void LRTF();
void RR();
void SJFS();
void SRTF();
void mft_main();
void insert_process_wf(int index, int process_size,std::vector <int> &partition, int *num_occupied_process, int *num_partitions, int *accomodated, int *n);
void insert_process_bf(int index, int process_size,std::vector <int> &partition, int *num_occupied_process, int *num_partitions, int *accomodated, int*n);
void insert_process_ff(int index, int process_size,std::vector <int> &partition, int *num_occupied_process, int *num_partitions, int *accomodated, int *n);
void mvt();
void insert_process_ff1(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int *n);
void insert_process_bf1(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int*n);
void insert_process_wf1(int index, int process_size, int *memory, int *num_partitions, int *accomodated, int *n);
void pg_rep();
int page_replacement();
int fifo_offset();
int optimal_replacement();
int lru_mru_replacement(int function);
int fifo_replacement();
void print_chart(int matrix_t[][100], int string_t[],int number_f,int string_count);
int qdelete();
void qinsert(int data, int size);
void prem_prio_sche();
void non_pre();
void HRRN();
void bankers();
int bankers_algo();
void wait1(int *s);
void signal1(int *s);
void execute(int *comp, int i, int *mutex, int *flag);