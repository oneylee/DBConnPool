#include "gtest/gtest.h"
#include "recycle_queue.h"


class CycleQueueTest : public ::testing::Test {
protected:
    // CycleQueueTest() {
        
    // }

    // ~CycleQueueTest() override {

    // }

    void SetUp() override {
        i = 100;
        r0.Init(3);
        r1.Init(2);
        r2.Init(3);
        int* p1 = new int(1);
        int* p2 = new int(2);
        std::string* p3 = new std::string("123");

        // r0.Push(p1);
        r1.Push(p2);
        r2.Push(p3);
    }

    // void TearDown() override {
        
    // }

    orz::RecycleQueue<int> r0;
    orz::RecycleQueue<int> r1;
    orz::RecycleQueue<std::string> r2;
    int i;
};

TEST_F(CycleQueueTest, InitQueue) {
    EXPECT_EQ(r0.Pop(), nullptr);
    EXPECT_EQ(*r1.Top(), 2);
    EXPECT_EQ(*r2.Pop(), "123");
    EXPECT_EQ(i, 100);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}