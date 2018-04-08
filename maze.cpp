#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include "grid.h"
using namespace std;


bool isRouteWellFormed(string route);
int navigateSegment(int r, int c, char dir, int maxSteps);
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);


bool isRouteWellFormed(string route)                             //first function
{
   
    
    if (route.size()==0)                                          //when it's an empty string
        return true;
    if (!isalpha(route[0]))                                        //when the first char of the string is not an alpha
        return false;
    
    
    
for (int k=0; k!=route.size(); k++)
    {
        
            route[k]=tolower(route[k]);
        if (!(route[k]=='n'||route[k]=='s'||route[k]=='w'|| route[k]=='e'||isdigit(route[k])))   //when the char is not one of the directions
                                                                                                //or digits
             return false;
        
        if (isalpha(route[k]))                                              //when the char is letter
            
            if (k+1<route.size()&&isdigit(route[k+1]))                      //when the next char is digit
                
                if (k+2< route.size()&& isdigit(route[k+2]))                //when the next char is digit too
                    
                    if (k+3 < route.size() && isdigit(route[k+3]))          //when the next char is digit too
                        return false;
        
            
    }
    return true;
}

/*
int main()                                          `//test for the 1st function
{
   if (isRouteWellFormed(""))
        cout <<"yes"<<endl;
    else
       cout <<"no"<<endl;
}

*/


int navigateSegment(int r, int c, char dir, int maxSteps)                       //second function
{
    dir=tolower(dir);                                                           //all letters turn into lowercases
    int k;
    if (isWall(r, c)||( dir!='n'&& dir!='e'&& dir!='s'&& dir!= 'w')|| r<1 ||r>getRows()|| c>getCols() || c<1 ||maxSteps<0)
        return -1;                                                              //when the starting point is not valid or the direction is
                                                                                //not one of the four or maxSteps is negative
    
    else if (dir=='n')                                                          //when the dir is north
    {
        for (k=1;  k<=maxSteps ; k++)
        {
            
            if (r-k<1 ||isWall(r-k, c))                                             //when the robot hits the wall or goes out of the grid
              return k-1;
    
        }  return maxSteps;
    
    }
    
    else if(dir=='s')                                                           //when the dir is south
    {   for (k=1; k<=maxSteps; k++)
       {
            if (r+k>getRows() ||isWall(r+k, c))                                     //when the robot hits the wall or goes out of the grid
               return k-1;
        
        }  return maxSteps;
    }
    
    
    else if (dir=='e')                                                          //when the dir is east
    {
           for (k=1; k<=maxSteps ; k++)
           {
               if (c+k>getCols() || isWall(r, c+k))                                 //when the robot hits the wall or goes out of the grid
                 return k-1;
       
            }  return maxSteps;
    }
    
    
    else                                                                        //when the dir is west
    {
              for (k=1; k<=maxSteps; k++)
              {
                  if (c-k<1 ||isWall(r, c-k))                                       //when the robot hits the wall or goes out of the grid
                     return k-1;
         
               }   return maxSteps;
    }
}

//int main()
//{
//    setSize(3,4);      // make a 3 by 4 grid
//    setWall(1,4);      // put a wall at (1,4)
//    setWall(2,2);      // put a wall at (2,2)
    
//    cout<<(navigateSegment(2,1 ,'e',5))<<endl;
//}





