#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include <stdlib.h>
#define true 0
#define false 1
#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_USERS 100


struct product{
		char id[10];   // product code/no.
		char name[20]; // product name
		int  quantity; // remaining quantity of product. Subtract from the original quantity the quantity purchased
        int  numSold;  // initially zero, when no purchase yet.
		float price;   // price of one piece of product
		float sales;   // accumulated sales, total sales for this product
		float total; // total
	};
	struct product prod[30];//maximum array.
	int count = 0;	//bakal di incremented jika ada produk nambah
 	FILE *f;	//file pointer


int writefile(){

    int i;
    f = fopen("inventory.txt", "w");  // file pointer
    if (f == NULL)
        return -1;
    fprintf(f, "%d\n", count);
    for (i = 0; i < count; ++i) // nulis semua detail dari semua fungsi ke file pointer.
    {
        // ngubah
        fputs(prod[i].id, f);
        fprintf(f, "\n");
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%d\n", prod[i].numSold);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%f\n", prod[i].sales);
        fprintf(f, "%f\n", prod[i].total);
    }
    fclose(f);
    return 0;
}
int readFile(){
    int n = 0;
    int i;
    f = fopen("inventory.txt", "r");
    if (f == NULL)
        return -1;
    fscanf(f, "%d\n", &n);
    for (i = 0; i < n; ++i)
    {
        fgets(prod[i].id, 10, f);
        prod[i].id[strlen(prod[i].id) - 1] = 0; // hapus new lines
        fgets(prod[i].name, 20, f);
        prod[i].name[strlen(prod[i].name)-1] = 0; // hapus new lines
        fscanf(f, "%d", &prod[i].quantity);
        fscanf(f, "%d", &prod[i].numSold);
        fscanf(f, "%f", &prod[i].price);
        fscanf(f, "%f\n", &prod[i].sales);
        fscanf(f, "%f\n",&prod[i].total);
    }
    fclose(f);
    return n;
}

