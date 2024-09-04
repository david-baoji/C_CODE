// ConsoleApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <random>
#include <sstream>

std::string generateUUID() {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<uint64_t> dis;

	uint64_t part1 = dis(gen);
	uint64_t part2 = dis(gen);

	std::ostringstream oss;
	oss << std::hex << part1 << part2;

	std::string uuidStr = oss.str();
	return uuidStr.substr(0, 32); // 截取32位作为简化的UUID
}

long GetFileLength(FILE *fp)
{
	long curpos = 0L;
	long length = 0L;

	curpos = ftell(fp);          // 保存fp相对于文件首的偏移量
	fseek(fp, 0L, SEEK_END);     // 将fp移动到文件尾
	length = ftell(fp);          // 统计文件大小
	fseek(fp, curpos, SEEK_SET); // 将fp归位

	return length;
}

int main()
{
    std::cout << "Hello World!\n";
	// 生成UUID
	std::string uuid = generateUUID();
	// 输出UUID
	std::cout << "Generated UUID: " << uuid << std::endl;

	FILE *fp = fopen("test.txt", "wb+");
	char buf[] = "0123456789";
	int len = strlen(buf);
	int size = sizeof(char);
	int count = len / size;
	int wCount = fwrite(buf, size, count, fp);
	fclose(fp);
	
	//printf("buf: %d, count: %d, wCoutn: %d", len, count, wCount);

	FILE *fpr = fopen("test.txt", "rb+");
	int length = GetFileLength(fpr);


	char *pbuf = (char*)malloc(sizeof(char)*length);
	int read = fread(pbuf, size, length, fpr);
	printf("length: %d, read: %d", length, read);

	printf("pbuf: %s, readc: %d", pbuf, read);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
