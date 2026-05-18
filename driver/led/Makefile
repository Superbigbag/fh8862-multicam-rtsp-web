#对应内核源码路径(学生需要修改为自己的内核源码路径)
KDIR = /home/fh8862/resource/FH8862_IPC_V1.0.0_20221111/board_support/kernel/linux-4.9



#处理器
ARCH = arm 
#交叉编译工具链前缀
CROSS_COMPILE = arm-fullhanv3-linux-uclibcgnueabi-
.PHONY:Kbuild
Kbuild:
	make -C $(KDIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules   # 核心make
	$(CROSS_COMPILE)gcc test_hello.c -o test_hello                                # 交叉编译：应用文件

clean:
	make -C $(KDIR) M=`pwd` clean
	
obj-m        =  hello_world.o        # 指定输出.ko, 必须写。要不就在kbuild里
obj-m        =  key.o  