#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>

/* ioctl命令行 */
#define LED_IOC_MAGIC 'L'
#define SET_LED_OFF    _IO(LED_IOC_MAGIC, 1)
#define SET_LED_ON     _IO(LED_IOC_MAGIC, 2)


void usage(void)         // usage: 用法说明函数
{
	// printf("#################################\n");
	// printf("please input:on|off|quit\n");
	// printf("#################################\n");
}


// test_hello  /dev/helloworld  on|off

int main(int argc, char *argv[])
{
	
	int ret;
	unsigned char key_val = 1;
	unsigned char key_check = 1;
	int led_on = 1;


	int fd1 = open("/dev/helloworld", O_RDWR);   //打开设备驱动节点
	int fd2 = open("/dev/key", O_RDWR); 

	if (fd1 < 0) {
		perror("open");
		return -1;
	}

	if (fd2 < 0) {
		perror("open");
		return -1;
	}




	while (1)  
	{ 
		ret = read(fd2, &key_val, 1);
		if (ret < 0)
		{
			if (errno == EINTR)
				continue;
			perror("read");
			return -1;
		}

		/* 查询方式消抖：检测到按下后延时再确认一次 */
		if (key_val == 0) {
			usleep(15000);
			ret = read(fd2, &key_check, 1);
			if (ret < 0)
				continue;

			if (key_check == 0) {
				led_on = !led_on;
				if (led_on)
					ioctl(fd1, SET_LED_ON);
				else
					ioctl(fd1, SET_LED_OFF);

				/* 等待按键释放，避免长按期间重复触发 */       
				do { 
					usleep(5000);
					ret = read(fd2, &key_check, 1);
					if (ret < 0)
						break;
				} while (key_check == 0);          // 就代表这里要一直在进行读操作的小循环，控制在这个小循环里，就不执行主循环的翻转操作
			}
		}

		usleep(2000);
		
	}
	
}
