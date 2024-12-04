#include <iostream>
#include <sstream>
#include "Log.h"
#include "Common.h"
#include "sub/Test.h"
using namespace std; //加上后，cout 等可以简写

#define WAIT std::cin.get()
#define OPEN_CURLY {

#ifdef MY_DEBUG //debug模式打印日志，release模式不打印日志
#define LOG(x) cout << x << endl
#else
#define LOG(x)
#endif

#ifdef __DEBUG__
#define LOG_RELEASE(x)
#else
#define LOG_RELEASE(x)  cout << x << endl
#endif

// #define LOG_MEM_ALLOCATE
#ifdef LOG_MEM_ALLOCATE //只要有LOG_MEM_ALLOCATE这个宏的定义，就会走到#ifdef分支；否则走到#else分支
#define LOG_MEM_ALLOCATE_TEST(x) cout << "ifdef "<< x << endl
#else
#define LOG_MEM_ALLOCATE_TEST(x) cout << "else "<< x << endl
#endif


#define XIOAYUMI_FLAG  2
#if XIOAYUMI_FLAG == 0
#define XIOAYUMI_FLAG_TEST(x) cout << "ifdef 0 " << x << endl
#elif  XIOAYUMI_FLAG == 1
#define XIOAYUMI_FLAG_TEST(x) cout << "elif 1  " << x << endl
#elif defined(LOG_MEM_ALLOCATE) // 判断LOG_MEM_ALLOCATE这个宏有没有定义
#define XIOAYUMI_FLAG_TEST(x) cout << "LOG_MEM_ALLOCATE isdefined:  " << x << endl
#else
#define XIOAYUMI_FLAG_TEST(x) cout << "else  " << x << endl
#endif

#define XIOAYUMI_TEST_FUNCTION_MACRO int getXiaoyumiTestFunction() \
    { cout<<"XIOAYUMI_TEST_FUNCTION"<<endl; \
return 1008;\
}
XIOAYUMI_TEST_FUNCTION_MACRO //这里代表把上面定义宏的代码粘贴过来

#define SQUARE(x) x*x

#define MALLOC(n, type) \
((type *) malloc((n)* sizeof(type)))

// 不能加 * 因为 指针 也是一种类型
#define SORT( a,  n)\
{\
int i, j;\
int *t = MALLOC(1,int);\
for(i=0; i<n-1; i++)\
{\
for(j=0; j<n-1-i; j++)\
{\
if(*(a+j) > *(a+j+1))\
{\
*t = *(a+j);\
*(a+j) = *(a+j+1);\
*(a+j+1) = *t;\
}\
}\
}\
}


class Entity {
public:
    string entityName;

    virtual string getName() {
        return "Entity";
    };

    virtual void printName() {
        cout << "entityName: " << entityName << " Name: " << getName() << endl;
    }
};

class PlayerEntity : public Entity {
private:
    string mName;

public:
    PlayerEntity(string name) {
        mName = name;
    }

    string getName() override {
        return mName;
    };

    void printName() override {
        cout << mName << endl;
    }
};

int produceRandom(short min, short max) {
    long timeme = time(nullptr);
    cout << "timeme = " << timeme << std::endl;
    srand(timeme); //如果timeme 没变化的话，下面的rand（）返回的数值经常是一样的
    return rand() % (max - min + 1) + (min);
}

//模版 + 类型
template<typename T>
void print(T value) {
    cout << value << endl;
}

//模版 + 数字
template<typename T, int N>
class Array {
private:
    T mArray[N];

public:
    int getSize() const { return N; }

public:
    string toString() {
        string result = "";
        for (int i = 0; i < N; i++) {
            result += mArray[i];
        }
        return result;
    }

public:
    void put(int index, T value) { mArray[index] = value; }
};

// namespace TestNameSpace{
//     string xiaoyumi = "TestNameSpace_xiaoyumi";
//     string xiaoyumi2  = "TestNameSpace_xiaoyumi2";
// }

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() OPEN_CURLY
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;

        std::cout << "xiaoyumi " << "i = " << i << " xixixi " << std::endl;
    }

    std::cout << "please enter 2 numbers: " << std::endl;
    double a;
    double b;
    // std::cin >> a;
    // std::cin >> b;
    // std::cout << a << " + " << b << " = " << a + b << std::endl;

    double d = floor(1.3);
    std::cout << "d= " << d << std::endl;

    char letter = 'a';
    double number = 9999.0;
    long number2 = 123456789L;
    auto fileSize = 989; //auto用于自动分配类型

    int cc = 1.23456789; //强制转换成1了
    std::cout << "cc = " << cc << std::endl; //这里是1

    int dd = {}; // 初始化为0了
    std::cout << "dd = " << dd << std::endl;

    short ee = 0B1111111111111111; //这里装不下，所以会有警告
    int ee2 = 0x11111111;
    std::cout << "ee = " << ee << std::endl;
    std::cout << "ee2 = " << ee2 << std::endl;

    unsigned int eeu = -255; //不能用unsigned定义一个负数
    cout << "eeu = " << eeu << std::endl;


    const short min = 1;
    const short max = 6;
    int result = produceRandom(min, max);
    cout << "eeuu = " << result << std::endl;

    print(1.0f);
    print("hello");
    print(1000L);
    // print<int>("hello");//这个编译错误
    print<std::string>("hello yayya");

    Array<string, 5> array;
    array.put(0, "hello ");
    array.put(1, "xiaoyumi; ");
    array.put(2, "hello ");
    array.put(3, "titi; ");
    array.put(4, "hello all; ");
    array.put(10, "hello all; "); //为什么这里不会报错？

    cout << "array.getSize() = " << array.getSize() << std::endl;
    cout << "array.toString() = " << array.toString() << std::endl;

    log("xiaoyumitest log ");

    Common *common = new Common();
    common->logcommon("hello");

    test();

    //这个是没有默认的Constructor的，所以必须用new
    // PlayerEntity playerEntity;
    PlayerEntity *playerEntity = new PlayerEntity("hello xiaoyumi player ");
    playerEntity->printName();

    Entity entity; // 这个是有默认的Constructor的，所以可以不用new
    entity.entityName = "hello entity";
    entity.printName();

    using namespace TestNameSpace;
    cout << xiaoyumi << endl;
    cout << TestNameSpace::xiaoyumi2 << endl;

    // std::cin.get();
    // WAIT;
    LOG("xiaoyumi use macro for debug");

    LOG_RELEASE("xiaoyumi use macro for release ");

    LOG_MEM_ALLOCATE_TEST("LOG_MEM_ALLOCATE_TEST");

    XIOAYUMI_FLAG_TEST("XIOAYUMI_FLAG_TEST");

    cout << "SQUARE :" << SQUARE(12) << endl;
    cout << "XIOAYUMI_TEST_FUNCTION_MACRO :" << getXiaoyumiTestFunction() << endl; //宏就是直接替换代码

    int data[] = {3, 200, 5};
    SORT(data, 3);
    cout << "after sort: " << endl;
    for (int value: data) {
        cout << value << ", " ;
    }
    cout << endl;

    return 1;
}


// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.


#include <stdio.h>
#include <stdlib.h>
