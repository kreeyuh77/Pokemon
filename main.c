//
//  Pokemon: The C program game.
//
//  Created by Kriya Naidu and Austin Smith on 11/4/19.
//  Copyright © 2019 Kriya Naidu and Austin Smith. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define INVENTORY_SIZE 5


int menu(void);
int randNum(int low, int high);
void readSave(void);
void go(void);
void arupville(void);
void kriaustintown(void);
void wilderness(void);
void foundPokemon(int pokeType);
int inventory(void);
void restore(void);
int exitGame(void);
void printPokemon(int pokeType);
int selPokemon(void);
void save(void);

typedef struct pokemon {
  char name[20];
  int maxHealth;
  int currentHealth;
} pokemon;

void battle(pokemon wildPokemon);

static pokemon allPokemon[5];
static pokemon playerPokemon[INVENTORY_SIZE];
//defining each of the pokemon to be used in the game through allPokemon.

void definePokemon(){
    strcpy(allPokemon[0].name, "Bulbusaur"); allPokemon[0].maxHealth = 15; allPokemon[0].currentHealth = allPokemon[0].maxHealth;
    strcpy(allPokemon[1].name, "Pikachu"); allPokemon[1].maxHealth = 10; allPokemon[1].currentHealth = allPokemon[1].maxHealth;
    strcpy(allPokemon[2].name, "Charmander"); allPokemon[2].maxHealth = 15; allPokemon[2].currentHealth = allPokemon[2].maxHealth;
    strcpy(allPokemon[3].name, "Squirtle"); allPokemon[3].maxHealth = 15; allPokemon[3].currentHealth = allPokemon[3].maxHealth;
    strcpy(allPokemon[4].name, "Caterpie"); allPokemon[4].maxHealth = 5; allPokemon[4].currentHealth = allPokemon[4].maxHealth;

    //player begins with one pokemon in stock
    playerPokemon[0] = allPokemon[randNum(0, 4)];
    for (int i = 1; i < INVENTORY_SIZE; i++)
        playerPokemon[i].maxHealth = -1;

}

int main(void) {
    //basic startup functionality, such as assigning pokemon to the allPokemon struct and starting random number generator.
    srand(time(0));
    definePokemon();


    //welcome the user
    printf("Welcome to...\n");
    printf("                                  ,'\\\n");
    printf("      _.----.        ____        ,'  _\\   ___    ___     ____\n");
    printf("  _,-'       `.     |    |  /`.   \\,-'   |   \\  /   |   |    \\  |`.\n");
    printf("  \\     __    \\    '-.  | /   `.  ___    |    \\/    |   '-.   \\ | |\n");
    printf("   \\.   \\ \\   |  __  |  |/    ,','_  `.  |          | __  |    \\| |\n");
    printf("    \\    \\/   /,' _`.|      ,' / / / /   |          ,' _`.|     | |\n");
    printf("     \\     ,-'/  /   \\    ,'  |  \\/ / ,`.|         /  / \\ |     | |\n");
    printf("      \\    \\ |   \\_/ |   `-.  \\    `'  / |  |    | |  \\_/ |  |\\   |\n");
    printf("      \\    \\ \\      /       `-.`.___,-'  |  |\\  /| \\      /  | |  |\n");
    printf("       \\    \\ `.__,'|  |`-._    `|       |__| \\/ |  `.__,'|  | |  |\n");
    printf("       \\_.-'        |__|    `-._ |               '-.|     '-.| |  |\n");
    printf("                                `'                            '-._|\n");

    //print menu and run task
    //runGame dertimines if game should continue or if program should end
    //this only changes if the user selects 5, and then decides to exit.
    int option = 0;
    int runGame = 1;
    while (runGame){
        option = menu();
        if (option == 2) {
            int pokeType = randNum(0,4);
            pokemon wildPokemon = allPokemon[pokeType];
            battle(wildPokemon);
        }
        else if (option == 3)
            inventory();
        else if (option == 4) {
            int sel;
            printf("\nWould you like to save your game or load a previous game?\n1 - Load\n2 - Write\n");
            scanf("%d", &sel);
            if (sel == 1)
                readSave();
            else if (sel == 2)
                save();
            else
                printf("Invalid selection!\n");
        }
        else if (option == 5)
            runGame = exitGame();
        else if (option == 6)
            go();
        else if (option == 7)
            restore();
        else
            printf("Invalid input!\n");
    }
    return 0;

}

