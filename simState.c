/*Krist Kalami
Last Updated: March 4, 2017
A complex state machine capable of transitioning through states depending on user input and checking 
to see which states are unreachable and if they are, then they are deleted from the state machine.
*/

#include <stdio.h>
#include <string.h>
#define MAX 8
#define MN  8
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
  
int garbage[MN];
void assignStates (void);
void printStates (void);
void i_garbage (void);
void garbageFinder (void);
int nextValue (void);
int trash[MN];

struct stateMachine
{
  char stateName;
  int delete;
  struct stateMachine *zero;
  struct stateMachine *one;
}

state[MN];

void assignStates (void)
{
  state[A].stateName = 'A';
  state[A].zero = &state[E];
  state[A].one= &state[B];
  state[A].delete = '\0';
  
  state[B].stateName = 'B';
  state[B].zero = &state[A];
  state[B].one= &state[G];
  state[B].delete = '\0';
  
  state[C].stateName = 'C';
  state[C].zero = &state[B];
  state[C].one= &state[H];
  state[C].delete = '\0';
  
  state[D].stateName = 'D';
  state[D].zero = &state[H];
  state[D].one= &state[C];
  state[D].delete = '\0';
  
  state[E].stateName = 'E';
  state[E].zero = &state[G];
  state[E].one= &state[F];
  state[E].delete = '\0';
  
  state[F].stateName = 'F';
  state[F].zero = &state[C];
  state[F].one= &state[A];
  state[F].delete = '\0';
  
  state[G].stateName = 'G';
  state[G].zero = &state[D];
  state[G].one= &state[G];
  state[G].delete = '\0';
  
  state[H].stateName = 'H';
  state[H].zero = &state[F];
  state[H].one= &state[E];
  state[H].delete = '\0';
  
}

int nextValue (void){
  int input;
  input = getchar();
  if(input != '\n'){
    return input;
  }else{
    return 13;
  }
}

void printStates(void)
{
  int i;
  fprintf(stdout, "\n");
  
  for (i=0; i < 8; i++)
  {
    if (!state[i].delete)
    {
      fprintf(stdout, "%c ",  state[i].stateName);
      fprintf(stdout, "%c ",  state[i].zero -> stateName);
      fprintf(stdout, "%c\n", state[i].one  -> stateName);
    }
  }
  
  fprintf(stdout, "\n");
}

void i_garbage(void)
{
  int i;
  
  for (i = 0; i < 8; i++)
    garbage[i] = i;
}

void garbageFinder(void)
{
  int i, j;
  
  for(j = 0; j < 8; j++){
        if(state[j].delete != 1){
                for (i = 0; i < 8; i++){
                                garbage[state[j].zero -> stateName - 'A'] = -1;
                                garbage[state[j].one -> stateName - 'A'] = -1;
                                
                        }
                }
          }
}

