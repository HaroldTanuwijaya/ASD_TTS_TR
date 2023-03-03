#include<stdio.h>
#include<conio.h>
#include<windows.h>
#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_USERS 100

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct User {
  char username[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int num_users = 0;

void read_users() {
  FILE *fp;
  fp = fopen("users.txt", "r");

  if (fp == NULL) {
    return;
  }

  char buffer[100];
  while (fgets(buffer, 100, fp) != NULL) {
    char* found_username = strtok(buffer, " ");
    char* found_password = strtok(NULL, " ");
    strcpy(users[num_users].username, found_username);
    strcpy(users[num_users].password, found_password);
    num_users++;
  }

  fclose(fp);
}

void write_users() {
  FILE *fp;
  fp = fopen("users.txt", "w");

  if (fp == NULL) {
    printf("Failed to open file.\n");
    return;
  }

  for (int i = 0; i < num_users; i++) {
    fprintf(fp, "%s %s\n", users[i].username, users[i].password);
  }

  fclose(fp);
}

int username_exists(char* username) {
  for (int i = 0; i < num_users; i++) {
    if (strcmp(users[i].username, username) == 0) {
      return 1;
    }
  }
  return 0;
}

void takepassword(char pwd[50]){
	int i;
	char ch;
	while(1){
		ch = getch();
		if(ch == ENTER || ch == TAB){
			pwd[i] = '\0';
			break;
		}else if(ch == BCKSPC){
			if(i>0){
				i--;
				printf("\b \b");
			}
		}else{
			pwd[i++] = ch;
			printf("* \b");
		}
	}
}


int main(){
    system("cls");
	system("color 0b");
	FILE *fp;
	int opt,usrFound = 0;
	cover();
    gotoxy(45,10);printf("Welcome to authentication system");
	gotoxy(46,14);printf("Please choose your operation");
	gotoxy(46,15);printf("1.Signup");
	gotoxy(46,16);printf("2.Login");
	gotoxy(46,17);printf("3.Exit");
    gotoxy(46,18);printf("Your choice : ");
	scanf("%d",&opt);
	fgetc(stdin);

	switch(opt){
		case 1:
		    signup();
		    main();
            break;
		case 2:
		    login();
		    main();
			break;
		case 3:
			ex();
			break;
        default:
            main();

	}
}

void signup() {
    system("cls");
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    cover1();
    gotoxy(54,10);printf("Register");
    gotoxy(32,13);printf("Enter a Username: ");
    scanf("%s", username);
    gotoxy(32,14);printf("Enter a password: ");
    takepassword(password);
    if (username_exists(username)) {
        gotoxy(32,19);printf("Username already exists.\n");
        getch();
        signup();
    }
    struct User user;
    strcpy(user.username, username);
    strcpy(user.password, password);
    users[num_users] = user;
    num_users++;
    write_users();
    gotoxy(32,19);printf("Account created successfully.\n");
    getch();
}

void login(){
    temp:
    system("cls");
    cover1();
    int a=0,pilih;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    gotoxy(54,10);printf("Login");
    gotoxy(32,13);printf("Enter your username: ");
    scanf("%s", username);gotoxy(32,14);
    printf("Enter your password: ");
    takepassword(password);
    while(1){
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            welcome();
            getch();
            menu();
        }
        else if(strcmp(users[i].username, username) == 1 && strcmp(users[i].password, password) == 1){
            invalid();
            gotoxy(45,17);printf("User is not registered!");
            Beep(750,300);
            getch();
            system("cls");
            temp1:
            cover1();
            gotoxy(35,12);printf("Apakah anda ingin Kembali ke menu utama?(y/n)?");
            scanf("%C",&pilih);
            if (pilih=='y'){
                main();
            }
            else if(pilih=='n'){
                login();
            }
            else{
                system("cls");
                goto temp1;
            }
                main();
            }
        else if((strcmp(users[i].username, username) == 1 && strcmp(users[i].password, password) == 0)||(strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password))){
            invalid();
            gotoxy(45,17);printf("Password do not matched!");
            Beep(750,300);
            getch();
            system("cls");
            temp2:
            cover1();
            gotoxy(35,12);printf("Apakah anda ingin Kembali ke menu utama?(y/n)?");
            scanf("%C",&pilih);
            if (pilih=='y'){
                main();
            }
            else if(pilih=='n'){
                login();
            }
            else{
                system("cls");
                goto temp2;
            }

        }
    }
    invalid();
    gotoxy(45,17);printf("User is not registered!");
    getch();
    system("cls");
    system("cls");
    temp3:
    cover1();
    gotoxy(35,12);printf("Apakah anda ingin Kembali ke menu utama?(y/n)?");
    scanf("%C",&pilih);
    if (pilih=='y'){
        main();
    }
    else if(pilih=='n'){
        login();
    }
    else{
        system("cls");
        goto temp3;
    }

    }
}