//random number generator, for ease of programming
int randNum(int low, int high){
    int num = 0;
    num = low+rand()%(high-low+1);
    return num;
}

void readSave(){
  // Loads up saved file and transfers its contents to the player inventory.
  printf("Reading Save File . . .\n");
  FILE * saveFile = fopen("saveFile.txt", "r");

  // Clears player's current inventory.
  for (int i = 0; i < INVENTORY_SIZE; i++) {
    playerPokemon[i].maxHealth = -1;
  }

  int i = 0;
  int maxHealth, currentHealth;
  char name[50];

  // Checks each slot in the save file and enters it into the inventory.
  while (i < INVENTORY_SIZE) {
    fscanf(saveFile, "%s", &name);
    if (strcmp(name, "MissingNo") == 0){
        i = 10;
        break;
    } else {
        fscanf(saveFile, "%d %d", &currentHealth, &maxHealth);
        strcpy(playerPokemon[i].name, name);
        playerPokemon[i].currentHealth = currentHealth;
        playerPokemon[i].maxHealth = maxHealth;
    }
    i++;
  }
  fclose(saveFile);

  printf("Last save loaded!\n");
}

int menu(){
    //print initial menu
    int option = 0;
    while(1){
        printf("\n          MAIN MENU\n");
        printf("          ---------\n");
        printf("What yould you like to do?\n");
        printf("1 - Explore\n");
        printf("2 - Battle\n");
        printf("3 - Inventory\n");
        printf("4 - Save\n");
        printf("5 - Exit\n");
        scanf("%d", &option);

        //if user chooses explore, prompt sub-menu, otherwise, just return their option
        //If user enters invalid number, run again.
        if (option == 1){
            //prompt sub-menu
            //return option, if user wants to return to main menu, run menu function
            //If user makes invalid selection, game runs again
            while(1){
                printf("\nHow would you like to explore?\n");
                //Actually option 6
                printf("1 - Travel Somewhere\n");
                //Acttually option 7
                printf("2 - Restore my Pokemon\n");
                //acturally option 8
                printf("3 - Return to Main Menu\n");
                scanf("%d", &option);

                if (option == 1){
                    return 6;
                }
                else if (option == 2){
                    return 7;
                }
                else if (option == 3){
                    break;
                }
                else{
                    printf("Invalid Selection\n");
                    continue;
                }
            }
        }
        else if (option >= 2 && option <= 5){
            return option;
        }
        else{
            printf("Invalid Selection\n");
            continue;
        }
    }
}

void go(){
    int option =0;
    //ask user where they would like to go
    while (1){
        printf("\nWhere would you like to go?\n");
        printf("1 - Arupville\n");
        printf("2 - Kriaustin Town\n");
        printf("3 - Wilderness\n");
        printf("4 - Return to main menu\n");
        scanf("%d", &option);

        //run proper go simulation depending on user choice
        //run loop again if choice is invalid
        if (option == 1){
            arupville();
            break;
        }
        else if (option == 2){
            kriaustintown();
            break;
        }
        else if (option == 3){
            wilderness();
            break;
        }
       else if (option == 4){
            break;
        }
        else{
            printf("Invalid Selection\n");
            continue;
        }
    }
}

void arupville(){
    printf("\nWelcome to Arupville!\n");
    //User has 50% chance of finding Balbasaur pokemon here
    //generate random number to determine if user finds a Pokemon or not
    //choose to catch or realease pokemon if found
    int findPoke = randNum(1, 2);
    if (findPoke == 1){
        foundPokemon(0);
    }
    else{
        printf("Sorry, you didn't find any Pokemon\n");
    }
}
void kriaustintown(){
    printf("\nWelcome to Kriaustin Town!\n");
    //User has 50% chance of finding Balbasaur pokemon here
    //generate random number to determine if user finds a Pokemon or not
    //choose to catch or realease pokemon if found
    int findPoke = randNum(1, 2);
    if (findPoke == 1){
        foundPokemon(1);
    }
    else{
        printf("Sorry, you didn't find any Pokemon\n");
    }
}

