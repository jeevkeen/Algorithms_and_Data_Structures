#include <gtest/gtest.h>
#include "StackOnMass.hpp"

#include <string>

using StackOnMass::TStackOnMass;

// ============================================================
//  Конструкторы
// ============================================================

TEST(StackConstructor, DefaultCapacity) {
    ASSERT_NO_THROW(TStackOnMass<int> s);
}

TEST(StackConstructor, CustomCapacity) {
    ASSERT_NO_THROW(TStackOnMass<int> s(100));
}

TEST(StackConstructor, CapacityOne) {
    ASSERT_NO_THROW(TStackOnMass<int> s(1));
}

TEST(StackConstructor, ZeroCapacityThrows) {
    ASSERT_THROW(TStackOnMass<int> s(0), std::invalid_argument);
}

// ============================================================
//  Копирующий конструктор
// ============================================================

TEST(StackCopyConstructor, CopiesAllElements) {
    TStackOnMass<int> original(5);
    original.push(10);
    original.push(20);
    original.push(30);

    TStackOnMass<int> copy(original);

    EXPECT_EQ(copy.pop(), 30);
    EXPECT_EQ(copy.pop(), 20);
    EXPECT_EQ(copy.pop(), 10);
    EXPECT_TRUE(copy.is_empty());
}

TEST(StackCopyConstructor, CopyIsIndependent) {
    TStackOnMass<int> original(5);
    original.push(1);
    original.push(2);

    TStackOnMass<int> copy(original);
    copy.push(3);

    // оригинал не изменился
    EXPECT_EQ(original.top(), 2);
    EXPECT_EQ(copy.top(), 3);
}

TEST(StackCopyConstructor, CopyEmptyStack) {
    TStackOnMass<int> original(5);
    TStackOnMass<int> copy(original);

    EXPECT_TRUE(copy.is_empty());
    EXPECT_FALSE(copy.is_full());
}

TEST(StackCopyConstructor, CopyFullStack) {
    TStackOnMass<int> original(3);
    original.push(1);
    original.push(2);
    original.push(3);

    TStackOnMass<int> copy(original);

    EXPECT_TRUE(copy.is_full());
    EXPECT_EQ(copy.pop(), 3);
    EXPECT_EQ(copy.pop(), 2);
    EXPECT_EQ(copy.pop(), 1);
}

// ============================================================
//  Оператор присваивания
// ============================================================

TEST(StackAssignment, AssignCopiesElements) {
    TStackOnMass<int> a(5);
    a.push(100);
    a.push(200);

    TStackOnMass<int> b(3);
    b.push(999);

    b = a;

    EXPECT_EQ(b.pop(), 200);
    EXPECT_EQ(b.pop(), 100);
    EXPECT_TRUE(b.is_empty());
}

TEST(StackAssignment, AssignIsIndependent) {
    TStackOnMass<int> a(5);
    a.push(1);

    TStackOnMass<int> b(3);
    b = a;
    b.push(2);

    EXPECT_EQ(a.top(), 1);
    EXPECT_EQ(b.top(), 2);
}

TEST(StackAssignment, SelfAssignment) {
    TStackOnMass<int> s(5);
    s.push(42);

    s = s;

    EXPECT_EQ(s.top(), 42);
    EXPECT_FALSE(s.is_empty());
}

TEST(StackAssignment, AssignEmptyToNonEmpty) {
    TStackOnMass<int> a(5);

    TStackOnMass<int> b(3);
    b.push(1);
    b.push(2);

    b = a;
    EXPECT_TRUE(b.is_empty());
}

// ============================================================
//  push
// ============================================================

TEST(StackPush, SingleElement) {
    TStackOnMass<int> s(5);
    ASSERT_NO_THROW(s.push(42));
    EXPECT_FALSE(s.is_empty());
}

TEST(StackPush, MultipleElements) {
    TStackOnMass<int> s(5);
    for (int i = 0; i < 5; ++i) {
        ASSERT_NO_THROW(s.push(i));
    }
    EXPECT_TRUE(s.is_full());
}

TEST(StackPush, OverflowThrows) {
    TStackOnMass<int> s(2);
    s.push(1);
    s.push(2);
    ASSERT_THROW(s.push(3), std::overflow_error);
}

TEST(StackPush, OverflowOnCapacityOne) {
    TStackOnMass<int> s(1);
    s.push(1);
    ASSERT_THROW(s.push(2), std::overflow_error);
}

// ============================================================
//  pop
// ============================================================

TEST(StackPop, ReturnsLastPushed) {
    TStackOnMass<int> s(5);
    s.push(10);
    s.push(20);

    EXPECT_EQ(s.pop(), 20);
}

TEST(StackPop, LIFOOrder) {
    TStackOnMass<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 1);
}

TEST(StackPop, EmptyAfterPoppingAll) {
    TStackOnMass<int> s(3);
    s.push(1);
    s.push(2);
    s.pop();
    s.pop();

    EXPECT_TRUE(s.is_empty());
}

TEST(StackPop, EmptyStackThrows) {
    TStackOnMass<int> s(5);
    ASSERT_THROW(s.pop(), std::underflow_error);
}

TEST(StackPop, PopThenPushAgain) {
    TStackOnMass<int> s(2);
    s.push(1);
    s.push(2);
    s.pop();
    ASSERT_NO_THROW(s.push(3));
    EXPECT_EQ(s.top(), 3);
}

