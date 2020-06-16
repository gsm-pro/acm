#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<queue>
#include<set>
using namespace std;
bool indexes[1000002]={false};
char c;
int k;

class BorTree
{
public:
	void addString()
	{
		BorNode* node=&root;
		int len;
		for (len=0;(c=fgetc(stdin)) && c!='\n' && c!='\r';len++)
		{
			if (node->links[c-'a']!=NULL) node=node->links[c-'a'];else
			{
				BorNode* new_node=new BorNode;
				node->links[c-'a']=new_node;
				node=new_node;
			}
		}
		node->out=words.size();
		words.push_back(len);
		scanf("\n");
	}

	void init()
	{
		root.fail=&root;
		queue<BorNode*> q;
		q.push(&root);
		while (!q.empty())
		{
			BorNode* current_node=q.front();
			q.pop();
			for (int i=0;i<26;i++)
			{
				if (current_node->links[i]==NULL) continue;
				BorNode* child=current_node->links[i];
				char symb=i;
				q.push(child);
				BorNode* parent_fail=current_node->fail;
				while (true)
				{
					BorNode* node=parent_fail->links[symb];
					if (node!=NULL)
					{
						child->fail=(node!=child ? node : &root);
						if (child->out<0) child->out=child->fail->out;
						break;
					}
					if (parent_fail==&root)
					{
						child->fail=&root;
						break;
					} else parent_fail=parent_fail->fail;
				}
			}
		}
	}

	void search()
	{
		BorNode* current_node=&root;
		for (int pos=1;(c=fgetc(stdin))!=EOF && c!='\n' && c!='\r';pos++)
		{
			BorNode* node=current_node->links[c-'a'];
			while (node==NULL)
			{
				current_node=current_node->fail;
				node=current_node->links[c-'a'];
				if (current_node==current_node->fail) break;
			}
			if (node!=NULL)
			{
				current_node=node;
				if (current_node->out>=0)
				{
					indexes[pos-words[current_node->out]+1]=true;
					BorNode* tmp=current_node->fail;
					while (tmp!=&root)
					{
						if(tmp->out>=0)
						{
							indexes[pos-words[tmp->out]+1]=true;
							tmp=tmp->fail;
						} else break;
					}
				}
			}
		}
	}

private:
	struct BorNode
	{
		BorNode():fail(NULL),out(-1)
		{
			for (int i=0;i<26;i++) links[i]=NULL;
		}
		BorNode* links[26];
		BorNode* fail;
		int out;
	};
	BorNode root;
	vector<int> words;
};

int main()
{
	BorTree borTree;
	scanf("%d\n",&k);
	for (int i=0;i<k;i++) borTree.addString();
	borTree.init();
	borTree.search();
	int res=0;
	for (int i=1;i<=1000000;i++)
		if (indexes[i]) res++;
	printf("%d\n",res);
	for (int i=1;i<=1000000;i++)
		if (indexes[i]) printf("%d ",i);
}