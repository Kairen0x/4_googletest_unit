#include <iostream>
#include <vector>
#include <memory>
#include <string>

// ============================================
// 1. КЛАСС ОЧЕРЕДИ (QUEUE)
// ============================================
template <typename T>
class Queue {
private:
    std::vector<T> elements;
    
public:
    void push(const T& value) {
        elements.push_back(value);
    }
    
    T pop() {
        if (elements.empty()) return T();
        T front = elements.front();
        elements.erase(elements.begin());
        return front;
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

// ============================================
// 2. КЛАСС КУЧИ (HEAP)
// ============================================
template <typename T>
class Heap {
private:
    std::vector<T> heap;
    
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] <= heap[parent]) break;
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
    }
    
    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;
            
            if (left < size && heap[left] > heap[largest]) largest = left;
            if (right < size && heap[right] > heap[largest]) largest = right;
            if (largest == index) break;
            
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
    }
    
public:
    void push(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
    
    T pop() {
        if (heap.empty()) return T();
        T result = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
        return result;
    }
    
    T top() const {
        return heap.empty() ? T() : heap[0];
    }
    
    bool empty() const {
        return heap.empty();
    }
    
    size_t size() const {
        return heap.size();
    }
};

// ============================================
// 3. КЛАСС БИНАРНОГО ДЕРЕВА
// ============================================
template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    std::unique_ptr<Node> root;
    
    void insertRecursive(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
            return;
        }
        if (value < node->data) {
            insertRecursive(node->left, value);
        } else if (value > node->data) {
            insertRecursive(node->right, value);
        }
    }
    
    bool searchRecursive(const std::unique_ptr<Node>& node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return searchRecursive(node->left, value);
        return searchRecursive(node->right, value);
    }
    
    T popMinRecursive(std::unique_ptr<Node>& node) {
        if (!node->left) {
            T minValue = node->data;
            node = std::move(node->right);
            return minValue;
        }
        return popMinRecursive(node->left);
    }
    
public:
    BinaryTree() : root(nullptr) {}
    
    void push(const T& value) {
        insertRecursive(root, value);
    }
    
    T pop() {
        if (!root) return T();
        return popMinRecursive(root);
    }
    
    bool search(const T& value) const {
        return searchRecursive(root, value);
    }
    
    bool empty() const {
        return root == nullptr;
    }
};

// ============================================
// 4. ТЕСТОВЫЙ ФРЕЙМВОРК
// ============================================
class TestResult {
public:
    static int totalTests;
    static int passedTests;
    static int failedTests;
    
    static void assertEquals(int expected, int actual, const std::string& testName) {
        totalTests++;
        if (expected == actual) {
            passedTests++;
            std::cout << "[✓] " << testName << std::endl;
        } else {
            failedTests++;
            std::cout << "[✗] " << testName << " (ожидалось: " << expected 
                     << ", получено: " << actual << ")" << std::endl;
        }
    }
    
    static void assertTrue(bool condition, const std::string& testName) {
        totalTests++;
        if (condition) {
            passedTests++;
            std::cout << "[✓] " << testName << std::endl;
        } else {
            failedTests++;
            std::cout << "[✗] " << testName << " (условие ложно)" << std::endl;
        }
    }
    
    static void assertFalse(bool condition, const std::string& testName) {
        assertTrue(!condition, testName);
    }
};

int TestResult::totalTests = 0;
int TestResult::passedTests = 0;
int TestResult::failedTests = 0;

// ============================================
// 5. ТЕСТЫ ДЛЯ КАЖДОГО КЛАССА
// ============================================
void testQueue() {
    std::cout << "\n=== ТЕСТИРОВАНИЕ ОЧЕРЕДИ ===" << std::endl;
    
    Queue<int> q;
    
    TestResult::assertTrue(q.empty(), "Очередь должна быть пустой");
    TestResult::assertEquals(0, static_cast<int>(q.size()), "Размер очереди должен быть 0");
    
    q.push(10);
    q.push(20);
    q.push(30);
    TestResult::assertFalse(q.empty(), "Очередь не должна быть пустой");
    TestResult::assertEquals(3, static_cast<int>(q.size()), "Размер очереди должен быть 3");
    
    TestResult::assertEquals(10, q.pop(), "Первый pop должен вернуть 10");
    TestResult::assertEquals(2, static_cast<int>(q.size()), "Размер очереди должен быть 2");
    TestResult::assertEquals(20, q.pop(), "Второй pop должен вернуть 20");
    TestResult::assertEquals(30, q.pop(), "Третий pop должен вернуть 30");
    TestResult::assertTrue(q.empty(), "Очередь должна быть пустой");
}

