#include<iostream>
#include<cstdlib>

#include"Tree.hpp"

using namespace std;
using namespace ariel;



Tree::Tree()
{
	_root = NULL;

}

Tree::node* Tree::CreatLeaf(int key)
{
	if(contains(key)==true)
	{
		throw std::invalid_argument("key already exist");
		return NULL;
	}
	node* n = new node;
	n->key = key;
	n->left = NULL;
	n->right = NULL;

	return n;
}

void Tree::insert(int key)
{
	insertPrivate(key, _root);
}

void Tree::insertPrivate(int key, node* ptr)
{
	//check if root is NULL then key will be the root
	if (_root == NULL&&!contains(key))
	{
		_root = CreatLeaf(key);
	}
	//if root already exist then check if key is smaller then root
	//then creat another leaf on the left side
	//otherwise creat a leaf on the right side
	else if (key < ptr->key)
	{
		if (ptr->left != NULL)
		{
			insertPrivate(key, ptr->left);
		}
		else
		{
			ptr->left = CreatLeaf(key);
		}
	}
	else if (key > ptr->key)
	{
		if (ptr->right != NULL)
		{
			insertPrivate(key, ptr->right);
		}
		else
		{
			ptr->right = CreatLeaf(key);
		}
	}
	//key is already in the tree
	else
	{
		throw std::invalid_argument("the key has already been added");
		std::cout << "The key " << key << " has already been added to the tree\n";
	}
}

void Tree::print()
{
	printPrivate(_root);
}

void Tree::printPrivate(node* ptr)
{
	//check if the tree is empty
	if (_root != NULL)
	{
		if (ptr->left != NULL)
		{
			printPrivate(ptr->left);
		}
		std::cout << ptr->key << " ";
		if (ptr->right != NULL)
		{
			printPrivate(ptr->right);
		}
	}
	else
	{
		std::cout << " The tree is empty\n";
	}
}

Tree::node* Tree::ReturnNode(int key)
{
	return ReturnNodePrivate(key, _root);
}

Tree::node* Tree::ReturnNodePrivate(int key, node* ptr)
{
	if (ptr != NULL)
	{
		if (ptr->key == key)
		{
			return ptr;
		}
		else
		{
			if (key < ptr->key)
			{
				return ReturnNodePrivate(key, ptr->left);
			}
			else
			{
				return ReturnNodePrivate(key, ptr->right);
			}
		}
	}
	else
	{
		return NULL;
	}




}

int Tree::root()
{
	if (_root != NULL)
	{
		return _root->key;
	}
	else
	{
	    throw std::invalid_argument("root doesn't exist");
		std::cout << "Root doesn't exist" << endl;
		return -1000;
	}
}
//change return type to int(right and left)
void Tree::children(int key) {
	node* ptr = ReturnNode(key);
	if (ptr != NULL)
	{
		std::cout << "Parent node = " << ptr->key << endl;

		ptr->left == NULL ? 
			std::cout << "Left child = NULL\n":
		std::cout << "Left child = " << ptr->left->key << endl;

		ptr->right == NULL ? 
			std::cout << "Right child = NULL\n":
		std::cout << "Right child = " << ptr->right->key << endl;

	}
	else
	{
		throw std::invalid_argument("key is not in the tree");
		std::cout << "Key " << key << "is not in the tree\n";
	}
}

int Tree::findSmallest()
{
	return findSmallestPrivate(_root);
}

int Tree::findSmallestPrivate(node* ptr)
{
	if (_root == NULL)
	{
		throw std::invalid_argument("The tree is empty");
		std::cout << "The tree is empty\n";
		return -1000;
	}
	else
	{
		if (ptr->left != NULL)
		{
			return findSmallestPrivate(ptr->left);
		}
		else
		{
			//we have made it to the smallest node in subtree
			return ptr->key;
		}
	}
}

void Tree::remove(int key)
{
	removePrivate(key, _root);
}

void Tree::removePrivate(int key, node* parent)
{
	if (_root != NULL)
	{
		if (_root->key == key)
		{
			removeRootMatch();
		}
		else {
			if (key < parent->key && parent->left != NULL)
			{
				parent->left->key == key ?
					removeMatch(parent, parent->left, true):
				removePrivate(key, parent->left);
			}
			else if (key > parent->key && parent->right != NULL)
			{
				parent->right->key == key ?
					removeMatch(parent, parent->right, false):
				removePrivate(key, parent->right);
			}
			else
			{
				throw std::invalid_argument("The key was not found");
				std::cout << "The key " << key << "was not found in the tree\n";
			}
		}
	}
	else
	{
		throw std::invalid_argument("The tree is empty");
		std::cout << "the tree is empty\n";
	}
}

void Tree::removeRootMatch()
{
	if (_root != NULL)
	{
		node* delPtr = _root;
		//store the current root key value in the root key variable
		int rootKey = _root->key;
		//in case our root has 2 children
		int smallestInRightSubtree;

		//case 0 - 0 childrens
		if (_root->left == NULL && _root->right == NULL)
		{
			_root = NULL;
			delete delPtr;
		}

		//case 1 - 1 child
		else if (_root->left == NULL && _root->right != NULL)
		{
			//the root point to the root right node that will become the new root
			_root = _root->right;
			//disconnect the old root from the tree
			delPtr->right = NULL;
			//delete the old root
			delete delPtr;
			cout << "The root node with key " << rootKey << " was deleted. " << " The new root contains key " << _root->key << endl;
		}

		else if (_root->left != NULL && _root->right == NULL)
		{
			_root = _root->left;
			delPtr->left = NULL;
			delete delPtr;
			cout << "The root node with key " << rootKey << " was deleted. " << " The new root contains key " << _root->key << endl;
		}
		//case 2 - 2 child
		else
		{
			//find the smallest value in our root right subtree by calling this func and passing in our root node right pointer.
			smallestInRightSubtree = findSmallestPrivate(_root->right);
			//removing that node from the tree.
			removePrivate(smallestInRightSubtree, _root);
			//overwrite the roots key with the value that was contained in the node containing the smallest key that was contained in our root right subtree.
			_root->key = smallestInRightSubtree;
			cout << "The root key containing " << rootKey << "was overwritten with key " << _root->key << endl;
		}
	}
	else
	{
		throw std::invalid_argument("tree is empty cannot remove root");
		cout << "Can not remove root. The tree is empty\n";
	}

}

