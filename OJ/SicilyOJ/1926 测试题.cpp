/* 1926 测试题 */

class NumCal {
    int *p;    // 数组首地址
    int size; // 数组size
public:
    int sum(); // 计算数组元素和
    NumCal(); // 构造函数
    NumCal(int *new_p, int new_size); // 构造函数
};

NumCal::NumCal(){
	p = 0; // NULL
	size = 0;
}

NumCal::NumCal(int *new_p, int new_size){
	p = new_p;
	size = new_size;
}

int NumCal::sum(){
	int var = 0;
	for(int i = 0; i < size; i++)
		var += *(p+i);
	return var;
}