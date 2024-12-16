#include "../include/artistList.hpp"
#include <iostream>

ArtistList::ArtistEntry::ArtistEntry(ArtistList *list, const Artist &a)
{
  this->list = list;
  this->artist = a;
}

// Allocate a new artist list
ArtistList::ArtistList()
{
  length = 0;
  first = nullptr;
  last = nullptr;
}

std::size_t ArtistList::size() const
{
  return length;
}

bool ArtistList::is_empty() const
{
  if (length == 0)
    return true;
  return false;
}

ArtistList::ArtistList(const ArtistList &list)
{
  length = 0;
  first = nullptr;
  last = nullptr;

  ArtistEntry *oldArtistEntry = list.first;
  for (int i = 0; i < static_cast<int>(list.size()); i++)
  {
    Artist oldArtist = oldArtistEntry->artist;
    std::string newList[Artist::max_genres];
    duplicateList(oldArtist.genres, newList, Artist::max_genres);
    Artist newArtist = Artist(oldArtist.id(), oldArtist.name(), oldArtist.total_followers, newList, oldArtist.popularity);
    appendArtist(newArtist);

    oldArtistEntry = oldArtistEntry->next;
  }
}

// Delete a artist list (and all entries)
ArtistList::~ArtistList() noexcept
{
  while (!is_empty())
  {
    removeFirstArtist();
  }
}

// prepend an artist at the beginning of list
void ArtistList::prependArtist(const Artist &a)
{
  ArtistEntry *newFirst = new ArtistEntry(this, a);
  if (first)
  {
    first->prev = newFirst;
    newFirst->next = first;
  }
  else
    last = newFirst;
  first = newFirst;
  length++;
}

// append an artist to the end of the list
void ArtistList::appendArtist(const Artist &a)
{
  ArtistEntry *newLast = new ArtistEntry(this, a);
  if (last)
  {
    last->next = newLast;
    newLast->prev = last;
  }
  else
    first = newLast;
  last = newLast;
  length++;
}

// remove the first artist from the list
void ArtistList::removeFirstArtist()
{
  if (first)
  {
    ArtistEntry *toDelete = first;

    if (length >= 2)
      toDelete->next->prev = nullptr;
    else
      last = nullptr;
    first = toDelete->next;

    delete toDelete;

    length--;
  }
}

// remove last artist from the list
void ArtistList::removeLastArtist()
{
  if (last)
  {
    ArtistEntry *toDelete = last;

    if (length >= 2)
      toDelete->prev->next = nullptr;
    else
      first = nullptr;
    last = toDelete->prev;

    delete toDelete;

    length--;
  }
}

// print an artist list
void ArtistList::printArtistList() const
{
  ArtistEntry *a = first;
  for (int i = 0; i < static_cast<int>(length); i++)
  {
    a->artist.printArtist();
  }
}

// find an artist by name in an unsorted list
Artist *ArtistList::findArtistName(const std::string &name) const
{
  ArtistEntry *a = first;
  for (int i = 0; i < static_cast<int>(length); i++)
  {
    if (a->artist.name() == name)
      return &a->artist;

    a = a->next;
  }

  return NULL;
}

// remove artist by name in an unsorted list
void ArtistList::removeArtistbyName(const std::string &name)
{
  if (first)
  {
    ArtistEntry *artistEntryToRemove = first;
    for (int i = 0; i < static_cast<int>(length); i++)
    {
      if (artistEntryToRemove->artist.name() == name)
      {
        // When artist is at the front of the list or there is only one artist in the list
        if (i == 0)
        {
          first = artistEntryToRemove->next;
          if (static_cast<int>(length) > 1)
            artistEntryToRemove->next->prev = nullptr;
          else
            last = nullptr;
        }
        // Removing the artist at the end of the list
        else if (i == static_cast<int>(length) - 1)
        {
          last = artistEntryToRemove->prev;
          artistEntryToRemove->prev->next = nullptr;
        }
        // Removing an artist that is not at the very start or end of the list
        else if (0 < i && i < static_cast<int>(length) - 1)
        {
          artistEntryToRemove->prev->next = artistEntryToRemove->next;
          artistEntryToRemove->next->prev = artistEntryToRemove->prev;
        }

        delete artistEntryToRemove;

        length--;

        return;
      }

      artistEntryToRemove = artistEntryToRemove->next;
    }
  }
}

void ArtistList::insertArtistAt(std::size_t index, const Artist &artist)
{
  if (index <= length)
  {
    ArtistEntry *newArtistEntry = new ArtistEntry(this, artist);

    ArtistEntry *entryToMove = first;
    int i = 0;
    while (i != static_cast<int>(index))
    {
      entryToMove = entryToMove->next;
      i++;
    }

    // For insterting at the start of a list
    if (static_cast<int>(index) == 0)
      prependArtist(artist);
    // For inserting at the very end of the list
    else if (static_cast<int>(index) == static_cast<int>(length))
      appendArtist(artist);
    else if (0 < static_cast<int>(index) && static_cast<int>(index) < static_cast<int>(length))
    {
      newArtistEntry->next = entryToMove;
      newArtistEntry->prev = entryToMove->prev;
      entryToMove->prev->next = newArtistEntry;
      entryToMove->prev = newArtistEntry;
      length++;
    }
  }
}

Artist *ArtistList::at(size_t index)
{
  if (index < length)
  {
    ArtistEntry *a = first;
    for (int i = 0; i != static_cast<int>(index); i++)
    {
      a = a->next;
    }

    return &a->artist;
  }
  return nullptr;
}

const Artist *ArtistList::at(size_t index) const
{
  if (index < length)
  {
    ArtistEntry *a = first;
    for (int i = 0; i != static_cast<int>(index); i++)
    {
      a = a->next;
    }

    return &a->artist;
  }
  return nullptr;
}

Artist *ArtistList::firstArtist()
{
  if (first)
    return &first->artist;
  return nullptr;
}

const Artist *ArtistList::firstArtist() const
{
  if (first)
    return &first->artist;
  return nullptr;
}

Artist *ArtistList::lastArtist()
{
  if (last)
    return &last->artist;
  return nullptr;
}

const Artist *ArtistList::lastArtist() const
{
  if (last)
    return &last->artist;
  return nullptr;
}

void duplicateList(std::string oldList[], std::string newList[], size_t size)
{
  for (int i = 0; i < static_cast<int>(size); i++)
    newList[i] = oldList[i];
}