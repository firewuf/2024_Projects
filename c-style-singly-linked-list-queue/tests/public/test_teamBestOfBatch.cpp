#include <catch_amalgamated.hpp>
#include "llqueue.h"
#include "futsal.h"

namespace {
    TEST_CASE("HW 3 Best of Batch Test 1 batch_size=3", "[teamBestOfBatchTest]") {
        Queue *q = newQueue();
        queuePushPlayerEntry(q, newPlayer("A", 5));
        queuePushPlayerEntry(q, newPlayer("B", 10));
        queuePushPlayerEntry(q, newPlayer("C", 3));
        queuePushPlayerEntry(q, newPlayer("D", 4));
        queuePushPlayerEntry(q, newPlayer("E", 2));
        queuePushPlayerEntry(q, newPlayer("F", 7));
        queuePushPlayerEntry(q, newPlayer("G", 1));

        Player *p = teamBestOfBatch(q, 3);
        CHECK(p->name == "B");

        deletePlayer(p);
        deleteQueue(q);
    }
    
    TEST_CASE("HW 3 Best of Batch Test 2 batch_size=5", "[teamBestOfBatchTest]") {
        Queue *q = newQueue();
        queuePushPlayerEntry(q, newPlayer("A", 5));
        queuePushPlayerEntry(q, newPlayer("B", 10));
        queuePushPlayerEntry(q, newPlayer("C", 3));
        queuePushPlayerEntry(q, newPlayer("D", 11));
        queuePushPlayerEntry(q, newPlayer("E", 2));
        queuePushPlayerEntry(q, newPlayer("F", 7));
        queuePushPlayerEntry(q, newPlayer("G", 1));

        Player *p = teamBestOfBatch(q, 5);
        CHECK(p->name == "D");

        deletePlayer(p);
        deleteQueue(q);
    }

    TEST_CASE("HW 3 Best of Batch Test 3 batch_size=2", "[teamBestOfBatchTest]") {
            Queue *q = newQueue();
            queuePushPlayerEntry(q, newPlayer("Neymar", 75));
            queuePushPlayerEntry(q, newPlayer("Messi", 69));
            queuePushPlayerEntry(q, newPlayer("Ronaldo", 80));
            queuePushPlayerEntry(q, newPlayer("Iniesta", 24));
            queuePushPlayerEntry(q, newPlayer("Xavi", 43));

            Player *p = teamBestOfBatch(q, 2);
            deletePlayer(p);

            // second batch run
            p = teamBestOfBatch(q, 2);
            CHECK(p->name == "Ronaldo");

            deletePlayer(p);
            deleteQueue(q);
        }
    
}