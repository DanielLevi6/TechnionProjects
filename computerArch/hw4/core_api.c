/* 046267 Computer Architecture - Spring 2020 - HW #4 */

#include "core_api.h"
#include "sim_api.h"
#include <stdio.h>

typedef enum {idle = 0,
			running = 1,
			halt = 2 }__state;

typedef struct _thread{
	int inst_offset;
	int clocks;
	int latency_to_wait;
	tcontext regs;
	__state state;
}thread;			

/* static functions */
static bool proccess_finished(thread **threads);
static bool thread_available(thread *current_thread);
static void update_latency(thread **threads , int current_thread);

/* static variables */
static thread ** threads = NULL;

static int instructions_of_FinegrainedMT = 0;
static int instructions_of_BlockedMT = 0;
static int clocks_of_FinegrainedMT = 0;
static int cycle_of_BlockedMT = 0;
static int num_of_threads;

int store_latency;
int load_latency;
int cycles_per_switch;

static bool switch_flag = false;

void CORE_BlockedMT() {

	num_of_threads = SIM_GetThreadsNum();
	store_latency = SIM_GetStoreLat();
	load_latency = SIM_GetLoadLat();
	cycles_per_switch = SIM_GetSwitchCycles();

	/* creating the threads context database */
	threads = (thread**)malloc(sizeof(thread*)*num_of_threads);
	for(int i=0; i<num_of_threads; i++){
		threads[i] = (thread*)malloc(sizeof(thread));
		threads[i]->inst_offset = 0;
		threads[i]->clocks = 0;
		threads[i]->state = idle;
		threads[i]->latency_to_wait=0;
		/* initialize all registers to 0 */
		for(int j=0; j<REGS_COUNT; j++)
			threads[i]->regs.reg[j] = 0;
				
	}
	int current_thread = 0;

	while(!proccess_finished(threads)){
		
		/* check if current_thread can be executed, otherwise switch*/
		if(!thread_available(threads[current_thread]) || switch_flag){

			/* check if we can exucute diffrent thread*/
			int i = (current_thread+1)%num_of_threads;
			while(i != current_thread){
				if(thread_available(threads[i])) break;
				i = (i+1)%num_of_threads;
			}
			if( i == current_thread){
				/* nothing to be executed so we wait a one cycle and update latencies to wait */
				
				/* meaning update every thread */
				update_latency(threads , num_of_threads);
				threads[current_thread]->clocks++;
  				cycle_of_BlockedMT++;

				if(threads[current_thread]->latency_to_wait==0)
				{
					switch_flag=false;
				}
				continue;
			}
			else {
				current_thread = i;
				cycle_of_BlockedMT+=cycles_per_switch;
				for(int j=0;j<cycles_per_switch;j++)
				{
					update_latency(threads, current_thread);
				}
			}
			switch_flag=false;
		}
		
		
		
		Instruction this_inst;
		SIM_MemInstRead(threads[current_thread]->inst_offset, &this_inst, current_thread);
		
		switch(this_inst.opcode){
			/* nop */
			case 0:
				/* do nothing */
				break;
			
			/* add */
			case 1:
				/* update registers */
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] +
																 threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				break;
			
			/* sub */
			case 2:	
				/* update registers */				
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] -
																 threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				break;

			/* addi */
			case 3:
				/* update registers */
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] +
																 this_inst.src2_index_imm;
				break;

			/* subi */
			case 4:
				/* update registers */
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] -
																 this_inst.src2_index_imm;
				break;

			/*load */
			case 5:
				/* put the thread in idle and set latency_to_wait */
				threads[current_thread]->state = idle;
				threads[current_thread]->latency_to_wait = load_latency;
				
				/* preparing arguments to read function */
				int32_t *dst = &(threads[current_thread]->regs.reg[this_inst.dst_index]);
				uint32_t memory_address = threads[current_thread]->regs.reg[this_inst.src1_index];
				if(this_inst.isSrc2Imm) memory_address+=this_inst.src2_index_imm;
				else memory_address+=threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				
				SIM_MemDataRead(memory_address, dst);			
				switch_flag = true;
				break;
				
			/* store */
			case 6:
				/* put the thread in idle and set latency_to_wait */
				threads[current_thread]->state = idle;
				threads[current_thread]->latency_to_wait = store_latency;
				
				/* preparing arguments to read function */
				int32_t val = threads[current_thread]->regs.reg[this_inst.src1_index];
				memory_address = threads[current_thread]->regs.reg[this_inst.dst_index];
				if(this_inst.isSrc2Imm) memory_address+=this_inst.src2_index_imm;
				else memory_address+=threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				
				SIM_MemDataWrite(memory_address, val);
				switch_flag = true;
				break;
			
			/* halt */
			case 7:
				threads[current_thread]->state = halt;
				switch_flag = true;
				break;			
		}
		
		update_latency(threads , current_thread);
		threads[current_thread]->inst_offset+=1;
		threads[current_thread]->clocks++;
		instructions_of_BlockedMT++;
		cycle_of_BlockedMT++;
		
	}
	
	return;
}

