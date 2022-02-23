//Cameron Monks
//CS280 S19
//Assignment: HashOA

template <typename T>
OAHashTable::OAHashTable(const OAHTConfig& Config)// Constructor
{
  Config_.InitialTableSize_ = Config.InitialTableSize_;
  Config_.PrimaryHashFunc_ = Config.PrimaryHashFunc_;
  Config_.SecondaryHashFunc_ = Config.SecondaryHashFunc_;
  Config_.MaxLoadFactor_ = Config.MaxLoadFactor_;
  Config_.GrowthFactor_ = Config.GrowthFactor_;
  Config_.DeletionPolicy_ = Config.DeletionPolicy;
  Config_.FreeProc_ = Config.FreeProc_;
  
  if(config_.SecondaryHashFunc_)
  {
    doubleHash = true;
  }
  else
  {
    doubleHash = false;
  }
  
  Table =(OATHSlot **) new(sizeof(OATHSlot*) * Config_.InitialTableSize_);
  
  for(int i = 0; i < Config_.InitialTableSize_; i++)
  {
    OAHTSlot * temp = new(OAHTSlot);
    temp->State = UNOCCUPIED;
    Table[i] = temp;
  }
  stats->TableSize = InitialTableSize_;
  stats->PrimaryHashFunc_ = Config_.PrimaryHashFunc_;
  stats->SecondaryHashFunc_ = Config_.SecondaryHashFunc_;
  
}  


template <typename T>
OAHashTable::~OAHashTable()                        // Destructor
{
  for(int i = 0; i < TableSize; i++
  {
    if(Table_[i]
    {
      delete(table_[i];
    }
  }
  delete(table_);
}


// Insert a key/data pair into table. Throws an exception if the
// insertion is unsuccessful.
template <typename T>
void OAHashTable::insert(const char *Key, const T& Data)
{
  
  double scale = (float)Level / stats->TableSize;
  
  if(scale >= Config_->MaxLoadFactor_)
  {
    GrowTable();
  }
  
  if(doubleHash)
  {
    stride = Config_.SecondaryHashFunc_(Key, stats->TableSize - 1) + 1; 
  }
  
  //linear probing
    unsigned index = PrimaryHashFunc_(Key, stats->TableSize - 1) + 1);
    
    if(table_[index]->Key == Key)
    {
      throw throw OAHashTableException(E_DUPLICATE, "This key already is in use");
    }
    
    //location is empty;
    if(table_[index]->State == UNOCCUPIED || table_[index]->State == DELETED)
    {
      OAHTSlot * slot = table_[index]
      slot->Key = Key;
      slot->Data = Data;
      slot->State = OCCUPIED;
      slot->probes = 1;
      probes++;
      stats->Count++;
      return;
    }
    
    else
    {
      unsigned initIndex = index;
      index+= stride;
      unsigned probeCounter
      bool found = false;
      while(!found)
      {
        if(table_[index]->Key == Key)
        {
          throw throw OAHashTableException(E_DUPLICATE, "This key already is in use");
        }
        
        if(table_[index]->State == UNOCCUPIED || table_[index]->State == DELETED)
        {
          OAHTSlot * slot = table_[index]
          slot->Key = Key;
          slot->Data = Data;
          slot->State = OCCUPIED;
          slot->probes = 1;
          probes++;
          found = true;
          stats->count++;
          return;
        }
        
        probes++;
        
        index += stride;
        
        if(index >= stats->TableSize - 1)
        {
          index -= (stats->TableSize - 1)
        }
        
        if(index == initIndex)
        {
          found = false;
          throw OAHashTableException(E_NO_MEMORY, "could not find an open slot");
        }
      }
    }
  std::cout << "something is wrong" << std::endl;
  return;
}


// Delete an item by key. Throws an exception if the key doesn't exist.
// Compacts the table by moving key/data pairs, if necessary
template <typename T>
void OAHashTable::remove(const char *Key)
{
    //MARK
  if(Config_->DeletionPolicy == MARK)
  {
    removeMark(Key);
  }
  else
  {
    removePACK(Key);
  }
  
}


// Find and return data by key (returns 0 if not found)
template <typename T>
const T& OAHashTable::find(const char *Key) const
{
  unsigned index = indexOf(Key);
  
  if(index != -1)
  {
    return Table_[index]
  }
  
  else
  {
    throw OAHashTableException(E_ITEM_NOT_FOUND, "Could not find that key");
  }
  
  
}


// Removes all items from the table (Doesn't deallocate table)
template <typename T>
void OAHashTable::clear()
{
  for(int i = 0; i < stats->TableSize; i++)
  {
    table_[i]->State = DELETED;
  }
}


// Allow the client to peer into the data
template <typename T>
OAHTStats OAHashTable::GetStats() const
{
  return stats;
}


template <typename T>
const OAHTSlot *OAHashTable::GetTable() const
{
  return &OAHTStats;
}


  // Expands the table when the load factor reaches a certain point
  // (greater than MaxLoadFactor) Grows the table by GrowthFactor,
  // making sure the new size is prime by calling GetClosestPrime
void OAHashTable::GrowTable()
{
  double factor = std::ceil(tableSize_ * Config_.GrowthFactor_); // Need to include <cmath>
  unsigned Nsize = GetClosestPrime(static_cast<unsigned>(factor)); // Get new prime size
  
  NTable =(OATHSlot **) new(sizeof(OATHSlot*) * Nsize);
  
  for(int i = 0; i < tableSize; i++)
  {
    OAHTSlot * temp = new(OAHTSlot);
    temp->State = table_[i]->State;
    temp->Key = table_[i]->Key;
    temp->Date = table_[i]->Data;
    temp->probes = table_[i]->probes;
    
    
    NTable[i] = temp;
  }
  stats->TableSize = Nsize;
  stats->Expansions++;
  
}

int IndexOf(const char *Key)
{
  if(doubleHash)
    {
      stride = Config_.SecondaryHashFunc_(Key, stats->TableSize - 1) + 1; 
    }
    
    //linear probing
    unsigned index = PrimaryHashFunc_(Key, stats->TableSize - 1) + 1)
    
    if(table_[index]->Key == Key)
    {
      return index;
    }
    
    else
      {
        unsigned initIndex = index;
        index+= stride;
        unsigned probeCounter
        bool found = false;
        while(!found)
        {
          if(table_[index]->Key == Key)
          {
            return index;
          }
          
          index += stride;
          
          if(index >= stats->TableSize - 1)
          {
            index -= (stats->TableSize - 1)
          }
          
          if(index == initIndex)
          {
            found = false;
            return -1;
          }
        }
      }
    std::cout << "whoops" << std::endl;
    }
}


void OAHashTable::removeMark(const char *Key)
{
    table_[indexOf(Key)]->State = Deleted;
    return;
}


void OAHashTable::removePACK(const char *Key)
{
  unsigned index = indexOf(Key);
  if(index == -1)
  {
    throw OAHashTableException(E_ITEM_NOT_FOUND, "Cannot find item to delete");
  }
  
  unsigned cluster = Config_->PrimaryHashFunc_(Key)
  
  OAHTSlot * temp = Table_[index]
  temp->State = UNOCCUPIED;
  temp = Table_[++index];
  
  while(PrimaryHashFunc_(temp->key) == cluster )
  {
    temp = Table_[index];
    temp->State = UNOCCUPIED;
    Insert(temp->Key, temp->Data);
    
    if(index == tableSize_ - 1)
    {
      index = 0;
    }
    
    else
    {
      index++;
    }
    
  }
  
  return;
}

