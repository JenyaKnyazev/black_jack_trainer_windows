#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int decks;
int players_count;
int rounds;
int seconds;
char *arr="23456789TJQKA";
char **players;
int arr_amount[13];

int sum;
int sum2;
COORD c,c2;
HANDLE h;
void clean_screen(){
    SetConsoleCursorPosition(h,c);
    puts("                                                             ");
    SetConsoleCursorPosition(h,c2);
    puts("                                                             ");
    SetConsoleCursorPosition(h,c);
}
void input(){
    int i;
    printf("enter amount of players: ");
    scanf("%d",&players_count);
    players_count++;
    printf("enter amount of decks: ");
    scanf("%d",&decks);
    clean_screen();
    printf("enter amount of rounds: ");
    scanf("%d",&rounds);
    printf("enter amount of delay in seconds: ");
    scanf("%d",&seconds);
    clean_screen();
    for(i=0;i<13;i++)
        arr_amount[i]=4*decks;
}
int amount_cards_in_deck(){
    int i,sum=0;
    for(i=0;i<13;i++)
        sum+=arr_amount[i];
    return sum;
}
void init_player(char *p,int max){
    int n=rand()%5+1;
    int i;
    for(i=0;i<n&&i<max;i++){
        do{
            p[i]=rand()%13;
        }while(!arr_amount[p[i]]);
        sum+=(p[i]<5)-(p[i]>8);
        arr_amount[p[i]]--;
        p[i]=arr[p[i]];
    }
    p[i]=0;
}
void one_round(int max){
    int i;
    for(i=0;i<players_count;i++)
        init_player(players[i],max);
    SetConsoleCursorPosition(h,c);
    printf("%s\n",players[0]);
    for(i=1;i<players_count;i++)
        printf("%s\t",players[i]);
    Sleep(1000*seconds);
    clean_screen();
}
void play(){
    int max,rounds2;
    label:
    sum=sum2=0;
    rounds2=rounds;
    while(rounds2--){
        max=amount_cards_in_deck();
        if(max/players_count<2)
            break;;
        one_round(max);
    }
    printf("enter answer: ");
    scanf("%d",&sum2);
    clean_screen();
    if(sum2==sum)
        printf("correct!");
    else
        printf("wrong!");
    Sleep(5000);
    clean_screen();
    printf("again = 0 other exit: ");
    scanf("%d",&sum);
    clean_screen();
    if(!sum)
        goto label;
}
int main(){
    int i;
    srand(time(NULL));
    h=GetStdHandle(-11);
    c.X=c.Y=0;
    c2.X=0;
    c2.Y=1;
    input();   
    players=(char**)malloc(sizeof(char*)*players_count);
    for(i=0;i<players_count;i++)
        players[i]=(char*)malloc(sizeof(char)*6);
    play();
    for(i=0;i<players_count;i++)
        free(players[i]);
    free(players);
    return 0;
}