void testHeap() {
    std::cout << "\n=== ТЕСТИРОВАНИЕ КУЧИ ===" << std::endl;
    
    Heap<int> h;
    
    TestResult::assertTrue(h.empty(), "Куча должна быть пустой");
    TestResult::assertEquals(0, static_cast<int>(h.size()), "Размер кучи должен быть 0");
    
    h.push(5);
    h.push(3);
    h.push(8);
    h.push(1);
    h.push(6);
    
    TestResult::assertFalse(h.empty(), "Куча не должна быть пустой");
    TestResult::assertEquals(5, static_cast<int>(h.size()), "Размер кучи должен быть 5");
    TestResult::assertEquals(8, h.top(), "Максимальный элемент должен быть 8");
    
    TestResult::assertEquals(8, h.pop(), "Первый pop должен вернуть 8");
    TestResult::assertEquals(6, h.pop(), "Второй pop должен вернуть 6");
    TestResult::assertEquals(5, h.pop(), "Третий pop должен вернуть 5");
    TestResult::assertEquals(3, h.pop(), "Четвертый pop должен вернуть 3");
    TestResult::assertEquals(1, h.pop(), "Пятый pop должен вернуть 1");
    TestResult::assertTrue(h.empty(), "Куча должна быть пустой");
}

void testBinaryTree() {
    std::cout << "\n=== ТЕСТИРОВАНИЕ БИНАРНОГО ДЕРЕВА ===" << std::endl;
    
    BinaryTree<int> tree;
    
    TestResult::assertTrue(tree.empty(), "Дерево должно быть пустым");
    TestResult::assertFalse(tree.search(5), "Поиск в пустом дереве должен вернуть false");
    
    tree.push(10);
    tree.push(5);
    tree.push(15);
    tree.push(3);
    tree.push(7);
    tree.push(12);
    tree.push(17);
    
    TestResult::assertFalse(tree.empty(), "Дерево не должно быть пустым");
    TestResult::assertTrue(tree.search(10), "Поиск 10 должен вернуть true");
    TestResult::assertTrue(tree.search(5), "Поиск 5 должен вернуть true");
    TestResult::assertTrue(tree.search(15), "Поиск 15 должен вернуть true");
    TestResult::assertTrue(tree.search(3), "Поиск 3 должен вернуть true");
    TestResult::assertTrue(tree.search(7), "Поиск 7 должен вернуть true");
    TestResult::assertTrue(tree.search(12), "Поиск 12 должен вернуть true");
    TestResult::assertTrue(tree.search(17), "Поиск 17 должен вернуть true");
    
    TestResult::assertFalse(tree.search(1), "Поиск 1 должен вернуть false");
    TestResult::assertFalse(tree.search(20), "Поиск 20 должен вернуть false");
    
    BinaryTree<int> tree2;
    tree2.push(20);
    tree2.push(10);
    tree2.push(30);
    tree2.push(5);
    tree2.push(15);
    tree2.push(25);
    tree2.push(35);
    
    int min1 = tree2.pop();
    TestResult::assertEquals(5, min1, "Первый pop должен вернуть 5");
    TestResult::assertFalse(tree2.search(5), "Элемент 5 должен отсутствовать");
    
    int min2 = tree2.pop();
    TestResult::assertEquals(10, min2, "Второй pop должен вернуть 10");
    TestResult::assertFalse(tree2.search(10), "Элемент 10 должен отсутствовать");
    
    TestResult::assertTrue(tree2.search(20), "Элемент 20 должен существовать");
    TestResult::assertTrue(tree2.search(30), "Элемент 30 должен существовать");
    TestResult::assertTrue(tree2.search(15), "Элемент 15 должен существовать");
}

// ============================================
// 6. ГЛАВНАЯ ФУНКЦИЯ
// ============================================
int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "   ЮНИТ-ТЕСТЫ - КЕЙС-ЗАДАЧА №4" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    testQueue();
    testHeap();
    testBinaryTree();
    
    std::cout << "\n=========================================" << std::endl;
    std::cout << "          РЕЗУЛЬТАТЫ ТЕСТОВ" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Всего тестов : " << TestResult::totalTests << std::endl;
    std::cout << "Пройдено    : " << TestResult::passedTests << std::endl;
    std::cout << "Провалено   : " << TestResult::failedTests << std::endl;
    std::cout << "Успешность  : " << (TestResult::passedTests * 100.0 / TestResult::totalTests) << "%" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    return 0;
}
