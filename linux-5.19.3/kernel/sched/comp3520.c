#include "sched.h"
#include "linux/list.h"
#include "linux/types.h"

const struct sched_class comp3520_sched_class;

#define TIMESLICE (10)
#define NO_QUEUES (10)

static inline struct task_struct * comp3520_task_of(struct comp3520_sched_entity *se)
{
	return container_of(se, struct task_struct, comp3520_se);
}

static void enqueue_task_comp3520(struct rq *rq, struct task_struct *p,
				  int flags)
{
    
    struct list_head *queue = &rq->comp3520_rq.queue[0];
    struct comp3520_sched_entity *se = &p->comp3520_se;

    list_add_tail(&se->run_list, queue);
    rq->comp3520_rq.nr_running[0]++;
    add_nr_running(rq, 1);
    se->on_rq = true;

    se->time_slice = TIMESLICE; 
}

static void dequeue_task_comp3520(struct rq *rq, struct task_struct *p,
				  int flags)
{
    struct comp3520_sched_entity *se = &p->comp3520_se;

    if (!se->on_rq) {
        return;
    }

    list_del(&se->run_list);
    rq->comp3520_rq.nr_running[se->queue_no]--;
    sub_nr_running(rq, 1);
    se->on_rq = false;
    se->queue_no = 0;
    
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
    struct comp3520_sched_entity *se = &curr->comp3520_se;
    struct list_head *queue;
    se->time_slice--;
    if (se->time_slice)
        return;

    se->time_slice = TIMESLICE;
    queue = &rq->comp3520_rq.queue[0];
    if (se->run_list.prev != se->run_list.next) {
        // move down a queue lvl if we have not reached the last queue lvl
        if (se->on_rq && se->queue_no < NO_QUEUES) {
            rq->comp3520_rq.nr_running[se->queue_no]--;
            list_move_tail(&se->run_list, &queue[se->queue_no]);
            se->queue_no++;
            rq->comp3520_rq.nr_running[se->queue_no]++;
        }
        resched_curr(rq);
    }
}

struct task_struct *pick_next_task_comp3520(struct rq *rq)
{
    struct list_head *queue = &rq->comp3520_rq.queue[0];
    struct comp3520_sched_entity *next;
    
    for (int i = 0; i < NO_QUEUES ;i++) {
        if (rq->comp3520_rq.nr_running[i] != 0) {
            next = list_entry(queue[i].next, struct comp3520_sched_entity, run_list);
            return comp3520_task_of(next);
        }
    }

    // if there are no active tasks.
    return NULL;
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

void init_comp3520_rq(struct comp3520_rq *comp3520_rq)
{  
    for (int i = 0; i < NO_QUEUES; i++) {
        INIT_LIST_HEAD(comp3520_rq->queue + i);
        comp3520_rq->nr_running[i] = 0;
    }
}

#ifdef CONFIG_SCHED_DEBUG
extern void print_comp3520_stats(struct seq_file *m, int cpu);
extern void print_comp3520_rq(struct seq_file *m, int cpu, struct rt_rq *rt_rq);
#endif