void menu(){
    system("cls");
    system("COLOR 0b");
    cover();
    int position = 1;
    int keyPressed = 0;
    int maxoption = 3;
    gotoxy(53,10);printf("Menu Toko Baju");
    while(keyPressed != 13){
        gotoxy(47,14);
        arrowhere(1,position); printf(" 1. Daftar Merk Baju");
        gotoxy(47,15);
        arrowhere(2,position); printf(" 2. Jumlah stok Baju");
        gotoxy(47,16);
        arrowhere(3,position); printf(" 3. Kalkulasi Harga");
        gotoxy(47,17);
        arrowhere(4,position); printf(" 4. Struk Baju");
        gotoxy(47,18);
        arrowhere(5,position); printf(" 5. LOG OUT");
        keyPressed = getch();
        if(keyPressed == 80 && position !=5){
            position++;
        }else if(keyPressed == 72 && position !=1){
            position--;
        }else{
            position = position;
        }
    }
    printf(" Select Option ,%d \n",position);
    int x = position;
    int a;
    int b;

    switch (x){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            main();
            break;

}
}

void ex(){
    int i;
    system("cls");
    system("COLOR b");
    for(i=15;i>=14;i--){//G
        gotoxy(16,i);printf("%c",178);
        Sleep(50);
    }
    for(i=16;i>=12;i--){//G
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=14;i<19;i++){//G
        gotoxy(12,i);printf("%c",178);
        Sleep(50);
    }
    for(i=12;i<=16;i++){//G
        gotoxy(i,19);printf("%c",178);
        Sleep(50);
    }
    for(i=19;i>=17;i--){//G
        gotoxy(16,i);printf("%c",178);
        Sleep(50);
    }
    for(i=15;i<=17;i++){//G
        gotoxy(i,17);printf("%c",178);
        Sleep(50);
    }
    for(i=20;i<=25;i++){//O
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=14;i<=19;i++){//O
        gotoxy(25,i);printf("%c",178);
        Sleep(50);
    }
     for(i=25;i>=20;i--){//O
        gotoxy(i,19);printf("%c",178);
        Sleep(50);
    }
    for(i=19;i>=14;i--){//O
        gotoxy(20,i);printf("%c",178);
        Sleep(50);
    }
    for(i=28;i<=33;i++){//O2
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=14;i<=19;i++){//O2
        gotoxy(33,i);printf("%c",178);
        Sleep(50);
    }
    for(i=33;i>=28;i--){//O2
        gotoxy(i,19);printf("%c",178);
        Sleep(50);
    }
    for(i=19;i>=14;i--){//O2
        gotoxy(28,i);printf("%c",178);
        Sleep(50);
    }
    for(i=14;i<=19;i++){//D
        gotoxy(35,i);printf("%c",178);
        Sleep(50);
    }
    for(i=35;i<=38;i++){//D
        gotoxy(i,19);printf("%c",178);
        Sleep(50);
    }
    for(i=18;i<=18;i++){
        gotoxy(39,i);printf("%c",178);
        Sleep(50);
    }
    for(i=17;i>=16;i--){//D
        gotoxy(40,i);printf("%c",178);
        Sleep(50);
    }
    for(i=15;i<=15;i++){
        gotoxy(39,i);printf("%c",178);
        Sleep(50);
    }
    for(i=38;i>=35;i--){//D
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=14;i<=19;i++){//B
        gotoxy(46,i);printf("%c",178);
        Sleep(50);
    }
    for(i=46;i<=49;i++){//B
        gotoxy(i,19);printf("%c",178);
        Sleep(50);
    }
    for(i=18;i>=17;i--){//B
        gotoxy(50,i);printf("%c",178);
        Sleep(50);
    }
    for(i=49;i>=46;i--){//B
        gotoxy(i,16);printf("%c",178);
        Sleep(50);
    }
    for(i=15;i>=15;i--){//B
        gotoxy(50,i);printf("%c",178);
        Sleep(50);
    }
    for(i=49;i>=46;i--){//B
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=53;i>=53;i--){//y
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=54;i>=54;i--){//y
        gotoxy(i,15);printf("%c",178);
        Sleep(50);
    }
    for(i=55;i>=55;i--){//y
        gotoxy(i,16);printf("%c",178);
        Sleep(50);
    }
    for(i=17;i<=19;i++){//y
        gotoxy(56,i);printf("%c",178);
        Sleep(50);
    }
    for(i=57;i>=57;i--){//y
        gotoxy(i,16);printf("%c",178);
        Sleep(50);
    }
    for(i=58;i>=58;i--){//y
        gotoxy(i,15);printf("%c",178);
        Sleep(50);
    }
    for(i=59;i>=59;i--){//y
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=14;i<=19;i++){//E
        gotoxy(62,i);printf("%c",178);
        Sleep(50);
    }
    for(i=62;i<=66;i++){//E
        gotoxy(i,14);printf("%c",178);
        Sleep(50);
    }
    for(i=62;i<=65;i++){//E
        gotoxy(i,17);printf("%c",178);
        Sleep(50);
    }
    for(i=62;i<=66;i++){//E
        gotoxy(i,19);printf("%c",178);
        Sleep(50);
    }
    for(i=8;i<=100;i++){//E
        gotoxy(i,21);printf("%c",219);
        Sleep(10);
    }
    gotoxy(18,26);printf("Create by:");
    gotoxy(20,28);printf("Pradena Tiara Maharani           672022028");
    gotoxy(20,29);printf("Harold Tanuwijaya                672022107");
    gotoxy(20,30);printf("Cornelius Ardhani Yoga Pratama   672022204");
    gotoxy(20,31);printf("M. Abdurrahman Al Munawar        672022304");
    gotoxy(20,32);printf("M. Abdurrahman Al Munawar        672022304");
    for(i=21;i<=36;i++){
        gotoxy(100,i);printf("%c",219);
        Sleep(50);
    }
    for(i=100;i>=8;i--){
        gotoxy(i,37);printf("%c",219);
        Sleep(10);
    }
    for(i=36;i>=21;i--){
        gotoxy(8,i);printf("%c",219);
        Sleep(50);
    }
    gotoxy(15,39);
    exit(0);
}

