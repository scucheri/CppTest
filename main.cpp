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

#define LOG_MEM_ALLOCATE
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

// #define MAX(x, y) (x > y ? x : y)

#define MAX(x, y) x > y ? x : y
#define MAX_2(x, y) (x > y ? x : y)

class Entity {
public:
    string entityName;

    //virtual function是可以继承的
    virtual string getName() {
        return "Entity";
    };

    virtual void printName() {
        cout << "entityName: " << entityName << " Name: " << getName() << endl;
    }

    virtual void printNameWithTag(string tag) {
        cout << "tag : "<< tag<<"entityName: " << entityName << " Name: " << getName() << endl;
    }
};

class PlayerEntity : public Entity {
private:
    string mName;

public:
    PlayerEntity() : Entity() {
        mName = "xiaoyumi_default_PlayerEntity";
    }

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

void printEntityNameWithTag(string tag, Entity entity) {
    entity.printNameWithTag(tag);
}

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


#define NEW_ARRAY(type, size, name)\
Array<type, size> name

#define NEW_ARRAY_FUN(type, size) newArray<type, size>()

template <typename T, int N>
Array<T,N> newArray() {
    return Array<T,N>();
}


// namespace TestNameSpace{
//     string xiaoyumi = "TestNameSpace_xiaoyumi";
//     string xiaoyumi2  = "TestNameSpace_xiaoyumi2";
// }

void testIfDefFun() {
#ifdef LOG_MEM_ALLOCATE //只要有LOG_MEM_ALLOCATE这个宏的定义，就会走到#ifdef分支；否则走到#else分支
    cout << "testIfDefFun  if " << endl;
#else
    cout << "testIfDefFun  else " << endl;
#endif
}

class MemEntity {
    private:
    string name = "MemEntity_name";
public:
    MemEntity() {
        name = "MemEntity_name_default";
        puts( std::format("MemEntity created!, {}!", name.c_str()).c_str());
    }

    MemEntity(string nameStr) {
        name = nameStr;
        puts( std::format("MemEntity created!, {}!", name.c_str()).c_str());
    }
    ~MemEntity() {
        puts( std::format("MemEntity destroyed!, {}!", name.c_str()).c_str());
    }