void wilderness(){
    printf("\nWelcome to the Wilderness!\n");
    //User has 50% chance of finding a pokemon here
    //generate random number to determine if user finds a Pokemon or not
    //if they do find a pokemon there is a 1/3 chance that is Charmander, Squirtle, or Cataperie
    //choose to catch or realease pokemon if found
    int findPoke = randNum(1, 2);
    if (findPoke >=1 && findPoke <= 5){
        int pokeType = randNum(2, 4);
        foundPokemon(pokeType);
    }
    else{
        printf("Sorry, you didn't find any Pokemon\n");
    }
}

void foundPokemon (int pokeType){
    //create wild pokemon with correct type
    pokemon wildPokemon = allPokemon[pokeType];
    int option = 0;

    //print name and image
    printf("You found ");
    printPokemon(pokeType);

    //choose to battle or realease
    while (1){
        printf("Press 1 to capture %s or press 2 to release him!\n", wildPokemon.name);
        scanf("%d", &option);
        if (option == 1){
            battle(wildPokemon);
            break;
        }
        else if (option == 2){
            printf("You released %s\n", wildPokemon.name);
            break;
        }
        else {
            printf("Invalid option\n");
            continue;
        }
    }
}

void battle(pokemon wildPokemon){
    int selection = 0;
    int wantFight = 0;
    //this variable will switch between 1 and 0, where 1 is the player's turn and 0 is the opponents turn
    int turn = 0;
    //this variable tells if the game is still on
    int continueGame = 1;
    //determines if Pokemon was caught
    int caughtPoke = 0;

    //player chooses their pokemon.
    printf("\nYou have encountered a %s!", wildPokemon.name);
    int current = selPokemon();
    if (current!=-1){
        //while it is the players turn
        while (continueGame){
            if (turn == 0){
                printf("\nYour Pokemon is %s: %d HP\n", playerPokemon[current].name, playerPokemon[current].currentHealth);
                while (1){
                    //print menu
                    printf("It is your turn! What will you do?\n");
                    printf("1 - Fight\n");
                    printf("2 - Change Pokemon\n");
                    printf("3 - Escape\n");
                    printf("4 - Capture\n");
                    scanf("%d", &selection);
                    if (selection == 1){
                        // "Fight" deals damage to the opponent pokemon and records it.
                        int damage = randNum(3, 8);
                        wildPokemon.currentHealth = wildPokemon.currentHealth - damage;
                        printf("Your pokemon dealt %d damage to the %s\n", damage, wildPokemon.name);
                        turn++;
                        break;

                    }
                    else if (selection == 2){
                        // "Change Pokemon" switches the current pokemon by calling the selectPokemon function.
                        current = selPokemon();
                        turn++;
                        break;
                    }
                    else if (selection == 3){
                        // "Escape" gives the player a chance to escape combat if they feel their opponent is too powerful.
                        int escape = randNum(1, 2);
                        if (escape == 1) {
                            printf("You successfuly escaped!\n");
                            continueGame = 0;
                            break;
                        }
                        else {
                            printf("You failed to escape!\n");
                            turn++;
                            break;
                        }
                    }
                    else if (selection == 4){
                        //"Capture" allows the player to catch the other pokemon. Success rate is based off the health of the pokemon.
                        int range = (wildPokemon.maxHealth*3)/wildPokemon.currentHealth;
                        if (randNum(1, range) >= wildPokemon.maxHealth){
                                      continueGame = 0;
                                      caughtPoke = 1;
                                      printf("You caught a %s!\n", wildPokemon.name);
                                      break;
                         }
                        else {
                            printf("Pokemon not caught!\n");
                            turn++;
                            break;
                        }
                    }
                    else {
                        printf("Invalid selection\n");
                        continue;
                    }
                }
            }
            else {
                //comp plays turn
                printf("\nIt is now the %s's turn!\n", wildPokemon.name);
                //damage is dealt to player Pokemon
                int damage = randNum(1, 5);
                playerPokemon[current].currentHealth -= damage;
                printf("Your %s is dealt %d damage!\n", playerPokemon[current].name, damage);
                //turn switiches
                turn--;
            }

            // Once both sides have had thier turn, check win loss contitions, else continue game
            //if wild Pokemon fainted, end game
            if (wildPokemon.currentHealth <= 0) {
                printf("The wild pokemon has fainted!\n");
                printf("You have won the battle!\n");
                caughtPoke = 1;
                continueGame = 0;
            }
            //if player lost, end game
            else if (playerPokemon[current].currentHealth <= 0) {
                printf("Your pokemon has fainted!\n");
                printf("You have lost the battle!\n");
                continueGame = 0;
            }
            //if neither are true, continue the game
            else{
                continue;
            }
        }
    }

    //using data from battle, determine if the plays keeps the Pokemon
    if (caughtPoke == 1){
        //print player inventory
        int hasPoke = inventory();
        //ask user which pokemon they want to switch
        int option = 0;
        if (hasPoke ==1){
            while (1) {
                printf("Pick an inventory slot to fill or switch, or, if you do not want to capture the wild %s, press 0\n", wildPokemon.name);
                scanf("%d", &option);
                if (option>=1 && option <=INVENTORY_SIZE){
                    playerPokemon[option-1] = wildPokemon;
                    printf("Here is your updated inventory:\n");
                    hasPoke = inventory();
                    break;
                }
                else if (option == 0){
                    printf("You released %s\n", wildPokemon.name);
                    break;
                }
                else{
                    printf("Invalid Selection\n");
                    continue;
                }
            }
        }
        else{
            while (1) {
                printf("Pick an inventory slot to fill\n");
                scanf("%d", &option);
                if (option>=1 && option <=3){
                    playerPokemon[option-1] = wildPokemon;
                    break;
                }
                else{
                    printf("Invalid Selection\n");
                    continue;
                }
            }
        }
    }
}



