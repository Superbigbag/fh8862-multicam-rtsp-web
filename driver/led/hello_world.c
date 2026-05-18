#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/kernfs.h>
#include <linux/device.h>   // 头文件：自动创建节点


#define GPIO_NUM (43)  /* 待操作的gpio管脚 */

/* ioctl命令行 */
#define LED_IOC_MAGIC 'L'
#define SET_LED_OFF    _IO(LED_IOC_MAGIC, 1) //开灯指令
#define SET_LED_ON     _IO(LED_IOC_MAGIC, 2) //关灯指令

enum led_stat { 
	LED_OFF = 0x0,
	LED_ON,
};

/* 假设有个全局的内核资源 */
static int g_data = 5;





/*文件打开函数*/
int hello_open(struct inode *inode, struct file *filp)
{    
    return 0; //这个是个空函数，默认都能成功打开
}

/*文件释放函数*/
int hello_release(struct inode *inode, struct file *filp)
{
    return 0; //这个是个空函数，默认都能成功打开
}

/*读函数*/
static ssize_t hello_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
  /* 将内核空间的数据copy到用户空间 */
    if (copy_to_user(buf, &g_data, size)) {
        return -EFAULT;
		
    }
	
    return size;
}

/*写函数*/
static ssize_t hello_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{   
    /* 将用户空间数据copy到内核空间 */
    if (copy_from_user(&g_data, buf, size)) {
        return -EFAULT;
    }
 
    return size;
}

/* ioctl函数 */
static long hello_ioctl( struct file *filp, unsigned int cmd, unsigned long arg)
{	
	long ret = 0;

	/* check IOCTL command magic */
	if (_IOC_TYPE(cmd) != LED_IOC_MAGIC) {
		printk("[%s] invalid arg!\n", __func__);
        return -ESRCH;
	}
	
	switch (cmd) { 
        case SET_LED_ON:
			gpio_direction_output(GPIO_NUM, LED_ON); //点亮该led
			break;
        case SET_LED_OFF:
			gpio_direction_output(GPIO_NUM, LED_OFF); //熄灭该led
			break;
        default:
            ret = -ESRCH;
	}
	
	return ret;
}




/*文件操作结构体*/
static const struct file_operations hello_fops =
{
	.owner = THIS_MODULE,
    .open = hello_open,   	//对应open 
    .read = hello_read,   	//对应read
    .write = hello_write, 	//对应write
	.unlocked_ioctl = hello_ioctl, //对应ioctl
    .release = hello_release, //对应close
};

struct cdev cdev; //静态定义字符设备cdev结构
dev_t devno;  //静态定义字符设备号
static struct class *hello_class;  // 自动创建节点

/*设备驱动模块加载函数*/
static int __init helloworld_init(void)
{   
	int ret = -1;
	unsigned int *addr;
	
    cdev_init(&cdev, &hello_fops);/* 初始化cdev结构， 并将文件IO与字符设备的cdev建立链接 */
    ret = alloc_chrdev_region(&devno, 0, 1, "helloworld"); /* 动态申请设备号， */
	if (ret) {
		printk("alloc_chrdev_region error:%d\n", ret);
		cdev_del(&cdev);   /*注销设备*/
		return ret;
	}
    cdev_add(&cdev, devno, 1); /* 向linux系统添加一个字符设备 ，也就是注册设备：register_chardev() */
	
	/* 自动创建节点 */
	hello_class = class_create(THIS_MODULE, "helloworld");
	device_create(hello_class, NULL, devno, NULL, "helloworld");

	/* 初始化gpio管脚 */
	/* 修改gpio42\gpio43\gpio52\gpio53管脚复用关系为gpio模式 */
	addr = ioremap(0x04020068, 4);     // 引脚复用的CR控制寄存器地址
	writel(0x01001000, addr);          // 为具体写入值，配置成GPIO通用模式
	writel(0x01001000, addr+1);
	writel(0x01001000, addr+2);
	writel(0x01001000, addr+3);
	iounmap(addr);
	ret = gpio_request(GPIO_NUM, "led_gpio"); //申请led一个gpio
	if(ret < 0) {
		printk("gpio_request[%d] error:%d\n", GPIO_NUM, ret);
		goto ERR;
	}
	gpio_direction_output(GPIO_NUM, LED_ON); //默认点亮该led
	printk("##request gpio success!\n");
	
	printk ("helloworld init\n");
	
	return 0;

ERR:  /* 自动创建节点失败，释放节点*/
	if (!IS_ERR_OR_NULL(hello_class)) {
		device_destroy(hello_class, devno);
		class_destroy(hello_class);
	}
	cdev_del(&cdev);   /*注销设备*/
    unregister_chrdev_region(devno, 1); /*释放设备号*/

	
	return ret;          // ret 主要关注有没有申请gpio成功
}

/*模块卸载函数*/
static void __exit helloworld_exit(void)
{
    cdev_del(&cdev);   /*注销设备*/
    unregister_chrdev_region(devno, 1); /*释放设备号*/
	
	device_destroy(hello_class, devno); /*释放节点*/
	class_destroy(hello_class);
	
	gpio_direction_output(GPIO_NUM, LED_OFF); //默认熄灭该led
	gpio_free(GPIO_NUM); 

	
	printk ("helloworld exit\n");
}
module_init(helloworld_init); //内核模块加载函数
module_exit(helloworld_exit); //内核模块卸载函数
MODULE_LICENSE("GPL"); 
MODULE_AUTHOR ("sang");
MODULE_DESCRIPTION ("this is a led module");
