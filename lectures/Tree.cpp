// #include <iostream>
// #include <type_traits>

// class ASTNode;

// class NodeOwner {
//     ASTNode* node = nullptr;
// public:
//     explicit NodeOwner(ASTNode* node) : node(node) {}

//     NodeOwner(const NodeOwner&) = delete;
//     NodeOwner& operator=(const NodeOwner&) = delete;
//     NodeOwner(NodeOwner&& other) { std::swap(node, other.node); }
//     NodeOwner& operator=(NodeOwner&& other) { std::swap(node, other.node); return *this; }

//     ASTNode* operator->() { return node; }
//     const ASTNode* operator->() const { return node; }
//     operator bool() const { return (bool)node; }

//     ~NodeOwner();
// };

/*

Реализации классов ASTNode, ASTNumberNode, ASTPlusNode и ASTMinusNode.
Реализации операторов operator+ и operator-.

*/

class ASTNode {
public:
    virtual void print() {}
    virtual int get_value() { return 0; }
    virtual ~ASTNode() {}
};

class ASTNumberNode : ASTNode {
    int value;
public:
    ASTNumberNode(int value) : value(value) {}
    static NodeOwner create(int value = 0) {
        return NodeOwner(new ASTNumberNode(value));
    }

    void print() {
        std::cout << value;
    }

    int get_value() {
        return value;
    }

    ~ASTNumberNode() = default;
};

class ASTPlusNode : ASTNode {
    NodeOwner left, right;
public:
    ASTPlusNode(NodeOwner left, NodeOwner right) : left(std::move(left)), right(std::move(right)) {}
    static NodeOwner create(NodeOwner left, NodeOwner right) {
        return std::move(NodeOwner(new ASTPlusNode(std::move(left), std::move(right))));
    }

    void print() {
        std::cout << "(";
        left->print();
        std::cout << " + ";
        right->print();
        std::cout << ")";
    }

    int get_value() {
        return left->get_value() + right->get_value();
    }

    ~ASTPlusNode() = default;
};

class ASTMinusNode : ASTNode {
    NodeOwner left, right;
public:
    ASTMinusNode(NodeOwner left, NodeOwner right) : left(std::move(left)), right(std::move(right)) {}
    static NodeOwner create(NodeOwner left, NodeOwner right) {
        return std::move(NodeOwner(new ASTMinusNode(std::move(left), std::move(right))));
    }

    void print() {
        std::cout << "(";
        left->print();
        std::cout << " - ";
        right->print();
        std::cout << ")";
    }

    int get_value() {
        return left->get_value() - right->get_value();
    }

    ~ASTMinusNode() = default;

};

NodeOwner operator+(NodeOwner left, NodeOwner right) {
    return std::move(NodeOwner(ASTPlusNode::create(std::move(left), std::move(right))));
}

NodeOwner operator-(NodeOwner left, NodeOwner right) {
    return std::move(NodeOwner(ASTMinusNode::create(std::move(left), std::move(right))));
}


// NodeOwner::~NodeOwner() {
//     if (node)
//         delete node;
// }

// int main() {
//     // static_assert(std::is_same::value, "ASTNumberNode::create() must return NodeOwner value");
//     // static_assert(std::is_same::value, "ASTPlusNode::create() must return NodeOwner value");
//     // static_assert(std::is_same::value, "(NodeOwner + NodeOwner) must return NodeOwner value");

//     auto expr_1 = ASTPlusNode::create(
//         ASTNumberNode::create(1),
//         ASTMinusNode::create(
//             ASTNumberNode::create(2),
//             ASTNumberNode::create(3)
//         )
//     );
//     expr_1->print();
//     std::cout << " = " << expr_1->get_value() << std::endl;

//     auto expr_2 = ASTNumberNode::create(4) - ASTNumberNode::create(5) + ASTNumberNode::create(6);
//     expr_2->print();
//     std::cout << " = " << expr_2->get_value() << std::endl;

//     return 0;
// }