int inventory(){
    //check if user has pokemon
    if (playerPokemon[0].name == NULL && playerPokemon[1].name == NULL && playerPokemon[2].name == NULL){
        printf("Whoops! You don't have any Pokemon.\n");
        //return 0 if the inventory is empty
        return 0;
    }
    //if user has at least one pokemon print inventory
    else{
        printf("\n          Your Pokemon:\n");
        printf("          -------------\n");
        //loop through user inventory and print pokemon and their stats
        for (int i = 0; i < INVENTORY_SIZE; i++){
            if (playerPokemon[i].maxHealth == -1){
                printf("%d: Empty\n", i+1);
            } else if (playerPokemon[i].currentHealth <= 0){
                printf("%d: %s - Health: Fainted/%d\n", i+1, playerPokemon[i].name, playerPokemon[i].maxHealth);
            } else {
                printf("%d: %s - Health: %d/%d\n", i+1, playerPokemon[i].name, playerPokemon[i].currentHealth, playerPokemon[i].maxHealth);
            }
        }
        //return one if the user has at least one pokemon
        return 1;
    }
}

void restore(){
    //check if user has pokemon
    int hasPokemon = inventory();
    //check if there are pokemon that need their health to be restored
    int hasPokeToRestore = 0;
    int option = 0;
    if (hasPokemon){
        //loop through player's inventory and see if there are any pokemon to be restored
        for (int i = 0; i < INVENTORY_SIZE; i++){
            if (playerPokemon[i].currentHealth != playerPokemon[i].maxHealth && playerPokemon[i].maxHealth != -1){
                hasPokeToRestore++;
            }
        }
        if (hasPokeToRestore>0){
            while(1){
                //ask user to enter which pokemon is to be restored
                printf("\nWhich pokemon would you like to restore?\n");
                scanf("%d", &option);
                //restore pokemon and notify user
                if (option>=1 && option <=INVENTORY_SIZE){
                    if (playerPokemon[option-1].maxHealth != -1){
                        playerPokemon[option-1].currentHealth = playerPokemon[option-1].maxHealth;
                        printf("%s health is now %d\n", playerPokemon[option-1].name, playerPokemon[option-1].currentHealth);
                        break;
                    } else {
                        printf("No pokemon there!\n");
                    }
                }
                else{
                    printf("Invalid Selection\n");
                    continue;
                }
            }
        }
        else{
            printf("All your Pokemon are at maximum health!\n");
        }
    }
}


