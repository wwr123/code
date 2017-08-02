#include<iostream>
using namespace std;
#include<gtest/gtest.h>
#include<stack>
//全局的  所有案例的前后执行
//class GlobalTest:public testing::Environment
//{
//	public:
//		virtual void SetUp()
//		{
//			cout<<"start push"<<endl;
//		}
//		
//		virtual void TearDown()
//		{
//			cout<<"end"<<endl;
//		}
//};
//
//TEST(testcasename,testcase)
//{
//    ASSERT_EQ(1,2);
//}
//
//TEST(testcasename,testcase1)
//{
//    ASSERT_EQ(1,2);
//}

//TestCase  在每个案例的前后执行
//class Case:public testing::Test
//{
//	public:
//		virtual void SetUp()
//		{
//			cout<<"start"<<endl;
//			s.push(1);
//		}
//		virtual void TearDown()
//		{
//			cout<<"end"<<endl;
//		}
//		stack<int> s;
//};
//TEST_F(Case,test)
//{
//	ASSERT_EQ(1,s.top());
//	EXPECT_EQ(2,s.top());
//}
//TEST_F(Case,test1)
//{
//	ASSERT_EQ(2,s.top());
//    EXPECT_EQ(1,s.top());
//}

class TestCase:public testing::Test
{
	public:
		static void SetUpTestCase()
		{
			cout<<"start"<<endl;
		}
		static void TearDownTestCase()
		{
			cout<<"end"<<endl;
		}
};

TEST_F(TestCase,test)
{	
	ASSERT_EQ(1,2);


	//EXPECT_EQ(2,*p);
}
TEST_F(TestCase,test1)
{
	//ASSERT_EQ(1,*p);
	//ASSERT_EQ(1,*p);
}
//TestS
int main(int argc,char* argv[])
{
   // GlobalTest *env=new GlobalTest;
	//testing::AddGlobalTestEnvironment(env); //向框架里面添加
	testing::InitGoogleTest(&argc,argv); //初始化
	return RUN_ALL_TESTS();
}
