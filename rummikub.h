//Cameron Monks
//CS280
//Rummikub
//This program determines if a given hand is valid in the game Rummikub.
//The goal for this assignment was to write such a program, with an emphasis on speed, and early termination optimizations

#ifndef RUMMIKUB_H
#define RUMMIKUB_H
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio> //for size_type

enum Color { Red, Green, Blue, Yellow };

//tile struct
//contains a color and denomination
struct Tile {
    int     denomination;
    Color   color;
    
    //operator overload to compare tiles
    bool operator <(const Tile & t)
    {
      if(denomination < t.denomination)
      {
        return false;
      }
      else if(denomination > t.denomination)
      {
        return true;
      }
      
      else if(color < t.color)
      {
        return false;
      }
      return true;
    }
};

//print overload for a tile to output it's color
std::ostream& operator<<(std::ostream& os, Tile const& t) {
    os << "{ "<< t.denomination << ",";
    switch ( t.color ) {
        case Red:      os << "R"; break;
        case Green:    os << "G"; break;
        case Blue:     os << "B"; break;
        case Yellow:   os << "Y"; break;
    }
    os << " }";
    return os;
}


class RummiKub {
    public:
        //constructor for a empty hand
        RummiKub(){};

        //simple function to add a tile to a hand
        void Add(Tile const& tile)
        {
          hand.push_back(tile);
          std::sort(hand.begin(), hand.end());
        }
        


        bool Solve()
        {
          //std::cout << " help" << std::endl;
          if(hand.size() == 0)
          {
            bool checkGroups = true;
            bool checkRuns = true;
            
            for(unsigned i =0; i < groups.size(); i++)
            {
              if(groups[i].size() != 3 ||groups[i].size() != 4)
              {
                checkGroups = false;
              }
            }
            
            
            for(unsigned i = 0; i < runs.size(); i++)
            {
              if(runs[i].size() < 3)
              {
                checkRuns = false;
              }
              else
              {
                for(unsigned j = 0; j < runs[i].size() -1; j++)
                {
                  if(runs[i][j].denomination + 1 != runs[i][j + 1].denomination)
                  {
                    checkRuns = false;
                  }
                }
              }
            }
            
            if(checkRuns && checkGroups)
            {
              return true;
            }
          }
          
          Tile end = hand.back();
          hand.pop_back();
          
          if(!runs.empty())
          {
            size_t runSize = runs.size();
            
            for(unsigned j = 0; j < runSize; j++)
            {
              bool valid = true;
              for(unsigned k = 0; k < runs[j].size(); k++)
              {
                if(end.denomination == runs[j][k].denomination)
                {
                  valid = false; 
                }
              }
              
              if(runs[j][0].color == end.color && valid)
              {
                runs[j].push_back(end); 
                if(Solve())
                {
                  return true;
                }
                runs[j].pop_back();
              }
            }
          }
          
          if(!groups.empty())
          {
            size_t groupSize = groups.size();
            
            for(unsigned j = 0; j < groupSize; j++)
            {
              bool valid = true;
              for(unsigned k = 0; k < groups[j].size(); k++)
              {
                if(end.color == groups[j][k].color)
                {
                  valid = false; 
                }
              }
              
              if(groups[j][0].denomination == end.denomination && valid)
              {
                groups[j].push_back(end); 
                if(Solve())
                {
                  return true;
                }
                groups[j].pop_back();
              }
            }
          }
          
          std::vector <Tile> run;
          run.push_back(end);
          runs.push_back(run);
          if(Solve())
          {
            return true;
          }
          
          runs.pop_back();
          
          
          
          
          std::vector <Tile> group;
          group.push_back(end);
          groups.push_back(group);
          if(Solve())
          {
            return true;
          }
          
          groups.pop_back();
          
          hand.push_back(end);
          return false;
        }
        
        // get solution - groups
        std::vector< std::vector< Tile > > GetGroups() const
        {
          return groups;
        }
        // get solution - runs
        std::vector< std::vector< Tile > > GetRuns() const
        {
          return runs;
        }
        // if both vectors are empty - no solution possible
    private:
      std::vector<Tile> hand; //hand container;
      std::vector<std::vector<Tile> > runs;
      std::vector<std::vector<Tile> > groups;
}; 
#endif
