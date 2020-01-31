#include <stdio.h>
#include <stdlib.h>

/* Asks the user for input and puts the user reply in the given buffer

  prompt: string prompt to display
  card_name: buffer where result is stored
*/
void get_card_name(char *prompt, char *card_name) {
  puts(prompt);
  scanf("%2s", card_name);
}

/* Check whether an integer value is a valid card value

  val: int value to check
  return: 0 if false, 1 otherwise
*/
int not_valid(int val) {
  return val < 1 || val > 10;
}

/* Evaluate whether a value is low or high or neither.
  If the value is low, return 1;
  else if the value is high, return -1;
  else return 0

  val: int value to evaluate
  return: 0, 1 or -1
*/
int evaluate_value(int val) {
  if (val > 2 && val < 7) {
    return 1;
  } else if (val == 10) {
    return -1;
  } else {
    return 0;
  }
}

int main() {
    char card_name[3];
    int count = 0;
    int val;
    do {
      get_card_name("Enter the card_name: ", card_name);
      switch (card_name[0]) {
        case 'K':
        case 'Q':
        case 'J':
          val = 10;
          break;
        case 'A':
          val = 1;
          break;
        case 'X':
          continue;
        default:
          val = atoi(card_name);
          if (not_valid(val)) {
            puts("I don't understand that value!");
            continue;
          }
      }
      count += evaluate_value(val);
      printf("Current count: %i\n", count);
    } while (card_name[0] != 'X');
    return 0;
}