int main (int argc, char* argv[])
{
  int i, input, inputA, inputB, inputC, inputD, inputE;
  int check;
  int garbage_flag = 0;
  int deleteFlag = 0;
  int current_state = D;
  //int temp;
  assignStates();
  i_garbage();
  
  
  printf("Command List: \n[0] Go to state 0\n[1] Go to state 1\n[c 0/1 'State'] Change state \n[p] Print\n[g] Garbage\n[d] Delete garbage\n[d State] Check if deleted\n[x] Exit\n **Pressing enter without a command tells you the present state\n");
  
  fprintf(stdout, "\nThe Present state is D\n");
  
  while ((input = nextValue()) != EOF){
    if(input != '0' && input != '1' && input != 'c' && input != 'p' && input != 'd' && input != 'g' && input != 'x' && input != 13){
      inputE = nextValue();
      if(inputE == 13){
        fprintf(stderr,"Incorrect command\n");
      }else{
        do{
          inputA = nextValue();
        }while(inputA != 13);
        fprintf(stderr, "Error\n");
      }
    }else if(input == '0'){
      inputE = nextValue();
      if (inputE == 13 && ((state[current_state].zero -> delete) == 0)){
        current_state = (state[current_state].zero -> stateName) - 'A';
        fprintf(stdout, "Present State: %c\n", state[current_state].stateName);        
      }else{
        do{
          inputA = nextValue();
        }while(inputA != 13);
        fprintf(stderr, "Error\n");
      }
    }else if(input == '1'){
      inputE = nextValue();
      if (inputE == 13 && ((state[current_state].one -> delete) == 0)){
        current_state = (state[current_state].one -> stateName) - 'A';
        fprintf(stdout,"Present State: %c\n", state[current_state].stateName);
      }else{
        do{
          inputA = nextValue();
        }while(inputA != 13);
        fprintf(stderr, "Error\n");
      }
    }else if(input == 'c'){
      inputA = nextValue(); 
      inputB = nextValue();
      inputC = nextValue();
      inputD = nextValue();
      inputE = nextValue();
      
      if(inputE == 13){
        if(!(inputD >= 'A' && inputD <= 'H') && inputD == ' '){
          fprintf(stderr, "No state inputted\n"); 
        }else if(!(inputD >= 'A' && inputD <= 'H')){
          fprintf(stderr, "Capital letter states only\n");
        }
        
        if(inputA != 32 || inputC != 32){
          fprintf(stderr, "Incorrect\n");
        }
        
        if(inputB == ' '){
          fprintf(stderr, "No path inputted\n");
        }
        
        if(state[inputD - 'A'].delete == 0){
          if(inputB == '0'){
            state[current_state].zero = &state[inputD - 'A']; 
          }else if(inputB == '1'){
            state[current_state].one= &state[inputD - 'A'];
          }else{
            fprintf(stderr, "0 or 1 only in second input\n");
          }
        }
      }else{
        do{
          inputE = nextValue();
        }while(inputE != 13);
        fprintf(stderr, "Error\n");
      }
    }else if(input == 'p'){
      inputE = nextValue();
      if(inputE == 13){
        printStates();
      }else{
        do{
          inputE = nextValue();
        }while(inputE != 13);
        fprintf(stderr, "Error\n"); 
      }
    }else if(input == 'x'){
      inputE = nextValue();
      return 0;
    }else if(input == 'g'){
      inputE = nextValue();
      if(inputE == 13){
        i_garbage();
        garbageFinder();
        
        for (i = 0; i < 8; i++){
          if(garbage[i] != -1){
            garbage_flag = 1;
          }
        }
        
        if (garbage_flag == 0){
          fprintf(stdout, "\nThere is No Garbage\n");
          fprintf(stdout, "\n");
        }else{
          fprintf(stdout, "\nGarbage: ");
          for (i = 0; i < 8; i++){
            if (garbage[i] != -1 && state[i].delete == 1){
              fprintf(stdout, "%c (deleted), ", garbage[i] + 'A');
            }else if (garbage[i] != -1){
              fprintf(stdout, "%c ", garbage[i] + 'A');
            }
          }
        }
        
        fprintf(stdout, "\n");
      }else{
        do{
          inputE = nextValue();
        }while(inputE != 13);
        fprintf(stderr, "Error\n");
      }
    }else if(input == 'd'){
      inputE = nextValue();   
      
      if(inputE == 13){
        i_garbage();        
        garbageFinder();
        
        fprintf(stdout, "Deleted: ");
        
        for (i = 0; i < 8; i++){
          if ((garbage[i] == i) && (state[i].delete == 0)){
            state[i].delete = 1;
            deleteFlag = 1;
            trash[i] = state[garbage[i]].stateName;
            fprintf(stdout, "%c ", state[garbage[i]].stateName);
          }
        }
        
        fprintf(stdout, "\n");
        
        if (deleteFlag == 0){
          fprintf(stdout, "No states deleted\n");
          fprintf(stdout, "\n");
        }
        
      }
      else if(inputE == ' '){
        inputB = nextValue();
        inputC = nextValue();
        
        if(inputC == 13){
          if(!(inputB >= 'A' && inputB <= 'H')){
            fprintf(stderr, "Capital Error\n");
          }
          
          i_garbage();        
          garbageFinder(); 
          
          if(inputB >= 'A' && inputB <= 'H'){
            for (i = 0; i < 8; i++){
              if((inputB != trash[i]) && (garbage[i] == i) && (state[i].delete == 0)){
                  state[i].delete = 1;
                  deleteFlag = 1;
                  trash[i] = state[garbage[i]].stateName;
                  fprintf(stdout, "Deleted: %c \n", state[garbage[i]].stateName);
                  check = 2;
                  break;    
              }else if(inputB == trash[i]){
                check = 1;
                break;
              }else{
                check = 0;
              }
            }
            if(check == 1){
              fprintf(stdout,"Deleted\n");
            }else if(check == 0){
              fprintf(stdout, "Not deleted\n");
            }else if(check == 2){
                
            }
          }
        }else{
          do{
            inputE = nextValue();
          }while(inputE != 13);
          fprintf(stderr, "Error\n");
        }
      }}else if(input == 13){
        fprintf(stdout, "Present State: %c\n", state[current_state].stateName);
      }
  }
} 


