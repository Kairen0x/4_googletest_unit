#include <iostream>
#include <vector>
#include <memory>

// ============================================
// 1. КЛАСС ОЧЕРЕДИ (QUEUE)
// ============================================
template <typename T>
class Queue {
private:
    std::vector<T> elements;
    
public:
    // Добавление элемента в конец очереди
    void push(const T& value) {
        // Реализация будет здесь
    }
    
    // Удаление элемента из начала очереди
    T pop() {
        // Реализация будет здесь
        return T(); // Заглушка
    }
    
    // Проверка на пустоту
    bool empty() const {
        return elements.empty();
    }
    
    // Получение размера очереди
    size_t size() const {
        return elements.size();
    }
    
    // Доступ к первому элементу
    T& front() {
        return elements.front();
    }
};

// ============================================
// 2. КЛАСС КУЧИ (HEAP)
// ============================================
template <typename T>
class Heap {
private:
    std::vector<T> heap;
    
    // Вспомогательные методы для поддержания свойства кучи
    void heapifyUp(int index) {
        // Реализация будет здесь
    }
    
    void heapifyDown(int index) {
        // Реализация будет здесь
    }
    
public:
    // Добавление элемента в кучу
    void push(const T& value) {
        // Реализация будет здесь
    }
    
    // Удаление максимального элемента
    T pop() {
        // Реализация будет здесь
        return T(); // Заглушка
    }
    
    // Получение максимального элемента без удаления
    T top() const {
        return heap.front();
    }
    
    bool empty() const {
        return heap.empty();
    }
    
    size_t size() const {
        return heap.size();
    }
};

// ============================================
// 3. КЛАСС БИНАРНОГО ДЕРЕВА (BINARY TREE)
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
    
    // Вспомогательные рекурсивные методы
    void insertRecursive(std::unique_ptr<Node>& node, const T& value) {
        // Реализация будет здесь
    }
    
    bool searchRecursive(const std::unique_ptr<Node>& node, const T& value) const {
        // Реализация будет здесь
        return false; // Заглушка
    }
    
    T popRecursive(std::unique_ptr<Node>& node) {
        // Реализация будет здесь
        return T(); // Заглушка
    }
    
public:
    BinaryTree() : root(nullptr) {}
    
    // Добавление элемента
    void push(const T& value) {
        insertRecursive(root, value);
    }
    
    // Удаление элемента (для простоты удаляем минимальный)
    T pop() {
        if (!root) return T();
        return popRecursive(root);
    }
    
    // Поиск элемента
    bool search(const T& value) const {
        return searchRecursive(root, value);
    }
    
    bool empty() const {
        return root == nullptr;
    }
};

// ============================================
// 4. ЮНИТ-ТЕСТЫ (GoogleTest)
// ============================================

// Если у вас установлен GoogleTest, раскомментируйте следующую строку:
// #include <gtest/gtest.h>

// Для работы без установленного GoogleTest используем упрощенную версию:
// Это минимальная реализация для демонстрации

class TestResult {
public:
    static int totalTests;
    static int passedTests;
    static int failedTests;
    
    static void assertEquals(int expected, int actual, const std::string& testName) {
        totalTests++;
        if (expected == actual) {
            passedTests++;
            std::cout << "[PASS] " << testName << std::endl;
        } else {
            failedTests++;
            std::cout << "[FAIL] " << testName << " (expected: " << expected 
                     << ", got: " << actual << ")" << std::endl;
        }
    }
    
