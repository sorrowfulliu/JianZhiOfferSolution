﻿#include "header.h"

/*

请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

示例 1：
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

示例 2：
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]

示例 3：
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]
 
示例 4：
输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回 null。
  
提示：
-10000 <= Node.val <= 10000
Node.random 为空（null）或指向链表中的节点。
节点数目不超过 1000 。

注意：本题与主站 138 题相同：https://leetcode-cn.com/problems/copy-list-with-random-pointer/

*/


// Definition for a Node.
class Node 
{
public:
	int val;
	Node *next;
	Node *random;

	Node(int _val) 
	{
		val = _val;
		next = NULL;
		random = NULL;
	}
};

//原地复制
class Solution1 {
public:
	Node * copyRandomList(Node *head) 
	{
		if (!head) return nullptr;
		Node *node = head;
		Node *copyNode = nullptr;
		while (node)
		{
			copyNode = new Node(node->val);
			copyNode->next = node->next;
			node->next = copyNode;
			node = copyNode->next;
		}
		node = head;
		copyNode = node->next;
		while (node)
		{
			if (node->random) copyNode->random = node->random->next;
			node = copyNode->next;
			if (node) copyNode = node->next;
		}
		node = head;
		copyNode = node->next;
		Node *copyHead = copyNode;
		while (node)
		{
			node->next = copyNode->next;
			node = node->next;
			if (node) copyNode->next = node->next;
			copyNode = copyNode->next;
		}
		return copyHead;
	}
};

//哈希
class Solution2 {
public:
	Node * copyRandomList(Node *head) 
	{
		if (!head) return nullptr;
		unordered_map<Node *, Node *> m;
		Node *node = head;
		while (node)
		{
			Node *copyNode = new Node(node->val);
			m[node] = copyNode;
			node = node->next;
		}
		node = head;
		while (node)
		{
			m[node]->next = m[node->next];
			m[node]->random = m[node->random];
			node = node->next;
		}
		return m[head];
	}
};
