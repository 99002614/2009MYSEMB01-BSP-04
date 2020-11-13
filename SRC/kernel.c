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
ssize_t driv_write (struct file *fp, const char __user *buf, size_t len, loff_t *off)
{
	printk("Inside %s function\n", __FUNCTION__);
	
	a=len;
	
	if(kfifo_is_full(&k))
		{printk("storage full\n");return -ENOSPC;}
	if(a>kfifo_avail(&k))
		{a=kfifo_avail(&k);}
	
	
	LOG *log=kmalloc(sizeof(LOG),GFP_KERNEL);
	log->data = kmalloc(a,GFP_KERNEL);
	
	
	char *temp = kmalloc(a,GFP_KERNEL);
	copy_from_user(temp,buf,a);
	strcpy(log->data,temp);
	printk("\n%s\n",log->data);
	kfifo_in(&k,temp,a);
			
	kfree(temp);
	list_add_tail((log->node),&list);
	
	
	return a;
}
int driv_open(struct inode *node, struct file *fp)
{
	printk("Inside %s function\n", __FUNCTION__);
	return 0;
}

int driv_close(struct inode *node, struct file *fp)
{
	printk("Inside %s function\n", __FUNCTION__);
	return 0;
}

struct file_operations driv_fop={
.owner=THIS_MODULE,
.open=driv_open,
.write=driv_write,
.read=driv_read,
.release=driv_close,
};

int driv_init(void)
{
printk("welcome driv\n", __FUNCTION__);
register_chrdev(257,"mad",&driv_fop);
pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);
kfifo_init(&k,pbuffer,MAX_SIZE);
return(0);
}
