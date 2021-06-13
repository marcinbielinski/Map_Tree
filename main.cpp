#include <iostream>
#include <memory>

/*
      5
     / \
    4  130
   / \
  3   8

DFS: 5 4 3 8 130

*/
template <typename K, typename V>
struct tree_node
{
    tree_node(K&& key, V&& value)
            : key(std::move(key))
            , value(std::move(value))
            , left(nullptr)
            , right(nullptr)
    {}

    void print()
    {
        std::cout << "key is : " << key << " value is: " << value << std::endl;
    }

    K key;
    V value;

    std::unique_ptr<tree_node<K, V>> left;
    std::unique_ptr<tree_node<K, V>> right;
};

template <typename Key, typename Value>
class my_map
{
    using tree_node_t = tree_node<Key, Value>;

public:
    my_map() : size(0), root(nullptr) {}

    bool insert(std::pair<Key, Value> values)
    {
        auto& wanted_key = values.first;
        auto& wanted_value = values.second;

        if(root == nullptr)
        {
            root = std::make_unique<tree_node_t>(std::move(wanted_key), std::move(wanted_value));
            ++size;
            return true;
        }
        else // we have a root already
        {
            bool ret = insert_recursive(wanted_key, wanted_value, root.get());
            if(ret)
                ++size;

            return ret;
        }
    }

    void print_dfs()
    {
        print_dfs_recursive(root.get());
    }

private:
    void print_dfs_recursive(tree_node_t* node)
    {
        if(node == nullptr)
            return;

        node->print();
        std::cout << "starting recursive call, node key is: " << node->key << std::endl;
        print_dfs_recursive(node->left.get());
        std::cout << "after left hand recursion, node key is: " << node->key << std::endl;
        print_dfs_recursive(node->right.get());
        std::cout << "after right hand recursion, node key is: " << node->key << std::endl;

//        return; // go one level up in stack
    }

    bool insert_recursive(Key& wanted_key, Value& wanted_value, tree_node_t* node)
    {
        if(wanted_key == node->key)
        {
            return false;
        }
        if(wanted_key < node->key)
        {
            if(node->left != nullptr)
            {
                return insert_recursive(wanted_key, wanted_value, node->left.get());
            }
            else if(node->left == nullptr)
            {
                node->left = std::make_unique<tree_node_t>(std::move(wanted_key), std::move(wanted_value));
                return true;
            }
        }
        if(wanted_key > node->key)
        {
            if(node->right != nullptr)
            {
                return insert_recursive(wanted_key, wanted_value, node->right.get());
            }
            else if(node->right == nullptr)
            {
                node->right = std::make_unique<tree_node_t>(std::move(wanted_key), std::move(wanted_value));
                return true;
            }
        }
        return false;
    }

    size_t size;
    std::unique_ptr<tree_node_t> root;
};

/*
 *    d
 *   / \
 *  b   y
   /   / \
  a   s   z

  */

int main()
{
    my_map<std::string, int> map1;

    std::cout << std::boolalpha << map1.insert({"d", 15}) << std::endl;
    std::cout << std::boolalpha << map1.insert({"b", 15}) << std::endl;
    std::cout << std::boolalpha << map1.insert({"a", 15}) << std::endl;
    std::cout << std::boolalpha << map1.insert({"y", 15}) << std::endl;
    std::cout << std::boolalpha << map1.insert({"z", 15}) << std::endl;
    std::cout << std::boolalpha << map1.insert({"z", 15}) << std::endl; // not unique key
    std::cout << std::boolalpha << map1.insert({"s", 15}) << std::endl;

    map1.print_dfs();
    return 0;
}