void CORE_FinegrainedMT() {
		
	num_of_threads = SIM_GetThreadsNum();
	store_latency = SIM_GetStoreLat();
	load_latency = SIM_GetLoadLat();
	cycles_per_switch = SIM_GetSwitchCycles();

	/* creating the threads context database */
	threads = (thread**)malloc(sizeof(thread*)*num_of_threads);
	for(int i=0; i<num_of_threads; i++){
		threads[i] = (thread*)malloc(sizeof(thread));
		threads[i]->inst_offset = 0;
		threads[i]->clocks = 0;
		threads[i]->state = idle;
		threads[i]->latency_to_wait=0;
		/* initialize all registers to 0 */
		for(int j=0; j<REGS_COUNT; j++)
			threads[i]->regs.reg[j] = 0;
				
	}
	int current_thread = 0;
	
	while(!proccess_finished(threads)){
		
		/* check if current_thread can be executed, otherwise switch*/
		if(!thread_available(threads[current_thread])){
			
			/* check if we can exucute diffrent thread*/
			int i = (current_thread+1)%num_of_threads;
			while(i != current_thread){
				if(thread_available(threads[i])) break;
				i = (i+1)%num_of_threads;
			}
			if( i == current_thread){
				/* nothing to be executed so we wait a one cycle and update latencies to wait */ 
				
				/* meaning update every thread */
				update_latency(threads , num_of_threads);
				//threads[current_thread]->inst_offset+=0x4;
				threads[current_thread]->clocks++;
				//instructions_of_FinegrainedMT++;
				clocks_of_FinegrainedMT++;
				continue;
			}
			else current_thread = i;
		}
		
		
		
		Instruction this_inst;
		SIM_MemInstRead(threads[current_thread]->inst_offset, &this_inst, current_thread);
		
		switch(this_inst.opcode){
			/* nop */
			case 0:
				/* do nothing */
				break;
			
			/* add */
			case 1:
				/* update registers */
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] +
																 threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				break;
			
			/* sub */
			case 2:	
				/* update registers */				
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] -
																 threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				break;

			/* addi */
			case 3:
				/* update registers */
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] +
																 this_inst.src2_index_imm;
				break;

			/* subi */
			case 4:
				/* update registers */
				threads[current_thread]->regs.reg[this_inst.dst_index]=threads[current_thread]->regs.reg[this_inst.src1_index] -
																 this_inst.src2_index_imm;
				break;

			/*load */
			case 5:
				/* put the thread in idle and set latency_to_wait */
				threads[current_thread]->state = idle;
				threads[current_thread]->latency_to_wait = load_latency;
				
				/* preparing arguments to read function */
				int32_t *dst = &(threads[current_thread]->regs.reg[this_inst.dst_index]);
				uint32_t memory_address = threads[current_thread]->regs.reg[this_inst.src1_index];
				if(this_inst.isSrc2Imm) memory_address+=this_inst.src2_index_imm;
				else memory_address+=threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				
				SIM_MemDataRead(memory_address, dst);			

				break;
				
			/* store */
			case 6:
				/* put the thread in idle and set latency_to_wait */
				threads[current_thread]->state = idle;
				threads[current_thread]->latency_to_wait = store_latency;
				
				/* preparing arguments to read function */
				int32_t val = threads[current_thread]->regs.reg[this_inst.src1_index];
				memory_address = threads[current_thread]->regs.reg[this_inst.dst_index];
				if(this_inst.isSrc2Imm) memory_address+=this_inst.src2_index_imm;
				else memory_address+=threads[current_thread]->regs.reg[this_inst.src2_index_imm];
				
				SIM_MemDataWrite(memory_address, val);

				break;
			
			/* halt */
			case 7:
				threads[current_thread]->state = halt;
				break;			
		}
		
		update_latency(threads , current_thread);
		threads[current_thread]->inst_offset+=1;
		threads[current_thread]->clocks++;
		instructions_of_FinegrainedMT++;
		clocks_of_FinegrainedMT++;
		
		current_thread = (current_thread + 1)%num_of_threads;
	
	}
	
	return;
}














double CORE_BlockedMT_CPI(){
	
	for (int i = 0; i < num_of_threads; i++)
	{
		free(threads[i]);
	}
	free(threads);
	return (double)cycle_of_BlockedMT / (double)instructions_of_BlockedMT;
}

double CORE_FinegrainedMT_CPI(){
	for (int i = 0; i < num_of_threads; i++)
	{
		free(threads[i]);
	}
	free(threads);
	return (double)clocks_of_FinegrainedMT / (double)instructions_of_FinegrainedMT ;
}

void CORE_BlockedMT_CTX(tcontext* context, int threadid) {
	for(int i=0; i<REGS_COUNT; i++){
		context->reg[threadid * REGS_COUNT + i]=threads[threadid]->regs.reg[i];
	}
}

void CORE_FinegrainedMT_CTX(tcontext* context, int threadid) {
	for(int i=0; i<REGS_COUNT; i++){
		context->reg[threadid * REGS_COUNT + i]=threads[threadid]->regs.reg[i];
	}
}

/* check if still have threads to run */
static bool proccess_finished(thread **threads){
		int num_of_threads = SIM_GetThreadsNum();
		for(int i=0;i<num_of_threads;i++){	
			if(threads[i]->state != halt) return false;
		}
		return true;
}

/* check if current_thread can be executed */
static bool thread_available(thread *current_thread){
		if(current_thread->state==halt){
			return false;
		}
		if(current_thread->state==idle){
			
			/* still have to wait for memory to arrive */
			if(current_thread->latency_to_wait !=0){
				return false;
			}
			else{
				current_thread->state = running;
				return true;
			}
		}
		return true;		
}

/* update all threds latency_to_wait */ 
static void update_latency(thread **threads , int current_thread){
	
	int num_of_threads = SIM_GetThreadsNum();
	for(int i=0;i<num_of_threads;i++){
		/* update everyone but current_thread */
		if(i != current_thread){
			if(threads[i]->state == idle){
				int latency = threads[i]->latency_to_wait;
				if(latency > 0){
					latency--;
					if(latency == 0){
						threads[i]->latency_to_wait = 0;
						threads[i]->state = running;
					}
					else threads[i]->latency_to_wait--;	
				}	
			}
		}
	}
}

