#pragma once
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
// добавьте неоходимые include-директивы сюда

class SingleLinkedList {

    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator {
        friend class SingleLinkedList;

        explicit BasicIterator(Node* node) {
            node_ = node;
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type>& other) noexcept {
            node_ = other.node_;
        }

        BasicIterator& operator=(const BasicIterator& rhs) =
            default;

        [[nodiscard]] bool operator==
            (const BasicIterator<const Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        [[nodiscard]] bool operator!=
            (const BasicIterator<const Type>& rhs) const noexcept {
            return node_ != rhs.node_;
        }

        [[nodiscard]] bool operator==
            (const BasicIterator<Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        [[nodiscard]] bool operator!=
            (const BasicIterator<Type>& rhs) const noexcept {
            return node_ != rhs.node_;
        }

        BasicIterator& operator++() noexcept {
            this->node_ = this->node_->next_node;
            return *this;
        }

        BasicIterator operator++(int) noexcept {
            auto old_value(*this);
            ++(*this);
            return old_value;
        }

        [[nodiscard]] reference operator*() const noexcept {
            return node_->value;
        }

        [[nodiscard]] pointer operator->() const noexcept {
            return &node_->value;
        }

    private:
        Node* node_ = nullptr;
    };

public:

    SingleLinkedList<Type>() {
        size_ = 0;
    }

    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;



    // Новые функции
    SingleLinkedList(std::initializer_list<Type> values) {
        // Реализуйте конструктор самостоятельно
        auto it = values.end();
        it--;
        while (it != values.begin()) {
            PushFront(*it);
            --it;
        }
        PushFront(*it);
    }

    SingleLinkedList(const SingleLinkedList& other) {
        // Реализуйте конструктор самостоятельно
        assert(size_ == 0 && head_.next_node == nullptr);
        SingleLinkedList temp_list;

        for (auto it_begin = other.begin(); it_begin != other.end(); it_begin++) {
            temp_list.push_back(*it_begin);
        }
        this->swap(temp_list);
    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
        // Реализуйте присваивание самостоятельно
        if (begin() != rhs.begin()) {
            auto lst(rhs);
            swap(lst);
        }
        return *this;
    }

    // Обменивает содержимое списков за время O(1)
    void swap(SingleLinkedList& other) noexcept {
        std::swap(this->head_.next_node, other.head_.next_node);
        std::swap(this->size_, other.size_);
    }


    //Новые методы урок 6

        // Возвращает итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] Iterator before_begin() noexcept {
        // Реализуйте самостоятельно
        return Iterator(const_cast<Node*>(&head_));
    }

    // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
        // Реализуйте самостоятельно
        return ConstIterator(const_cast<Node*>(&head_));
    }

    // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator before_begin() const noexcept {
        // Реализуйте самостоятельно
        return Iterator(const_cast<Node*>(&head_));
    }

    /*
     * Вставляет элемент value после элемента, на который указывает pos.
     * Возвращает итератор на вставленный элемент
     * Если при создании элемента будет выброшено исключение, список останется в прежнем состоянии
     */
    Iterator InsertAfter(ConstIterator pos, const Type& value) {
        // Заглушка. Реализуйте метод самостоятельно
        if (pos == end()) { return Iterator{ nullptr }; }
        Node* N1 = new Node(value, pos.node_->next_node);
        pos.node_->next_node = N1;
        size_++;
        return Iterator(const_cast<Node*>(N1));
    }

    void PopFront() noexcept {
        // Реализуйте метод самостоятельно
        Node* p = head_.next_node;
        head_.next_node = p->next_node;
        delete p;
    }

    /*
     * Удаляет элемент, следующий за pos.
     * Возвращает итератор на элемент, следующий за удалённым
     */
    Iterator EraseAfter(ConstIterator pos) noexcept {
        // Заглушка. Реализуйте метод самостоятельно
        if (pos == end()) { return Iterator{ nullptr }; }
        if (pos.node_->next_node != nullptr) {
            Node* element_del = pos.node_->next_node;
            pos.node_->next_node = element_del->next_node;
            delete element_del;
            size_--;
            return Iterator(const_cast<Node*>(pos.node_));
        }
        else
        {
            return Iterator(const_cast<Node*>(pos.node_));
        }

    }




    [[nodiscard]] Iterator begin() noexcept {
        return Iterator(head_.next_node);
    }
    [[nodiscard]] Iterator end() noexcept {
        return Iterator(nullptr);
    }

    [[nodiscard]] ConstIterator begin() const noexcept {
        return ConstIterator(head_.next_node);
    }

    [[nodiscard]] ConstIterator end() const noexcept {
        return ConstIterator(nullptr);
    }

    [[nodiscard]] ConstIterator cbegin() const noexcept {
        return ConstIterator(head_.next_node);
    }

    [[nodiscard]] ConstIterator cend() const noexcept {
        return ConstIterator(nullptr);
    }

    [[nodiscard]] size_t GetSize() const noexcept {
        return size_;
    }

    [[nodiscard]] bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    void PushFront(const Type& value) {
        head_.next_node = new Node(value, head_.next_node);
        ++size_;
    }

    Type get_tail_value() {
        return tail_->value;
    }


    void push_back(const Type& value) {
        Node* p = new Node(value, nullptr);
        if (IsEmpty()) {
            head_.next_node = p;
            tail_ = p;
            ++size_;
            return;
        }
        tail_->next_node = p;
        tail_ = p;
        ++size_;
    }


    void Clear() noexcept {
        Node* next_node;
        while (head_.next_node != nullptr) {
            next_node = head_.next_node->next_node;
            delete head_.next_node;
            head_.next_node = next_node;
        }
        size_ = 0;
    }

    ~SingleLinkedList() {
        Clear();
    }

private:
    Node head_;
    Node* tail_;
    size_t size_ = 0;
};

// внешние функции разместите здесь
template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}