    const char* test() {
        return name.c_str();
    }
};

void ex1() {
    puts("--------");
    puts("Entering ex1");
    {
        puts("Entering ex1::scope1");
        auto e1 = std::make_unique<MemEntity>("ex1_e1");
        //推荐使用的方式是make_unique这种
        std::unique_ptr<MemEntity> testE1 = std::make_unique<MemEntity>("ex1_testE1");
        testE1->test();
        std::unique_ptr<MemEntity> testE2(new MemEntity("ex1_testE2"));
        testE2->test();
        puts("Leaving ex1::scope1");
    }
    puts("Leaving ex1");
}

void foo(std::unique_ptr<MemEntity> ptr) {
    puts("Entering foo");
    puts(ptr->test());
    puts("Leaving foo");
}

void ex2() {
    puts("--------");
    puts("Entering ex2");
    auto e1 = std::make_unique<MemEntity>("ex2_e1");
    // auto e2 = e1;//这个不被允许
    auto e2 = std::move(e1);
    // foo(std::move(e1));//这里e1的所有权已经转移给e2了，e1已经是个空指针了
    if (e1 == nullptr ) {
        puts("ex2 : e1 is null");
    }
    foo(std::move(e2));
    // e1 was destoried.
    puts("Leaving ex2");
}

void ex3() {
    puts("--------");
    puts("Entering ex3");
    auto e1 = std::make_shared<MemEntity>("ex3_e1");
    std::cout << e1.use_count() << std::endl;
    {
        puts("Entering ex3::scope1");
        auto e2 = e1; // use_count ++
        std::cout <<"e1.use_count() " <<e1.use_count() << std::endl;
        std::cout <<"e2.use_count() " <<e2.use_count() << std::endl;

        std::cout <<"e2 before std::move  " <<e2.get() << std::endl;
        auto e3 = std::move(e2); // use_count remains
        std::cout <<"e2 after std::move  " <<e2.get() << std::endl;
        std::cout <<"e2 after std::move e2  is nullptr  " <<(e2 == nullptr) << std::endl;
        // std::cout <<"e2 after std::move  " <<e2->test() << std::endl;
        std::cout <<"e3 after std::move  " <<e3->test() << std::endl;

        std::cout << "e1.use_count() "<<e1.use_count() << std::endl;
        std::cout <<"e2.use_count() " <<e2.use_count() << std::endl;
        std::cout <<"e3.use_count() " <<e3.use_count() << std::endl;
        puts("Leaving ex3::scope1");
    }
     std::cout << "e1.use_count() "<<e1.use_count() << std::endl;
    puts("Leaving ex3");
}

void observe(std::weak_ptr<MemEntity> ew) {
    if (std::shared_ptr<MemEntity> spt = ew.lock()) {//调用lock的时候会使得引用计数+1
        std::cout <<" e1.use_count when weak_ptr lock"<<  spt.use_count() << std::endl;
        std::cout << "entity still alive!" << std::endl;
    } else {
        std::cout << "entity was expired :(" << std::endl;
    }
}

void ex4() {
    puts("--------");
    puts("Entering ex4");
    std::weak_ptr<MemEntity> ew;
    {
        puts("Entering ex4::scope1");
        auto e1 = std::make_shared<MemEntity>("ex4_e1");//shared_ptr定义的两种方法
        std::shared_ptr<MemEntity> testE1(new MemEntity("ex4_testE1"));
        testE1->test();
        std::cout <<" e1.use_count"<< e1.use_count() << std::endl;
        std::cout <<" ew.use_count"<< ew.use_count() << std::endl;
        ew = e1; // use_count remains
        std::cout <<" e1.use_count after weak_ptr"<< e1.use_count() << std::endl;
        std::cout <<" ew.use_count after weak_ptr"<< ew.use_count() << std::endl;
        observe(ew);
        std::cout <<" ew.use_count after observe"<< ew.use_count() << std::endl;
        puts("Leaving ex4::scope1");
    }
    observe(ew);
    std::cout << ew.use_count() << std::endl;
    puts("Leaving ex4");
}

void ex5() {
    puts("Entering ex5");
    MemEntity mem_entity;// 会用默认的构造函数初始化MemEntity_name_default
    //局部变量执行结束后会被自动析构

    MemEntity mem_entity_1 =   MemEntity("ex5_e1");
}

void ex6() {
    try {
        MemEntity* mem_entity = new MemEntity("ex6_e1");
        puts("Entering ex6");
        throw std::runtime_error("ex6 Error!"); // 抛出异常
        mem_entity->test();
    } catch (const std::exception& e) {
        puts("ex6 error occured!  " );
    }
}

class TestStatic {
  public:
    static MemEntity* mem_entity;
    static MemEntity stack_mem_entity;
    static unique_ptr<MemEntity> mem_entity_smart_pointer;

};

MemEntity* TestStatic::mem_entity = new MemEntity("TestStatic"); //这种写法需要手动delete才能释放，进程退出时也不能自动释放
MemEntity TestStatic::stack_mem_entity =  MemEntity("TestStaticStack"); //这种写法不需要手动delete，在进程退出时会自动释放
unique_ptr<MemEntity> TestStatic::mem_entity_smart_pointer = std::make_unique<MemEntity>("TestStaticSmartPointer"); //这种写法不需要手动delete，在进程退出时会自动释放

void testSmartPointer() {
    ex1();
    ex2();
    ex3();
    ex4();
    ex5();
    ex6();
}

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

    // Array<string, 5> array;// new Array的不同写法
    // NEW_ARRAY(string, 5, array);
    // Array<string,5> array = newArray<string,5>();
    Array<string,5> array = NEW_ARRAY_FUN(string, 5);
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

    //使用default的constructor初始化
    PlayerEntity playerEntity;
    playerEntity.printName();
    printEntityNameWithTag("printEntityNameWithTag ",playerEntity);

    PlayerEntity *playerEntity1 = new PlayerEntity("hello xiaoyumi player ");
    playerEntity1->printName();
  printEntityNameWithTag("printEntityNameWithTag ", *playerEntity1);


    Entity entity; // 这个是有默认的Constructor的，所以可以不用new
    entity.entityName = "hello entity";
    entity.printName();
   printEntityNameWithTag("printEntityNameWithTag ",  entity);

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
        cout << value << ", ";
    }
    cout << endl;

    testIfDefFun();

    int ret1 = MAX(7, 5) * 10;// 7 > 5 ? 7 : 5 * 10,编译后变成这个，所以返回了7
    cout << "MAX without  bracket " << ret1 << endl;

    int ret2 = MAX_2(7, 5) * 10; //(7 > 5 ? 7 : 5) * 10 编译后变成这个，所以返回了70
    cout << "MAX with  bracket " << ret2 << endl;


  testSmartPointer();
    return 1;
}


// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.


#include <stdio.h>
#include <stdlib.h>
