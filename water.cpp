//Cameron Monks
//CS280 Spring 2019
//Water Retainment

#include "water.h"
#include <stdstring.h>
#include <limits.h>


typedef struct{
  int height;   //the height of the cell
  int level;    //the current water elvel of the cell
  cell* up, down, left, right; //pointers to adjacent cells
  bool border = false; //a marker to tell if the cell is a border
  

  //a simple < operator overload to compare the height of two cells
  bool operator<(cell &rhs)
  {
    if(height < rhs->height)
    {
      return false;
    }
    return true;
  }
  
}cell;

bool evaluate(cell *temp, cell *adj)
{
  int height = INT_MAX;
  int startHeight = adj->height;
  if(temp->level < adj->level)
  {
    height = temp->level;
  }
  
  else
  {
    height = adj->level;
  }
  
  if(adj->height > height)
  {
    height = adj->height;
  }
  
  if(adj->height != startHeight)
  {
    return true;
  }
  return false;
}


void initializeCell(int i, int j, cell* cellT, std::priority_queue<cell> *queue)
{
  if (i == 0)
  {
    cellT->up = NULL;
    cellT->level = height;
    cellT->border = true;
  }

  if (j == 0)
  {
    cellT->left = NULL;
    cellT->level = height;
    cellT->border = true;
  }

  if (i = height - 1)
  {
    cellT->down = NULL;
    cellT->level = height;
    cellT->border = true;
  }

  if (j = width - 1)
  {
    cellT->right = NULL;
    cellT->level = height;
    cellT->border = true;
  }

  if (cellT->up)
  {
    cellT->up = array[i - 1][j];
    cellT->level = INT_MAX;
  }

  if (cellT->down)
  {
    cellT->down = array[i + 1][j];
    cellT->level = INT_MAX;
  }

  if (cell->left)
  {
    cellT->left = array[i][j - 1];
    cellT->level = INT_MAX;
  }

  if (cellT->right)
  {
    cellT->right = array[i][j + 1];
    cellT->level = INT_MAX;
  }

  fscanf(file, "%i", temp)
    cellT->height = temp;
  cellT->level = 0;
  array[i][j] = cellT;
  if (cell->border)
  {
    queue->push_back(cell);
  }
}
long int waterret( char const* filename )
{
  //open and read in the file specified
  FILE * file;
  file = fopen(filename, "rt");
  int height, width, temp;
  
  //make sure the file exists
  if(!file)
  {
    return NULL;
  }
  
  //create variables for reading from the file
  string Buffer;
  char buff;
  
  //read in the height and width of the grid from the first two values in the file
  fscanf(file, "%i %i", height, width);
  
  //allocate an array to match the size of the file
  cellA** array = (cell**)malloc(height * width * sizeof(cell));
  
  //iterate through the array and fill in the cell information
  for(int i = 0; i < height; i++)
  {
    for(int j; j < width; j++)
    {
      //allocate a cell
      cell * cellT = (cell *)malloc(sizeof(cell));
      
      //read in the nex value and assign it's height to the correct cell
      fscanf(file, "%i", temp)
      cellT->height = temp;

      //set the cell's water value to be zero
      cell->level = 0;

      //set up each of the cell's refrences to itself
      //this is done to avoid null pointers in the future, any cell that refrences itself must be a border
      cellT->up = cellT;
      cellT->down = cellT;
      cellT->left = cellT;
      cellT->right = cellT;
      
      cellA[i][j] = cellT;
    }
  }
  
  //close the file
  fclose(file);
  std::priority_queue<cell> queue;
  
  //attach each cell to its neighbors, and if its an edge, set the height to -1
  for(int i = 0; i < height; i++)
  {
    for(int j; j < width; j++)
    {
      cell * cellT = cellA[i][j];
      //border checks
      initializeCell(i, j, cellT, &queue)
    }
  }
  
  while(!queue.empty)
  {
    Cell * temp = queue.pop_back();
    if(temp->left)
    {
      if(evaluate(temp, temp->left))
      {
        queue.push_back(temp->left);
      }
    }
    
    if(temp->right)
    {
      if(evaluate(temp, temp->right))
      {
        queue.push_back(temp->right);
      }
    }
    
    if(temp->up)
    {
      if(evaluate(temp, temp->up))
      {
        queue.push_back(temp->up);
      }
    }
    
    if(temp->down)
    {
      if(evaluate(temp, temp->down))
      {
        queue.push_back(temp->down);
      }
    }
  }
  
  long int capacity = 0;
  
  for(int i = 0; i < height; i++)
  {
    for(int j; j < width; j++)
    {
      capacity += cellA[i][j];
    }
  }
  return capacity;
}