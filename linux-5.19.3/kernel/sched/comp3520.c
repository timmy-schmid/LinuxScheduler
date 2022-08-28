#include "sched.h"
#include "linux/list.h"
#include "linux/types.h"

const struct sched_class comp3520_sched_class;

// TODO: Complete me
static void enqueue_task_comp3520(struct rq *rq, struct task_struct *p,
				  int flags)
{
}

// TODO: Complete me
static void dequeue_task_comp3520(struct rq *rq, struct task_struct *p,
				  int flags)
{
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
}

// TODO: Complete me
struct task_struct *pick_next_task_comp3520(struct rq *rq)
{
	return NULL;
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
static inline struct task_struct * comp3520_task_of(struct sched_comp3520_entity *se)
{
	return NULL;
}

// TODO: Complete me
void init_comp3520_rq(struct comp3520_rq *comp3520_rq)
{
}

#ifdef CONFIG_SCHED_DEBUG
extern void print_comp3520_stats(struct seq_file *m, int cpu);
extern void print_comp3520_rq(struct seq_file *m, int cpu, struct rt_rq *rt_rq);
#endif