void invalid(){
    int i;
    system("cls");
    gotoxy(52,11);printf("Loading..");
    gotoxy(51,17);printf("Processing");
    gotoxy(74,15);printf("%c",217);
    gotoxy(38,15);printf("%c",192);
    gotoxy(38,13);printf("%c",218);
    gotoxy(74,13);printf("%c",191);
    for(i=40;i<73;i++){
    gotoxy(i,14);printf("%c",177);}
    for(i=14;i<15;i++){
    gotoxy(38,i);printf("%c",179);}
    for(i=14;i<15;i++){
    gotoxy(74,i);printf("%c",179);}
    for(i=39;i<74;i++){
    gotoxy(i,15);printf("%c",196);}
    for(i=39;i<74;i++){
    gotoxy(i,13);printf("%c",196);}
    system("COLOR 7");
    gotoxy(40,14);
    for(i=0;i<33;i++){
        printf("%c",219);
        Sleep(100);
    }
    system("COLOR 4");
    Beep(750,300);
}



void welcome(){
    int i;
    system("cls");
    gotoxy(52,11);printf("Loading..");
    gotoxy(51,17);printf("Processing");
    gotoxy(74,15);printf("%c",217);
    gotoxy(38,15);printf("%c",192);
    gotoxy(38,13);printf("%c",218);
    gotoxy(74,13);printf("%c",191);
    for(i=40;i<73;i++){
        gotoxy(i,14);printf("%c",177);
    }
    for(i=14;i<15;i++){
        gotoxy(38,i);printf("%c",179);
    }
    for(i=14;i<15;i++){
        gotoxy(74,i);printf("%c",179);
    }
    for(i=39;i<74;i++){
        gotoxy(i,15);printf("%c",196);
    }
    for(i=39;i<74;i++){
        gotoxy(i,13);printf("%c",196);
    }
    system("COLOR 7");
    gotoxy(40,14);
    for(i=0;i<33;i++){
        printf("%c",219);
        Sleep(100);
    }
    system("COLOR 3");
    gotoxy(48,17);printf("Success to Login");
    gotoxy(51,18);printf("");
    Sleep(1000);
}

void cover(){
    int i;
    for (i=42;i<=79;i++){
        gotoxy(i,8);printf("%c",178);
    }
    for (i=42;i<=79;i++){
        gotoxy(i,20);printf("%c",178);
    }
    for (i=42;i<=79;i++){
        gotoxy(i,12);printf("%c",178);
    }
    for (i=8;i<=20;i++){
        gotoxy(42,i);printf("%c",178);
    }
    for (i=8;i<=20;i++){
        gotoxy(79,i);printf("%c",178);
    }
}

void cover1(){
    int i;
    system("color 0b");
    for (i=25;i<=93;i++){
        gotoxy(i,8);printf("%c",219);
    }
    for (i=25;i<=93;i++){
        gotoxy(i,22);printf("%c",219);
    }
    for (i=8;i<=21;i++){
        gotoxy(25,i);printf("%c",219);
    }
    for (i=8;i<=21;i++){
        gotoxy(93,i);printf("%c",219);
    }
}

void arrowhere (int realposition,int arrowposition){
    if(realposition == arrowposition){
        printf("-->");
    }else{
        printf("   ");
    }
}