void gotoxy(int x, int y){ //tiara
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct User {//tiara
  char username[MAX_USERNAME_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];//tiara
int num_users = 0,quant;

void read_users() {//tiara
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

void write_users() {//tiara
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

void takepassword(char pwd[50]){//tiara
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

int main(){//tiara
    system("cls");
    system("color 0b");
	FILE *fp;
	int opt,usrFound = 0;
	cover();
    int position = 1;
    int keyPressed = 0;
    int maxoption = 3;
    gotoxy(45,10);printf("Welcome to authentication system");
	gotoxy(46,14);printf("Please choose your operation");
    while(keyPressed != 13){
        gotoxy(46,15);
        arrowhere(1,position); printf("1.Signup");
        gotoxy(46,16);
        arrowhere(2,position); printf("2.Login");//JADINYA ADMIN ASW INI BUKAN PELANGGAN BANGSATTTTT JADI BINGGUNG KAN KONSEPNYA GMN
        gotoxy(46,17);
        arrowhere(3,position); printf("3.Exit");
        keyPressed = getch();
        if(keyPressed == 80 && position !=3){
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


void signup() {//tiara
    system("cls");
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    cover1();
    gotoxy(54,10);printf("Register");
    gotoxy(32,13);printf("Enter a Username: ");
    scanf("%s", username);
    gotoxy(32,14);printf("Enter a password: ");
    takepassword(password);//fungsi takepassword untuk inputan bintang
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

void login(){//tiara


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
void merkbaju(){//harold
    int ch,i,n;
    system("cls");
    system("COLOR 0b");
    count = readFile();
    if (count < 0)
    puts("cannot open file");
    printf("------------------------------------------------------------------------------------\n");
    printf("S.N.|    NAME     |   ID  |     QUANTITY      |    PRICE    | \n");
    printf("------------------------------------------------------------------------------------\n");
    for (i=0;i<count;i++){
        printf("%d     %-10s       %-8s     %-5d             %-6.2f        \n",i+1,prod[i].name,prod[i].id,prod[i].quantity,prod[i].price);
    }
    gotoxy(45,26); printf("Press any key to go back to menu");
    while (1) {
        if ( kbhit() ) {
            ch = getch();
            if (ch == 13){
                menu();
            }
        }
    }
}

void hpsprod(){
	count=readFile();
	char id[10];
	int i,j;
	int z=false;
    printf("Enter the id that you want to be delete : "); //user memasukkan input id untuk menghapus item.
    fflush(stdin);
    gets(id);

    for(i=0;i<count;i++){		//looping untuk menemukan yg user cari
        z=true;
        if(strcmp(prod[i].id,id)==0){ // jika input user=data yg dipilih
        for( j=i; j<(count-1); j++)	// data yg dipilih bakal dihapus
                {
                    prod[j]=prod[j+1];
                }
                count--;
        }
    }
    if(z==false){	// will be executed if the product id is not available.
        printf("Cant find product id: %s .",id);
    }
    writefile();
    menu();
}

void menu2(){
    system("COLOR 0A");
    int key=0;
    int p=1;
    while(key!=13){
          system("cls");
          fflush(stdin);
    cover();
        gotoxy(47,14);arrowhere(1,p); printf("1. tambah merk\n");
        gotoxy(47,15);arrowhere(2,p); printf("2. edit baranggg\n");
        gotoxy(47,16);arrowhere(3,p); printf("3. delete produk \n");
        gotoxy(47,17);arrowhere(4,p); printf("4. balik menu \n");
    key=getch();
        if (key==80 && p !=4){
            p++;
        }
        else if(key==72 && p!=1){
            p--;
        }
        else{
            p=p;
        }
    }

    if(key==13 && p==1){
    nambahmerk();
    }
    else if(key==13 && p==2){
        editProd();
    }
    else if(key==13 && p==3){
        hpsprod();
    }
    else if(key==13 && p==4){
        menu();
    }
}

void nambahmerk(){
    system("cls");
  	printf("Tambah merk baju:\n");
	readFile();		//baca file.
  	    if (count>0) {
            count=readFile();
            IDChecker(0,count); // buat ngecek uda dipake blm.
        }
        else{
            printf("\nID Baju: ");
            fflush(stdin);
            gets(prod[count].id);
        }
        printf("Merk baju: ");gets(prod[count].name);
        printf("Stok baju: ");scanf("%d",&prod[count].quantity);
        printf("Harga : ");scanf("%f",&prod[count].price);
        ++count; // increment untuk menghitung posisi produk dan berapa jumlah array.

	writefile(); // save file.
	menu();
}

int checkID(char id[]){ // ngecek id nya ada atau engga
	int i;
    count=readFile();
    readFile();
    for(i=0;i<count;i++){
        if(strcmp(id,prod[i].id)!=0){ //jika id dan id yg dicari tidak cocok.
            fclose(f);
        }
        return 1;		// return error.
    }
    fclose(f);
    menu();
    return 0; // return jika no error.
}

int IDChecker(int i, int j){
	count=readFile();
    printf("Product ID: ");
    fflush(stdin);
	gets(prod[count].id);
    if (strcmp(prod[i].id,prod[j].id)==0){
        printf("ID number is already taken!");
        return IDChecker(i++,j--);
    }
}

void editProd(){
    system("cls");
	char id[10];
    int test;
    int i;
	int choice;
    printf("EDIT A PRODUCT!");
    printf("\nEnter the id of the product that you want to edit: ");
	fflush(stdin);
	gets(id);
	test=checkID(id);
    if (test == 0){
        printf("The id num %s is not found.", id);
    }else{
        readFile();
        {
            for(i=0;i<count;i++){
                if(strcmp(id,prod[i].id)!=0) // if the data is not empty
                    writefile();
                else{
                    printf("\n1. Update Nama Merk? ");
                    printf("\n2. Update Stok barang?");
                    printf("\n3. Update Harga barang?");
                    printf("\nEnter your choice:");
                    fflush(stdin);
                    scanf("%d", &choice);
                    switch (choice){
                    case 1:
                        printf("Enter new Name: ");
                        fflush(stdin);
                        gets(prod[i].name);
                        break;
                    case 2:
                        printf("Enter Quantity: ");
                        scanf("%d",&prod[i].quantity);
                        break;
                    case 3:
                        printf("Enter the new price: ");
                        scanf("%f",&prod[i].price);
                        break;
                    default:
                        printf("Invalid Selection");
                        break;
                    }
                writefile();
                }

            }
        }
        fclose(f);
        f = fopen("Inventory.txt", "r");
        readFile();{
            writefile();
        }
        fclose(f);
        printf("RECORD UPDATED");
        menu();
    }
}

void beliprod(){// function beli produk
    system("cls");
	int i,ch;
    char id[10];
    int z=false;
    count=readFile();
    printf("------------------------------------------------------------------------------------\n");
    printf("S.N.|    NAME     |   ID  |     QUANTITY      |    PRICE    | SALES |\n");
    printf("------------------------------------------------------------------------------------\n");
    for (i=0;i<count;i++){
        printf("%d     %-10s       %-8s     %-5d          %-6.2f      %.2lf  \n",i+1,prod[i].name,prod[i].id,prod[i].quantity,prod[i].price,prod[i].sales);
    }
	printf("\n\n Beli Barang ");
    printf("\nProduct ID: ");
    fflush(stdin);
	gets(id);
    for (i=0; i<count; i++){
        if (strcmp(id,prod[i].id)==0){ 	// jika id yang user cari dan id yg disave difile cocok.
        	z=true;
            printf("\nItem found! Containing: \n");//...lalu munculkan yg cocok
            printf("\nProduct name: %s",prod[i].name);
            printf("\nPrice: Rp. %.2lf\n\n",prod[i].price);
            printf("Enter the quantity you want to buy  : ");
            fflush(stdin);
			scanf("%d",&quant);
            if (quant>prod[i].quantity){		// jika quantitas<quantitas user
                puts("\nInsufficient Quantity\nPlease Restock.\n ");
                break;
				}
            float tempSales = prod[i].sales;  // akan di eksekusi jika quantity > quantitas users.
            prod[i].numSold += quant;
            prod[i].quantity -= quant;
            prod[i].sales = quant*prod[i].price;
            prod[i].sales += tempSales;
			}

	}
    if(z==false){	//if the product id is not available.
        printf("Cant find the product id: %s.",id);
    }
	writefile();
	printf("barang terbeli!, pencet enter untuk kembali ke menu");
    while (1) {
        if ( kbhit() ) {
            ch = getch();
            if (ch == 13){
                menu();}}}
}

void menu(){//tiara
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
        arrowhere(2,position); printf(" 2. Tambah Stok Baju");//JADINYA ADMIN ASW INI BUKAN PELANGGAN BANGSATTTTT JADI BINGGUNG KAN KONSEPNYA GMN
        gotoxy(47,16);
        arrowhere(3,position); printf(" 3. Beli Barang");
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
	    merkbaju();
            break;
        case 2:
            menu2();
            break;
        case 3:
            beliprod();
            break;
        case 4:
            nota();
            break;
        case 5:
            main();
            break;

    }
}

void nota(){ //Cornelius Ardhani Yoga Pratama - 672022204
    int i,kembalian,uang;
    float total_pembelian;
    system("cls");
    printf("------------------------------------------------------------------------------------\n");
    printf("    NAME     |     QUANTITY      |    PRICE    | SUBTOTAL |\n");
    printf("------------------------------------------------------------------------------------\n");
    for (i=0; i<count; i++){
        total_pembelian+=prod[i].sales;
        printf("       %-8s     %-5d             %-6.2f   =     Rp. %.2f\n",prod[i].name,quant,prod[i].price,prod[i].sales);
    }
    printf("\n\nTotal pembelian Anda adalah: Rp. %.2f",total_pembelian);
    bayar:
        printf("\n\n\tMasukan uang anda :Rp. ");
        scanf("%d",&uang);
    if(uang < total_pembelian) //jika uang nya tidak mencukupi maka akan print angka dibawah
    {
        printf("\tMaaf uang anda kurang, Silahkan ulangi transaksi!!!\n");
        printf("\tSilahkan masukan kembali uang anda!!!");
        goto bayar;
    }
    //untuk menampilkan uang kembalian
    kembalian = uang - total_pembelian;
    printf("\tKembalian anda : Rp. %d\n\n",kembalian);
    printf("\tTerimakasih Sudah Bertransaksi Di Toko Kami\n\n");
    system("pause");
    menu();
}

void ex(){//tiara
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
    gotoxy(20,32);printf("Kevin Nahot                      672022322");
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

void welcome(){//tiara
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

void cover(){//tiara
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

void cover1(){//tiara
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

void arrowhere (int realposition,int arrowposition){//tiara
    if(realposition == arrowposition){
        printf("-->");
    }else{
        printf("   ");
    }
}