// ============================================================
//  top (мутабельная версия)
// ============================================================

TEST(StackTop, ReturnsLastPushed) {
    TStackOnMass<int> s(5);
    s.push(10);
    s.push(20);

    EXPECT_EQ(s.top(), 20);
}

TEST(StackTop, DoesNotRemoveElement) {
    TStackOnMass<int> s(5);
    s.push(42);

    s.top();
    s.top();

    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.top(), 42);
}

TEST(StackTop, EmptyStackThrows) {
    TStackOnMass<int> s(5);
    ASSERT_THROW(s.top(), std::underflow_error);
}

TEST(StackTop, MutableTopAllowsModification) {
    TStackOnMass<int> s(5);
    s.push(1);

    s.top() = 999;

    EXPECT_EQ(s.top(), 999);
    EXPECT_EQ(s.pop(), 999);
}

// ============================================================
//  top (const-версия)
// ============================================================

TEST(StackConstTop, ReturnsCorrectValue) {
    TStackOnMass<int> s(5);
    s.push(7);
    s.push(14);

    const TStackOnMass<int>& cs = s;
    EXPECT_EQ(cs.top(), 14);
}

TEST(StackConstTop, EmptyStackThrows) {
    TStackOnMass<int> s(5);
    const TStackOnMass<int>& cs = s;
    ASSERT_THROW(cs.top(), std::underflow_error);
}

// ============================================================
//  is_empty
// ============================================================

TEST(StackIsEmpty, TrueOnNewStack) {
    TStackOnMass<int> s(5);
    EXPECT_TRUE(s.is_empty());
}

TEST(StackIsEmpty, FalseAfterPush) {
    TStackOnMass<int> s(5);
    s.push(1);
    EXPECT_FALSE(s.is_empty());
}

TEST(StackIsEmpty, TrueAfterPushAndPopAll) {
    TStackOnMass<int> s(5);
    s.push(1);
    s.push(2);
    s.pop();
    s.pop();
    EXPECT_TRUE(s.is_empty());
}

// ============================================================
//  is_full
// ============================================================

TEST(StackIsFull, FalseOnNewStack) {
    TStackOnMass<int> s(5);
    EXPECT_FALSE(s.is_full());
}

TEST(StackIsFull, TrueWhenFilled) {
    TStackOnMass<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_TRUE(s.is_full());
}

TEST(StackIsFull, FalseAfterPopFromFull) {
    TStackOnMass<int> s(2);
    s.push(1);
    s.push(2);
    EXPECT_TRUE(s.is_full());

    s.pop();
    EXPECT_FALSE(s.is_full());
}

TEST(StackIsFull, CapacityOneElement) {
    TStackOnMass<int> s(1);
    EXPECT_FALSE(s.is_full());
    s.push(1);
    EXPECT_TRUE(s.is_full());
}

// ============================================================
//  Работа с разными типами
// ============================================================

TEST(StackTypes, WorksWithChar) {
    TStackOnMass<char> s(3);
    s.push('a');
    s.push('b');

    EXPECT_EQ(s.top(), 'b');
    EXPECT_EQ(s.pop(), 'b');
    EXPECT_EQ(s.pop(), 'a');
}

TEST(StackTypes, WorksWithDouble) {
    TStackOnMass<double> s(3);
    s.push(3.14);
    s.push(2.71);

    EXPECT_DOUBLE_EQ(s.pop(), 2.71);
    EXPECT_DOUBLE_EQ(s.pop(), 3.14);
}

TEST(StackTypes, WorksWithString) {
    TStackOnMass<std::string> s(3);
    s.push("hello");
    s.push("world");

    EXPECT_EQ(s.top(), "world");
    EXPECT_EQ(s.pop(), "world");
    EXPECT_EQ(s.pop(), "hello");
}

// ============================================================
//  Комплексные сценарии
// ============================================================

TEST(StackComplex, PushPopInterleaved) {
    TStackOnMass<int> s(3);

    s.push(1);
    s.push(2);
    EXPECT_EQ(s.pop(), 2);

    s.push(3);
    s.push(4);
    EXPECT_TRUE(s.is_full());

    EXPECT_EQ(s.pop(), 4);
    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 1);
    EXPECT_TRUE(s.is_empty());
}

TEST(StackComplex, FillEmptyRefill) {
    TStackOnMass<int> s(2);

    s.push(1);
    s.push(2);
    EXPECT_TRUE(s.is_full());

    s.pop();
    s.pop();
    EXPECT_TRUE(s.is_empty());

    s.push(10);
    s.push(20);
    EXPECT_TRUE(s.is_full());

    EXPECT_EQ(s.pop(), 20);
    EXPECT_EQ(s.pop(), 10);
}

TEST(StackComplex, CopyThenModifyBoth) {
    TStackOnMass<int> a(5);
    a.push(1);
    a.push(2);

    TStackOnMass<int> b(a);

    a.push(3);
    b.pop();

    EXPECT_EQ(a.top(), 3);
    EXPECT_EQ(b.top(), 1);
}

TEST(StackComplex, AssignChain) {
    TStackOnMass<int> a(5);
    a.push(10);

    TStackOnMass<int> b(3);
    TStackOnMass<int> c(7);

    c = b = a;

    EXPECT_EQ(b.top(), 10);
    EXPECT_EQ(c.top(), 10);
}
