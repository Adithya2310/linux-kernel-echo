#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL"); //*
MODULE_AUTHOR("ADITHYA"); //!
MODULE_DESCRIPTION("A KERNEL DRIVER"); //!

static struct proc_dir_entry *custom_proc_node;

static ssize_t custom_read(struct file * file_name, char *user_space_buffer, size_t count, loff_t* offset){
    char msg[] = "Ack!\n";
    size_t len=strlen(msg);
    int res;


    if(*offset>=len) 
        return 0;

    res = copy_to_user(user_space_buffer, msg, len);
    *offset+=len;

    printk(KERN_INFO "KERNEL PROC FS READ: ENTRY\n");
    
    return len;
}

static ssize_t custom_write(struct file * file_name, const char __user *user_space_buffer, size_t count, loff_t* offset){
    char kernel_buffer[128];
    size_t len;
    int res;

    len = count < sizeof(kernel_buffer) - 1 ? count : sizeof(kernel_buffer) - 1;

    if(*offset>=len) 
        return 0;

    res = copy_from_user(kernel_buffer, user_space_buffer, len);
    *offset+=len;

    printk(KERN_INFO "KERNEL PROC FS WRITE: %s\n", kernel_buffer);
    
    return len;
}

struct proc_ops driver_proc_ops = {
    .proc_read = custom_read,
    .proc_write = custom_write
};

static int kernel_driver_module_init(void){
    printk(KERN_INFO "KERNEL DRIVER LOADED: ENTRY");
    custom_proc_node = proc_create("kernel_driver", 0666, NULL, &driver_proc_ops);

    if(custom_proc_node == NULL)
    {
        printk(KERN_INFO "KERNEL DRIVER LOADED: EXIT");
        return -1;
    }

    printk(KERN_INFO "KERNEL DRIVER LOADED: EXIT");
    return 0;
}

static void kernel_driver_module_exit(void){
    printk(KERN_INFO "KERNEL DRIVER UNLOADED: ENTRY");
    proc_remove(custom_proc_node);
    printk(KERN_INFO "KERNEL DRIVER UNLOADED: EXIT");
}

module_init(kernel_driver_module_init);
module_exit(kernel_driver_module_exit);