#include "rummikub.h"


RummiKub::Add(Tile cons& tile)
{
  hand.push_back(tile);
}



bool RummiKub::solve_rec(Tile tile) 
{
  bool solved = false;
    if(hand.size < 1)
    {
      // base case
      // out of tiles - check if runs and groups are legal
      // return true if yest and exit
      for(int i = 0; i < runs.size(); i++)
      {
        if(runs[i].size < 3)
        {
          runs.erase(i);
        }
      }
      
      for(i = 0; i < groups,size(); i+)
      {
        if(groups[i].size < 3 || groups[i].size() > 4)
        {
          groups.erase(i);
        }
      }
      
      if(runs.size() != 0 | groups.size() != 0)
      {
        return true;
      }
    }
    
    //add to an avalable run
    for(int i = 0; i < runs.size(); i++)
    {
      if(runs[i][0].Color == tile.Color && rus[i].back == tile.denomination -1)
      {
        runs[i].pushback(tile)
        hand.pop_back();
        solve(hand.back());
      }
    }
    
    add to an avalable group
    if(!solved)
    {
      for(int i = 0; i < groups.size(); i++)
      {
        if(groups[i].denomination == tile.denomination && groups[i].size < 4)
        {
          bool flag = true;
          for(int j = 0; j < groups[i].size();  j++)
          {
            if(groups[i][j].Color == tile.Color)
            {
              flag = false;
            }
          }
          if(flag)
          {
            groups[i].pushback(tile)
            hand.pop_back();
            solve(hand.back());
          }
        }
      }
    }
    
    if(!solved)
    {
      runs.emplace_back(std::vector<Tile>(tile));
      hand.pop_back();
      solved = solve(hand.back());
    }
    
    if(!solved)
    {
      groups.emplace_back(std::vector<Tile>(tile));
      hand.pop_back();
      solved = solve(hand.back());
    }
    
    
    
    /*for ( action : actions ) {
        if()// action is legal execute it
        solve( ... ); // recursive call
        if()// solved - return true;
        undo the action
    }*/

    return false; // could not find place for current tile - backtrack
}