#ifndef FUTSAL_H
#define FUTSAL_H

#include "llqueue.h"
#include "player.h"

Player *teamBestOfBatch(Queue *q, int k);
Player *findBestInBatch(Queue *q, Queue *tmp_q, int batch_size);
void teamCreateFromBest(Queue *applicant_q, Queue *welcome_q, int batch_size);
#endif