    static void assertTrue(bool condition, const std::string& testName) {
        totalTests++;
        if (condition) {
            passedTests++;
            std::cout << "[PASS] " << testName << std::endl;
        } else {
            failedTests++;
            std::cout << "[FAIL] " << testName << " (condition is false)" << std::endl;
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
// 5. НАПИСАНИЕ ТЕСТОВ
// ============================================

void testQueue() {
    std::cout << "\n=== TESTING QUEUE ===" << std::endl;
    
    Queue<int> q;
    
    // Тест 1: Проверка пустой очереди
    TestResult::assertTrue(q.empty(), "Queue should be empty initially");
    TestResult::assertEquals(0, static_cast<int>(q.size()), "Queue size should be 0");
    
    // Тест 2: Проверка push
    q.push(10);
    q.push(20);
    q.push(30);
    TestResult::assertFalse(q.empty(), "Queue should not be empty after pushes");
    TestResult::assertEquals(3, static_cast<int>(q.size()), "Queue size should be 3");
    
    // Тест 3: Проверка pop и порядка
    TestResult::assertEquals(10, q.pop(), "First pop should return 10");
    TestResult::assertEquals(2, static_cast<int>(q.size()), "Queue size should be 2");
    TestResult::assertEquals(20, q.pop(), "Second pop should return 20");
    TestResult::assertEquals(30, q.pop(), "Third pop should return 30");
    TestResult::assertTrue(q.empty(), "Queue should be empty after all pops");
    
    // Тест 4: Проверка на больших данных
    for (int i = 0; i < 100; ++i) {
        q.push(i);
    }
    TestResult::assertEquals(100, static_cast<int>(q.size()), "Queue should have 100 elements");
    TestResult::assertEquals(0, q.pop(), "First element should be 0");
    TestResult::assertEquals(99, static_cast<int>(q.size()), "Queue should have 99 elements");
}

void testHeap() {
    std::cout << "\n=== TESTING HEAP ===" << std::endl;
    
    Heap<int> h;
    
    // Тест 1: Проверка пустой кучи
    TestResult::assertTrue(h.empty(), "Heap should be empty initially");
    TestResult::assertEquals(0, static_cast<int>(h.size()), "Heap size should be 0");
    
    // Тест 2: Проверка push и max heap свойства
    h.push(5);
    h.push(3);
    h.push(8);
    h.push(1);
    h.push(6);
    
    TestResult::assertFalse(h.empty(), "Heap should not be empty");
    TestResult::assertEquals(5, static_cast<int>(h.size()), "Heap size should be 5");
    TestResult::assertEquals(8, h.top(), "Maximum element should be 8");
    
    // Тест 3: Проверка pop
    TestResult::assertEquals(8, h.pop(), "First pop should return 8");
    TestResult::assertEquals(6, h.pop(), "Second pop should return 6");
    TestResult::assertEquals(5, h.pop(), "Third pop should return 5");
    TestResult::assertEquals(3, h.pop(), "Fourth pop should return 3");
    TestResult::assertEquals(1, h.pop(), "Fifth pop should return 1");
    TestResult::assertTrue(h.empty(), "Heap should be empty after all pops");
    
    // Тест 4: Проверка с дублирующимися значениями
    h.push(7);
    h.push(7);
    h.push(7);
    TestResult::assertEquals(3, static_cast<int>(h.size()), "Heap should have 3 elements with duplicates");
    TestResult::assertEquals(7, h.pop(), "First duplicate pop should return 7");
    TestResult::assertEquals(7, h.pop(), "Second duplicate pop should return 7");
    TestResult::assertEquals(7, h.pop(), "Third duplicate pop should return 7");
}

void testBinaryTree() {
    std::cout << "\n=== TESTING BINARY TREE ===" << std::endl;
    
    BinaryTree<int> tree;
    
    // Тест 1: Проверка пустого дерева
    TestResult::assertTrue(tree.empty(), "Tree should be empty initially");
    TestResult::assertFalse(tree.search(5), "Search in empty tree should return false");
    
    // Тест 2: Проверка push и search
    tree.push(10);
    tree.push(5);
    tree.push(15);
    tree.push(3);
    tree.push(7);
    tree.push(12);
    tree.push(17);
    
    TestResult::assertFalse(tree.empty(), "Tree should not be empty");
    TestResult::assertTrue(tree.search(10), "Search for 10 should return true");
    TestResult::assertTrue(tree.search(5), "Search for 5 should return true");
    TestResult::assertTrue(tree.search(15), "Search for 15 should return true");
    TestResult::assertTrue(tree.search(3), "Search for 3 should return true");
    TestResult::assertTrue(tree.search(7), "Search for 7 should return true");
    TestResult::assertTrue(tree.search(12), "Search for 12 should return true");
    TestResult::assertTrue(tree.search(17), "Search for 17 should return true");
    
    // Тест 3: Проверка поиска отсутствующих элементов
    TestResult::assertFalse(tree.search(1), "Search for 1 should return false");
    TestResult::assertFalse(tree.search(20), "Search for 20 should return false");
    TestResult::assertFalse(tree.search(8), "Search for 8 should return false");
    
    // Тест 4: Проверка pop (удаление минимального элемента)
    BinaryTree<int> tree2;
    tree2.push(20);
    tree2.push(10);
    tree2.push(30);
    tree2.push(5);
    tree2.push(15);
    tree2.push(25);
    tree2.push(35);
    
    // Удаляем минимальный элемент (должен быть 5)
    int min1 = tree2.pop();
    TestResult::assertEquals(5, min1, "First pop should return minimum element 5");
    TestResult::assertFalse(tree2.search(5), "Element 5 should not exist after pop");
    
    // Удаляем следующий минимальный (должен быть 10)
    int min2 = tree2.pop();
    TestResult::assertEquals(10, min2, "Second pop should return minimum element 10");
    TestResult::assertFalse(tree2.search(10), "Element 10 should not exist after pop");
    
    // Проверяем, что остальные элементы на месте
    TestResult::assertTrue(tree2.search(20), "Element 20 should still exist");
    TestResult::assertTrue(tree2.search(30), "Element 30 should still exist");
    TestResult::assertTrue(tree2.search(15), "Element 15 should still exist");
}

// ============================================
// 6. ГЛАВНАЯ ФУНКЦИЯ
// ============================================

int main() {
    std::cout << "=====================================" << std::endl;
    std::cout << "   UNIT TESTS - CASE STUDY #4" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    // Запуск всех тестов
    testQueue();
    testHeap();
    testBinaryTree();
    
    // Вывод результатов
    std::cout << "\n=====================================" << std::endl;
    std::cout << "          TEST SUMMARY" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Total tests  : " << TestResult::totalTests << std::endl;
    std::cout << "Passed tests : " << TestResult::passedTests << std::endl;
    std::cout << "Failed tests : " << TestResult::failedTests << std::endl;
    std::cout << "Success rate : " << (TestResult::passedTests * 100.0 / TestResult::totalTests) << "%" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    return 0;
}
