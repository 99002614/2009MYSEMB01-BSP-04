#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/kfifo.h>
#include<linux/string.h>
#define MAX_SIZE 300

int a,b;
unsigned char *pbuffer;

struct kfifo k;

typedef struct{
char *data;
struct list_head *node;
}LOG; 

LIST_HEAD(list);

ssize_t driv_read(struct file *fp, char __user *buf, size_t len, loff_t *off)
{
	printk("Inside %s function\n", __FUNCTION__);
		
	if(kfifo_is_empty(&k))
		{printk("buffer is empty\n");return 0;}
	if(b>kfifo_len(&k))
		b=kfifo_len(&k);
	
	char *temp=kmalloc(b,GFP_KERNEL);
	kfifo_out(&k,temp,b);
	copy_to_user(buf, temp,b);

	kfree(temp);
	return b;
}