int selPokemon(){
    int option = 0;
    int hasPoke = inventory();
    if (hasPoke ==1){
        while (1) {
          printf("\nWhich pokemon will you choose?\n");
          scanf("%d", &option);
          if (option>=1 && option <=INVENTORY_SIZE){
              if (playerPokemon[option-1].maxHealth == -1){
                  printf("You don't have a Pokemon stored here.\n");
                  continue;
              }
              else{
                  return (option-1);
                  break;
              }
          }
          else{
              printf("Invalid Selection\n");
              continue;
          }
        }
    }
    else{
        printf("Whoops! You don't have any Pokemon.");
        return -1;
    }
}

void save(){
    //Opening file to write into.
    FILE * saveFile = fopen("saveFile.txt", "w");

    //Gets each pokemon in the player's inventory and writes them to the save file.
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (playerPokemon[i].maxHealth != -1){
            fprintf(saveFile, "%s %d %d\n", playerPokemon[i].name, playerPokemon[i].currentHealth, playerPokemon[i].maxHealth);
        }
    }
    fprintf(saveFile, "MissingNo");
    fclose(saveFile);

    printf("File saved!\n");
}

int exitGame(){
    int option = 0;
    while (1){
        printf("\n       EXIT MENU\n");
        printf("       ---------\n");
        printf("1 - Save and Exit\n");
        printf("2 - Exit without saving\n");
        printf("3 - Return to Main Menu\n");
        scanf("%d", &option);
        if (option == 1){
            save();
            printf("Progress Saved. Goodbye!\n");
            return 0;
        }
        else if (option == 2){
            printf("Thanks for playing! Goodbye!\n");
            return 0;
        }
        else if (option == 3){
            return 1;
        }
        else{
            printf("Invalid Selection\n");
            continue;
        }
    }
}