void Tree::removeMatch(node* parent, node* match, bool left)
{
	//if our matching node is the left or right child  
	//if true then its the left child 
	//if false then its the right one
	if (_root != NULL)
	{
		node* delPtr;
		int matchKey = match->key;
		//using this variable in case that the node that we want to delete has children.
		int smallestInRightSubtree;

		//case 0 - 0 children
		if (match->left == NULL && match->right == NULL)
		{
			delPtr = match;
			//make sure that the parent of that matching node its left or right pointer is now pointing to null.
			left == true ? parent->left = NULL : parent->right = NULL;
			//delete this matching node.
			delete delPtr;
			cout << "The node containing key " << matchKey << "was removed\n";
		}
		//case 1 - 1 child
		else if (match->left == NULL && match->right != NULL)
		{
			left == true ? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			delPtr = match;
			delete delPtr;
			cout << "The node containing key " << matchKey << "was removed\n";
		}
		else if (match->left != NULL && match->right == NULL)
		{
			left == true ? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			delPtr = match;
			delete delPtr;
			cout << "The node containing key " << matchKey << "was removed\n";
		}
		//case 2 - 2 children
		//find the smallest value in that matching node right subtree.
		else
		{
			smallestInRightSubtree = findSmallestPrivate(match->right);
			//we deleted the node with the smallest value in the right subtree.
			removePrivate(smallestInRightSubtree, match);
			//overaw our matching node (its key value) with the key value that has the smallest key in the right subtree.
			match->key = smallestInRightSubtree;
		}
	}
	else
	{
		cout << "can not remove match. the tree is empty\n";
	}
}
///////////////////////////////////////////////////////

bool Tree::contains(int key)
{
	return containsPrivate(key, _root);

}

bool Tree::containsPrivate(int key,node* ptr)
{
	//if the tree is empty return false
    if(ptr==NULL)
    {
        return false;
        
    }
    //if it found the key return true
    if(ptr->key==key)
    {
        return true;
        
    }
    //recursive call
    else if(key < ptr->key)
    {
        return containsPrivate(key,ptr->left);
        
    }
    else 
    {
        return containsPrivate(key,ptr->right);
        
    }
}
////////////////////////////////////////////////////////////////////
int Tree::left(int key)
{
    return leftPrivate(key,_root);
}

int Tree::leftPrivate(int key,node* ptr)
{
    //if the tree is empty return error message 
    if(ptr==NULL)
    {
	throw std::invalid_argument("no left child");
        cout <<"Sorry, there is no left child\n";
        return -1;
    }
    //if it found the father return the left-child 
    if(ptr->key==key)
    {
        return ptr->left->key;
    }
    //recursive call
    else  if(key < ptr->key)
    {
        return leftPrivate(key,ptr->left);
    }
    else
    {
        return leftPrivate(key,ptr->right);
    }
}
////////////////////////////////////////////////////////////
int Tree::right(int key)
{
    return rightPrivate(key,_root);
}


int Tree::rightPrivate(int key,node* ptr)
{
    //if the tree is empty return error message 
    if(ptr==NULL)
    {
		throw std::invalid_argument("no rigth child");
        cout <<"Sorry, there is no right child\n";
        return -1;
    }
    //if it found the father return the right-child 
    if(ptr->key==key)
    {
        return ptr->right->key;
    }
    //recursive call
    else  if(key < ptr->key)
    {
        return rightPrivate(key,ptr->left);
    }
    else
    {
        return rightPrivate(key,ptr->right);
    }
}
////////////////////////////////////////////////////////////

int Tree::parent (int key)
{
    return parentPrivate (key,_root);
}


int Tree::parentPrivate (int key, node* ptr)
{
    //if the tree is empty or there are no children return error message
    if((ptr==NULL)||(ptr->left==NULL&&ptr->right==NULL))
    {
		throw std::invalid_argument("no parent");
        cout<<"Sorry, there is no parent\n";
        return -1;
    }
    //if it found one of the children return the father
    if((ptr->left!=NULL&&ptr->left->key==key)||(ptr->right!=NULL&&ptr->right->key==key))
    {
        return ptr->key;
    }
    //recursive call
    else if (ptr->key > key)
    {
        return parentPrivate(key,ptr->left);
    }
    else
    {
        return parentPrivate(key,ptr->right);
    }
}
///////////////////////////////////////////////////////
int Tree::size()
{
	return sizePrivate(_root);
}
int Tree::sizePrivate(node* ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}
	else
	{
		return (sizePrivate(ptr->left) + 1 + sizePrivate(ptr->right));
	}
}
//////////////////////////////////////////////////////////

Tree::~Tree()
{
	removeSubtree(_root);
}

void Tree::removeSubtree(node* ptr)
{
	if (ptr != NULL)
	{
		if (ptr->left != NULL)
		{
			removeSubtree(ptr->left);
		}
		if (ptr->right != NULL)
		{
			removeSubtree(ptr->right);
		}
		cout << "Deleting the node containing key" << ptr->key << endl;
		delete ptr;
	}
}

