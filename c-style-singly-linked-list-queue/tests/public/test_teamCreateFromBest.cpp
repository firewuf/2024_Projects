#include <catch_amalgamated.hpp>
#include "llqueue.h"
#include "futsal.h"
#include <vector>

namespace {
    void assert_team_equal(std::vector<std::string> expected, Queue* welcome_q) {        
        INFO("Queue size should be " << expected.size() << " and it is " << queueSize(welcome_q));
        REQUIRE(queueSize(welcome_q) == expected.size());

        for (size_t i = 0; i < expected.size(); i++) {
            INFO("The "<<i<< "-th player was expected to be " << expected[i]  << "; found "<< queueFront(welcome_q)->name);
            REQUIRE(expected[i] == queueFront(welcome_q)->name);

            queuePopPlayerEntry(welcome_q);
        }
    }

    TEST_CASE("HW 3 Create Team From Batches Test 1 batch_size=3", "[teamCreateFromBestTest]") {
        Queue *q = newQueue();
        queuePushPlayerEntry(q, newPlayer("A", 5));
        queuePushPlayerEntry(q, newPlayer("B", 10));
        queuePushPlayerEntry(q, newPlayer("C", 3));
        queuePushPlayerEntry(q, newPlayer("D", 4));
        queuePushPlayerEntry(q, newPlayer("E", 2));
        queuePushPlayerEntry(q, newPlayer("F", 7));
        queuePushPlayerEntry(q, newPlayer("G", 1));

        Queue *welcome_q = newQueue();
        teamCreateFromBest(q, welcome_q, 3);
        
        std::vector<std::string> expected{"B", "F", "A", "D", "C"};
        assert_team_equal(expected, welcome_q);

        deleteQueue(q);
        deleteQueue(welcome_q);
    }

    TEST_CASE("HW 3 Create Team From Batches Test 2 batch_size=5", "[teamCreateFromBestTest]") {
        Queue *q = newQueue();
        queuePushPlayerEntry(q, newPlayer("A", 8));
        queuePushPlayerEntry(q, newPlayer("B", 1));
        queuePushPlayerEntry(q, newPlayer("C", 4));
        queuePushPlayerEntry(q, newPlayer("D", 4));
        queuePushPlayerEntry(q, newPlayer("E", 3));
        queuePushPlayerEntry(q, newPlayer("F", 7));
        queuePushPlayerEntry(q, newPlayer("G", 10));

        Queue *welcome_q = newQueue();
        teamCreateFromBest(q, welcome_q, 5);
        
        std::vector<std::string> expected{"A", "G", "F", "C", "D"};
        assert_team_equal(expected, welcome_q);

        deleteQueue(q);
        deleteQueue(welcome_q);
    }
}
