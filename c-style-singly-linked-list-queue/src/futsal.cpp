#include "../include/futsal.h"
// add your findBestInBatch function here (optional helper function)
// to avoid making the teamBestOfBatch function too long
// Player *findBestInBatch(Queue *q, Queue *tmp_q, int batch_size) {

// }

// add your teambestOfBatch function here
Player *teamBestOfBatch(Queue *q, int k)
{
    if (q && q->size > 0)
    {
        Queue *tmp_q = new Queue{0, nullptr, nullptr};
        Player *highScore = nullptr;

        Player *tmp = nullptr;

        int size = k;
        if (k > static_cast<int>(q->size)) {
            size = q->size;
        }

        for (int p = 0; p < size; p++)
        {
            tmp = copyPlayer(queueFront(q));
            queuePopPlayerEntry(q);

            if (!highScore || tmp->num_goals > highScore->num_goals)
            {
                deletePlayer(highScore);
                highScore = copyPlayer(tmp);
            }

            queuePushPlayerEntry(tmp_q, tmp);
        }

        for (int p = 0; p < size; p++)
        {
            tmp = copyPlayer(queueFront(tmp_q));
            queuePopPlayerEntry(tmp_q);

            if (tmp->name != highScore->name)
            {
                queuePushPlayerEntry(q, tmp);
            } else
            {
                deletePlayer(tmp);
            }
        }

        deleteQueue(tmp_q);

        return highScore;
    }
    return NULL;
}

// add your teamCreateFromBest function here
void teamCreateFromBest(Queue *applicant_q, Queue *welcome_q, int batch_size)
{
    Player *bestOfB = nullptr;
    for (int p = 0; p < 5; p++)
    {
        bestOfB = teamBestOfBatch(applicant_q, batch_size);
        if (bestOfB)
            queuePushPlayerEntry(welcome_q, bestOfB);
    }
}