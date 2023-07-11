//Gamze Nur Madan - 260201084
//Halil İbrahim Buğday - 280201094
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/seq_file.h>
#include <linux/mm.h>

//Module informations
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Group-13, HW4");
MODULE_DESCRIPTION("The kernel module displays detailed information based on the process ID or name it receives from the user.");
MODULE_VERSION("0.13");

static unsigned int upid = 0; //Unsigned, Process ID
static char *upname = ""; //Unsigned, Process Name

// Module parameters
module_param(upid, int, 0); //module parameter name, type, permission mask
MODULE_PARM_DESC(upid, "Process ID"); // Module description
module_param(upname, charp, 0);
MODULE_PARM_DESC(upname, "Process name");

// Function to get task_struct based on PID
static struct task_struct *getTaskByPid(unsigned int pid) {
    return pid_task(find_vpid(pid), PIDTYPE_PID); //object that detects the process id
}

// Function to get task_struct based on process name
static struct task_struct *getTaskByName(const char *name) {
    struct task_struct *task = NULL; //variable that represents an operation.
    struct task_struct *pos = NULL; //loop variable representing an operation.

//comm variable representing the process name
    for_each_process(pos) {
        if (strcmp(pos->comm, name) == 0) {
            task = pos;
            break;
        }
    }
    return task;
}

// Function to print process information
static void printProcessInfo(struct seq_file *m, struct task_struct *task) {
    struct mm_struct *mm = task->mm; //variable representing memory management information.
    unsigned long rss = 0; //Resident set size
    int taskState = task_state_index(task); //convert state to index value


    seq_printf(m, "Name: %s\n", task->comm); //prints the process name
    seq_printf(m, "PID: %d\n", task->pid); //prints the process ID
    seq_printf(m, "PPID: %d\n", task->real_parent->pid); // prints the parent process ID
    seq_printf(m, "UID: %d\n", from_kuid(&init_user_ns, task->cred->uid)); //prints the user ID of the process
    seq_printf(m, "Path: /proc/%d\n", task->pid); //prints the path of the process in the /proc directory
    seq_printf(m, "State: %d\n", taskState); // prints the state of the process

    // running process states
    if (taskState == TASK_RUNNING) {
        rss = get_mm_rss(mm); //calculate the memory usage associated with the mm_struct structure -> get_mm_rss
        // calculated memory usage in kilobytes
        seq_printf(m, "Memory Usage: %lu KB\n", rss * PAGE_SIZE / 1024);
    else {
        seq_printf(m, "Memory Usage: None (Process is not running)\n");
    }
}

// function to display process information based on user input
static int displayProcInfo(struct seq_file *m, void *v) {
    struct task_struct *task = NULL;
    int errorCode = 0;

    if (upid != 0) {
        task = getTaskByPid(upid);
        if (task == NULL) {
            seq_printf(m, "Process with ID not found\n");
            pr_err("Error: Process with ID not found\n");
            errorCode = -ENOENT; // entry not found
            goto out;
        }
    } else if (strlen(upname) != 0) {
        task = getTaskByName(upname);
        if (task == NULL) {
            seq_printf(m, "Process with name %s not found\n", upname);
            pr_err("Error: Process with name not found\n");
            errorCode = -ENOENT;
            goto out;
        }
    } else {
        seq_printf(m, "Either correct process ID or name must be provided!\n");
        pr_err("Error: Either correct process ID or name must be provided!\n");
        errorCode = -EINVAL; // invalid argument
        goto out;
    }
    printProcessInfo(m, task);
out:
    return errorCode;
}

// function to open the proc file
static int procInfoOpen(struct inode *inode, struct file *file) {
    return single_open(file, displayProcInfo, NULL);
}
// file operations for the proc file
static const struct proc_ops procInfoFops = {
    .proc_open = procInfoOpen, // specifies the function to be called when the proc file is opened.
    .proc_read = seq_read, // specifies the function that performs the read operation from the seq file.
    .proc_lseek = seq_lseek, // specifies the function that performs the seek operation within the seq file.
    .proc_release = single_release, // specifies the function to be called when the proc file is closed.
};

// module initialization function
static int __init procInfoInit(void) {
    struct proc_dir_entry *entry;

// create the proc file
    entry = proc_create("proc_info_module", 0666, NULL, &procInfoFops);
    if (!entry) {
        pr_err("Failed to create proc_info_module\n");
        return -ENOMEM; // out of memory
    }
    return 0;
}
// module exit function
static void __exit procInfoExit(void) {
    // remove the proc file
    remove_proc_entry("proc_info_module", NULL);
}

module_init(procInfoInit);
module_exit(procInfoExit);
