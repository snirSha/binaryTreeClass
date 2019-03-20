namespace ariel{
class Tree {
private:

	struct node
	{
		int key;
		node* left;
		node* right;
	};

	node* _root;
	void insertPrivate(int key, node* ptr);
	void printPrivate(node* ptr);
	node* ReturnNodePrivate(int key, node* ptr);
	void removePrivate(int key, node* parent);
	void removeRootMatch();
	void removeMatch(node* parent, node* match, bool left);
	int findSmallestPrivate(node* ptr);
	node* CreatLeaf(int key);
	node* ReturnNode(int key);
	void removeSubtree(node* ptr);
	bool containsPrivate(int key,node* ptr);
	int leftPrivate(int key,node* ptr);
	int rightPrivate(int key,node* ptr);
	int parentPrivate (int key, node* ptr);
	int sizePrivate(node* ptr);
	
public:

	Tree();
	~Tree();
	void insert(int key);
	void print();
	int root();
	void children(int key);
	int findSmallest();
	void remove(int key);
	bool contains(int key);

	int left(int key);
	int right(int key);
	int parent (int key);
	int size();

}; 
};
