#list test case name
./myTest --gtest_list_tests

#--gtest_filter 对执行的测试案例进行过滤，支持通配符
?    单个字符; 	
*    任意字符	
-    排除，如，-a 表示除了a	
:    取或，如，a:b 表示a或b

./foo_test 没有指定过滤条件，运行所有案例
./foo_test --gtest_filter=* 使用通配符*，表示运行所有案例
./foo_test --gtest_filter=FooTest.* 运行所有“测试案例名称(testcase_name)”为FooTest的案例
./foo_test --gtest_filter=*Null*:*Constructor* 运行所有“测试案例名称(testcase_name)”或“测试名称(test_name)”包含Null或Constructor的案例。
./foo_test --gtest_filter=-*DeathTest.* 运行所有非死亡测试案例。
./foo_test --gtest_filter=FooTest.*-FooTest.Bar 运行所有“测试案例名称(testcase_name)”为FooTest的案例，但是除了FooTest.Bar这个案例



#布尔值检查
Fatal assertion 			:	ASSERT_TRUE(condition); ASSERT_FALSE(condition); 
Nonfatal assertion Verifies :	EXPECT_TRUE(condition); EXPECT_FALSE(condition); 

#数值型数据检查
Fatal assertion 				Nonfatal assertion 				Verifies 
ASSERT_EQ(expected, actual);	EXPECT_EQ(expected, actual);	expected == actual 
ASSERT_NE(val1, val2); 			EXPECT_NE(val1, val2); 			val1 != val2 
ASSERT_LT(val1, val2); 			EXPECT_LT(val1, val2); 			val1 < val2 
ASSERT_LE(val1, val2); 			EXPECT_LE(val1, val2); 			val1 <= val2 
ASSERT_GT(val1, val2); 			EXPECT_GT(val1, val2); 			val1 > val2 
ASSERT_GE(val1, val2); 			EXPECT_GE(val1, val2); 			val1 >= val2

#字符串检查 
Fatal assertion 							Nonfatal assertion 								Verifies 
ASSERT_STREQ(expected_str, actual_str); 	EXPECT_STREQ(expected_str, actual_str); 		the two C strings have the same content 
ASSERT_STRNE(str1, str2); 					EXPECT_STRNE(str1, str2); 						the two C strings have different content 
ASSERT_STRCASEEQ(expected_str, actual_str);	EXPECT_STRCASEEQ(expected_str, actual_str); 	the two C strings have the same content, ignoring case 
ASSERT_STRCASENE(str1, str2);				EXPECT_STRCASENE(str1, str2); 					the two C strings have different content, ignoring case 


#全局事件
 
要实现全局事件，必须写一个类，继承testing::Environment类，实现里面的SetUp和TearDown方法。
 
1. SetUp()方法在所有案例执行前执行
2. TearDown()方法在所有案例执行后执行

class FooEnvironment : public testing::Environment
 {
 public:
     virtual void SetUp()
     {
         std::cout << "Foo FooEnvironment SetUP" << std::endl;
     }
     virtual void TearDown()
     {
         std::cout << "Foo FooEnvironment TearDown" << std::endl;
     }
 };
 
int _tmain(int argc, _TCHAR* argv[])
{
     testing::AddGlobalTestEnvironment(new FooEnvironment);
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
}

#TestSuite事件
我们需要写一个类，继承testing::Test，然后实现两个静态方法
1. SetUpTestCase() 方法在第一个TestCase之前执行
2. TearDownTestCase() 方法在最后一个TestCase之后执行

class FooTest : public testing::Test {
  protected:
   static void SetUpTestCase() {
     shared_resource_ = new ;
   }
   static void TearDownTestCase() {
     delete shared_resource_;
     shared_resource_ = NULL;
   }
   // Some expensive resource shared by all tests.
   static T* shared_resource_;
 };

在编写测试案例时，我们需要使用TEST_F这个宏，第一个参数必须是我们上面类的名字，代表一个TestSuite。
TEST_F(FooTest, Test1)
  {
     // you can refer to shared_resource here 
 }
 TEST_F(FooTest, Test2)
  {
     // you can refer to shared_resource here 
 }
 
#TestCase事件
TestCase事件是挂在每个案例执行前后的，实现方式和上面的几乎一样，不过需要实现的是SetUp方法和TearDown方法：
1. SetUp()方法在每个TestCase之前执行
2. TearDown()方法在每个TestCase之后执行

class FooCalcTest:public testing::Test
{
 protected:
     virtual void SetUp()
     {
         m_foo.Init();
     }
     virtual void TearDown()
     {
         m_foo.Finalize();
     }
 
    FooCalc m_foo;
};
 
TEST_F(FooCalcTest, HandleNoneZeroInput)
{
    EXPECT_EQ(4, m_foo.Calc(12, 16));
}
 
TEST_F(FooCalcTest, HandleNoneZeroInput_Error)
{
    EXPECT_EQ(5, m_foo.Calc(12, 16));
}

