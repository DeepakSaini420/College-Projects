#include <iostream>
using namespace std;

class Node{
	public:
		Node *front;
		int data{0};
		Node *next;
};

class DLL{
	Node *head;
	public:
		DLL(){
			head=NULL;
		}
		void insert(int data){
			// NULL<-5-><-6->NULL
			Node *q,*p=NULL;
			if(head==NULL){
				p = new Node;
				p->front = NULL;
				p->data=data;
				p->next = NULL;
				q=p;
				head=p;
			}else{
				p = new Node;
				p->front=q;
				p->data = data;
				p->next=NULL;
				q->next = p;
				q=p;
			}
		}
		void print(){
			Node *q=NULL;
			q=head;
			while(q){
				cout << q->data <<" ";
				q = q->next;
			}
			cout << endl;
		}
		void search(int data){
			Node *q=NULL;
			q=head;
			while(q){
				if(q->data==data){
					cout << q->data <<endl;
					break;
				}
				q=q->next;
			}
		}
		void Delete(int data){
			Node *q=NULL;
			q=head;
			while(q){
				if(q->data==data){
					q->front->next=q->next;
					q->front=NULL;
					q->next=NULL;
					break;
				}
				q=q->next;
			}
		}
};

int main(){
	DLL l;
	l.insert(5);
	l.insert(6);
	l.insert(12);
	l.insert(15);
	l.print();
	l.search(6);
	l.Delete(6);
	l.print();
}
