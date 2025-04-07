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
	EXPECT_NO_THROW(ListNode<int>*node = new ListNode<int>());
}


TEST(List, list_Can_Create_List_From_First_Node)
{
	ListNode<int>* node = new ListNode<int>();

	EXPECT_NO_THROW(List<int> list(node));
}


TEST(List, list_Identical_Lists_Are_Equal)
{
	// Ñîáèðàåì list_1
	ListNode<int>* node_1_1 = new ListNode<int>();
	ListNode<int>* node_1_2 = new ListNode<int>();
	ListNode<int>* node_1_3 = new ListNode<int>();

	node_1_1->data = 1;
	node_1_1->pNext = node_1_2;

	node_1_2->data = 3;
	node_1_2->pNext = node_1_3;

	node_1_3->data = 100;

	List<int> list_1(node_1_1);


	// Ñîáèðàåì list_2
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


TEST(List, list_Can_Copy_List)
{
	// Ñîáèðàåì list_1
	ListNode<int>* node_1_1 = new ListNode<int>();
	ListNode<int>* node_1_2 = new ListNode<int>();
	ListNode<int>* node_1_3 = new ListNode<int>();

	node_1_1->data = 1;
	node_1_1->pNext = node_1_2;

	node_1_2->data = 3;
	node_1_2->pNext = node_1_3;

	node_1_3->data = 100;

	List<int> list_1(node_1_1);

	// Êîïèðóêì list_1 â list_2 êîíñòðóêòîðîì
	List<int> list_2(list_1);

	// Êîïèðóåì list_1 â list_3 îïðåðàòîðîì "="
	List<int> list_3 = list_1;

	EXPECT_EQ(list_1, list_2);
	EXPECT_EQ(list_1, list_3);
}

/*
TEST(List, list_Operator_Eq_Returns_New_Value)
{
	// Ñîáèðàåì list_1
	ListNode<int>* node_1_1 = new ListNode<int>();
	ListNode<int>* node_1_2 = new ListNode<int>();
	ListNode<int>* node_1_3 = new ListNode<int>();

	node_1_1->data = 1;
	node_1_1->pNext = node_1_2;

	node_1_2->data = 3;
	node_1_2->pNext = node_1_3;

	node_1_3->data = 100;

	List<int> list_1(node_1_1);
	List<int> list_2 = List<int>();

	EXPECT_EQ(list_1, (list_2 = list_1));
}
*/


TEST(List, list_Can_Insert_First_Into_Empty_List)
{
	// Ëèñò ïðèìåð, ñ êîòîðûì áóäåì ñðàâíèâàòü
	ListNode<int>* nodeExample = new ListNode<int>();
	nodeExample->data = 10;

	List<int> listExample(nodeExample);

	// Ñàì insert
	List<int> list = List<int>();
	list.insertFirst(10);

	EXPECT_EQ(listExample, list);
}


TEST(List, list_Can_Insert_First_Into_Non_Empty_List)
{
	// Ëèñò ïðèìåð, ñ êîòîðûì áóäåì ñðàâíèâàòü
	ListNode<int>* nodeExample_1 = new ListNode<int>();
	ListNode<int>* nodeExample_2 = new ListNode<int>();

	nodeExample_1->data = 10;
	nodeExample_1->pNext = nodeExample_2;

	nodeExample_2->data = 5;

	List<int> listExample(nodeExample_1);

	// Ñàì insert
	List<int> list = List<int>();
	list.insertFirst(5);
	list.insertFirst(10);

	EXPECT_EQ(listExample, list);
}
//

TEST(List, list_Can_Insert_Last_Into_Empty_List)
{
	// Ëèñò ïðèìåð, ñ êîòîðûì áóäåì ñðàâíèâàòü
	ListNode<int>* nodeExample = new ListNode<int>();
	nodeExample->data = 10;

	List<int> listExample(nodeExample);

	// Ñàì insert
	List<int> list = List<int>();
	list.insertLast(10);

	EXPECT_EQ(listExample, list);
}


TEST(List, list_Can_Insert_Last_Into_Non_Empty_List)
{
	// Ëèñò ïðèìåð, ñ êîòîðûì áóäåì ñðàâíèâàòü
	ListNode<int>* nodeExample_1 = new ListNode<int>();
	ListNode<int>* nodeExample_2 = new ListNode<int>();

	nodeExample_1->data = 5;
	nodeExample_1->pNext = nodeExample_2;

	nodeExample_2->data = 10;

	List<int> listExample(nodeExample_1);

	// Ñàì insert
	List<int> list = List<int>();
	list.insertLast(5);
	list.insertLast(10);

	EXPECT_EQ(listExample, list);
}

TEST(List, list_Can_Insert_In_Any_Spot)
{
	// Ëèñò ïðèìåð, ñ êîòîðûì áóäåì ñðàâíèâàòü
	ListNode<int>* nodeExample_1 = new ListNode<int>();
	ListNode<int>* nodeExample_2 = new ListNode<int>();
	ListNode<int>* nodeExample_3 = new ListNode<int>();

	nodeExample_1->data = 5;
	nodeExample_1->pNext = nodeExample_2;

	nodeExample_2->data = 10;
	nodeExample_2->pNext = nodeExample_3;

	nodeExample_3->data = 20;

	List<int> listExample(nodeExample_1);

	// Ñàì insert
	List<int> list = List<int>();
	list.insert(0, 5);
	list.insert(1, 20);
	list.insert(1, 10);

	EXPECT_EQ(listExample, list);
}

TEST(List, list_Can_Remove_Element)
{
	List<int> list;
	list.insertLast(10);
	list.insertLast(20);
	list.insertLast(30);

	EXPECT_NO_THROW(list.remove(0));
	EXPECT_EQ(2, list.size());
	EXPECT_EQ(20, list.getFirst());

	EXPECT_NO_THROW(list.remove(1));
	EXPECT_EQ(1, list.size());
	EXPECT_EQ(20, list.getFirst());

	EXPECT_NO_THROW(list.remove(0));
	EXPECT_EQ(0, list.size());
	EXPECT_TRUE(list.empty());
}

TEST(List, list_Remove_Throws_When_Index_Is_Invalid)
{
	List<int> list;
	list.insertLast(10);

	EXPECT_THROW(list.remove(1), std::exception);
	EXPECT_THROW(list.remove(-1), std::exception);
	list.remove(0);
	EXPECT_THROW(list.remove(0), std::exception);
}

TEST(List, list_Size_Is_Correct)
{
	List<int> list = List<int>();

	EXPECT_EQ(0, list.size());

	list.insertLast(10);

	EXPECT_EQ(1, list.size());

	for (int i = 0; i < 10; i++)
		list.insertLast(10);

	EXPECT_EQ(11, list.size());
}

TEST(List, list_Empty_Is_Correct)
{
	List<int> list = List<int>();

	EXPECT_TRUE(list.empty());

	list.insertLast(10);

	EXPECT_FALSE(list.empty());
}
///
TEST(List, list_Can_View_First_Element)
{
	List<int> list = List<int>();
	list.insertFirst(10);
	list.insertLast(5);
	list.insertFirst(2);

	EXPECT_EQ(2, list.getFirst());
}

TEST(List, list_Can_Edit_First_Element)
{
	List<int> list = List<int>();
	list.insertFirst(10);
	list.insertLast(5);
	list.insertFirst(2);

	list.getFirst() = 100;

	EXPECT_EQ(100, list.getFirst());
}

TEST(List, list_Can_View_Last_Element)
{
	List<int> list = List<int>();
	list.insertFirst(10);
	list.insertLast(5);
	list.insertFirst(2);

	EXPECT_EQ(5, list.getLast());
}

TEST(List, list_Can_Edit_Last_Element)
{
	List<int> list = List<int>();
	list.insertFirst(10);
	list.insertLast(5);
	list.insertFirst(2);

	list.getLast() = 100;

	EXPECT_EQ(100, list.getLast());
}