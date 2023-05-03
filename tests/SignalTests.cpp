/****************************************************************************
 * Coffee
 * Copyright 2023 Eric Dymkoski eric.dymkoski@gmail.com
 * This software is distributed under the MIT license (see ~/License.md)
 ****************************************************************************/

// Signal tests

#include "coffee/Signal.h"
#include "gtest/gtest.h"

namespace coffee {
namespace engine {
namespace {

struct Execute {
    int count = 0;  // Initialize to known value

    // Sets member so that you know it has been called
    void execute() { ++count; }
};

struct RefCounter {
    int &count;  // Initialize to known value

    // Sets member so that you know it has been called
    void execute() { ++count; }
};

struct RefAggregator {
    int &count;  // Initialize to known value

    // Sets member so that you know it has been called
    void execute(int i) { count += i; }
};

void foo() {}

void bar(int) {}

// Testing a connection and publishing through a signal
TEST(SignalTest, Connect) {
    Execute ex;
    ASSERT_EQ(0, ex.count);
    engine::Signal<void()> signal;
    ASSERT_EQ(0, ex.count);
    ASSERT_EQ(0, signal.countActiveConnection());

    signal.connect(&ex, &Execute::execute);
    ASSERT_EQ(1, signal.countActiveConnection());
    ASSERT_EQ(0, ex.count);

    // Trigger the signal
    signal();
    ASSERT_EQ(1, ex.count);
    signal();
    ASSERT_EQ(2, ex.count);

    // Disconnect all
    signal.disconnectAll();
    ASSERT_EQ(0, signal.countActiveConnection());

    // Calling
    ASSERT_NO_THROW(signal());
}

TEST(SignalTest, ConnectOneArg) {
    engine::Signal<void(int)> signal;

    ASSERT_NO_THROW(signal.connect(bar));
    ASSERT_EQ(1, signal.countActiveConnection());
    signal(1);
}

// void test(double, int) {}

TEST(SignalTest, ConnectOneArgMember) {
    engine::Signal<void(int)> signal;
    int count = 0;
    RefAggregator ex{count};

    signal.connect(&ex, &RefAggregator::execute, std::placeholders::_1);
    ASSERT_EQ(1, signal.countActiveConnection());
    ASSERT_EQ(0, count);
    signal(3);
    ASSERT_EQ(3, count);
}

// Test connecting a listener through the constructor
TEST(SignalTest, Construct) {
    Execute ex;
    engine::Signal<void()> signal(&ex, &Execute::execute);
    ASSERT_EQ(1, signal.countActiveConnection());
    ASSERT_EQ(0, ex.count);

    // Trigger the signal
    signal();
    ASSERT_EQ(1, ex.count);
}

// Test connecting a listener through the constructor
TEST(SignalTest, ConnectBefore) { ASSERT_TRUE(false); }

// Test connecting multiple listeners
TEST(SignalTest, MultipleListeners) {
    engine::Signal<void()> signal;
    ASSERT_EQ(0, signal.countActiveConnection());

    // Connect member function
    Execute ex;
    signal.connect(&ex, &Execute::execute);
    ASSERT_EQ(1, signal.countActiveConnection());

    // Connect lambda
    int lCount = 2;
    {
        signal.connect([&]() -> void { ++lCount; });
        ASSERT_EQ(2, signal.countActiveConnection());
    }
    // Call function
    signal();
    ASSERT_EQ(1, ex.count);
    ASSERT_EQ(3, lCount);

    signal();
    ASSERT_EQ(2, ex.count);
    ASSERT_EQ(4, lCount);

    // Disconnect all
    signal.disconnectAll();
    ASSERT_EQ(0, signal.countActiveConnection());
}

// Test connecting multiple listeners, with one duplicate
TEST(SignalTest, DuplicateListener) {
    engine::Signal<void()> signal;
    ASSERT_EQ(0, signal.countActiveConnection());

    // Connect member function
    Execute ex;
    signal.connect(&ex, &Execute::execute);
    ASSERT_EQ(1, signal.countActiveConnection());

    // Connect lambda
    int lCount = 2;
    {
        signal.connect([&]() -> void { ++lCount; });
    }
    ASSERT_EQ(2, signal.countActiveConnection());

    ASSERT_NO_THROW(signal.connect(foo));
    ASSERT_EQ(3, signal.countActiveConnection());
    ASSERT_NO_THROW(signal.connect(foo));
    ASSERT_EQ(4, signal.countActiveConnection());  // Duplicate permitted

    // Attempt duplicate connection
    ASSERT_NO_THROW(signal.connect(&ex, &Execute::execute));
    EXPECT_EQ(5, signal.countActiveConnection());  // size is unchanged

    // Call function
    signal();
    ASSERT_EQ(2, ex.count);  // Duplicate registration is called twice
    ASSERT_EQ(3, lCount);

    signal();
    ASSERT_EQ(4, ex.count);  // Duplicate registration is called twice
    ASSERT_EQ(4, lCount);

    // Disconnect all
    signal.disconnectAll();
    ASSERT_EQ(0, signal.countActiveConnection());
}

// Test connecting a listener with a return value
TEST(SignalTest, NoThrowCollector) {}

// Test disconnecting an individual listener
TEST(SignalTest, Disconnect) {
    engine::Signal<void()> signal;
    ASSERT_EQ(0, signal.countActiveConnection());

    // Add several listeners
    int lCount = 2;
    connection_t id0 = signal.connect([&]() -> void { ++lCount; });
    connection_t id1 = signal.connect([&]() -> void { ++lCount; });
    connection_t id2 = signal.connect([&]() -> void { ++lCount; });
    connection_t id3 = signal.connect([&]() -> void { ++lCount; });
    ASSERT_EQ(4, signal.countActiveConnection());

    // Call, verifying the incrementing happened
    signal();
    ASSERT_EQ(6, lCount);

    // Disconnect
    ASSERT_TRUE(signal.disconnect(id2));
    ASSERT_EQ(3, signal.countActiveConnection());
    signal();
    ASSERT_EQ(9, lCount);

    ASSERT_TRUE(signal.disconnect(id0));
    ASSERT_TRUE(signal.disconnect(id3));

    // Test re-connecting a new signal
    signal.connect([&]() -> void { ++lCount; });
    ASSERT_EQ(2, signal.countActiveConnection());
    ASSERT_TRUE(signal.disconnect(id1));

    ASSERT_EQ(1, signal.countActiveConnection());
    signal();
    ASSERT_EQ(10, lCount);
}

// Test that the signal manages the lifetime of the function
TEST(SignalTest, ManagedLifetime) {
    engine::Signal<void()> signal;
    ASSERT_EQ(0, signal.countActiveConnection());

    // Connect member function within local scope, so that the destructor is
    // called
    int lCount = 0;
    int counter = 0;
    signal.connect([&]() -> void { ++lCount; });

    {
        // Trackers can only be attached to objects managed by shared_ptr
        std::shared_ptr<RefCounter> ex(new RefCounter{counter});

        // Use of a shared_ptr allows this to be managed
        signal.connectManaged(ex, ex.get(), &RefCounter::execute);
        signal();
        EXPECT_EQ(1, lCount);
        EXPECT_EQ(1, counter);
    }

    // As the Execute object went out of scope, there should be no remaining
    // connections
    EXPECT_EQ(1, signal.countActiveConnection());

    ASSERT_NO_THROW(signal());
    EXPECT_EQ(1, counter);  // counter is unchanged
    EXPECT_EQ(2, lCount);   // Other connection is still active
}

}  // namespace
}  // namespace engine
}  // namespace coffee