void printPokemon(int pokeType){
    if (pokeType == 0){
        printf("Bulbasaur!\n");
        printf("                            _,.------....___,.' ',.-.\n");
        printf("                         ,-'          _,.--\"        |\n");
        printf("                     ,'         _.-'              .\n");
        printf("                    /   ,     ,'                   `\n");
        printf("                   .   /     /                     ``.\n");
        printf("                  |  |     .                       \\.\\\n");
        printf("        ____      |___._.  |       __               \\ `.\n");
        printf("      .'    `---""       ``\"-.--\"'`  \\               .  \\\n");
        printf("     .  ,            __               `              |   .\n");
        printf("     `,'         ,-\"'  .               \\             |    L\n");
        printf("    ,'          '    _.'                -._          /    |\n");
        printf("   ,`-.    ,\".   `--'                      >.      ,'     |\n");
        printf("  . .'\'   `-'       __    ,  ,-.         /  `.__.-      ,'\n");
        printf("  ||:, .           ,'  ;  /  / \\ `        `.    .      .'/\n");
        printf("  j|:D  \\          `--'  ' ,'_  . .         `.__, \\   , /\n");
        printf(" / L:_  |                 .  \"' :_;                `.'.'\n");
        printf(" .    ""'                  \"\"\"\"\"'                    V\n");
        printf("  `.                                 .    `.   _,..  `\n");
        printf("    `,_   .    .                _,-'/    .. `,'   __  `\n");
        printf("     ) \\`._        ___....----\"'  ,'   .'  \\ |   '  \\  .\n");
        printf("    /   `. \"`-.--\"'         _,' ,'     `---' |    `./  |\n");
        printf("   .   _  `\"\"'--.._____..--\"   ,             '         |\n");
        printf("   | .\" `. `-.                /-.           /          ,\n");
        printf("   | `._.'    `,_            ;  /         ,'          .\n");
        printf("  .'          /| `-.        . ,'         ,           ,\n");
        printf("  '-.__ __ _,','    '`-..___;-...__   ,.'\\ ____.___.'\n");
        printf("  `\"^--'..'   '-`-^-'\"--    `-^-'`.''\"\"\"\"\"`.,^.`.--'\n");
    }
    else if (pokeType ==1){
         printf("Pikachu!\n");
         printf("quu..__\n");
         printf("$$$b  `---.__\n");
         printf("\"$$b        `--.                          ___.---uuudP\n");
         printf(" `$$b           `.__.------.__     __.---'      $$$$\"              .\n");
         printf("   \"$b          -'            `-.-'            $$$\"              .'|\n");
         printf("    \".                                       d$\"             _.'  |\n");
         printf("     `.   /                              ...\"             .'     |\n");
         printf("       `./                           ..::-'            _.'       |\n");
         printf("       /                         .:::-'            .-'         .'\n");
         printf("      :                          ::''\\          _.'            |\n");
         printf("     .' .-.             .-.           `.      .'               |\n");
         printf("     : /'$$|           .@\"$\\           `.   .'              _.-'\n");
         printf("    .'|$u$$|          |$$,$$|           |  <            _.-'\n");
         printf("    | `:$$:'          :$$$$$:           `.  `.       .-'\n");
         printf("    :                  `\"--'             |    `-.     \\\n");
         printf("   :##.       ==             .###.       `.      `.    `\\\n");
         printf("   |##:                      :###:        |        >     >\n");
         printf("   |#'     `..'`..'          `###'        x:      /     /\n");
         printf("    \\                                   xXX|     /    ./\n");
         printf("     \\                                xXXX'|    /   ./\n");
         printf("    /`-.                                  `.  /   /\n");
         printf("   :    `-  ...........,                   | /  .'\n");
         printf("   |         ``:::::::'       .            |<    `.\n");
         printf("   |             ```          |           x| \\ `.:``.\n");
         printf("    |                         .'    /'   xXX|  `:`M`M':.\n");
         printf("    |    |                    ;    /:' xXXX'|  -'MMMMM:'\n");
         printf("    `.  .'                   :    /:'       |-'MMMM.-'\n");
         printf("    |  |                   .'   /'        .'MMM.-'\n");
         printf("    `'`'                   :  ,'          |MMM<\n");
         printf("      |                     `'            |tbap\\\n");
         printf("      \\                                  :MM.-'\n");
         printf("       \\                 |              .''\n");
         printf("        \\.               `.            /\n");
         printf("       /     .:::::::.. :           /\n");
         printf("      |     .:::::::::::`.         /\n");
         printf("       |   .:::------------\\       /\n");
         printf("      /   .''               >::'  /\n");
         printf("     `',:                 :    .'\n");
         printf("                          `:.:'\n");
    }
     else if (pokeType ==2){
          printf("Charmander!\n");
         printf("               --\"\"`-..\n");
         printf("            ,'          `.\n");
         printf("          ,'          __  `.\n");
         printf("         /|          \" __   \\\n");
         printf("        , |           / |.   .\n");
         printf("        |,'          !_.'|   |\n");
         printf("      ,'             '   |   |\n");
         printf("     /              |`--'|   |\n");
         printf("    |                `---'   |\n");
         printf("     .   ,                   |                       ,\".\n");
         printf("      ._     '           _'  |                    , ' \\ `\n");
         printf("  `.. `.`-...___,...---\"\"    |       __,.        ,`\"   L,|\n");
         printf("  |, `- .`._        _,-,.'   .  __.-'-. /        .   ,    \\\n");
         printf("-:..     `. `-..--_.,.<       `\"      / `.        `-/ |   .\n");
         printf("  `,         \"\"\"\"'     `.              ,'         |   |  ',,\n");
         printf("    `.      '            '            /          '    |'. |/\n");
         printf("      `.   |              \\       _,-'           |       ''\n");
         printf("        `._'               \\   '\"\\                .      |\n");
         printf("           |                '     \\                `._  ,'\n");
         printf("           |                 '     \\                 .'|\n");
         printf("           |                 .      \\                | |\n");
         printf("           |                 |       L              ,' |\n");
         printf("           `                 |       |             /   '\n");
         printf("            \\                |       |           ,'   /\n");
         printf("          ,' \\               |  _.._ ,-..___,..-'    ,'\n");
         printf("         /     .             .      `!             ,j'\n");
         printf("        /       `.          /        .           .'/\n");
         printf("       .          `.       /         |        _.'.'\n");
         printf("        `.          7`'---'          |------\"'_.'\n");
         printf("       _,.`,_     _'                ,''-----\"'\n");
         printf("   _,-_    '       `.     .'      ,\\\n");
         printf("   -\" /`.         _,'     | _  _  _.|\n");
         printf("    \"\"--'---\"\"\"\"\"'        `' '! |! /\n");
         printf("                            `\" \" -'\n");
     }
    else if (pokeType ==3){
         printf("Squirtle!\n");
         printf("               ,........__\n");
         printf("           ,-'            \"`-.\n");
         printf("         ,'                   `-.\n");
         printf("       ,'                        \\\n");
         printf("     ,'                           .\n");
         printf("     .'\\               ,\"\".       `\n");
         printf("    ._.'|             / |  `       \\\n");
         printf("    |   |            `-.'  ||       `.\n");
         printf("    |   |            '-._,'||       | \\\n");
         printf("    .`.,'             `..,'.'       , |`-.\n");
         printf("    l                       .'`.  _/  |   `.\n");
         printf("    `-.._'-   ,          _ _'   -\" \\  .     `\n");
         printf("`.\"\"\"\"\"'-.`-...,---------','         `. `....__.\n");
         printf("  .'        `\"-..___      __,'\\          \\  \\     \\\n");
         printf("  \\_ .          |   `\"\"\"\"'    `.           . \\     \\\n");
         printf("    `.          |              `.          |  .     L\n");
         printf("      `.        |`--...________.'.        j   |     |\n");
         printf("     `._    .'      |          `.     .|   ,     |\n");
         printf("       `--,\\       .            `7\"\"' |  ,      |\n");
         printf("           ` `      `            /     |  |      |    _,-'\"\"\"`-.\n");
         printf("            \\ `.     .          /      |  '      |  ,'          `.\n");
         printf("             \\  v.__  .        '       .   \\    /| /              \\\n");
         printf("              \\/    `\"\"\\\"\"\"\"\"\"\"`.       \\   \\  /.''     |\n");
         printf("               `        .        `._ ___,j.  `/ .-       ,---.     |\n");
         printf("               ,`-.      \\         .\"     `.  |/        j     `    |\n");
         printf("              /    `.     \\       /         \\ /         |     /    j\n");
         printf("             |       `-.   7-.._ .          |\"          '         /\n");
         printf("             |          `./_    `|          |            .     _,'\n");
         printf("             `.           / `----|          |-............`---'\n");
         printf("               \\          \\      |        |\n");
         printf("              ,'           )     `.         |\n");
         printf("               7____,,..--'      /          |\n");
         printf("                                 `---.__,--.'\n");
    }
    else if(pokeType ==4){
         printf("Caterpie!\n");
         printf("                   ,........_\n");
         printf("              _.-'    ___    `-._\n");
         printf("           ,-'      ,'   \\       `.\n");
         printf(" _,...    ,'      ,-'     |  ,\"\"\":`._.\n");
         printf("/     `--+.   _,.'      _.',',|\"|  ` \\`\n");
         printf(" \\_         `\"'     _,-\"'  | / `-'   l L\\\n");
         printf(" `\"---.._      ,-\"       | l       | | |\n");
         printf("    /   `.   |          ' `.     ,' ; |\n");
         printf("    j     |   |           `._`\"\"\"' ,'  |__\n");
         printf("    |      `--'____          `----'    .' `.\n");
         printf("    |    _,-\"\"\"    `-.                 |    \\\n");
         printf("    l   /             `.               F     l\n");
         printf("     `./     __..._     `.           ,'      |\n");
         printf("       |  ,-\"      `.    | ._     _.'        |\n");
         printf("       . j           \\   j   /`\"\"\"      __   |          ,\"`.\n");
         printf("        `|           | _,.__ |        ,'  `. |          |   |\n");
         printf("         `-._       /-'     `L       .     , '          |   |\n");
         printf("             F-...-'          `      |    , /           |   |\n");
         printf("             |            ,----.     `...' /            |   |\n");
         printf("             .--.        j      l        ,'             |   j\n");
         printf("            j    L       |      |'-...--<               .  /\n");
         printf("            `     |       . __,,_    ..  |               \\/\n");
         printf("             `-..'.._  __,-'     \\  |  |/`._           ,'`\n");
         printf("                 |   \"\"       .--`. `--,  ,-`..____..,'   |\n");
         printf("                  L          /     \\ _.  |   | \\  .-.\\    j\n");
         printf("                 .'._        l     .\\    `---' |  |  || ,'\n");
         printf("                  .  `..____,-.._.'  `._       |  `--;\"I'\n");
         printf("                   `--\"' `.            ,`-..._/__,.-1,'\n");
         printf("                           `-.__  __,.'     ,' ,' _-'\n");
         printf("                                `'...___..`'--^--'\n");

    }
}
