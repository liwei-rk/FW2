#ifndef LWFS_H
#define LWFS_H
#include <sys/statfs.h>
#include <iostream>
using namespace std;
float GetDiskfreeSpacePercent(const char *pDisk){
	long long totalspace=0;
	long long freespace=0;
	struct statfs disk_statfs;
	if(statfs(pDisk,&disk_statfs)>=0){
		freespace=(((long long)disk_statfs.f_bsize*(long long)disk_statfs.f_bfree)/(long long)1024);
		totalspace=(((long long)disk_statfs.f_bsize*(long long)disk_statfs.f_blocks)/(long long)1024);
	}
	return ((float)freespace/(float)totalspace)*100;
}
bool warning(string pDisk){
	float gate=0.1f;
	float freeSpacePercent=GetDiskfreeSpacePercent(pDisk.c_str());
	if(freeSpacePercent<=gate){
		return true;
	}else{
		return false;
	}
}
#endif //LWFS_H
