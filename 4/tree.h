#pragma once

#include <memory>

namespace NBinTree {

template <typename T>
class TNode : public std::enable_shared_from_this<TNode<T>> {
public:
    using TNodePtr = std::shared_ptr<TNode<T>>;
    using TNodeConstPtr = std::shared_ptr<const TNode<T>>;

    bool HasLeft() const {
        return Left != nullptr;
    }

    bool HasRight() const {
        return Right != nullptr;
    }

    bool HasParent() const {
        return !Parent.expired();
    }

    T& GetValue() {
        return Value;
    }

    const T& GetValue() const {
        return Value;
    }

    TNodePtr GetLeft() {
        return Left;
    }

    TNodeConstPtr GetLeft() const {
        return Left;
    }

    TNodePtr GetRight() {
        return Right;
    }

    TNodeConstPtr GetRight() const {
        return Right;
    }

    TNodePtr GetParent() {
        return Parent.lock(); // Convert weak_ptr to shared_ptr
    }

    TNodeConstPtr GetParent() const {
        return Parent.lock(); // Convert weak_ptr to shared_ptr
    }

    // Fork now accepts raw pointers instead of shared_ptr
    static TNodePtr Fork(T value, TNode* left, TNode* right) {
        // Use shared_from_this() to convert raw pointers to shared_ptr
        TNodePtr leftPtr = (left) ? left->shared_from_this() : nullptr;
        TNodePtr rightPtr = (right) ? right->shared_from_this() : nullptr;

        TNodePtr ptr = TNodePtr(new TNode(value, leftPtr, rightPtr));
        SetParent(ptr->GetLeft(), ptr);
        SetParent(ptr->GetRight(), ptr);
        return ptr;
    }

    TNodePtr ReplaceLeft(TNodePtr left) {
        SetParent(left, this->shared_from_this());
        SetParent(Left, nullptr);  // Unset previous Left's parent
        std::swap(left, Left);
        return left;
    }

    TNodePtr ReplaceRight(TNodePtr right) {
        SetParent(right, this->shared_from_this());
        SetParent(Right, nullptr);  // Unset previous Right's parent
        std::swap(right, Right);
        return right;
    }

    TNodePtr ReplaceRightWithLeaf(T value) {
        return ReplaceRight(CreateLeaf(value));
    }

    TNodePtr ReplaceLeftWithLeaf(T value) {
        return ReplaceLeft(CreateLeaf(value));
    }

    TNodePtr RemoveLeft() {
        return ReplaceLeft(nullptr);
    }

    TNodePtr RemoveRight() {
        return ReplaceRight(nullptr);
    }

    static TNodePtr CreateLeaf(T value) {
        return TNodePtr(new TNode(value));
    }

private:
    T Value;
    TNodePtr Left = nullptr;
    TNodePtr Right = nullptr;
    std::weak_ptr<TNode<T>> Parent;  // Use weak_ptr to avoid cycles

    // Make constructors private so only factory methods can call them
    TNode(T value)
        : Value(value) {}

    TNode(T value, TNodePtr left, TNodePtr right)
        : Value(value), Left(left), Right(right) {}

    static void SetParent(TNodePtr node, TNodePtr parent) {
        if (node) {
            node->Parent = parent;  // Set the weak pointer to avoid circular references
        }
    }
};

} // namespace NBinTree
