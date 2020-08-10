#pragma once
#include "test_runner.h"
using namespace std;

// class ReadingManager
// {
// };

// void TestRead()
// {
//     ReadingManager manager;

//     ASSERT_EQUAL(0, manager.Cheer(5));
//     manager.Read(1, 10);
//     ASSERT_EQUAL(1, manager.Cheer(1));
//     manager.Read(2, 5);
//     manager.Read(3, 7);
//     ASSERT_EQUAL(0, manager.Cheer(2));
//     ASSERT_EQUAL(0.5, manager.Cheer(3));
//     manager.Read(3, 10);
//     ASSERT_EQUAL(0.5, manager.Cheer(3));
//     manager.Read(3, 11);
//     ASSERT_EQUAL(1, manager.Cheer(3));
//     ASSERT_EQUAL(0.5, manager.Cheer(1));
//     manager.Read(2, 11);
//     ASSERT_EQUAL(0.5, manager.Cheer(3));
//     ASSERT_EQUAL(0.5, manager.Cheer(2));
//     manager.Read(2, 12);
//     ASSERT_EQUAL(0.5, manager.Cheer(3));
//     ASSERT_EQUAL(1, manager.Cheer(2));
//     manager.Read(1, 13);
//     manager.Read(2, 13);
//     manager.Read(3, 13);
//     ASSERT_EQUAL(0, manager.Cheer(1));
//     ASSERT_EQUAL(0, manager.Cheer(2));
//     ASSERT_EQUAL(0, manager.Cheer(3));
//     cout << "TestRead OK" << endl;
// }

#define TEST2(tp, name)                       \
    void TestRead2()                          \
    {                                         \
        {                                     \
            tp name;                          \
            ASSERT_EQUAL(name.Cheer(5), 0);   \
            name.Read(1, 10);                 \
            name.Read(2, 10);                 \
            name.Read(3, 9);                  \
            name.Read(2, 11);                 \
            ASSERT_EQUAL(name.Cheer(1), 0.5); \
        }                                     \
        {                                     \
            tp name;                          \
            ASSERT_EQUAL(name.Cheer(5), 0);   \
            name.Read(1, 10);                 \
            name.Read(2, 11);                 \
            ASSERT_EQUAL(name.Cheer(1), 0);   \
        }                                     \
        {                                     \
            tp name;                          \
            ASSERT_EQUAL(name.Cheer(5), 0);   \
            name.Read(1, 10);                 \
            name.Read(2, 11);                 \
            name.Read(1, 11);                 \
            name.Read(2, 12);                 \
            ASSERT_EQUAL(name.Cheer(2), 1);   \
        }                                     \
        {                                     \
            tp name;                          \
            ASSERT_EQUAL(name.Cheer(5), 0);   \
            name.Read(1, 10);                 \
            name.Read(2, 11);                 \
            name.Read(3, 10);                 \
            ASSERT_EQUAL(name.Cheer(2), 1);   \
        }                                     \
        cout << "TestRead2 OK" << endl;       \
    }
