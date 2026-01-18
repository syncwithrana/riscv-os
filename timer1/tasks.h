void taskA(void);
void taskB(void);
void taskC(void);
void init_task(int i, void (*fn)(void));
void schedule(void);
void task_switch(void);