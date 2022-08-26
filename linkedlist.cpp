#include <iostream>
using namespace std;

class Node{
	public:
		int data;
		Node *next;
};

class LinkedList{
	Node *head;
	int count{0};
	public:
		LinkedList(){
			head=NULL;
		}
		void addNode(int data){
			Node *p,*q=NULL;
			if(head==NULL){
				q = new Node;
				q->data=data;
				q->next=NULL;
				head=q;
				p=head;
				count++;
			}else{
				q=new Node;
				q->data = data;
				q->next=NULL;
				p->next=q;
				p=q;
				count++;
			}
		}
		void insertBetween(int data,int pos){
			Node *q,*p,*x;
			if(pos==count){
				return;
			}
			if(pos==1){
				q=new Node;
				q->data=data;
				q->next=head;
				head=q;
				count++;
			}else{
				q=head;
				int i{1};
				while(q){
					// 4->5->6->8->12
					if(i==pos){
						x=new Node;
						x->data=data;
						p->next=x;
						x->next=q;
						count++;
						break;
					}
					i++;
					p=q;
					q=q->next;
				}
			}
		}
		void print(){
			Node *q;
			q=head;
			while(q){
				cout << q->data<<" ";
				q=q->next;
			}
			cout <<endl;
		}
		void deleteNode(int data){
			Node *q,*n;
			if(head->data==data){
				q=head;
				head=head->next;
				q->next=NULL;
				delete q;
			}else{
				q=head;
				while(q){
					if(q->data==data){
						n->next=q->next;
						q->next=NULL;
						break;
					}
					n=q;
					q=q->next;
				}
				delete q;
			}
		}
		void search(int data){
			Node *q;
			q=head;
			while(q){
				if(q->data==data){
					cout<< q->data<<endl;
					break;
				}
				q=q->next;
			}
			delete q;
		}
};
// 4->5->6->8
int main(){
	LinkedList l;
	l.addNode(4);
	l.addNode(6);
	l.addNode(8);
	l.addNode(12);
	l.print();
	l.deleteNode(6);
	l.print();
	l.insertBetween(5,2);
	l.print();
	
}
