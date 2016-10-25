/* Author     : Pallavi
   Created on : 23-10-2016
*/

#include <iostream>
#include <cstdlib>
using namespace std;

struct node{
	int value;
	node *left=NULL;
	node *right=NULL;
}*root;

class bstTree{
	public:
		void insert(node *,node *);
		void find(int, node **, node **);
		void print(node *,int);
		node* search(node *,int);
		void case_a(node *,node *);
        void case_b(node *,node *);
        void case_c(node *,node *);
		void removeEle(int);
		node* min(node *);
		node* max(node *);
		void successor(node *,int);
		void predecessor(node *, int);
		bstTree(){
			root = NULL;
		}
};

int main (){
	int choice,data;
	bstTree bst;
	node *temp;
	while(1){
		cout<<"\n";
		cout<<"1.Insert Element "<<endl;
        cout<<"2.Find Element "<<endl;
        cout<<"3.Remove Element"<<endl;
        cout<<"4.Find min element"<<endl;
        cout<<"5.Find max element"<<endl;
        cout<<"6.Find successor"<<endl;
        cout<<"7.Find predecessor"<<endl;
        cout<<"8.Print Elements"<<endl;
        cout<<"9.Quit"<<endl;
        cout<<"What you wish to do? Input your choice.";
        cout<<"\n";
        cin>>choice;
        switch(choice){
        	case 1:
        		temp = new node;
        		cout<<"Input element ";
        		cin>>data;
        		temp->value = data;
        		bst.insert(root,temp);
        		break;
        	case 2:
        		cout<<"Enter the number to be found\n";
        		node *result1;
        		cin>>data;
        		result1 = bst.search(root,data);
        		if (result1 != NULL){
        			cout<<"element found \n";
        		}else{
        			cout<<"element not found\n";
        		}
        		break;
        	case 3:
        		cout<<"Enter the number to be deleted \n";
        		cin>>data;
        		bst.removeEle(data);
        		break;
        	case 4:
        		cout<<"min element is:\n";
        		node *result2;
        		result2 = bst.min(root);
        		if (result2 == NULL)
        			cout<<"BST is empty\n";
        		break;
        	case 5:
        		cout<<"max element is:\n";
        		node *result3;
        		result3 = bst.max(root);
        		if (result3 == NULL){
        			cout<<"BST is empty\n";
        		}
        		break;
        	case 6:
        		cout<<"Input element to find its successor\n";
        		cin>>data;
        		bst.successor(root,data);
        		break;
        	case 7:
        		cout<<"Input element to find its predecessor\n";
        		cin>>data;
        		bst.predecessor(root,data);
        		break;
        	case 8:
        		cout<<"printing the tree \n";
        		bst.print(root,1);
        		cout<<"\n";
        		break;
        	case 9:
        		exit(1);
        	default:
        		cout<<"Wrong input\n";
        }
	}
	return 0;
}

void bstTree::insert(node *currNode, node *temp){
	if(root == NULL){
		root = new node;
		root->value = temp->value;
		root->left=NULL;
		root->right=NULL;
		cout<<"root node added\n";
		return;
	}else if (temp->value == currNode->value){
		cout<<"element already present in the bst\n";
		return;
	}else if (temp->value < currNode->value){
		if(currNode->left != NULL){
			insert(currNode->left,temp);
		}else{
			temp->left = NULL;
			temp->right = NULL;
			currNode->left = temp;
			cout<<"element added to the left of the tree\n";
			return;
		}
	}else{
		if(currNode->right != NULL){
			insert(currNode->right,temp);
		}else{
			temp->left = NULL;
			temp->right = NULL;
			currNode->right = temp;
			cout<<"element added to the right of the tree\n";
			return;
		}
	}	
}

node *bstTree::search(node *currNode, int key){
	if(root == NULL){
		cout<<"BST empty \n";
		return 0;
	}else if(currNode->value == key){
		return currNode;
	}else if (key < currNode->value){
		if(currNode->left != NULL){
			search(currNode->left,key);
		}else{
			return NULL;
		}
	}else{
		if(currNode->right != NULL){
			search(currNode->right,key);
		}else{
			return NULL;
		}
	}
	
	
}

void bstTree::case_a(node *par, node *loc )
{
    if (par == NULL)
    {
        root = NULL;
    }
    else
    {
        if (loc == par->left)
            par->left = NULL;
        else
            par->right = NULL;
    }
}
 
void bstTree::case_b(node *par, node *loc)
{
    node *child;
    if (loc->left != NULL)
        child = loc->left;
    else
        child = loc->right;
    if (par == NULL)
    {
        root = child;
    }
    else
    {
        if (loc == par->left)
            par->left = child;
        else
            par->right = child;
    }
}
 

