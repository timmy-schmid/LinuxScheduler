#include "sched.h"
#include "linux/list.h"
#include "linux/types.h"

const struct sched_class comp3520_sched_class;

//100ms for HZ = 100 in Arm. 100 * HZ / 1000
#define TIMESLICE (1)

// DONE
static inline struct task_struct * comp3520_task_of(struct comp3520_sched_entity *se)
{
	return container_of(se, struct task_struct, comp3520_se);
}

// TODO: Complete me
static void enqueue_task_comp3520(struct rq *rq, struct task_struct *p,
				  int flags)
{
    //printk ("ENQUEUE_TASK_COMP3520\n"); 
    struct list_head *queue = &rq->comp3520_rq.queue;
    struct comp3520_sched_entity *se = &p->comp3520_se;
    //printk("--Enqueing sched ent : %px\n",&se->run_list);
    //printk ("  -Task pointer: %px\n",p); 
    //printk ("  -Task pid: %d\n",p->pid); 

    //if (se->on_rq) {
        //printk("On run queue! aborting enqueue\n");
        //return;
    //}

    list_add_tail(&se->run_list, queue);
    rq->comp3520_rq.nr_running++;
    add_nr_running(rq, 1);
    se->on_rq = true;

    se->time_slice = TIMESLICE;

    //PRINT QUEUE
    struct list_head *position = NULL ; 
    struct comp3520_sched_entity  *entity  = NULL ;
    int i = 1;
    //printk ("current run_list queue of se after enqueue:\n"); 
    /*list_for_each (position , queue) { 
         entity = list_entry(position, struct comp3520_sched_entity,run_list);
         printk ("  -%d | %px | PID:%d \n",i,entity, comp3520_task_of(entity)->pid); 
         i++;
    }*/
    
}

// TODO: Complete me
static void dequeue_task_comp3520(struct rq *rq, struct task_struct *p,
				  int flags)
{

    //printk ("DEQUEUE_TASK_COMP3520\n"); 
    struct comp3520_sched_entity *se = &p->comp3520_se;
    //printk("--Dequeing sched ent : %px\n",&se->run_list);
    //printk ("  -Task pointer: %px\n",p); 
    //printk ("  -Task pid: %d\n",p->pid); 

    if (!se->on_rq) {
        return;
    }

    list_del(&se->run_list);
    rq->comp3520_rq.nr_running--;
    sub_nr_running(rq, 1);
    se->on_rq = false;
    
    //PRINT QUEUE
    struct list_head *queue = &rq->comp3520_rq.queue;
    struct list_head *position = NULL ; 
    struct comp3520_sched_entity  *entity  = NULL ;
    int i = 1;
    //printk ("current run_list queue of se after dequeue\n:"); 
    /*
    list_for_each (position , queue) { 
         entity = list_entry(position, struct comp3520_sched_entity,run_list);
         printk ("  -%d | %px | PID:%d \n",i,entity, comp3520_task_of(entity)->pid); 
         i++;
    }*/
}

// TODO: Complete me
static void yield_task_comp3520(struct rq *rq)
{
};

// TODO: Complete me
static void check_preempt_curr_comp3520(struct rq *rq, struct task_struct *p,
					int wake_flags)
{
}

// TODO: Complete me
static void set_next_task_comp3520(struct rq *rq, struct task_struct *p, bool first)
{
}

// TODO: Complete me
static void task_tick_comp3520(struct rq *rq, struct task_struct *curr,
			       int queued)
{
    //printk ("TASK_TICK_COMP3520\n"); 
    struct comp3520_sched_entity *se = &curr->comp3520_se;
    //printk("TASK: %px\n",curr);
    //printk("SE: %px\n",se);
    
    //printk("  timeslice before: %d\n",se->time_slice);
    se->time_slice--;
    if (se->time_slice)
        return;

    se->time_slice = TIMESLICE;
    struct list_head *queue = &rq->comp3520_rq.queue;
    if (se->run_list.prev != se->run_list.next) {
            if (se->on_rq) {
                list_move_tail(&se->run_list, queue);
            }
			resched_curr(rq);
    }

    //PRINT QUEUE
    struct list_head *position = NULL ; 
    struct comp3520_sched_entity  *entity  = NULL ;
    int i = 1;
    printk ("current run_list queue of se after tick\n"); 
    list_for_each (position , queue) { 
         entity = list_entry(position, struct comp3520_sched_entity,run_list);
         printk ("-%d | %px | PID:%d \n",i,entity, comp3520_task_of(entity)->pid); 
         i++;
    }
    //u64 now = rq->clock_task;
    //u64 elapsed = now - curr->sched_info.last_arrival;
    //se->sum_runtime += elapsed;
    //printk("now: %llu\n",now);
    //printk("elapsed: %llu\n",elapsed);
    //printk("old sum_runtime: %llu\n",se->sum_runtime);
    //if (se->sum_runtime >= time_slice) {
        //se->sum_runtime -= time_slice;
        //printk("new sum_runtime: %llu\n",se->sum_runtime);
        //resched_curr(rq);
    //}
}

// TODO: Complete me
struct task_struct *pick_next_task_comp3520(struct rq *rq)
{
    //printk ("PICK_NEXT_TASK_TICK_COMP3520\n"); 
    struct list_head *queue = &rq->comp3520_rq.queue;

    if (!rq->comp3520_rq.nr_running) {
        return NULL;
    }

    struct comp3520_sched_entity *next = list_entry(queue->next, struct comp3520_sched_entity,run_list);
    //printk ("picking next se: %px\n",next); 
    //printk ("picking next task: %px\n",comp3520_task_of(next));

    struct task_struct *next_task = comp3520_task_of(next);
    //printk ("picking next task pid: %d\n",next_task->pid); 
	return comp3520_task_of(next);
}
// Required by core.c
void put_prev_task_comp3520(struct rq *rq, struct task_struct *prev) {
}

// Required by core.c
void prio_changed_comp3520(struct rq *rq, struct task_struct *task, int oldprio) {
}

const struct sched_class
	comp3520_sched_class __section("__comp3520_sched_class") = {
		.enqueue_task = enqueue_task_comp3520,
		.dequeue_task = dequeue_task_comp3520,
		.yield_task = yield_task_comp3520,
		.check_preempt_curr = check_preempt_curr_comp3520,
		.set_next_task = set_next_task_comp3520,
		.task_tick = task_tick_comp3520,
		.pick_next_task = pick_next_task_comp3520,
        .put_prev_task = put_prev_task_comp3520,
        .prio_changed = prio_changed_comp3520,

#ifdef CONFIG_SMP
		.balance = balance_comp3520,
		.select_task_rq = select_task_rq_comp3520,
		.migrate_task_rq = migrate_task_rq_comp3520,

		.rq_online = rq_online_comp3520,
		.rq_offline = rq_offline_comp3520,

		.task_dead = task_dead_comp3520,
		.set_cpus_allowed = set_cpus_allowed_common,
#endif


#ifdef CONFIG_UCLAMP_TASK
		.uclamp_enabled = 1,
#endif

};

// TODO: Complete me
void init_comp3520_rq(struct comp3520_rq *comp3520_rq)
{  
    //printk ("INIT_COMP3520_rq\n"); 
    INIT_LIST_HEAD(&comp3520_rq->queue);
    //printk ("printing queue head: %px\n",comp3520_rq->queue); 
}

#ifdef CONFIG_SCHED_DEBUG
extern void print_comp3520_stats(struct seq_file *m, int cpu);
extern void print_comp3520_rq(struct seq_file *m, int cpu, struct rt_rq *rt_rq);
#endif
