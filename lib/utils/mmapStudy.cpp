/*
 * mmapStudy.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: echgchi
 */

#include "mmapStudy.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>


/*
text.txt

aaaaaaaaa
bbbbbbbbb
ccccccccc
ddddddddd
 *
 */

mmapStudy::mmapStudy() {
	// TODO Auto-generated constructor stub

}

mmapStudy::~mmapStudy() {
	// TODO Auto-generated destructor stub
}

void mmapStudy::modifyfile(string filename) {

	int fd, nread, i;
	struct stat sb;
	char *mapped, buf[BUF_SIZE];

	for (i = 0; i < BUF_SIZE; i++) {
		buf[i] = '#';
	}

	/* 打开文件 */
	if ((fd = open(filename.c_str(), O_RDWR)) < 0) {
		perror("open");
	}

	/* 获取文件的属性 */
	if ((fstat(fd, &sb)) == -1) {
		perror("fstat");
	}

	/* 将文件映射至进程的地址空间 */
	if ((mapped = (char *) mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0)) == (void *) -1) {
		perror("mmap");
	}

	/* 映射完后, 关闭文件也可以操纵内存 */
	close(fd);

	printf("%s", mapped);

	/* 修改一个字符,同步到磁盘文件
	 * 刷新变化函数msync()
	 * 进程在映射空间的对共享内容的改变并不直接写回到磁盘文件中，往往在调用munmap()后才执行该操作。
	 * 可以通过调用msync()函数来实现磁盘文件内容与共享内存区中的内容一致,即同步操作.
	 * */
	mapped[20] = '9';
	if ((msync((void *) mapped, sb.st_size, MS_SYNC)) == -1) {
		perror("msync");
	}

	/* 释放存储映射区 */
	if ((munmap((void *) mapped, sb.st_size)) == -1) {
		perror("munmap");
	}

	return;

}