int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)                 //thrid function
{
    
   
    if (!isWall(sr,sc)&& !isWall(er, ec) && sr<=getRows()&& sr>0 && sc<=getCols() && sc>0 && er<=getRows()&& er>0 && ec<=getCols()&& ec>0 && isRouteWellFormed(route))                                       //when (r,c) and (er,ec) are empty grid positions
                                                                        //and route is valid
    {
         nsteps=0;
       
        for (int k=0; k!=route.size(); k++)
        {
            if (isalpha(route[k]))                                     //when the char you're checking is a letter
            {
                if( k == route.size()-1)                                    //when the last char of the string is a letter
                {                                                           
                                                                            //four situations of different directions are listed below
                    if (tolower(route[k])=='n')
                    {
                      if(navigateSegment(sr, sc, 'n', 1)==1)
                      {
                          nsteps++;
                         sr--;
                      }
                    else return 3;
                }
                else if (tolower(route[k])=='s')
                {
                    if (navigateSegment(sr, sc, 's', 1)==1)
                    {
                        nsteps++;
                        sr++;
                    }
                    else return 3;
                }
                else if (tolower(route[k])=='e')
                {
                    if (navigateSegment(sr, sc, 'e', 1)==1)
                    {
                        nsteps++;
                       sc++;
                    }
                    else return 3;
                }
                else if (tolower(route[k])=='w')
                {
                    if (navigateSegment(sr, sc, 'w', 1)==1)
                    {
                        nsteps++;
                       sc--;
                    }
                    else return 3;
                }
                }

                
                if (isdigit(route[k+1]) && k+1 ==route.size()-1)        //when the last two chars are a letter and a digit
                {                                                               //four situations of different directions are listed below
                
                    if (tolower(route[k])=='n')
                    {
                      if(navigateSegment(sr, sc, 'n',route[k+1]-'0' )==route[k+1]-'0')   //"Characters and Integers" helps!
                      {
                          nsteps+=(route[k+1]-'0');
                          sr-=route[k+1]-'0';
                      }
                      else
                      {
                          nsteps+=navigateSegment(sr, sc, 'n',route[k+1]-'0' );
                      return 3;
                      }
                    }
                else if (tolower(route[k])=='s')
                {
                    if(navigateSegment(sr, sc, 's', route[k+1]-'0')==route[k+1]-'0')
                    {
                        nsteps+=(route[k+1]-'0');
                        sr+=route[k+1]-'0';
                    }
                    else
                    {
                        nsteps+=navigateSegment(sr, sc, 's',route[k+1]-'0' );
                        return 3;
                    }
                }
                else if (tolower(route[k])=='e')
                {
                    if(navigateSegment(sr, sc, 'e', route[k+1]-'0')==route[k+1]-'0')
                    {
                        nsteps+=(route[k+1]-'0');
                        sc+=route[k+1]-'0';
                    }
                    else
                    {
                        nsteps+=navigateSegment(sr, sc, 'e',route[k+1]-'0' );
                      return 3;
                    }
                }
                else if (tolower(route[k])=='w')
                {
                    if(navigateSegment(sr, sc, 'w', route[k+1]-'0')==route[k+1]-'0')
                    {  nsteps+=(route[k+1]-'0');
                        sc-=route[k+1]-'0';
                    }
                    else
                    {
                        nsteps+=navigateSegment(sr, sc, 'w',route[k+1]-'0' );
                       return 3;
                    }
                }
            }

            
                else if (isalpha(route[k+1]))                                 //when the segment is a letter only
                    {
                                                                              //four situations of different directions are listed below
                        if (tolower(route[k])=='n')
                        {
                            if(navigateSegment(sr, sc, 'n', 1)==1)
                            {
                                nsteps++;
                                sr--;
                            }
                            else return 3;
                        }
                        else if (tolower(route[k])=='s')
                             {
                                 if (navigateSegment(sr, sc, 's', 1)==1)
                                 {
                                     nsteps++;
                                    sr++;
                                 }
                                 else return 3;
                             }
                        else if (tolower(route[k])=='e')
                             {
                                 if (navigateSegment(sr, sc, 'e', 1)==1)
                                 {
                                     nsteps++;
                                    sc++;
                                 }
                                 else return 3;
                              }
                        else if (tolower(route[k])=='w')
                             {
                                 if (navigateSegment(sr, sc, 'w', 1)==1)
                                 { nsteps++;
                                     sc--;
                                 }
                                 else return 3;
                             }
                     }
            
                
            
            
                   else if (isdigit(route[k+1]) && isalpha(route[k+2]))             //when the segment is letter+digit
                   {
                                                                                    //four situations of different directions are listed below
                       if (tolower(route[k])=='n')
                       {
                           if(navigateSegment(sr, sc, 'n',route[k+1]-'0' )==route[k+1]-'0')
                           {    sr-=route[k+1]-'0';
                               nsteps+=(route[k+1]-'0');
                           }
                           else
                           {   nsteps+=navigateSegment(sr, sc, 'n',route[k+1]-'0');
                               return 3;
                       }
                       }
                       else if (tolower(route[k])=='s')
                       {
                           if(navigateSegment(sr, sc, 's', route[k+1]-'0')==route[k+1]-'0')
                           {
                               sr+=route[k+1]-'0';
                               nsteps+=(route[k+1]-'0');
                           }
                           else
                           {nsteps+=navigateSegment(sr, sc, 's',route[k+1]-'0');
                               return 3;
                           }
                       }
                       else if (tolower(route[k])=='e')
                       {
                           if(navigateSegment(sr, sc, 'e', route[k+1]-'0')==route[k+1]-'0')
                           {    sc+=route[k+1]-'0';
                               nsteps+=(route[k+1]-'0');
                           }
                           else
                           {
                              nsteps+=navigateSegment(sr, sc, 'e',route[k+1]-'0');
                             return 3;
                           }
                       }
                       else if (tolower(route[k])=='w')
                       {
                           if(navigateSegment(sr, sc, 'w', route[k+1]-'0')==route[k+1]-'0')
                           {   sc-=route[k+1]-'0';
                              nsteps+=(route[k+1]-'0');
                           }
                           else
                           {
                              nsteps+=navigateSegment(sr, sc, 'w',route[k+1]-'0');
                             return 3;
                           }
                       }
                    }
                
                
                
                
                   else if (isdigit(route[k+1]) && isdigit(route[k+2])&& isalpha(route[k+3]))  //when the segment is letter+digit+digit
                   {
                                                                            //four situations of different directions are listed below
                       if (tolower(route[k])=='n')
                       {
                           if(navigateSegment(sr, sc, 'n',(10*(route[k+1]-'0')+(route[k+2]-'0'))==(10*(route[k+1]-'0')+(route[k+2]-'0'))))
                           {
                               nsteps+= ((10*(route[k+1]-'0'))+ (route[k+2]-'0'));
                               sr-=(10*(route[k+1]-'0')+(route[k+2]-'0'));
                           }
                           else
                           {
                               nsteps+=navigateSegment(sr, sc, 'n',(10*(route[k+1]-'0')+(route[k+2]-'0')));
                               return 3;
                                               }
                            
                       }
                       else if (tolower(route[k])=='s')
                       {
                           if(navigateSegment(sr, sc, 's', (10*(route[k+1]-'0')+(route[k+2]-'0'))==(10*(route[k+1]-'0')+(route[k+2]-'0'))))
                           {
                               nsteps+= ((10*(route[k+1]-'0'))+ (route[k+2]-'0'));
                               sr+=(10*(route[k+1]-'0')+(route[k+2]-'0'));
                           }
                           else
                           {
                               nsteps+=navigateSegment(sr, sc, 's',(10*(route[k+1]-'0')+(route[k+2]-'0')));

                           return 3;
                           }
                       }
                       else if (tolower(route[k])=='e')
                       {
                           if(navigateSegment(sr, sc, 'e', (10*(route[k+1]-'0')+(route[k+2]-'0'))==(10*(route[k+1]-'0')+(route[k+2]-'0'))))
                           {
                               nsteps+= ((10*(route[k+1]-'0'))+ (route[k+2]-'0'));
                               sc+=(10*(route[k+1]-'0')+(route[k+2]-'0'));
                           }
                           else
                           {
                               nsteps+=navigateSegment(sr, sc, 'e',(10*(route[k+1]-'0')+(route[k+2]-'0')));

                           return 3;
                           }
                       }
                       else if (tolower(route[k])=='w')
                       {
                           if(navigateSegment(sr, sc, 'w', (10*(route[k+1]-'0')+(route[k+2]-'0'))==(10*(route[k+1]-'0')+(route[k+2]-'0'))))
                           {
                               nsteps+= ((10*(route[k+1]-'0'))+ (route[k+2]-'0'));
                               sc-=(10*(route[k+1]-'0')+(route[k+2]-'0'));
                           }
                           else
                           {
                               nsteps+=navigateSegment(sr, sc, 'w',(10*(route[k+1]-'0')+(route[k+2]-'0')));

                              return 3;
                           }
                       }
                    }
            }
        }
    
        if (sr==er && sc==ec)                                       //when the robot gets to the end point successfully
            return 0;
        else return 1;                                              //when it ends up at somewhere else
    }
    
            

        
    else return 2;                                     //when starting point or end point are not empty grid positions or out of the grid or
                                                       //the route is not valid
    
    
}



int main()
{
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);

    assert(isRouteWellFormed("n12e4"));
    
    assert(!isRouteWellFormed("e1x"));
    assert(navigateSegment(3, 1, 'w', 2) == 0);
    int len;
    len = -999;  // so we can detect whether navigateRoute sets len
    int test = navigateRoute(3,1, 3,4, "N2eE01n0s2e1", len);
    cout << test << endl;
    assert(navigateRoute(3,1, 3,3, "n2e2s2", len) == 0  &&  len == 6);
    len = -999;  // so we can detect whether navigateRoute sets len
   // assert(navigateRoute(3,1, 3,4, "e1x", len) == 2  &&  len == -999);
   // len = -999;  // so we can detect whether navigateRoute sets len
  //  navigateRoute(2,4, 1,1, "w3n1", len);
  //  assert(navigateRoute(2,4, 1,1, "w3n1", len) == 3  &&  len == 1);

    cout << "All tests succeeded" << endl;
}