void bstTree::case_c(node *par, node *loc)
{
    node *ptr, *ptrsave, *suc, *parsuc;
    ptrsave = loc;
    ptr = loc->right;
    while (ptr->left != NULL)
    {
        ptrsave = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrsave;
    if (suc->left == NULL && suc->right == NULL)
        case_a(parsuc, suc);
    else
        case_b(parsuc, suc);
    if (par == NULL)
    {
        root = suc;
    }
    else
    {
        if (loc == par->left)
            par->left = suc;
        else
            par->right = suc;
    }
    suc->left = loc->left;
    suc->right = loc->right;
}

void bstTree::find(int item, node **par, node **loc)
{
    node *ptr, *ptrsave;
    if (root == NULL)
    {
        *loc = NULL;
        *par = NULL;
        return;
    }
    if (item == root->value)
    {
        *loc = root;
        *par = NULL;
        return;
    }
    if (item < root->value)
        ptr = root->left;
    else
        ptr = root->right;
    ptrsave = root;
    while (ptr != NULL)
    {
        if (item == ptr->value)
        {
            *loc = ptr;
            *par = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item < ptr->value)
            ptr = ptr->left;
    	else
    	    ptr = ptr->right;
    }
    *loc = NULL;
    *par = ptrsave;
}

void bstTree::removeEle(int key){
	node *parent, *location;
    if (root == NULL)
    {
        cout<<"Tree empty"<<endl;
        return;
    }
    find(key, &parent, &location);
    if (location == NULL)
    {
        cout<<"Item not present in tree"<<endl;
        return;
    }
    if (location->left == NULL && location->right == NULL)
        case_a(parent, location);
    if (location->left != NULL && location->right == NULL)
        case_b(parent, location);
    if (location->left == NULL && location->right != NULL)
        case_b(parent, location);
    if (location->left != NULL && location->right != NULL)
        case_c(parent, location);
    free(location);
}

node* bstTree::min(node *currNode){
	if(root == NULL){
		cout<< "BST is empty. Nothing to find\n";
		return NULL;
	}else{
		while(currNode->left != NULL){
			currNode = currNode->left;
		}
		cout<<currNode->value<<"\n";
		return currNode;
	}

}

node *bstTree::max(node *currNode){
	if(root == NULL){
		cout<< "BST is empty. Nothing to find\n";
		return NULL;
	}else{
		while(currNode->right != NULL){
			currNode = currNode->right;
		}
		cout<<currNode->value<<"\n";
		return currNode;
	}

}

void bstTree::successor(node *root,int key){
	node * currNode;
	node * minOfRight;
	currNode = search(root,key);
	if(currNode != NULL){
		if ((currNode == root) && (currNode->left == NULL) && (currNode->right == NULL)){
			cout << "no successor \n";
		}
		else if(currNode->right != NULL){
			minOfRight = min(currNode->right);
		}else{
			node *parent, *next;
			parent = root;
			next = root;
			while(next != NULL){
				if(next->value < key){
					parent = next;
					next = next->right;

				}else if(next->value > key){
					parent = next;
					next = next->left;
				}else{
					break;	
				}
			}if((next->left == NULL) && (next->right == NULL) && (parent->right != NULL)){
				cout << "no successor \n";
			}else if((next->left == NULL) && (next->right == NULL) && (parent->right == NULL)){
				cout << "successor "<<parent->value<<"\n";
			}
		}
	}else{
		cout<<"no successor\n";
	}
}

void bstTree::predecessor(node *root,int key){
	node * currNode;
	node * maxOfLeft;
	currNode = search(root,key);
	if(currNode != NULL){
		if(currNode == root){
			cout<<"no predecessor \n";
		}
		else if(currNode->left != NULL){
			maxOfLeft = max(currNode->left);
		}
		else{
			node *parent, *next;
			parent = root;
			next = root;
			while(next != NULL){
				if(key > next->value){
					parent = next;
					next = next->right;

				}else if (key < next->value){
					next = next->left;
				}else{
					break;
				}
			}
			cout<<"predecessor "<<parent->value<<"\n";
		}
	}else{
		cout<<"no predecessor \n";
	}
}

void bstTree::print(node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        print(ptr->right, level+1);
        cout<<endl;
        if (ptr == root)
            cout<<"start->:  ";
        else
        {
            for (i = 0;i < level;i++)
                cout<<"       ";
	    }
        cout<<ptr->value;
        print(ptr->left, level+1);
    }
}
