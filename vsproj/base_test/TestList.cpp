#include "gtest.h"
#include "List.h"

TEST(List, list_Can_Create_List)
{
	EXPECT_NO_THROW(List<int> list = List<int>());
}


TEST(List, list_Empty_By_Default)
{
	List<int> list = List<int>();
	EXPECT_TRUE(list.empty());
}


TEST(List, list_Size_Is_Zero_By_Default)
{
	List<int> list = List<int>();
	EXPECT_EQ(0, list.size());
}


TEST(List, list_Can_Create_Node)
{
	EXPECT_NO_THROW(ListNode<int>* node = new ListNode<int>());
}


TEST(List, list_Can_Create_List_From_First_Node)
{
	ListNode<int>* node = new ListNode<int>();

	EXPECT_NO_THROW(List<int> list(node));
}


TEST(List, list_Identical_Lists_Are_Equal)
{
	// Собираем list_1
	ListNode<int>* node_1_1 = new ListNode<int>();
	ListNode<int>* node_1_2 = new ListNode<int>();
	ListNode<int>* node_1_3 = new ListNode<int>();

	node_1_1->data = 1;
	node_1_1->pNext = node_1_2;

	node_1_2->data = 3;
	node_1_2->pNext = node_1_3;

	node_1_3->data = 100;

	List<int> list_1(node_1_1);


	// Собираем list_2
	ListNode<int>* node_2_1 = new ListNode<int>();
	ListNode<int>* node_2_2 = new ListNode<int>();
	ListNode<int>* node_2_3 = new ListNode<int>();

	node_2_1->data = 1;
	node_2_1->pNext = node_2_2;

	node_2_2->data = 3;
	node_2_2->pNext = node_2_3;

	node_2_3->data = 100;

	List<int> list_2(node_2_1);

	EXPECT_TRUE(list_1 == list_2);
}


TEST(List, list_Can_Insert_First_Into_Empty_List)
{
	// Лист пример, с которым будем сравнивать
	ListNode<int>* nodeExample = new ListNode<int>();
	nodeExample->data = 10;

	List<int> listExample(nodeExample);

	// Сам insert
	List<int> list = List<int>();
	list.InsertFirst(10);

	EXPECT_EQ(listExample, list);
}


TEST(List, list_Can_Insert_First_Into_Non_Empty_List)
{
	// Лист пример, с которым будем сравнивать
	ListNode<int>* nodeExample_1 = new ListNode<int>();
	ListNode<int>* nodeExample_2 = new ListNode<int>();

	nodeExample_1->data = 10;
	nodeExample_1->pNext = nodeExample_2;

	nodeExample_2->data = 5;

	List<int> listExample(nodeExample_1);

	// Сам insert
	List<int> list = List<int>();
	list.InsertFirst(5);
	list.InsertFirst(10);

	EXPECT_EQ(listExample, list);
}


TEST(List, list_Can_Insert_Last_Into_Empty_List)
{
	// Лист пример, с которым будем сравнивать
	ListNode<int>* nodeExample = new ListNode<int>();
	nodeExample->data = 10;

	List<int> listExample(nodeExample);

	// Сам insert
	List<int> list = List<int>();
	list.InsertLast(10);

	EXPECT_EQ(listExample, list);
}


TEST(List, list_Can_Insert_Last_Into_Non_Empty_List)
{
	// Лист пример, с которым будем сравнивать
	ListNode<int>* nodeExample_1 = new ListNode<int>();
	ListNode<int>* nodeExample_2 = new ListNode<int>();

	nodeExample_1->data = 5;
	nodeExample_1->pNext = nodeExample_2;

	nodeExample_2->data = 10;

	List<int> listExample(nodeExample_1);

	// Сам insert
	List<int> list = List<int>();
	list.InsertLast(5);
	list.InsertLast(10);

	EXPECT_EQ(listExample, list);
}

// тут не все, но надо больше