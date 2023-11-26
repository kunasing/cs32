#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator(std::vector<ValueType>* values)
        {
            m_values = values;
        }
        Iterator(){
            m_values = nullptr;
        }

        ValueType& get_value() const
        {
            if (is_valid() == false)
                exit(101);
                
            return (*m_values)[m_valOn];
        }

        bool is_valid() const
        {
            if (m_values == nullptr)
                return false;
            return m_valOn < m_values->size();
        }

        void advance()
        {
            m_valOn++;
        }

      private:
        std::vector<ValueType>* m_values;
        int m_valOn = 0;
    };

    
    // Functions
    TreeMultimap()
    {
        // Does not need to do anything
    }

    ~TreeMultimap()
    {
        clearNodes(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
            m_root = new Node(key, value);
        else
            insertFromRoot(key, value, m_root);
    }

    Iterator find(const KeyType& key) const
    {
        Node* valueBranch = findFromRoot(key, m_root);
        if (valueBranch == nullptr)
            return Iterator();  // Replace this line with correct code.
        else
            return Iterator(&valueBranch->values);
    }

  private:
    // Node
    struct Node{
        Node(const KeyType& key1, const ValueType& val1){
            key = key1;
            values.push_back(val1);
            lessTree = greaterTree = nullptr;
        }
        
        KeyType key;
        std::vector<ValueType> values;
        Node* lessTree, * greaterTree;
        
    };
    
    // Root
    Node* m_root = nullptr;
    
    
    // recursive insert
    void insertFromRoot(const KeyType& key, const ValueType& value, Node*& current){
        
        if (current == nullptr){
            current = new Node(key, value);
            return;
        }
        
        if (key == current->key){
            current->values.push_back(value);
            return;
        }
        else if (key < current->key){
            insertFromRoot(key, value, current->lessTree);
        }
        else if (key > current->key){
            insertFromRoot(key, value, current->greaterTree);
        }
        
        return;
    }
    
    // recursive find
    Node* findFromRoot(const KeyType& key, Node* current) const{
        if (current == nullptr)
            return nullptr;
        
        if (key == current->key)
            return current;
        else if (key < current->key)
            current = current->lessTree;
        else if (key > current->key)
            current = current->greaterTree;
        
        return findFromRoot(key, current);
    }
    
    // recursive clear and deallocation of all nodes
    void clearNodes(Node* current){
        if (current == nullptr)
            return;
        
        clearNodes(current->lessTree);
        clearNodes(current->greaterTree);
        
        delete current;
        
    }
    
};

#endif // TREEMULTIMAP_INCLUDED
