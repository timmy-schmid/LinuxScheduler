#include "sched.h"
#include "linux/list.h"
#include "linux/types.h"

const struct sched_class comp3520_sched_class;

/*
// I have set this to 100 milliseconds. HZ is defined to be the HZ of the chip.
// Arm is HZ rate of 1/100.
// See: http://books.gigatux.nl/mirror/kerneldevelopment/0672327201/ch10lev1sec2.html
*/

#define TIMESLICE (100 * 100 / 1000)

// DONE
static inline struct task_struct * comp3520_task_of(struct comp3520_sched_entity *se)
{
	return container_of(se, struct task_struct, comp3520_se);
}

// TODO: Complete me
static void enqueue_task_comp3520(struct rq *rq, struct task_struct *p,
				  int flags)
{
    
    struct list_head *queue = &rq->comp3520_rq.queue;
    struct comp3520_sched_entity *se = &p->comp3520_se;
    list_add_tail(&se->run_list, queue);

    rq->comp3520_rq.nr_running++;
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
    rq->comp3520_rq.nr_running--;
    sub_nr_running(rq, 1);
    se->on_rq = false;
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

static void task_tick_comp3520(struct rq *rq, struct task_struct *curr,
			       int queued)
{
    struct comp3520_sched_entity *se = &curr->comp3520_se;
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
}

struct task_struct *pick_next_task_comp3520(struct rq *rq)
{
    struct list_head *queue = &rq->comp3520_rq.queue;

    if (!rq->comp3520_rq.nr_running) {
        return NULL;
    }

    struct comp3520_sched_entity *next = list_entry(queue->next,
                                        struct comp3520_sched_entity,run_list);

    struct task_struct *next_task = comp3520_task_of(next);
	return comp3520_task_of(next);
}
// Required by core.c
void put_prev_task_comp3520(struct rq *rq, struct task_struct *prev) {
}

// Required by core.c
void prio_changed_comp3520(struct rq *rq, struct task_struct *task, int oldprio) {
}

// Required by core.c
void update_curr_comp3520(struct rq *rq) {
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
        .update_curr = update_curr_comp3520,
        

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
    INIT_LIST_HEAD(&comp3520_rq->queue);
}


#ifdef CONFIG_SCHED_DEBUG
extern void print_comp3520_stats(struct seq_file *m, int cpu);
extern void print_comp3520_rq(struct seq_file *m, int cpu, struct rt_rq *rt_rq);
#endif
