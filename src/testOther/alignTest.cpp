/*
 * alignTest.cpp
 *
 *  Created on: May 9, 2017
 *      Author: echgchi
 */

#include "alignTest.h"

// ./MyTest --gtest_filter=alignTest.*

void alignTest::SetUpTestCase() {

}

void alignTest::TearDownTestCase() {

}

TEST_F (alignTest, pack1) {

#pragma pack(1) // 按照1字节方式进行对齐
	typedef struct bb {
		int id;             //[0]....[3]
		double weight;      //[8].....[15]　　　　　　原则１
		float height;      //[16]..[19],总长要为８的整数倍,补齐[20]...[23]　　　　　原则３
	} BB;

	typedef struct aa {
		char name[2];     //[0],[1]
		int id;         //[4]...[7]　　　　　　　　　　原则１

		double score;     //[8]....[15]
		short grade;    //[16],[17]
		BB b;             //[24]......[47]　　　　　　　　　　原则２
	} AA;

#pragma pack() // 取消1字节对齐方式
	std::cout << "size AA: " << sizeof(AA) << " size BB: " << sizeof(BB)
			<< std::endl;

}

TEST_F (alignTest, origPack) {

	struct TCPHEADER1 {
		short SrcPort; // 16位源端口号
		short DstPort; // 16位目的端口号
		int SerialNo; // 32位序列号
		int AckNo; // 32位确认号
		unsigned char HaderLen :4; // 4位首部长度
		unsigned char Reserved1 :4; // 保留6位中的4位
		unsigned char Reserved2 :2; // 保留6位中的2位
		unsigned char URG :1;
		unsigned char ACK :1;
		unsigned char PSH :1;
		unsigned char RST :1;
		unsigned char SYN :1;
		unsigned char FIN :1;
		short WindowSize; // 16位窗口大小
		short TcpChkSum; // 16位TCP检验和
		short UrgentPointer; // 16位紧急指针
	};

	std::cout << "TCPHEADER size on orig packet: " << sizeof(struct TCPHEADER1)
			<< std::endl;
}

TEST_F (alignTest, pack4) {

#pragma pack(4) // 按照4字节方式进行对齐
	struct TCPHEADER4 {
		short SrcPort; // 16位源端口号
		short DstPort; // 16位目的端口号
		int SerialNo; // 32位序列号
		int AckNo; // 32位确认号
		unsigned char HaderLen :4; // 4位首部长度
		unsigned char Reserved1 :4; // 保留6位中的4位
		unsigned char Reserved2 :2; // 保留6位中的2位
		unsigned char URG :1;
		unsigned char ACK :1;
		unsigned char PSH :1;
		unsigned char RST :1;
		unsigned char SYN :1;
		unsigned char FIN :1;
		short WindowSize; // 16位窗口大小
		short TcpChkSum; // 16位TCP检验和
		short UrgentPointer; // 16位紧急指针
	};
	std::cout << "TCPHEADER size on  pack4 : " << sizeof(struct TCPHEADER4)
			<< std::endl;
#pragma pack() // 取消1字节对齐方式

}

TEST_F (alignTest, general) {

	class CMemoryTest {
		int a;
		char b;
		int c;
		char d;
	};
	class CMemoryTest1 {
		int a;
		char b;
		char d;
		int c;
	};
	class CMemoryTest2 {
		int a;
		char b;
		char d;
		char e;
		char f;
		int c;
	};
	class CMemoryTest3 {
		int a;
		char b;
		int c;
		char d;
	}__attribute__((packed));

	class CMemoryTest4 {
		short a;
		char b;
		int c;
		char d;
	}__attribute((aligned (8)));

	cout<<"MemoryTest "<<sizeof(CMemoryTest)<<endl;
	cout<<"MemoryTest1 "<<sizeof(CMemoryTest1)<<endl;
	cout<<"MemoryTest2 "<<sizeof(CMemoryTest2)<<endl;
	cout<<"MemoryTest3 "<<sizeof(CMemoryTest3)<<endl;
	cout<<"MemoryTest4-64 "<<sizeof(CMemoryTest4)<<endl;

}

