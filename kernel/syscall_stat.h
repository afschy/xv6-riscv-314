struct syscall_stat {
    struct spinlock lock;
    char name[16];
    int count;
    int time;
};

enum syscall_arg_type{INT, PTR, STR, VOID};